#ifndef COMPILER_H
#define COMPILER_H

#include <Riva/Memory.h>
#include <Std/Function.h>

#include "assembler.h"
#include "bitset.h"
#include "integertable.h"
#include "stringtable.h"

#include <setjmp.h>

struct compiler_t {
	struct function_t {
		struct loop_t {
			struct trap_t {
				trap_t *Prev;
				uint32_t Index;
				bitset_t *Free0, *Free1;
				label_t *Start, *Start0, *Failure, *Continue;
			};

			struct expression_t {
				expression_t *Prev;
				bitset_t *Temps;
			};

			struct assignment_t {
				assignment_t *Prev;
				operand_t *Self;
			};

			loop_t *Prev;
			int32_t Index;
			uint32_t NoOfLocals;
			bitset_t *Free0, *Free1;
			label_t *Start, *Start0, *Exit, *Receiver;
			trap_t *Trap;
			expression_t *Expression;
			operand_t *Self;
		};

		loop_t *Loop;
		function_t *Up;
		frame_t Frame;
		integertable_t LoopTable;
		integertable_t VarTable;

		function_t();
		uint32_t lookup(loop_t *Loop);
	};

	struct scope_t {
		enum type_t {SC_GLOBAL, SC_LOCAL} Type;
		scope_t *Up;
		function_t::loop_t *Loop;
		function_t *Function;
		stringtable_t NameTable;
		scope_t(type_t Type, scope_t *Up = 0) {
			this->Type = Type;
			this->Up = Up;
		};
	};

	function_t *Function;
	scope_t *Scope, *Global;

	compiler_t() {
		Scope = Global = new scope_t(scope_t::SC_GLOBAL);
		Function = 0;
	};

	operand_t *new_parameter(bool Indirect);
	operand_t *new_local(bool Reference = false);
	uint32_t new_temporary(uint32_t Count = 1);

	label_t *push_loop(label_t *Start, label_t *Exit);
	void pop_loop();

	void push_expression();
	void pop_expression();

	label_t *push_trap(label_t *Start, label_t *Failure);
	uint32_t use_trap();
	uint32_t use_trap(label_t *Start, label_t *Failure);
	void pop_trap();
	void back_trap(label_t *Start);
	uint32_t trap() {return Function->Loop->Trap->Index;};

	frame_t *frame() {return &Function->Frame;};

	void push_function();
	frame_t *pop_function();

	void push_scope();
	void push_scope(scope_t::type_t Type);
	void pop_scope();
	void declare(const char *Name, operand_t *Operand);
	operand_t *lookup(int LineNo, const char *Name);

	struct {
		jmp_buf Handler;
		const char *Message;
		int LineNo;
	} Error;

	__attribute__ ((noreturn)) void raise_error(int LineNo, const char *Format, ...);
};

struct expr_t {
	expr_t *Next;
	int LineNo;
	virtual void print(int Indent) {};
	virtual operand_t *compile(compiler_t *Compiler, label_t *Start, label_t *Success) {return 0;};
	virtual operand_t *constant(compiler_t *Compiler) {return 0;};
};

struct assign_expr_t : expr_t {
	expr_t *Left, *Right;
	assign_expr_t(int LineNo, expr_t *Left, expr_t *Right) {
		this->LineNo = LineNo;
		this->Left = Left;
		this->Right = Right;
	};
	void print(int Indent);
	operand_t *compile(compiler_t *Compiler, label_t *Start, label_t *Success);
};

struct ref_assign_expr_t : expr_t {
	expr_t *Left, *Right;
	ref_assign_expr_t(int LineNo, expr_t *Left, expr_t *Right) {
		this->LineNo = LineNo;
		this->Left = Left;
		this->Right = Right;
	};
	void print(int Indent);
	operand_t *compile(compiler_t *Compiler, label_t *Start, label_t *Success);
};

struct invoke_expr_t : expr_t {
	expr_t *Function, *Args;
	invoke_expr_t(int LineNo, expr_t *Function, expr_t *Args) {
		this->LineNo = LineNo;
		this->Function = Function;
		this->Args = Args;
	};
	void print(int Indent);
	operand_t *compile(compiler_t *Compiler, label_t *Start, label_t *Success);
};

struct const_expr_t : expr_t {
	operand_t *Operand;
	const_expr_t(int LineNo, void *Value) {
		this->LineNo = LineNo;
		Operand = new operand_t;
		Operand->Type = operand_t::CNST;
		Operand->Value = (Std$Object_t *)Value;
	};
	void print(int Indent);
	operand_t *compile(compiler_t *Compiler, label_t *Start, label_t *Success);
	operand_t *constant(compiler_t *Compiler) {return Operand;};
};

struct func_expr_t : expr_t {
	struct parameter_t {
		parameter_t *Next;
		int LineNo;
		const char *Name;
		bool Reference;
	};
	operand_t *Constant;
	parameter_t *Parameters;
	expr_t *Body;
	func_expr_t(int LineNo, parameter_t *Parameters, expr_t *Body) {
		this->LineNo = LineNo;
		this->Parameters = Parameters;
		this->Body = Body;
	};
	void print(int Indent);
	operand_t *compile(compiler_t *Compiler, label_t *Start, label_t *Success);
	operand_t *constant(compiler_t *Compiler) {
		Constant = new operand_t;
		Constant->Type = operand_t::CNST;
		closure_t *Closure = new closure_t;
		Constant->Value = (Std$Object_t *)Closure;
		return Constant;
	};
};

struct ident_expr_t : expr_t {
	const char *Name;
	ident_expr_t(int LineNo, const char *Name) {
		this->LineNo = LineNo;
		this->Name = Name;
	};
	void print(int Indent);
	operand_t *compile(compiler_t *Compiler, label_t *Start, label_t *Success);
};

struct qualident_expr_t : expr_t {
	struct name_t {
		name_t *Next;
		const char *Ident;
	} *Names;
	qualident_expr_t(int LineNo, name_t *Names) {
		this->LineNo = LineNo;
		this->Names = Names;
	};
	void print(int Indent);
	operand_t *compile(compiler_t *Compiler, label_t *Start, label_t *Success);
	operand_t *constant(compiler_t *Compiler);
};

struct ret_expr_t : expr_t {
	expr_t *Value;
	ret_expr_t(int LineNo, expr_t *Value) {
		this->LineNo = LineNo;
		this->Value = Value;
	};
	void print(int Indent);
	operand_t *compile(compiler_t *Compiler, label_t *Start, label_t *Success);
};

struct susp_expr_t : expr_t {
	expr_t *Value;
	susp_expr_t(int LineNo, expr_t *Value) {
		this->LineNo = LineNo;
		this->Value = Value;
	};
	void print(int Indent);
	operand_t *compile(compiler_t *Compiler, label_t *Start, label_t *Success);
};

struct fail_expr_t : expr_t {
	fail_expr_t(int LineNo) {
		this->LineNo = LineNo;
	};
	void print(int Indent);
	operand_t *compile(compiler_t *Compiler, label_t *Start, label_t *Success);
};

struct back_expr_t : expr_t {
	back_expr_t(int LineNo) {
		this->LineNo = LineNo;
	};
	void print(int Indent);
	operand_t *compile(compiler_t *Compiler, label_t *Start, label_t *Success);
};

struct rep_expr_t : expr_t {
	expr_t *Body;
	rep_expr_t(int LineNo, expr_t *Body) {
		this->LineNo = LineNo;
		this->Body = Body;
	};
	void print(int Indent);
	operand_t *compile(compiler_t *Compiler, label_t *Start, label_t *Success);
};

struct exit_expr_t : expr_t {
	expr_t *Value;
	exit_expr_t(int LineNo, expr_t *Value) {
		this->LineNo = LineNo;
		this->Value = Value;
	};
	void print(int Indent);
	operand_t *compile(compiler_t *Compiler, label_t *Start, label_t *Success);
};

struct step_expr_t : expr_t {
	step_expr_t(int LineNo) {
		this->LineNo = LineNo;
	};
	void print(int Indent);
	operand_t *compile(compiler_t *Compiler, label_t *Start, label_t *Success);
};

struct every_expr_t : expr_t {
	expr_t *Condition, *Body;
	every_expr_t(int LineNo, expr_t *Condition, expr_t *Body) {
		this->LineNo = LineNo;
		this->Condition = Condition;
		this->Body = Body;
	};
	void print(int Indent);
	operand_t *compile(compiler_t *Compiler, label_t *Start, label_t *Success);
};

struct all_expr_t : expr_t {
	expr_t *Value;
	all_expr_t(int LineNo, expr_t *Value) {
		this->LineNo = LineNo;
		this->Value = Value;
	};
	void print(int Indent);
	operand_t *compile(compiler_t *Compiler, label_t *Start, label_t *Success);
};

struct send_expr_t : expr_t {
	expr_t *Value;
	send_expr_t(int LineNo, expr_t *Value) {
		this->LineNo = LineNo;
		this->Value = Value;
	};
	void print(int Indent);
	operand_t *compile(compiler_t *Compiler, label_t *Start, label_t *Success);
};

struct self_expr_t : expr_t {
	self_expr_t(int LineNo) {
		this->LineNo = LineNo;
	};
	void print(int Indent);
	operand_t *compile(compiler_t *Compiler, label_t *Start, label_t *Success);
};

struct sequence_expr_t : expr_t {
	expr_t *Exprs;
	sequence_expr_t(int LineNo, expr_t *Exprs) {
		this->LineNo = LineNo;
		this->Exprs = Exprs;
	};
	void print(int Indent);
	operand_t *compile(compiler_t *Compiler, label_t *Start, label_t *Success);
};

struct typeof_expr_t : expr_t {
	expr_t *Expr;
	typeof_expr_t(int LineNo, expr_t *Expr) {
		this->LineNo = LineNo;
		this->Expr = Expr;
	};
	void print(int Indent);
	operand_t *compile(compiler_t *Compiler, label_t *Start, label_t *Success);
};

struct limit_expr_t : expr_t {
	expr_t *Limit, *Expr;
	limit_expr_t(int LineNo, expr_t *Limit, expr_t *Expr) {
		this->LineNo = LineNo;
		this->Limit = Limit;
		this->Expr = Expr;
	};
	void print(int Indent);
	operand_t *compile(compiler_t *Compiler, label_t *Start, label_t *Success);
};

struct infinite_expr_t : expr_t {
	expr_t *Expr;
	infinite_expr_t(int LineNo, expr_t *Expr) {
		this->LineNo = LineNo;
		this->Expr = Expr;
	};
	void print(int Indent);
	operand_t *compile(compiler_t *Compiler, label_t *Start, label_t *Success);
};

struct parallel_expr_t : expr_t {
	expr_t *Left, *Right;
	parallel_expr_t(int LineNo, expr_t *Left, expr_t *Right) {
		this->LineNo = LineNo;
		this->Left = Left;
		this->Right = Right;
	};
	void print(int Indent);
	operand_t *compile(compiler_t *Compiler, label_t *Start, label_t *Success);
};

struct left_expr_t : expr_t {
	expr_t *Left, *Right;
	left_expr_t(int LineNo, expr_t *Left, expr_t *Right) {
		this->LineNo = LineNo;
		this->Left = Left;
		this->Right = Right;
	};
	void print(int Indent);
	operand_t *compile(compiler_t *Compiler, label_t *Start, label_t *Success);
};

struct right_expr_t : expr_t {
	expr_t *Left, *Right;
	right_expr_t(int LineNo, expr_t *Left, expr_t *Right) {
		this->LineNo = LineNo;
		this->Left = Left;
		this->Right = Right;
	};
	void print(int Indent);
	operand_t *compile(compiler_t *Compiler, label_t *Start, label_t *Success);
};

struct cond_expr_t : expr_t {
	expr_t *Condition, *Success, *Failure;
	cond_expr_t(int LineNo, expr_t *Condition, expr_t *Success, expr_t *Failure) {
		this->LineNo = LineNo;
		this->Condition = Condition;
		this->Success = Success;
		this->Failure = Failure;
	};
	void print(int Indent);
	operand_t *compile(compiler_t *Compiler, label_t *Start, label_t *Success);
};

struct comp_expr_t : expr_t {
	int Eq;
	expr_t *Left, *Right;
	comp_expr_t(int LineNo, int Eq, expr_t *Left, expr_t *Right) {
		this->LineNo = LineNo;
		this->Eq = Eq;
		this->Left = Left;
		this->Right = Right;
	};
	void print(int Indent);
	operand_t *compile(compiler_t *Compiler, label_t *Start, label_t *Success);
};

struct when_expr_t : expr_t {
	struct case_t {
		struct range_t {
			range_t *Next;
			int LineNo;
			expr_t *Min, *Max;
			range_t(int LineNo, expr_t *Min, expr_t *Max) {
				this->LineNo = LineNo;
				this->Min = Min;
				this->Max = Max;
			};
		};
		case_t *Next;
		int LineNo;
		range_t *Ranges;
		expr_t *Body;
		case_t(int LineNo, range_t *Ranges, expr_t *Body) {
			this->LineNo = LineNo;
			this->Ranges = Ranges;
			this->Body = Body;
		};
	};
	expr_t *Condition;
	case_t *Cases;
	expr_t *Default;
	void print(int Indent);
	operand_t *compile(compiler_t *Compiler, label_t *Start, label_t *Success);
};

struct block_expr_t : expr_t {
	struct localvar_t {
		localvar_t *Next;
		int LineNo;
		const char *Name;
		bool Reference;
	};
	struct localdef_t {
		localdef_t *Next;
		int LineNo;
		const char *Name;
		expr_t *Value;
	};
	struct receiver_t {
		const char *Var;
		expr_t *Body;
	};
	localvar_t *Vars;
	localdef_t *Defs;
	expr_t *Body, *Final;
	receiver_t Receiver;
	void print(int Indent);
	operand_t *compile(compiler_t *Compiler, label_t *Start, label_t *Success);
};

struct module_expr_t : expr_t {
	struct globalimp_t {
		struct uselist_t {
			uselist_t *Next;
			int LineNo;
			const char *Name;
		};
		globalimp_t *Next;
		int LineNo;
		struct path_t {
			path_t *Next;
			const char *Part;
		} *Path;
		const char *Alias;
		bool Relative;
		uselist_t *Uses;
		bool Exported;
	};
	struct globalvar_t {
		globalvar_t *Next;
		int LineNo;
		const char *Name;
		bool Exported;
	};
	struct globaldef_t {
		globaldef_t *Next;
		int LineNo;
		const char *Name;
		bool Exported;
		expr_t *Value;
	};

	Sys$Module_t *Module;
	globalimp_t *Imps;
	globaldef_t *Defs;
	globalvar_t *Vars;
	expr_t *Body;
	const char *Name;

	void print(int Indent);
	operand_t *compile(compiler_t *Compiler, label_t *Start, label_t *Success);
	void compile(compiler_t *Compiler);
};

struct command_expr_t : expr_t {
	struct globalimp_t {
		struct uselist_t {
			uselist_t *Next;
			int LineNo;
			const char *Name;
		};
		globalimp_t *Next;
		int LineNo;
		struct path_t {
			path_t *Next;
			const char *Part;
		} *Path;
		const char *Alias;
		bool Relative;
		uselist_t *Uses;
	};
	struct globalvar_t {
		globalvar_t *Next;
		int LineNo;
		const char *Name;
	};
	struct globaldef_t {
		globaldef_t *Next;
		int LineNo;
		const char *Name;
		expr_t *Value;
	};

	globalimp_t *Imps;
	globaldef_t *Defs;
	globalvar_t *Vars;
	expr_t *Body;

	void print(int Indent);
	int compile(compiler_t *Compiler, Std$Function_result *Result);
};

#endif
