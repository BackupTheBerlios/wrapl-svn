#include "compiler.h"
#include "missing.h"

#include <Std.h>

#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>

void compiler_t::raise_error(int LineNo, const char *Format, ...) {
	va_list Args;
	va_start(Args, Format);
	vasprintf((char **)&Error.Message, Format, Args);
	va_end(Args);
	Error.LineNo = LineNo;
	longjmp(Error.Handler, 1);
};

compiler_t::function_t::function_t() {
	Loop = new loop_t;
	Loop->Free0 = new bitset_t();
	Loop->Free1 = new bitset_t();
	Loop->Free0->reserve(0);
	integertable_put(LoopTable, (uint32_t)Loop, (void *)0);
	Expression = new expression_t;
	Expression->Temps = new bitset_t();
	Frame.NoOfScopes = 1;
};

operand_t *compiler_t::function_t::new_parameter(bool Indirect) {
	++Frame.NoOfParams;
	operand_t *Operand = new operand_t;
	Operand->Type = Indirect ? operand_t::LREF : operand_t::LVAR;
	Operand->Index = Frame.NoOfLocals++;
	Operand->Loop = 0;
	return Operand;
};

operand_t *compiler_t::function_t::new_local(bool Reference) {
	operand_t *Operand = new operand_t;
	Operand->Type = Reference ? operand_t::LREF : operand_t::LVAR;
	if (Loop->Index == -1) {
		uint32_t Index = Loop->Free0->allocate(Loop->Free1);
		for (loop_t *Prev = Loop->Prev; Prev; Prev = Prev->Prev) Prev->Free1->reserve(Index);
		Loop->Index = Index;
		if (Index >= Frame.NoOfScopes) Frame.NoOfScopes = Index + 1;
		integertable_put(LoopTable, (uint32_t)Loop, (void *)Index);
		Operand->Loop = Loop->Index;
		Operand->Index = Loop->NoOfLocals++;
	} else if (Loop->Index == 0) {
		Operand->Loop = 0;
		Operand->Index = Frame.NoOfLocals++;
	} else {
		Operand->Loop = Loop->Index;
		Operand->Index = Loop->NoOfLocals++;
	};
	return Operand;
};

uint32_t compiler_t::function_t::new_temporary(uint32_t Count) {
	return Expression->Temps->allocate(Count);
};

label_t *compiler_t::function_t::push_loop(label_t *Start, label_t *Exit) {
	loop_t *Loop = new loop_t;
	Loop->Index = -1;
	Loop->Free0 = new bitset_t(this->Loop->Free0);
	Loop->Free1 = new bitset_t();
	Loop->Start0 = Start;
	Loop->Trap = Trap;
	if (Block) Loop->Receiver = Block->Receiver;
	Start->link(Loop->Start = new label_t);
	Loop->Exit = Exit;
	Loop->Prev = this->Loop;
	this->Loop = Loop;
	return Loop->Start;
};

void compiler_t::function_t::pop_loop() {
	if (Loop->NoOfLocals) Loop->Start0->scope(Loop->Index, Loop->NoOfLocals);
	Loop = Loop->Prev;
};

void compiler_t::function_t::push_expression() {
	expression_t *Expression = new expression_t;
	if (this->Expression) {
		Expression->Temps = new bitset_t(this->Expression->Temps);
		Expression->Prev = this->Expression;
	} else {
		Expression->Temps = new bitset_t();
	};
	this->Expression = Expression;
};

void compiler_t::function_t::pop_expression() {
	uint32_t NoOfTemps = Expression->Temps->size();
	if (NoOfTemps > Frame.NoOfTemps) Frame.NoOfTemps = NoOfTemps;
	Expression = Expression->Prev;
};

void compiler_t::function_t::push_assignment(operand_t *Self) {
	assignment_t *Assignment = new assignment_t;
	Assignment->Self = Self;
	Assignment->Prev = this->Assignment;
	this->Assignment = Assignment;
};

void compiler_t::function_t::pop_assignment() {
	Assignment = Assignment->Prev;
};

void compiler_t::function_t::push_block(label_t *Receiver) {
	block_t *Block = new block_t;
	Block->Receiver = Receiver;
	Block->Prev = this->Block;
	this->Block = Block;
};

void compiler_t::function_t::pop_block() {
	Block = Block->Prev;
};

label_t *compiler_t::function_t::push_trap(label_t *Start, label_t *Failure) {
	function_t::trap_t *Trap = new function_t::trap_t;
	if (this->Trap) {
		Trap->Free0 = new bitset_t(this->Trap->Free0);
	} else {
		Trap->Free0 = new bitset_t();
	};
	Trap->Free1 = new bitset_t();
	Trap->Continue = Trap->Failure = Failure;

	(Trap->Start0 = Start)->link(Trap->Start = new label_t);
	Trap->Index = 0xFFFFFFFF;
	Trap->Prev = this->Trap;
	this->Trap = Trap;
	return Trap->Start;
};

uint32_t compiler_t::function_t::use_trap() {
	if (Trap->Index == 0xFFFFFFFF) {
		uint32_t Index = Trap->Free0->allocate(Trap->Free1);
		for (trap_t *Prev = Trap->Prev; Prev; Prev = Prev->Prev) Prev->Free1->reserve(Index);
		Trap->Index = Index;
		if (Index >= Frame.NoOfTraps) Frame.NoOfTraps = Index + 1;
		Trap->Start0->zero(Index, Trap->Failure);
	};
	return Trap->Index;
};

uint32_t compiler_t::function_t::use_trap(label_t *Start, label_t *Failure) {
	if (Trap->Index == 0xFFFFFFFF) {
		uint32_t Index = Trap->Free0->allocate(Trap->Free1);
		for (trap_t *Prev = Trap->Prev; Prev; Prev = Prev->Prev) Prev->Free1->reserve(Index);
		Trap->Index = Index;
		if (Index >= Frame.NoOfTraps) Frame.NoOfTraps = Index + 1;
		Trap->Start0->zero(Index, Failure);
	} else {
		Start->trap(Trap->Index, Failure);
	};
	return Trap->Index;
};

label_t *compiler_t::function_t::seq_trap(label_t *New) {
	label_t *Old = Trap->Continue;
	Trap->Continue = New;
	return Old;
};

void compiler_t::function_t::pop_trap() {
	Trap = Trap->Prev;
};

uint32_t compiler_t::function_t::lookup(loop_t *Loop) {
	int32_t Index = (int32_t)integertable_get(LoopTable, (long)Loop);
	if (Index == -1) {
		Index = -1 - (++Frame.NoOfUpScopes);
		integertable_put(LoopTable, (long)Loop, (void *)Index);
		upscope_t *UpScope = new(upscope_t);
		UpScope->Index = Up->lookup(Loop);
		UpScope->Next = Frame.UpScopes;
		Frame.UpScopes = UpScope;
	};
	return Index;
};


void compiler_t::push_function() {
	function_t *Function = new function_t();
	Function->Up = this->Function;
	this->Function = Function;
};

frame_t *compiler_t::pop_function() {
	frame_t *Frame = &Function->Frame;
	uint32_t NoOfTemps = Function->Expression->Temps->size();
	if (NoOfTemps > Frame->NoOfTemps) Frame->NoOfTemps = NoOfTemps;
	Function = Function->Up;
	return Frame;
};

void compiler_t::push_scope() {
	if (this->Scope->Type == scope_t::SC_LOCAL) {
		scope_t *Scope = new scope_t(scope_t::SC_LOCAL, this->Scope);
		Scope->Loop = Function->Loop;
		Scope->Function = Function;
		this->Scope = Scope;
	} else {
		scope_t *Scope = new scope_t(scope_t::SC_GLOBAL, this->Scope);
		this->Scope = Scope;
	};
};

void compiler_t::push_scope(scope_t::type_t Type) {
	if (Type == scope_t::SC_LOCAL) {
		scope_t *Scope = new scope_t(scope_t::SC_LOCAL, this->Scope);
		Scope->Loop = Function->Loop;
		Scope->Function = Function;
		this->Scope = Scope;
	} else {
		scope_t *Scope = new scope_t(scope_t::SC_GLOBAL, this->Scope);
		this->Scope = Scope;
	};
};

void compiler_t::pop_scope() {
	Scope = Scope->Up;
};

void compiler_t::declare(const char *Name, operand_t *Operand) {
	stringtable_put(Scope->NameTable, Name, Operand);
};

operand_t *compiler_t::lookup(int LineNo, const char *Name) {
	for (scope_t *Scope = this->Scope; Scope; Scope = Scope->Up) {
		operand_t *Operand = (operand_t *)stringtable_get(Scope->NameTable, Name);
		if (Operand) {
			switch (Scope->Type) {
			case scope_t::SC_GLOBAL: {
				if (Operand->Type == operand_t::FUTR) {
					Sys$Module_t *Module = Sys$Module$load(0, Operand->Module);
					if (Module == 0) raise_error(LineNo, "Error: module not found %s\n", Operand->Module);
					if (Operand->Import) {
						if (Sys$Module$import(Module, Operand->Import, (int *)&Operand->Type, (void **)&Operand->Value) == 0) {
							raise_error(LineNo, "Error: import not found %s.%s\n", Operand->Module, Operand->Import);
						};
					} else {
						Operand->Type = operand_t::CNST;
						Operand->Value = (Std$Object_t *)Module;
					};
				};
				return Operand;
			};
			case scope_t::SC_LOCAL: {
				if (Scope->Function == Function) return Operand;
				operand_t *Operand2 = (operand_t *)integertable_get(Function->VarTable, (uint32_t)Operand);
				if (Operand2 != (operand_t *)0xFFFFFFFF) return Operand2;
				Operand2 = new operand_t;
				Operand2->Type = Operand->Type;
				Operand2->Index = Operand->Index;
				Operand2->Loop = Function->lookup(Scope->Loop);
				integertable_put(Function->VarTable, (uint32_t)Operand, Operand2);
				return Operand2;
			};
			};
		};
	};
	/*switch (this->Scope->Type) {
	case scope_t::SC_GLOBAL: {
		operand_t *Operand = new operand_t;
		Operand->Type = operand_t::GVAR;
		Std$Object_t **Address = new Std$Object_t *;
		Address[0] = Std$Object$Nil;
		Operand->Address = Address;
		declare(Name, Operand);
		return Operand;
	};
	case scope_t::SC_LOCAL: {
		operand_t *Operand = new_local();
		declare(Name, Operand);
		return Operand;
	};
	};*/
	raise_error(LineNo, "Error: identifier %s not declared", Name);
};

void assign_expr_t::print(int Indent) {
	Left->print(Indent);
	printf(" <- ");
	Right->print(Indent);
};

void ref_assign_expr_t::print(int Indent) {
	Left->print(Indent);
	printf(" <<= ");
	Right->print(Indent);
};

void invoke_expr_t::print(int Indent) {
	Function->print(Indent);
	printf("(");
	if (Args) {
		Args->print(Indent);
		for (expr_t *Arg = Args->Next; Arg; Arg = Arg->Next) {
			printf(", ");
			Arg->print(Indent);
		};
	};
	printf(")");
};

void func_expr_t::print(int Indent) {
	printf("<");
	if (Parameters) {
		printf("%s", Parameters->Name);
		for (parameter_t *Param = Parameters->Next; Param; Param = Param->Next) {
			printf(", %s", Param->Name);
		};
	};
	printf("> ");
	Body->print(Indent);
};

void ident_expr_t::print(int Indent) {
	printf("%s", Name);
};

void qualident_expr_t::print(int Indent) {
	printf("%s", Names->Ident);
	for (qualident_expr_t::name_t *Name = Names->Next; Name; Name = Name->Next) printf(".%s", Name->Ident);
};

SYMBOL($AT, "@");

void const_expr_t::print(int Indent) {
	Std$Function_result Result;
	if (Std$Function$call((Std$Object_t *)$AT, 2, &Result, Operand->Value, 0, Std$String$T, 0) < FAILURE) {
		printf("%s", Std$String$flatten((Std$String_t *)Result.Val));
	} else {
		printf("#%x", Operand->Value);
	};
};

void ret_expr_t::print(int Indent) {
	printf("RET ");
	Value->print(Indent);
};

void susp_expr_t::print(int Indent) {
	printf("SUSP ");
	Value->print(Indent);
};

void fail_expr_t::print(int Indent) {
	printf("FAIL");
};

void back_expr_t::print(int Indent) {
	printf("BACK");
};

void rep_expr_t::print(int Indent) {
	printf("REP ");
	Body->print(Indent);
};

void exit_expr_t::print(int Indent) {
	printf("EXIT ");
	Value->print(Indent);
};

void step_expr_t::print(int Indent) {
	printf("STEP");
};

void every_expr_t::print(int Indent) {
	printf("EVERY ");
	Condition->print(Indent);
	printf(" DO ");
	Body->print(Indent);
};

void send_expr_t::print(int Indent) {
	printf("SEND ");
	Value->print(Indent);
};

void self_expr_t::print(int Indent) {
	printf("$");
};

void sequence_expr_t::print(int Indent) {
	Exprs->print(Indent);
	for (expr_t *Expr = Exprs->Next; Expr; Expr = Expr->Next) {
		printf(" | ");
		Expr->print(Indent);
	};
};

void typeof_expr_t::print(int Indent) {
	printf("?");
	Expr->print(Indent);
};

void infinite_expr_t::print(int Indent) {
	printf("|");
	Expr->print(Indent);
};

void parallel_expr_t::print(int Indent) {
	Left->print(Indent);
	printf(" ! ");
	Right->print(Indent);
};

void left_expr_t::print(int Indent) {
	Left->print(Indent);
	printf(" \\ ");
	Right->print(Indent);
};

void right_expr_t::print(int Indent) {
	Left->print(Indent);
	printf(" & ");
	Right->print(Indent);
};

void cond_expr_t::print(int Indent) {
	Condition->print(Indent);
	if (Success) {
		printf(" => ");
		Success->print(Indent);
	};
	if (Failure) {
		printf(" // ");
		Failure->print(Indent);
	};
};

void comp_expr_t::print(int Indent) {
	Left->print(Indent);
	printf(Eq ? " == " : " ~== ");
	Right->print(Indent);
};

void when_expr_t::print(int Indent) {
	printf("WHEN ");
	Condition->print(Indent);
	printf("\n");
	for (case_t *Case = Cases; Case; Case = Case->Next) {
		for (int I = Indent; I--;) printf("    ");
		printf("IS ");
		case_t::range_t *Range = Case->Ranges;
		Range->Min->print(Indent);
		if (Range->Max) {
			printf(" .. ");
			Range->Max->print(Indent);
		};
		for (Range = Range->Next; Range; Range = Range->Next) {
			printf(", ");
			Range->Min->print(Indent);
			if (Range->Max) {
				printf(" .. ");
				Range->Max->print(Indent);
			};
		};
		printf(" DO ");
		Case->Body->print(Indent);
		printf("\n");
	};
	printf("DO ");
	Default->print(Indent);
};

void block_expr_t::print(int Indent) {
	if (Vars || Body || Receiver.Body) {
		printf("(\n");
		++Indent;
		for (localvar_t *Var = Vars; Var; Var = Var->Next) {
			for (int I = Indent; I--;) printf("    ");
			printf(Var->Name);
			printf(";\n");
		};
		for (expr_t *Expr = Body; Expr; Expr = Expr->Next) {
			for (int I = Indent; I--;) printf("    ");
			Expr->print(Indent);
			printf(";\n");
		};
		if (Receiver.Body) {
			for (int I = Indent; I--;) printf("    ");
			printf("RECV %s DO ", Receiver.Var);
			Receiver.Body->print(Indent);
			printf(";\n");
		};
		if (Final) {
			for (int I = Indent; I--;) printf("    ");
			Final->print(Indent);
			printf(";\n");
		};
		--Indent;
		for (int I = Indent; I--;) printf("    ");
		printf(")");
	} else if (Final) {
		printf("(");
		Final->print(Indent);
		printf(")");
	} else {
		printf("()");
	};
};

void module_expr_t::print(int Indent) {
	printf("MOD %s;\n", Name);
	printf("\n");
	if (Imps) {
		for (globalimp_t *Imp = Imps; Imp; Imp = Imp->Next) {
			printf("IMP ");
			if (Imp->Relative) printf(".");
			printf("%s", Imp->Path->Part);
			for (globalimp_t::path_t *Path = Imp->Path->Next; Path; Path = Path->Next) printf(".%s", Path->Part);
			printf(" AS %s", Imp->Alias);
			if (Imp->Uses) {
				printf(" USE %s", Imp->Uses->Name);
				for (globalimp_t::uselist_t *Use = Imp->Uses->Next; Use; Use = Use->Next) printf(", %s", Use->Name);
			};
			printf(";\n");
		};
		printf("\n");
	};
	if (Defs) {
		for (globaldef_t *Def = Defs; Def; Def = Def->Next) {
			printf("DEF %s%s <- ", Def->Name, Def->Exported ? "!" : "");
			Def->Value->print(0);
			printf(";\n");
		};
		printf("\n");
	};
	if (Vars) {
		for (globalvar_t *Var = Vars; Var; Var = Var->Next) {
			printf("VAR %s%s;\n", Var->Name, Var->Exported ? "!" : "");
		};
		printf("\n");
	};
	if (Body) {
		for (expr_t *Expr = Body; Expr; Expr = Expr->Next) {
			Expr->print(0);
			printf(";\n");
		};
		printf("\n");
	};
	printf("END %s.\n", Name);
};

void command_expr_t::print(int Indent) {
	if (Imps) {
		for (globalimp_t *Imp = Imps; Imp; Imp = Imp->Next) {
			printf("IMP ");
			if (Imp->Relative) printf(".");
			printf("%s", Imp->Path->Part);
			for (globalimp_t::path_t *Path = Imp->Path->Next; Path; Path = Path->Next) printf(".%s", Path->Part);
			printf(" AS %s", Imp->Alias);
			if (Imp->Uses) {
				printf(" USE %s", Imp->Uses->Name);
				for (globalimp_t::uselist_t *Use = Imp->Uses->Next; Use; Use = Use->Next) printf(", %s", Use->Name);
			};
			printf(";\n");
		};
	};
	if (Defs) {
		for (globaldef_t *Def = Defs; Def; Def = Def->Next) {
			printf("DEF %s <- ", Def->Name);
			Def->Value->print(0);
			printf(";\n");
		};
	};
	if (Vars) {
		for (globalvar_t *Var = Vars; Var; Var = Var->Next) {
			printf("VAR %s;\n", Var->Name);
		};
	};
	if (Body) {
		for (expr_t *Expr = Body; Expr; Expr = Expr->Next) {
			Expr->print(0);
			printf(";\n");
		};
	};
};

operand_t *assign_expr_t::compile(compiler_t *Compiler, label_t *Start, label_t *Success) {
	label_t *Label0 = new label_t;
	operand_t *Dest = Left->compile(Compiler, Start, Label0);
	if (Dest == Register) {
		label_t *Label1 = new label_t;
		operand_t *Self = new operand_t;
		Self->Type = operand_t::LREF;
		Self->Index = Compiler->new_temporary();
		Self->Loop = -1;
		Label0->store_ref(Self);
		Label0->link(Label1);
		Label0 = Label1;
		Dest = Self;
	};
	Compiler->push_assignment(Dest);
		label_t *Label1 = new label_t;
		operand_t *Src = Right->compile(Compiler, Label0, Label1);
		if (Src->Type == operand_t::CNST) {
			Label1->store_con(Dest, Src->Value);
		} else {
			Label1->load(Src);
			Label1->store_val(Dest);
		};
		Label1->link(Success);
	Compiler->pop_assignment();
	return Register;
};

operand_t *ref_assign_expr_t::compile(compiler_t *Compiler, label_t *Start, label_t *Success) {
	label_t *Label0 = new label_t;
	operand_t *Dest = Left->compile(Compiler, Start, Label0);
	if (Dest->Type != operand_t::LREF) {
		Compiler->raise_error(LineNo, "Error: can only assign addresses to reference variables");
	};
	label_t *Label1 = new label_t;
	Label1->load(Right->compile(Compiler, Label0, Label1));
	Label1->store_ref(Dest);
	Label1->link(Success);
	return Register;
};

operand_t *invoke_expr_t::compile(compiler_t *Compiler, label_t *Start, label_t *Success) {
	label_t *Label0 = new label_t;
	operand_t *FunctionOperand = Function->compile(Compiler, Start, Label0);
	//if ((FunctionOperand->Type == operand_t::CNST) && (FunctionOperand->Value->Type == Std$Integer$SmallT)) {
	//	printf("%s:%d: I'm not done yet!\n", __FILE__, __LINE__);
	//} else {
		label_t *Label2 = new label_t;
		uint32_t Count = 0;
		uint32_t ArgsArray = 0;
		uint32_t Trap = Compiler->use_trap();
		if (Args) {
			for (expr_t *Arg = Args; Arg; Arg = Arg->Next) ++Count;
			ArgsArray = Compiler->new_temporary(Count);
			if (FunctionOperand == Register) {
				FunctionOperand = new operand_t;
				FunctionOperand->Type = operand_t::LVAR;
				FunctionOperand->Index = Compiler->new_temporary();
				FunctionOperand->Loop = -1;
				label_t *Label1 = new label_t;
				Label0->store_val(FunctionOperand);
				Label0->link(Label1);
				Label0 = Label1;
			};
			uint32_t I = 0;
			for (expr_t *Arg = Args; Arg; Arg = Arg->Next) {
				uint32_t Index = ArgsArray + I++;
				label_t *Label1 = new label_t;
				operand_t *Value = Arg->compile(Compiler, Label0, Label1);
				Label1->store_arg(Index, Value);
				Label2->fixup_arg(Index, Value);
				Label0 = new label_t;
				Label1->link(Label0);
			};
		};
		Label0->link(Label2);
		Label2->load(FunctionOperand);
		Label2->invoke(Trap, ArgsArray, Count, Label2);
		Label2->link(Success);
	//};
	return Register;
};

operand_t *func_expr_t::compile(compiler_t *Compiler, label_t *Start, label_t *Success) {
	Compiler->push_function();
		Compiler->push_scope(compiler_t::scope_t::SC_LOCAL);
			for (func_expr_t::parameter_t *Parameter = Parameters; Parameter; Parameter = Parameter->Next) {
				operand_t *ParamOperand = Compiler->new_parameter(Parameter->Reference);
				Compiler->declare(Parameter->Name, ParamOperand);
			};
			label_t *Start0 = new label_t;
			label_t *Success0 = new label_t;
			label_t *Failure0 = new label_t;
			Success0->load(Body->compile(Compiler, Compiler->push_trap(Start0, Failure0), Success0));
			Success0->ret();
			Failure0->fail();
			Compiler->pop_trap();
		Compiler->pop_scope();
	frame_t *Frame = Compiler->pop_function();
	operand_t *Closure = Start0->assemble(Frame, Constant);
	Start->link(Success);
	return Closure;
};

operand_t *ident_expr_t::compile(compiler_t *Compiler, label_t *Start, label_t *Success) {
	Start->link(Success);
	return Compiler->lookup(LineNo, Name);
};

operand_t *qualident_expr_t::compile(compiler_t *Compiler, label_t *Start, label_t *Success) {
	const char *Ident = Names->Ident;
	operand_t *Operand = Compiler->lookup(LineNo, Ident);
	for (qualident_expr_t::name_t *Name = Names->Next; Name; Name = Name->Next) {
		if (Operand->Type != operand_t::CNST) Compiler->raise_error(LineNo, "Error: %s is not constant", Ident);
		if (Operand->Value->Type != Sys$Module$T) Compiler->raise_error(LineNo, "Error: %s is not a module", Ident);
		Sys$Module_t *Module = (Sys$Module_t *)Operand->Value;
		Operand = new operand_t;
		if (Sys$Module$import(Module, Name->Ident, (int *)&Operand->Type, (void **)&Operand->Value) == 0) {
			Compiler->raise_error(LineNo, "Error: import not found %s.%s", Ident, Name->Ident);
		};
		Ident = Name->Ident;
	};
	Start->link(Success);
	return Operand;
};

operand_t *qualident_expr_t::constant(compiler_t *Compiler) {
	const char *Ident = Names->Ident;
	operand_t *Operand = Compiler->lookup(LineNo, Ident);
	for (qualident_expr_t::name_t *Name = Names->Next; Name; Name = Name->Next) {
		if (Operand->Type != operand_t::CNST) return 0;
		if (Operand->Value->Type != Sys$Module$T) Compiler->raise_error(LineNo, "Error: %s is not a module", Ident);
		Sys$Module_t *Module = (Sys$Module_t *)Operand->Value;
		Operand = new operand_t;
		if (Sys$Module$import(Module, Name->Ident, (int *)&Operand->Type, (void **)&Operand->Value) == 0) {
			Compiler->raise_error(LineNo, "Error: import not found %s.%s", Ident, Name->Ident);
		};
		if (Operand->Type != operand_t::CNST) return 0;
		Ident = Name->Ident;
	};
	return Operand;
};

operand_t *const_expr_t::compile(compiler_t *Compiler, label_t *Start, label_t *Success) {
	Start->link(Success);
	return Operand;
};

operand_t *ret_expr_t::compile(compiler_t *Compiler, label_t *Start, label_t *Success) {
	label_t *Label0 = new label_t;
	label_t *Label1 = new label_t;
	Start = Compiler->push_trap(Start, Label1);
		Label0->load(Value->compile(Compiler, Start, Label0));
		Label0->ret();
		Label1->fail();
	Compiler->pop_trap();
	return Register;
};

operand_t *susp_expr_t::compile(compiler_t *Compiler, label_t *Start, label_t *Success) {
	label_t *Label0 = new label_t;
	Label0->load(Value->compile(Compiler, Start, Label0));
	Label0->susp();
	Label0->link(Success);
	return Register;
};

operand_t *fail_expr_t::compile(compiler_t *Compiler, label_t *Start, label_t *Success) {
	Start->fail();
	return Register;
};

operand_t *back_expr_t::compile(compiler_t *Compiler, label_t *Start, label_t *Success) {
	uint32_t Trap = Compiler->trap();
	if (Trap != 0xFFFFFFFF) {
		Start->back(Trap);
	} else {
		Start->link(Compiler->failure());
	};
	return Register;
};

operand_t *rep_expr_t::compile(compiler_t *Compiler, label_t *Start, label_t *Success) {
	label_t *Label0 = new label_t;
	Label0->link(Start);
	label_t *Label1 = Compiler->push_trap(Start, Label0);
		Label1 = Compiler->push_loop(Label1, Success);
			Body->compile(Compiler, Label1, Start);
		Compiler->pop_loop();
	Compiler->pop_trap();
	return Register;
};

operand_t *exit_expr_t::compile(compiler_t *Compiler, label_t *Start, label_t *Success) {
	compiler_t::function_t::loop_t *Loop = Compiler->loop();
	label_t *Receiver = Compiler->handler();
	if (Receiver != Loop->Receiver) {
		label_t *Label1 = new label_t;
		Start->recv(Loop->Receiver);
		Start->link(Label1);
		Start = Label1;
	};
	label_t *Label1 = new label_t;
	label_t *Label2 = new label_t;
	label_t *Label0 = Compiler->push_trap(Start, Label2);
		Label1->load(Value->compile(Compiler, Label0, Label1));
		Label1->link(Loop->Exit);
	Compiler->pop_trap();
	uint32_t Trap = Loop->Trap->Index;
	if (Trap != 0xFFFFFFFF) {
		Label2->back(Trap);
	} else {
		Label2->link(Loop->Trap->Failure);
	};
	return Register;
};

operand_t *step_expr_t::compile(compiler_t *Compiler, label_t *Start, label_t *Success) {
	compiler_t::function_t::loop_t *Loop = Compiler->loop();
	label_t *Receiver = Compiler->handler();
	if (Receiver != Loop->Receiver) Start->recv(Loop->Receiver);
	Start->link(Loop->Start);
	return Register;
};

operand_t *every_expr_t::compile(compiler_t *Compiler, label_t *Start, label_t *Success) {
	label_t *Label0 = new label_t;
	label_t *Label1 = new label_t;
	Condition->compile(Compiler, Start, Label0);
	Label0 = Compiler->push_trap(Label0, Label1);
		Label0 = Compiler->push_loop(Label0, Success);
			Body->compile(Compiler, Label0, Label1);
		Compiler->pop_loop();
	Compiler->pop_trap();
	uint32_t Trap = Compiler->trap();
	if (Trap != 0xFFFFFFFF) {
		Label1->back(Trap);
	} else {
		Label1->link(Compiler->failure());
	};
	return Register;
};

operand_t *send_expr_t::compile(compiler_t *Compiler, label_t *Start, label_t *Success) {
	label_t *Label0 = new label_t;
	Label0->load(Value->compile(Compiler, Start, Label0));
	Label0->send();
	return 0;
};

operand_t *self_expr_t::compile(compiler_t *Compiler, label_t *Start, label_t *Success) {
	Start->link(Success);
	return Compiler->Function->Assignment->Self;
};

operand_t *sequence_expr_t::compile(compiler_t *Compiler, label_t *Start, label_t *Success) {
	label_t *Label0 = Start;
	label_t *Label1 = new label_t;
	label_t *Label2 = new label_t;
	label_t *Label3 = new label_t;

	expr_t *Expr = Exprs;

	uint32_t Trap = Compiler->use_trap(Label0, Label3);
	Label0->link(Label1);
	label_t *Continue = Compiler->seq_trap(Label3);
	Label2->load(Expr->compile(Compiler, Label1, Label2));
	Label2->link(Success);
	Label0 = Label3;
	while ((Expr = Expr->Next)) {
		Label1 = new label_t;
		Label2 = new label_t;
		Label3 = new label_t;
		Label0->trap(Trap, Label3);
		Label0->link(Label1);
		Compiler->seq_trap(Label3);
		Label2->load(Expr->compile(Compiler, Label1, Label2));
		Label2->link(Success);
		Label0 = Label3;
	};
	Compiler->seq_trap(Continue);
	Label0->link(Continue);
	return Register;
};

operand_t *typeof_expr_t::compile(compiler_t *Compiler, label_t *Start, label_t *Success) {
	operand_t *Constant = Expr->constant(Compiler);
	if (Constant) {
		Start->link(Success);
		operand_t *Operand = new operand_t;
		Operand->Type = operand_t::CNST;
		Operand->Value = (Std$Object_t *)Constant->Value->Type;
		return Operand;
	};
	label_t *Label0 = new label_t;
	Label0->load(Expr->compile(Compiler, Start, Label0));
	Label0->type_of();
	Label0->link(Success);
	return Register;
};

operand_t *infinite_expr_t::compile(compiler_t *Compiler, label_t *Start, label_t *Success) {
	label_t *Label0 = new label_t;
	uint32_t Trap = Compiler->use_trap();
	Start->trap(Trap, Start);
	Start->link(Label0);
	label_t *Continue = Compiler->seq_trap(Start);
	operand_t *Result = Expr->compile(Compiler, Label0, Success);
	Compiler->seq_trap(Continue);
	return Result;
};

operand_t *parallel_expr_t::compile(compiler_t *Compiler, label_t *Start, label_t *Success) {
	label_t *Label0 = new label_t;
	label_t *Label1 = new label_t;
	label_t *Label2 = new label_t;
	label_t *Label3 = new label_t;
	label_t *Label4 = new label_t;
	Left->compile(Compiler, Label0, Label1);
	Compiler->push_trap(Start, Label2)->link(Label0);
		uint32_t Index = Compiler->use_trap();
		for (compiler_t::function_t::trap_t *Trap = Compiler->Function->Trap->Prev; Trap; Trap = Trap->Prev) {
			Trap->Free0->reserve(Index);
		};
		Label1->back(Index);
		Label2->trap(Index, Label3);
		Label2->link(Label4);
		operand_t *Result = Right->compile(Compiler, Label4, Success);
	Compiler->pop_trap();
	Index = Compiler->trap();
	if (Index != 0xFFFFFFFF) {
		Label3->back(Index);
	} else {
		Label3->link(Compiler->failure());
	};
	return Result;
};


operand_t *left_expr_t::compile(compiler_t *Compiler, label_t *Start, label_t *Success) {
	label_t *Label0 = new label_t;
	operand_t *Result = Left->compile(Compiler, Start, Label0);
	if (Result == Register) {
		Result = new operand_t;
		Result->Type = operand_t::TEMP;
		Result->Index = Compiler->new_temporary();
		Result->Loop = -1;
		label_t *Label1 = new label_t;
		Label0->store_tmp(Result->Index);
		Label0->link(Label1);
		Label0 = Label1;
	};
	Right->compile(Compiler, Label0, Success);
	return Result;
};

operand_t *right_expr_t::compile(compiler_t *Compiler, label_t *Start, label_t *Success) {
	label_t *Label0 = new label_t;
	Left->compile(Compiler, Start, Label0);
	return Right->compile(Compiler, Label0, Success);
};

operand_t *cond_expr_t::compile(compiler_t *Compiler, label_t *Start, label_t *Success) {
	if (this->Failure == 0) {
		label_t *Success0 = new label_t;
		label_t *Failure0 = new label_t;
		Compiler->push_expression();
			Start = Compiler->push_trap(Start, Failure0);
				Condition->compile(Compiler, Start, Success0);
			Compiler->pop_trap();
		Compiler->pop_expression();

		uint32_t Trap = Compiler->trap();
		if (Trap != 0xFFFFFFFF) {
			Failure0->back(Trap);
		} else {
			Failure0->link(Compiler->failure());
		};
		return this->Success->compile(Compiler, Success0, Success);
	} else if (this->Success == 0) {
		label_t *Success0 = new label_t;
		label_t *Failure0 = new label_t;
		Compiler->push_expression();
			Start = Compiler->push_trap(Start, Failure0);
				Condition->compile(Compiler, Start, Success0);
			Compiler->pop_trap();
		Compiler->pop_expression();

		uint32_t Trap = Compiler->trap();
		if (Trap != 0xFFFFFFFF) {
			Success0->back(Trap);
		} else {
			Success0->link(Compiler->failure());
		};
		return this->Failure->compile(Compiler, Failure0, Success);
	} else {
		label_t *Success0 = new label_t;
		label_t *Failure0 = new label_t;
		label_t *Success1 = new label_t;
		label_t *Failure1 = new label_t;
		Compiler->push_expression();
			Start = Compiler->push_trap(Start, Failure0);
				Condition->compile(Compiler, Start, Success0);
			Compiler->pop_trap();
		Compiler->pop_expression();

		Success1->load(this->Success->compile(Compiler, Success0, Success1));
		Success1->link(Success);
		Failure1->load(this->Failure->compile(Compiler, Failure0, Failure1));
		Failure1->link(Success);
	};
	return Register;
};

operand_t *comp_expr_t::compile(compiler_t *Compiler, label_t *Start, label_t *Success) {
	label_t *Label0 = new label_t;
	operand_t *Operand = Left->compile(Compiler, Start, Label0);
	if (Operand == Register) {
		Operand = new operand_t;
		Operand->Type = operand_t::LVAR;
		Operand->Index = Compiler->new_temporary();
		Operand->Loop = -1;
		Label0->store_val(Operand);
		label_t *Label1 = new label_t;
		Label0->link(Label1);
		Label0 = Label1;
	};
	label_t *Label1 = new label_t;
	label_t *Label2 = new label_t;
	operand_t *Result = Right->compile(Compiler, Label0, Label1);
	if (Result->Type == operand_t::CNST && Operand->Type == operand_t::CNST) {
		if ((Result->Value == Operand->Value) == Eq) {
			Label1->link(Success);
		} else {
			uint32_t Trap = Compiler->trap();
			if (Trap != 0xFFFFFFFF) {
				Label1->back(Trap);
			} else {
				Label1->link(Compiler->failure());
			};
		};
	} else {
		Label1->load(Result);
		Label1->comp(Eq, Operand, Label2);
		Label1->link(Success);
		uint32_t Trap = Compiler->trap();
		if (Trap != 0xFFFFFFFF) {
			Label2->back(Trap);
		} else {
			Label2->link(Compiler->failure());
		};
	};
	return Result;
};

operand_t *when_expr_t::compile(compiler_t *Compiler, label_t *Start, label_t *Success) {
	label_t *Label0 = new label_t;
	label_t *Label1 = new label_t;
	Label0->load(Condition->compile(Compiler, Start, Label0));
	Label0->link(Label1);
	Label0 = Label1;
	if (Cases == 0) {
		if (Default) {
			return Default->compile(Compiler, Label0, Success);
		} else {
			uint32_t Trap = Compiler->trap();
			if (Trap != 0xFFFFFFFF) {
				Label0->back(Trap);
			} else {
				Label0->link(Compiler->failure());
			};
			return Register;
		};
	};
	case_t *Case = Cases;
	Label1 = new label_t;
	label_t *Label2 = new label_t;
	Label2->load(Case->Body->compile(Compiler, Label1, Label2));
	Label2->link(Success);
	case_t::range_t *Range = Case->Ranges;
	operand_t *Operand = Range->Min->constant(Compiler);
	if (Operand == 0) Compiler->raise_error(Range->Min->LineNo, "Error: case is not constant");
	Std$Object_t *Value = Operand->Value;
	if (Value->Type == Std$Integer$SmallT) {
		select_integer_inst_t::case_t *ICase = new select_integer_inst_t::case_t;
		ICase->Min = ((Std$Integer_smallt *)Value)->Value;
		if (Range->Max) {
			Operand = Range->Max->constant(Compiler);
			if (Operand == 0) Compiler->raise_error(Range->Max->LineNo, "Error: case is not constant");
			Value = Operand->Value;
			if (Value->Type != Std$Integer$SmallT) Compiler->raise_error(Range->Max->LineNo, "Error: case is not correct type");
			ICase->Max = ((Std$Integer_smallt *)Value)->Value;
		} else {
			ICase->Max = ICase->Min;
		};
		ICase->Body = Label1;
		while (Range = Range->Next) {
			select_integer_inst_t::case_t *ICase0 = new select_integer_inst_t::case_t;
			Operand = Range->Min->constant(Compiler);
			if (Operand == 0) Compiler->raise_error(Range->Min->LineNo, "Error: case is not constant");
			Value = Operand->Value;
			if (Value->Type != Std$Integer$SmallT) Compiler->raise_error(Range->Min->LineNo, "Error: case is not correct type");
			ICase0->Min = ((Std$Integer_smallt *)Value)->Value;
			if (Range->Max) {
				Operand = Range->Max->constant(Compiler);
				if (Operand == 0) Compiler->raise_error(Range->Max->LineNo, "Error: case is not constant");
				Value = Operand->Value;
				if (Value->Type != Std$Integer$SmallT) Compiler->raise_error(Range->Max->LineNo, "Error: case is not correct type");
				ICase0->Max = ((Std$Integer_smallt *)Value)->Value;
			} else {
				ICase0->Max = ICase0->Min;
			};
			ICase0->Body = Label1;
			ICase0->Next = ICase;
			ICase = ICase0;
		};
		while (Case = Case->Next) {
			Label1 = new label_t;
			Label2 = new label_t;
			Label2->load(Case->Body->compile(Compiler, Label1, Label2));
			Label2->link(Success);
			for (Range = Case->Ranges; Range; Range = Range->Next) {
				select_integer_inst_t::case_t *ICase0 = new select_integer_inst_t::case_t;
				Operand = Range->Min->constant(Compiler);
				if (Operand == 0) Compiler->raise_error(Range->Min->LineNo, "Error: case is not constant");
				Value = Operand->Value;
				if (Value->Type != Std$Integer$SmallT) Compiler->raise_error(Range->Min->LineNo, "Error: case is not correct type");
				ICase0->Min = ((Std$Integer_smallt *)Value)->Value;
				if (Range->Max) {
					Operand = Range->Max->constant(Compiler);
					if (Operand == 0) Compiler->raise_error(Range->Max->LineNo, "Error: case is not constant");
					Value = Operand->Value;
					if (Value->Type != Std$Integer$SmallT) Compiler->raise_error(Range->Max->LineNo, "Error: case is not correct type");
					ICase0->Max = ((Std$Integer_smallt *)Value)->Value;
				} else {
					ICase0->Max = ICase0->Min;
				};
				ICase0->Body = Label1;
				ICase0->Next = ICase;
				ICase = ICase0;
			};
		};
		Label1 = new label_t;
		if (Default) {
			Label2 = new label_t;
			Label2->load(Default->compile(Compiler, Label1, Label2));
			Label2->link(Success);
		} else {
			uint32_t Trap = Compiler->trap();
			if (Trap != 0xFFFFFFFF) {
				Label1->back(Trap);
			} else {
				Label1->link(Compiler->failure());
			};
		};
		Label0->select_integer(ICase, Label1);
		return Register;
	} else if (Value->Type == Std$String$T) {
		if (Range->Max) Compiler->raise_error(Range->Max->LineNo, "Error: case can not be a range");
		select_string_inst_t::case_t *ICase = new select_string_inst_t::case_t;
		ICase->Key = Std$String$flatten((Std$String_t *)Value);
		ICase->Length = ((Std$String_t *)Value)->Length.Value;
		ICase->Body = Label1;
		while (Range = Range->Next) {
			select_string_inst_t::case_t *ICase0 = new select_string_inst_t::case_t;
			Operand = Range->Min->constant(Compiler);
			if (Operand == 0) Compiler->raise_error(Range->Min->LineNo, "Error: case is not constant");
			Value = Operand->Value;
			if (Value->Type != Std$String$T) Compiler->raise_error(Range->Min->LineNo, "Error: case is not correct type");
			ICase0->Key = Std$String$flatten((Std$String_t *)Value);
			ICase0->Length = ((Std$String_t *)Value)->Length.Value;
			if (Range->Max) Compiler->raise_error(Range->Max->LineNo, "Error: case can not be a range");
			ICase0->Body = Label1;
			ICase0->Next = ICase;
			ICase = ICase0;
		};
		while (Case = Case->Next) {
			Label1 = new label_t;
			Label2 = new label_t;
			Label2->load(Case->Body->compile(Compiler, Label1, Label2));
			Label2->link(Success);
			for (Range = Case->Ranges; Range; Range = Range->Next) {
				select_string_inst_t::case_t *ICase0 = new select_string_inst_t::case_t;
				Operand = Range->Min->constant(Compiler);
				if (Operand == 0) Compiler->raise_error(Range->Min->LineNo, "Error: case is not constant");
				Value = Operand->Value;
				if (Value->Type != Std$String$T) Compiler->raise_error(Range->Min->LineNo, "Error: case is not correct type");
				ICase0->Key = Std$String$flatten((Std$String_t *)Value);
				ICase0->Length = ((Std$String_t *)Value)->Length.Value;
				if (Range->Max) Compiler->raise_error(Range->Max->LineNo, "Error: case can not be a range");
				ICase0->Body = Label1;
				ICase0->Next = ICase;
				ICase = ICase0;
			};
		};
		Label1 = new label_t;
		if (Default) {
			Label2 = new label_t;
			Label2->load(Default->compile(Compiler, Label1, Label2));
			Label2->link(Success);
		} else {
			uint32_t Trap = Compiler->trap();
			if (Trap != 0xFFFFFFFF) {
				Label1->back(Trap);
			} else {
				Label1->link(Compiler->failure());
			};
		};
		Label0->select_string(ICase, Label1);
		return Register;
	} else {
		if (Range->Max) Compiler->raise_error(Range->Max->LineNo, "Error: case can not be a range");
		select_object_inst_t::case_t *ICase = new select_object_inst_t::case_t;
		ICase->Object = Value;
		ICase->Body = Label1;
		while (Range = Range->Next) {
			select_object_inst_t::case_t *ICase0 = new select_object_inst_t::case_t;
			Operand = Range->Min->constant(Compiler);
			if (Operand == 0) Compiler->raise_error(Range->Min->LineNo, "Error: case is not constant");
			Value = Operand->Value;
			ICase0->Object = Value;
			if (Range->Max) Compiler->raise_error(Range->Max->LineNo, "Error: case can not be a range");
			ICase0->Body = Label1;
			ICase0->Next = ICase;
			ICase = ICase0;
		};
		while (Case = Case->Next) {
			Label1 = new label_t;
			Label2 = new label_t;
			Label2->load(Case->Body->compile(Compiler, Label1, Label2));
			Label2->link(Success);
			for (Range = Case->Ranges; Range; Range = Range->Next) {
				select_object_inst_t::case_t *ICase0 = new select_object_inst_t::case_t;
				Operand = Range->Min->constant(Compiler);
				if (Operand == 0) Compiler->raise_error(Range->Min->LineNo, "Error: case is not constant");
				Value = Operand->Value;
				ICase0->Object = Value;
				if (Range->Max) Compiler->raise_error(Range->Max->LineNo, "Error: case can not be a range");
				ICase0->Body = Label1;
				ICase0->Next = ICase;
				ICase = ICase0;
			};
		};
		Label1 = new label_t;
		if (Default) {
			Label2 = new label_t;
			Label2->load(Default->compile(Compiler, Label1, Label2));
			Label2->link(Success);
		} else {
			uint32_t Trap = Compiler->trap();
			if (Trap != 0xFFFFFFFF) {
				Label1->back(Trap);
			} else {
				Label1->link(Compiler->failure());
			};
		};
		Label0->select_object(ICase, Label1);
		return Register;
	};
	Compiler->raise_error(LineNo, "Muhahaha: something is not implemented yet!");
};

operand_t *block_expr_t::compile(compiler_t *Compiler, label_t *Start, label_t *Success) {
	operand_t *Result = 0;
	Compiler->push_scope(compiler_t::scope_t::SC_LOCAL);
	for (block_expr_t::localdef_t *Def = Defs; Def; Def = Def->Next) {
		operand_t *Operand = Def->Value->constant(Compiler);
		if (Operand) Compiler->declare(Def->Name, Operand);
	};
	for (block_expr_t::localdef_t *Def = Defs; Def; Def = Def->Next) {
		Compiler->push_function();
		label_t *Start = new label_t;
		label_t *Success = new label_t;
		label_t *Failure = new label_t;
			Compiler->push_expression();
				Success->load(Def->Value->compile(Compiler, Compiler->push_trap(Start, Failure), Success));
				Compiler->pop_trap();
				Success->ret();
				Failure->fail();
			Compiler->pop_expression();
		frame_t *Frame = Compiler->pop_function();
		operand_t *Closure = Start->assemble(Frame);
		Std$Function_result Result;
		if (Std$Function$call(Closure->Value, 0, &Result) < FAILURE) {
			operand_t *Operand = new operand_t;
			Operand->Type = operand_t::CNST;
			Operand->Value = Result.Val;
			Compiler->declare(Def->Name, Operand);
		} else {
			Compiler->raise_error(LineNo, "Error: constant initialization failed");
		};
	};
	for (block_expr_t::localvar_t *Var = Vars; Var; Var = Var->Next) {
		operand_t *Operand = Compiler->new_local(Var->Reference);
		Compiler->declare(Var->Name, Operand);
	};
	if (Receiver.Body) {
		label_t *OldHandler = Compiler->handler();
		label_t *NewHandler = new label_t;
		Compiler->push_scope();
			operand_t *Message = Compiler->new_local();
			Compiler->declare(Receiver.Var, Message);
			NewHandler->store_val(Message);
			NewHandler->recv(OldHandler);
			label_t *Label0 = new label_t;
			label_t *Label1 = new label_t;
			NewHandler->link(Label0);
			Label1->load(Receiver.Body->compile(Compiler, Label0, Label1));
			Label1->link(Success);
		Compiler->pop_scope();
		Compiler->push_block(NewHandler);
			Label0 = new label_t;
			Start->recv(NewHandler);
			Start->link(Label0);
			for (expr_t *Expr = Body; Expr; Expr = Expr->Next) {
				Label1 = new label_t;
				Compiler->push_expression();
					Label0 = Compiler->push_trap(Label0, Label1);
						Expr->compile(Compiler, Label0, Label1);
					Compiler->pop_trap();
				Compiler->pop_expression();
				Label0 = Label1;
			};
			if (Final) {
				Label1 = new label_t;
				label_t *Label2 = new label_t;
				Label0 = Compiler->push_trap(Label0, Label2);
					Result = Final->compile(Compiler, Label0, Label1);
					Label0 = Label1;
				Compiler->pop_trap();
				Label2->recv(OldHandler);
				Label2->back(Compiler->trap());
			};
			Label0->recv(OldHandler);
			Label0->link(Success);
		Compiler->pop_block();
	} else {
		label_t *Label0 = Start;
		for (expr_t *Expr = Body; Expr; Expr = Expr->Next) {
			label_t *Label1 = new label_t;
			Compiler->push_expression();
				Label0 = Compiler->push_trap(Label0, Label1);
					Expr->compile(Compiler, Label0, Label1);
					Label1->flush();
					Label1->link(Label0 = new label_t);
				Compiler->pop_trap();
			Compiler->pop_expression();
		};
		if (Final) {
			label_t *Label1 = new label_t;
			Result = Final->compile(Compiler, Label0, Label1);
			Label0 = Label1;
		} else if (Result == 0) {
			Result = new operand_t;
			Result->Type = operand_t::CNST;
			Result->Value = Std$Object$Nil;
		};
		Label0->link(Success);
	};
	Compiler->pop_scope();
	return Result;
};

operand_t *module_expr_t::compile(compiler_t *Compiler, label_t *Start, label_t *Success) {
	const char *ModulePath = Sys$Module$get_path(Module);
	operand_t *Operand = new operand_t;
	Operand->Type = operand_t::CNST;
	Operand->Value = (Std$Object_t *)Module;
	Compiler->declare(Name, Operand);
	for (module_expr_t::globalvar_t *Var = Vars; Var; Var = Var->Next) {
		operand_t *Operand = new operand_t;
		Operand->Type = operand_t::GVAR;
		Std$Object_t **Address = new Std$Object_t *;
		Address[0] = Std$Object$Nil;
		Operand->Address = Address;
		Compiler->declare(Var->Name, Operand);
		if (Var->Exported) Sys$Module$export(Module, Var->Name, 1, Address);
	};
	for (module_expr_t::globalimp_t *Imp = Imps; Imp; Imp = Imp->Next) {
		int Length = Imp->Relative ? strlen(ModulePath) : 0;
		for (module_expr_t::globalimp_t::path_t *Path = Imp->Path; Path; Path = Path->Next) Length += strlen(Path->Part) + 1;
		char *ImportPath = new char[Length];
		char *Temp = Imp->Relative ? stpcpy(ImportPath, ModulePath) : ImportPath;
		for (module_expr_t::globalimp_t::path_t *Path = Imp->Path; Path; Path = Path->Next) {
			Temp = stpcpy(Temp, Path->Part);
			Temp++[0] = PATHCHR;
		};
		(--Temp)[0] = 0;
		operand_t *Operand = new operand_t;
		if (Imp->Exported) {
			Operand->Type = operand_t::CNST;
			Operand->Value = (Std$Object_t *)Sys$Module$load(0, ImportPath);
			Sys$Module$export(Module, Imp->Alias, 0, Operand->Value);
		} else {
			Operand->Type = operand_t::FUTR;
			Operand->Module = ImportPath;
		};
		Compiler->declare(Imp->Alias, Operand);
		for (module_expr_t::globalimp_t::uselist_t *Use = Imp->Uses; Use; Use = Use->Next) {
			operand_t *Operand = new operand_t;
			Operand->Type = operand_t::FUTR;
			Operand->Module = ImportPath;
			Operand->Import = Use->Name;
			Compiler->declare(Use->Name, Operand);
		};
	};
	for (module_expr_t::globaldef_t *Def = Defs; Def; Def = Def->Next) {
		operand_t *Operand = Def->Value->constant(Compiler);
		if (Operand) Compiler->declare(Def->Name, Operand);
	};
	for (module_expr_t::globaldef_t *Def = Defs; Def; Def = Def->Next) {
		Compiler->push_function();
		label_t *Start = new label_t;
		label_t *Success = new label_t;
		label_t *Failure = new label_t;
			Compiler->push_expression();
				Success->load(Def->Value->compile(Compiler, Compiler->push_trap(Start, Failure), Success));
				Compiler->pop_trap();
				Success->ret();
				Failure->fail();
			Compiler->pop_expression();
		frame_t *Frame = Compiler->pop_function();
		operand_t *Closure = Start->assemble(Frame);
		Std$Function_result Result;
		if (Std$Function$call(Closure->Value, 0, &Result) < FAILURE) {
			operand_t *Operand = new operand_t;
			Operand->Type = operand_t::CNST;
			Operand->Value = Result.Val;
			Compiler->declare(Def->Name, Operand);
			if (Def->Exported) Sys$Module$export(Module, Def->Name, 0, Result.Val);
		} else {
			Compiler->raise_error(LineNo, "Error: constant initialization failed");
		};
	};
	if (Body) {
		Compiler->push_function();
			label_t *Start = new label_t;
			label_t *Label0 = Start;
			for (expr_t *Expr = Body; Expr; Expr = Expr->Next) {
				label_t *Label1 = new label_t;
				Compiler->push_expression();
					Label0 = Compiler->push_trap(Label0, Label1);
						Expr->compile(Compiler, Label0, Label1);
						Label1->flush();
						Label1->link(Label0 = new label_t);
					Compiler->pop_trap();
				Compiler->pop_expression();
			};
			Label0->ret();
		frame_t *Frame = Compiler->pop_function();
		operand_t *Closure = Start->assemble(Frame);
		Std$Function_result Result;
		if (Std$Function$call(Closure->Value, 0, &Result) == MESSAGE) {
			if (Std$Function$call((Std$Object_t *)$AT, 2, &Result, Result.Val, 0, Std$String$T, 0) < FAILURE) {
				Compiler->raise_error(LineNo, Std$String$flatten((Std$String_t *)Result.Val));
			} else {
				Compiler->raise_error(0, "Error: unhandled message");
			};
		};
	};
	Start->link(Success);
	return Operand;
};

void module_expr_t::compile(compiler_t *Compiler) {
	compile(Compiler, new label_t, new label_t);
};

int command_expr_t::compile(compiler_t *Compiler, Std$Function_result *Result) {
	char ModulePath[256];
	int PathLength;
	bool InitPath = false;
	for (command_expr_t::globalvar_t *Var = Vars; Var; Var = Var->Next) {
		operand_t *Operand = new operand_t;
		Operand->Type = operand_t::GVAR;
		Std$Object_t **Address = new Std$Object_t *;
		Address[0] = Std$Object$Nil;
		Operand->Address = Address;
		Compiler->declare(Var->Name, Operand);
	};
	for (command_expr_t::globalimp_t *Imp = Imps; Imp; Imp = Imp->Next) {
		if (Imp->Relative && !InitPath) {
			getcwd(ModulePath, 256);
			strcat(ModulePath, PATHSTR);
			PathLength = strlen(ModulePath);
		};
		operand_t *Operand = new operand_t;
		Operand->Type = operand_t::FUTR;
		int Length = Imp->Relative ? PathLength : 0;
		for (command_expr_t::globalimp_t::path_t *Path = Imp->Path; Path; Path = Path->Next) Length += strlen(Path->Part) + 1;
		char *ImportPath = new char[Length];
		char *Temp = Imp->Relative ? stpcpy(ImportPath, ModulePath) : ImportPath;
		for (command_expr_t::globalimp_t::path_t *Path = Imp->Path; Path; Path = Path->Next) {
			Temp = stpcpy(Temp, Path->Part);
			Temp++[0] = PATHCHR;
		};
		(--Temp)[0] = 0;
		Operand->Module = ImportPath;
		Compiler->declare(Imp->Alias, Operand);
		for (command_expr_t::globalimp_t::uselist_t *Use = Imp->Uses; Use; Use = Use->Next) {
			operand_t *Operand = new operand_t;
			Operand->Type = operand_t::FUTR;
			Operand->Module = ImportPath;
			Operand->Import = Use->Name;
			Compiler->declare(Use->Name, Operand);
		};
	};
	for (command_expr_t::globaldef_t *Def = Defs; Def; Def = Def->Next) {
		operand_t *Operand = Def->Value->constant(Compiler);
		if (Operand) Compiler->declare(Def->Name, Operand);
	};
	int Status;
	for (command_expr_t::globaldef_t *Def = Defs; Def; Def = Def->Next) {
		Compiler->push_function();
		label_t *Start = new label_t;
		label_t *Success = new label_t;
		label_t *Failure = new label_t;
			Compiler->push_expression();
				Success->load(Def->Value->compile(Compiler, Compiler->push_trap(Start, Failure), Success));
				Compiler->pop_trap();
				Success->ret();
				Failure->fail();
			Compiler->pop_expression();
		frame_t *Frame = Compiler->pop_function();
		operand_t *Closure = Start->assemble(Frame);
		Status = Std$Function$call(Closure->Value, 0, Result);
		if (Status < FAILURE) {
			operand_t *Operand = new operand_t;
			Operand->Type = operand_t::CNST;
			Operand->Value = Result->Val;
			Compiler->declare(Def->Name, Operand);
		} else {
			Compiler->raise_error(LineNo, "Error: constant initialization failed");
		};
	};
	if (Body) {
		Compiler->push_function();
			label_t *Start = new label_t;
			label_t *Success = new label_t;
			label_t *Failure = new label_t;
			label_t *Label0 = Start;
			for (expr_t *Expr = Body; Expr; Expr = Expr->Next) {
				label_t *Label1 = new label_t;
				Compiler->push_expression();
					if (Expr->Next) {
						Label0 = Compiler->push_trap(Label0, Label1);
							Expr->compile(Compiler, Label0, Label1);
							Label1->flush();
							Label1->link(Label0 = new label_t);
						Compiler->pop_trap();
					} else {
						Label0 = Compiler->push_trap(Label0, Failure);
							Success->load(Expr->compile(Compiler, Label0, Success));
						Compiler->pop_trap();
					};
				Compiler->pop_expression();
			};
			Success->ret();
			Failure->fail();
		frame_t *Frame = Compiler->pop_function();
		operand_t *Closure = Start->assemble(Frame);
		Status = Std$Function$call(Closure->Value, 0, Result);
	};
	return Status;
};
