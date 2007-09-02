#include "parser.h"
#include "scanner.h"
#include "compiler.h"
#include "missing.h"

#include <Riva.h>
#include <string.h>
#include <Std.h>

#include <stdio.h>

SYMBOL($AT, "@");
SYMBOL($QUERY, "?");
SYMBOL($EQUAL, "=");
SYMBOL($NOTEQ, "~=");
SYMBOL($LESS, "<");
SYMBOL($GREATER, ">");
SYMBOL($LSEQ, "<=");
SYMBOL($GREQ, ">=");
SYMBOL($IN, "in");
SYMBOL($SUBTYPE, "<:");
SYMBOL($PLUS, "+");
SYMBOL($MINUS, "-");
SYMBOL($MULTIPLY, "*");
SYMBOL($DIVIDE, "/");
SYMBOL($MODULO, "%");
SYMBOL($POWER, "^");
SYMBOL($PARTIAL, "!!");
SYMBOL($INDEX, "[]");
SYMBOL($BACKSLASH, "\\");
SYMBOL($INVERSE, "~");
SYMBOL($EXCLAIM, "!");
SYMBOL($HASH, "#");

static func_expr_t::parameter_t *accept_parameters(scanner_t *Scanner) {
	if (Scanner->parse(tkIDENT)) {
		func_expr_t::parameter_t *Param = new func_expr_t::parameter_t;
		Param->Name = Scanner->Token.Ident;
		Param->Reference = Scanner->parse(tkPLUS);
		func_expr_t::parameter_t *Last = Param;
		while (Scanner->parse(tkCOMMA)) {
			func_expr_t::parameter_t *Next = new func_expr_t::parameter_t;
			Scanner->accept(tkIDENT);
			Next->Name = Scanner->Token.Ident;
			Next->Reference = Scanner->parse(tkPLUS);
			Last->Next = Next;
			Last = Next;
		};
		return Param;
	} else {
		return 0;
	};
};

struct typed_parameters {
	func_expr_t::parameter_t *Parameters;
	expr_t *Types;
};

expr_t *accept_expr(scanner_t *Scanner);
static expr_t *parse_expr(scanner_t *Scanner);

static typed_parameters accept_typed_parameters(scanner_t *Scanner) {
	func_expr_t::parameter_t *Param = new func_expr_t::parameter_t;
	if (Scanner->parse(tkIDENT)) {
		Param->Name = Scanner->Token.Ident;
		Param->Reference = Scanner->parse(tkPLUS);
	} else {
		asprintf(&Param->Name, "anon:%x", Param);
	};
	expr_t *Type;
	if (Scanner->parse(tkAT)) {
		Type = new const_expr_t(Scanner->Token.LineNo, Std$Symbol$In);
		Type->Next = accept_expr(Scanner);
	} else if (Scanner->parse(tkEQUAL)) {
		Type = new const_expr_t(Scanner->Token.LineNo, Std$Symbol$Is);
		Type->Next = accept_expr(Scanner);
	} else {
		Type = new const_expr_t(Scanner->Token.LineNo, Std$Object$Nil);
		Type->Next = new const_expr_t(Scanner->Token.LineNo, Std$Object$Nil);
	};
	if (Scanner->parse(tkCOMMA)) {
		typed_parameters TP = accept_typed_parameters(Scanner);
		Param->Next = TP.Parameters;
		TP.Parameters = Param;
		Type->Next->Next = TP.Types;
		TP.Types = Type;
		return TP;
	} else {
		typed_parameters TP = {Param, Type};
		return TP;
	};
};

#define PREFIX(SYMBOL)\
	if (Scanner->parse(tk ## SYMBOL)) {\
		expr_t *Function = new const_expr_t(Scanner->Token.LineNo, $ ## SYMBOL);\
		return new invoke_expr_t(Scanner->Token.LineNo, Function, accept_term(Scanner));\
	};

expr_t *accept_expr_list(scanner_t *Scanner) {
	expr_t *List = parse_expr(Scanner);
	if (List == 0) return 0;
	expr_t *Tail = List;
	while (Scanner->parse(tkCOMMA)) {
		Tail->Next = accept_expr(Scanner);
		Tail = Tail->Next;
	};
	return List;
};

static expr_t *accept_table_list(scanner_t *Scanner) {
	expr_t *List = parse_expr(Scanner);
	if (List == 0) return 0;
	expr_t *Tail = List;
	if (Scanner->parse(tkIS)) {
		Tail->Next = accept_expr(Scanner);
	} else {
		Tail->Next = new const_expr_t(Scanner->Token.LineNo, Std$Object$Nil);
	};
	Tail = Tail->Next;
	while (Scanner->parse(tkCOMMA)) {
		Tail->Next = accept_expr(Scanner);
		Tail = Tail->Next;
		if (Scanner->parse(tkIS)) {
			Tail->Next = accept_expr(Scanner);
		} else {
			Tail->Next = new const_expr_t(Scanner->Token.LineNo, Std$Object$Nil);
		};
		Tail = Tail->Next;
	};
	return List;
};

extern Riva$Module_t Riva$Symbol[];

static Std$Array_t *accept_fields(scanner_t *Scanner, int Index = 0) {
	Std$Object_t *Field;
	if (Scanner->parse(tkIDENT)) {
		int Type;
		Riva$Module$import(Riva$Symbol, Scanner->Token.Ident, &Type, (void **)&Field);
	} else if (Scanner->parse(tkSYMBOL)) {
		Field = Scanner->Token.Const;
	} else {
		return Std$Array$new(Index);
	};
	Scanner->parse(tkCOMMA);
	Std$Array_t *Fields = accept_fields(Scanner, Index + 1);
	Fields->Values[Index] = Field;
	return Fields;
};

static expr_t *accept_factor(scanner_t *Scanner);

static when_expr_t::case_t::range_t *accept_when_expr_range(scanner_t *Scanner) {
	expr_t *Min = accept_expr(Scanner);
	expr_t *Max = Scanner->parse(tkDOTDOT) ? accept_expr(Scanner) : 0;
	when_expr_t::case_t::range_t *Range = new when_expr_t::case_t::range_t(Scanner->Token.LineNo, Min, Max);
	if (Scanner->parse(tkCOMMA)) Range->Next = accept_when_expr_range(Scanner);
	return Range;
};

static when_expr_t *accept_when_expr_case(scanner_t *Scanner) {
	if (Scanner->parse(tkIS)) {
		when_expr_t::case_t::range_t *Ranges = accept_when_expr_range(Scanner);
		Scanner->accept(tkDO);
		when_expr_t::case_t *Case = new when_expr_t::case_t(Scanner->Token.LineNo, Ranges, accept_expr(Scanner));
		when_expr_t *Expr = accept_when_expr_case(Scanner);
		Case->Next = Expr->Cases;
		Expr->Cases = Case;
		return Expr;
	} else {
		when_expr_t *Expr = new when_expr_t;
		Expr->Default = Scanner->parse(tkDO) ? accept_expr(Scanner) : new back_expr_t(Scanner->Token.LineNo);
		return Expr;
	};
};

static expr_t *accept_when_expr(scanner_t *Scanner) {
	expr_t *Condition = accept_expr(Scanner);
	int LineNo = Scanner->Token.LineNo;
	when_expr_t *Expr = accept_when_expr_case(Scanner);
	Expr->Condition = Condition;
	Expr->LineNo = LineNo;
	return Expr;
};

extern Std$Object_t Std$Type$New[];

static block_expr_t *accept_localstatement(scanner_t *Scanner);

static block_expr_t *accept_localvar(scanner_t *Scanner) {
	block_expr_t::localvar_t *Var = new block_expr_t::localvar_t;
	Var->LineNo = Scanner->Token.LineNo;
	Scanner->accept(tkIDENT);
	Var->Name = Scanner->Token.Ident;
	Var->Reference = Scanner->parse(tkPLUS);
	if (Scanner->parse(tkASSIGN)) {
		ident_expr_t *Ident = new ident_expr_t(Scanner->Token.LineNo, Var->Name);
		assign_expr_t *Assign = new assign_expr_t(Scanner->Token.LineNo, Ident, accept_expr(Scanner));
		if (Scanner->parse(tkCOMMA)) {
			block_expr_t *Block = accept_localvar(Scanner);
			Var->Next = Block->Vars;
			Block->Vars = Var;
			if (Block->Final) {
				Assign->Next = Block->Body;
				Block->Body = Assign;
			} else {
				Block->Final = Assign;
			};
			return Block;
		} else {
			Scanner->accept(tkSEMICOLON);
			block_expr_t *Block = accept_localstatement(Scanner);
			Var->Next = Block->Vars;
			Block->Vars = Var;
			if (Block->Final) {
				Assign->Next = Block->Body;
				Block->Body = Assign;
			} else {
				Block->Final = Assign;
			};
			return Block;
		};
	} else if (Scanner->parse(tkREFASSIGN)) {
		ident_expr_t *Ident = new ident_expr_t(Scanner->Token.LineNo, Var->Name);
		ref_assign_expr_t *Assign = new ref_assign_expr_t(Scanner->Token.LineNo, Ident, accept_expr(Scanner));
		if (Scanner->parse(tkCOMMA)) {
			block_expr_t *Block = accept_localvar(Scanner);
			Var->Next = Block->Vars;
			Block->Vars = Var;
			if (Block->Final) {
				Assign->Next = Block->Body;
				Block->Body = Assign;
			} else {
				Block->Final = Assign;
			};
			return Block;
		} else {
			Scanner->accept(tkSEMICOLON);
			block_expr_t *Block = accept_localstatement(Scanner);
			Var->Next = Block->Vars;
			Block->Vars = Var;
			if (Block->Final) {
				Assign->Next = Block->Body;
				Block->Body = Assign;
			} else {
				Block->Final = Assign;
			};
			return Block;
		};
	} else if (Scanner->parse(tkLPAREN)) {
		func_expr_t::parameter_t *Parameters = accept_parameters(Scanner);
		Scanner->accept(tkRPAREN);
		func_expr_t *Func = new func_expr_t(Scanner->Token.LineNo, Parameters, accept_expr(Scanner));
		ident_expr_t *Ident = new ident_expr_t(Scanner->Token.LineNo, Var->Name);
		assign_expr_t *Assign = new assign_expr_t(Scanner->Token.LineNo, Ident, Func);
		if (Scanner->parse(tkCOMMA)) {
			block_expr_t *Block = accept_localvar(Scanner);
			Var->Next = Block->Vars;
			Block->Vars = Var;
			if (Block->Final) {
				Assign->Next = Block->Body;
				Block->Body = Assign;
			} else {
				Block->Final = Assign;
			};
			return Block;
		} else {
			Scanner->accept(tkSEMICOLON);
			block_expr_t *Block = accept_localstatement(Scanner);
			Var->Next = Block->Vars;
			Block->Vars = Var;
			if (Block->Final) {
				Assign->Next = Block->Body;
				Block->Body = Assign;
			} else {
				Block->Final = Assign;
			};
			return Block;
		};
	} else {
		if (Scanner->parse(tkCOMMA)) {
			block_expr_t *Block = accept_localvar(Scanner);
			Var->Next = Block->Vars;
			Block->Vars = Var;
			return Block;
		} else {
			Scanner->accept(tkSEMICOLON);
			block_expr_t *Block = accept_localstatement(Scanner);
			Var->Next = Block->Vars;
			Block->Vars = Var;
			return Block;
		};
	};
};

static block_expr_t *accept_localdef(scanner_t *Scanner) {
	block_expr_t::localdef_t *Def = new block_expr_t::localdef_t;
	Def->LineNo = Scanner->Token.LineNo;
	Scanner->accept(tkIDENT);
	Def->Name = Scanner->Token.Ident;
	if (Scanner->parse(tkLPAREN)) {
		func_expr_t::parameter_t *Parameters = accept_parameters(Scanner);
		Scanner->accept(tkRPAREN);
		Def->Value = new func_expr_t(Scanner->Token.LineNo, Parameters, accept_expr(Scanner));
		block_expr_t *Block;
		if (Scanner->parse(tkCOMMA)) {
			Block = accept_localvar(Scanner);
		} else {
			Scanner->accept(tkSEMICOLON);
			Block = accept_localstatement(Scanner);
		};
		Def->Next = Block->Defs;
		Block->Defs = Def;
		if (Block->Final == 0) Block->Final = new ident_expr_t(Scanner->Token.LineNo, Def->Name);
		return Block;
	} else {
		Scanner->accept(tkASSIGN);
		Def->Value = accept_expr(Scanner);
		block_expr_t *Block;
		if (Scanner->parse(tkCOMMA)) {
			Block = accept_localdef(Scanner);
		} else {
			Scanner->accept(tkSEMICOLON);
			Block = accept_localstatement(Scanner);
		};
		Def->Next = Block->Defs;
		Block->Defs = Def;
		if (Block->Final == 0) Block->Final = new ident_expr_t(Scanner->Token.LineNo, Def->Name);
		return Block;
	};
};

static block_expr_t *accept_localrecv(scanner_t *Scanner) {
	Scanner->accept(tkIDENT);
	const char *Var = Scanner->Token.Ident;
	Scanner->accept(tkDO);
	expr_t *Body = accept_expr(Scanner);
	if (Scanner->parse(tkSEMICOLON)) {
		block_expr_t *Block = accept_localstatement(Scanner);
		Block->Receiver.Var = Var;
		Block->Receiver.Body = Body;
		return Block;
	} else {
		block_expr_t *Block = new block_expr_t;
		Block->Receiver.Var = Var;
		Block->Receiver.Body = Body;
		return Block;
	};
};

static block_expr_t *accept_localstatement(scanner_t *Scanner) {
	if (Scanner->parse(tkVAR)) return accept_localvar(Scanner);
	if (Scanner->parse(tkDEF)) return accept_localdef(Scanner);
	if (Scanner->parse(tkRECV)) return accept_localrecv(Scanner);
	expr_t *Expr = parse_expr(Scanner);
	if (Expr) {
		if (Scanner->parse(tkSEMICOLON)) {
			block_expr_t *Block = accept_localstatement(Scanner);
			if (Block->Final) {
				Expr->Next = Block->Body;
				Block->Body = Expr;
			} else {
				Block->Final = Expr;
			};
			return Block;
		} else {
			block_expr_t *Block = new block_expr_t;
			Block->Final = Expr;
			return Block;
		};
	};
	return new block_expr_t;
};

module_expr_t *accept_module(scanner_t *Scanner, Sys$Module_t *Module);

SYMBOL($AS, "@");

LOCAL_FUNCTION(CreateStringBlock) {
	for (int I = 0; I < Count; ++I) {
		Std$Object_t *Arg = Args[I].Val;
		if (Arg->Type != Std$String$T) {
			int Status = Std$Function$call((Std$Object_t *)$AS, 2, Result, Arg, 0, Std$String$T, 0);
			if (Status >= FAILURE) return Status;
			Args[I].Val = Result->Val;
		};
	};
	int NoOfBlocks = 0, Length = 0;
	for (int I = 0; I < Count; ++I) {
		Std$String_t *String = (Std$String_t *)Args[I].Val;
		NoOfBlocks += String->Count;
		Length += String->Length.Value;
	};
	Std$String_t *String = (Std$String_t *)Riva$Memory$alloc(sizeof(Std$String_t) + (NoOfBlocks + 1) * sizeof(Std$String_block));
	String->Type = Std$String$T;
	String->Length.Type = Std$Integer$SmallT;
	String->Length.Value = Length;
	String->Count = NoOfBlocks;
	void *Block = String->Blocks;
	for (int I = 0; I < Count; ++I) {
		Std$String_t *String0 = (Std$String_t *)Args[I].Val;
#ifdef LINUX
		Block = mempcpy(Block, String0->Blocks, String0->Count * sizeof(Std$String_block));
#else
		int Length = String0->Count * sizeof(Std$String_block);
		memcpy(Block, String0->Blocks, Length);
		Block = Block + Length;
#endif
	};
	Result->Val = (Std$Object_t *)String;
	Result->Ref = 0;
	return SUCCESS;
};

static expr_t *parse_factor(scanner_t *Scanner) {
	if (Scanner->parse(tkCONST)) return new const_expr_t(Scanner->Token.LineNo, Scanner->Token.Const);
	if (Scanner->parse(tkSTRBLOCK)) return new invoke_expr_t(Scanner->Token.LineNo,
		new const_expr_t(Scanner->Token.LineNo, (Std$Object_t *)&CreateStringBlock),
		(expr_t *)Scanner->Token.Const
	);
	if (Scanner->parse(tkSYMBOL)) return new const_expr_t(Scanner->Token.LineNo, Scanner->Token.Const);
	if (Scanner->parse(tkIDENT)) {
		const char *Ident = Scanner->Token.Ident;
		if (Scanner->parse(tkDOT)) {
			qualident_expr_t::name_t *Head = new qualident_expr_t::name_t;
			Head->Ident = Ident;
			Scanner->accept(tkIDENT);
			qualident_expr_t::name_t *Tail = new qualident_expr_t::name_t;
			Head->Next = Tail;
			Tail->Ident = Scanner->Token.Ident;
			while (Scanner->parse(tkDOT)) {
				qualident_expr_t::name_t *Next = new qualident_expr_t::name_t;
				Scanner->accept(tkIDENT);
				Next->Ident = Scanner->Token.Ident;
				Tail->Next = Next;
				Tail = Next;
			};
			return new qualident_expr_t(Scanner->Token.LineNo, Head);
		} else {
			return new ident_expr_t(Scanner->Token.LineNo, Ident);
		};
	};
	if (Scanner->parse(tkSELF)) return new self_expr_t(Scanner->Token.LineNo);
	if (Scanner->parse(tkNIL)) return new const_expr_t(Scanner->Token.LineNo, Std$Object$Nil);
	if (Scanner->parse(tkLBRACKET)) {
		expr_t *Expr = new invoke_expr_t(Scanner->Token.LineNo,
			new const_expr_t(Scanner->Token.LineNo, Std$List$Make),
			accept_expr_list(Scanner)
		);
		Scanner->accept(tkRBRACKET);
		return Expr;
	};
	if (Scanner->parse(tkLBRACE)) {
		expr_t *Expr = new invoke_expr_t(Scanner->Token.LineNo,
			new const_expr_t(Scanner->Token.LineNo, Std$Table$Make),
			accept_table_list(Scanner)
		);
		Scanner->accept(tkRBRACE);
		return Expr;
	};
	if (Scanner->parse(tkLESS)) {
		if (Scanner->parse(tkLBRACKET)) {
			expr_t *Parents = accept_expr_list(Scanner);
			Scanner->accept(tkRBRACKET);
			expr_t *Fields;
			//if (Scanner->parse(tkGREATER)) {
			//	Fields = new const_expr_t(Scanner->Token.LineNo, Std$Array$new(0));
			//} else {
				Fields = new const_expr_t(Scanner->Token.LineNo, accept_fields(Scanner));
				Scanner->accept(tkGREATER);
			//};
			Fields->Next = Parents;
			return new invoke_expr_t(Scanner->Token.LineNo, new const_expr_t(Scanner->Token.LineNo, Std$Type$New), Fields);
		} else {
			func_expr_t::parameter_t *Parameters = accept_parameters(Scanner);
			Scanner->accept(tkGREATER);
			return new func_expr_t(Scanner->Token.LineNo, Parameters, accept_expr(Scanner));
		};
	};
	if (Scanner->parse(tkLPAREN)) {
		expr_t *Block = accept_localstatement(Scanner);
		Scanner->accept(tkRPAREN);
		return Block;
	};
	if (Scanner->parse(tkBACK)) return new back_expr_t(Scanner->Token.LineNo);
	if (Scanner->parse(tkFAIL)) return new fail_expr_t(Scanner->Token.LineNo);
	if (Scanner->parse(tkRET)) {
		expr_t *Value = parse_expr(Scanner);
		if (Value == 0) Value = new const_expr_t(Scanner->Token.LineNo, Std$Object$Nil);
		return new ret_expr_t(Scanner->Token.LineNo, Value);
	};
	if (Scanner->parse(tkSUSP)) return new susp_expr_t(Scanner->Token.LineNo, accept_expr(Scanner));
	if (Scanner->parse(tkREP)) return new rep_expr_t(Scanner->Token.LineNo, accept_expr(Scanner));
	if (Scanner->parse(tkALL)) return new all_expr_t(Scanner->Token.LineNo, accept_expr(Scanner));
	if (Scanner->parse(tkEXIT)) {
		expr_t *Value = parse_expr(Scanner);
		if (Value == 0) Value = new const_expr_t(Scanner->Token.LineNo, Std$Object$Nil);
		return new exit_expr_t(Scanner->Token.LineNo, Value);
	};
	if (Scanner->parse(tkSTEP)) return new step_expr_t(Scanner->Token.LineNo);
	if (Scanner->parse(tkEVERY)) {
		expr_t *Condition = accept_expr(Scanner);
		if (Scanner->parse(tkDO)) return new every_expr_t(Scanner->Token.LineNo, Condition, accept_expr(Scanner));
		return new every_expr_t(Scanner->Token.LineNo, Condition, new const_expr_t(Scanner->Token.LineNo, Std$Object$Nil));
	};
	/*if (Scanner->parse(tkNOT)) return new cond_expr_t(Scanner->Token.LineNo,
		accept_expr(Scanner),
		new back_expr_t(Scanner->Token.LineNo),
		new const_expr_t(Scanner->Token.LineNo, Std$Object$Nil)
	);*/
	if (Scanner->parse(tkWHILE)) return new cond_expr_t(Scanner->Token.LineNo,
		accept_expr(Scanner),
		new back_expr_t(Scanner->Token.LineNo),
		new exit_expr_t(Scanner->Token.LineNo, new const_expr_t(Scanner->Token.LineNo, Std$Object$Nil))
	);
	if (Scanner->parse(tkUNTIL)) return new cond_expr_t(Scanner->Token.LineNo,
		accept_expr(Scanner),
		new exit_expr_t(Scanner->Token.LineNo, new const_expr_t(Scanner->Token.LineNo, Std$Object$Nil)),
		new back_expr_t(Scanner->Token.LineNo)
	);
	if (Scanner->parse(tkWHEN)) return accept_when_expr(Scanner);
	if (Scanner->parse(tkSEND)) return new send_expr_t(Scanner->Token.LineNo, accept_expr(Scanner));
	if (Scanner->parse(tkTO)) {
		expr_t *Symbol = accept_factor(Scanner);
		Scanner->accept(tkLPAREN);
		typed_parameters TP = {0, 0};
		if (!Scanner->parse(tkRPAREN)) {
			TP = accept_typed_parameters(Scanner);
			Scanner->accept(tkRPAREN);
		};
		expr_t *Body;
		if (Scanner->parse(tkDO)) {
			Body = accept_expr(Scanner);
		} else {
			Body = new func_expr_t(Scanner->Token.LineNo, TP.Parameters, accept_expr(Scanner));
		};
		Symbol->Next = Body;
		Body->Next = TP.Types;
		return new invoke_expr_t(Scanner->Token.LineNo, new const_expr_t(Scanner->Token.LineNo, Std$Symbol$Set), Symbol);
	};
	if (Scanner->parse(tkDO)) {
		expr_t *Function = new func_expr_t(Scanner->Token.LineNo, 0,
			new every_expr_t(Scanner->Token.LineNo,
				new susp_expr_t(Scanner->Token.LineNo, accept_expr(Scanner)),
				new const_expr_t(Scanner->Token.LineNo, Std$Object$Nil)
			)
		);
		return new invoke_expr_t(Scanner->Token.LineNo, new const_expr_t(Scanner->Token.LineNo, Std$Coexpr$New), Function);
	};
	if (Scanner->parse(tkYIELD)) {
		return new invoke_expr_t(Scanner->Token.LineNo, new const_expr_t(Scanner->Token.LineNo, Std$Coexpr$Yield), accept_expr(Scanner));
	};
	if (Scanner->parse(tkMOD)) return accept_module(Scanner, 0);
	return 0;
};

static expr_t *accept_factor(scanner_t *Scanner) {
	expr_t *Expr = parse_factor(Scanner);
	if (Expr) return Expr;
	Scanner->raise_error(Scanner->Token.LineNo, "Error: expected factor not %s\n", Tokens[Scanner->NextToken.Type]);
};

static expr_t *accept_term(scanner_t *Scanner);

static expr_t *parse_term(scanner_t *Scanner) {
	PREFIX(MODULO);
	PREFIX(POWER);
	PREFIX(MINUS);
	PREFIX(DIVIDE);
	PREFIX(BACKSLASH);
	PREFIX(INVERSE);
	PREFIX(EXCLAIM);
	PREFIX(HASH);
	if (Scanner->parse(tkQUERY)) return new typeof_expr_t(Scanner->Token.LineNo, accept_term(Scanner));
	if (Scanner->parse(tkOR)) return new infinite_expr_t(Scanner->Token.LineNo, accept_term(Scanner));
	expr_t *Expr = parse_factor(Scanner);
	if (Expr == 0) return 0;
start:
	if (Scanner->parse(tkAT)) {
		expr_t *Function = new const_expr_t(Scanner->Token.LineNo, $AT);
		Expr->Next = parse_factor(Scanner);
		Expr = new invoke_expr_t(Scanner->Token.LineNo, Function, Expr);
		goto start;
	};
	if (Scanner->parse(tkSYMBOL)) {
		expr_t *Symbol = new const_expr_t(Scanner->Token.LineNo, Scanner->Token.Const);
		if (Scanner->parse(tkLPAREN)) {
			Expr->Next = accept_expr_list(Scanner);
			Scanner->accept(tkRPAREN);
		};
		Expr = new invoke_expr_t(Scanner->Token.LineNo, Symbol, Expr);
		goto start;
	};
	if (Scanner->parse(tkLPAREN)) {
		Expr = new invoke_expr_t(Scanner->Token.LineNo, Expr, accept_expr_list(Scanner));
		Scanner->accept(tkRPAREN);
		goto start;
	};
	if (Scanner->parse(tkLBRACE)) {
		Expr = new parallel_invoke_expr_t(Scanner->Token.LineNo, Expr, accept_expr_list(Scanner));
		Scanner->accept(tkRBRACE);
		goto start;
	};
	if (Scanner->parse(tkLBRACKET)) {
		Expr->Next = accept_expr_list(Scanner);
		Expr = new invoke_expr_t(Scanner->Token.LineNo, new const_expr_t(Scanner->Token.LineNo, $INDEX), Expr);
		Scanner->accept(tkRBRACKET);
		goto start;
	};
	return Expr;
};

static expr_t *accept_term(scanner_t *Scanner) {
	expr_t *Expr = parse_term(Scanner);
	if (Expr) return Expr;
	Scanner->raise_error(Scanner->Token.LineNo, "Error: expected term not %s\n", Tokens[Scanner->NextToken.Type]);
};

static expr_t *accept_expr2(scanner_t *Scanner, int Precedence = 0);

#define INFIX(SYMBOL, PRECEDENCE)\
	if (Scanner->parse(tk ## SYMBOL)) {\
		expr_t *Symbol = new const_expr_t(Scanner->Token.LineNo, $ ## SYMBOL);\
		Term->Next = accept_expr2(Scanner, PRECEDENCE + 1);\
		Term = new invoke_expr_t(Scanner->Token.LineNo, Symbol, Term);\
		goto start;\
	};

static expr_t *parse_expr2(scanner_t *Scanner, int Precedence = 0) {
	if (Scanner->parse(tkNOT)) return new cond_expr_t(Scanner->Token.LineNo,
		accept_expr2(Scanner),
		new back_expr_t(Scanner->Token.LineNo),
		new const_expr_t(Scanner->Token.LineNo, Std$Object$Nil)
	);
	expr_t *Term = parse_term(Scanner);
	if (Term == 0) return 0;
	start: switch(Precedence) {
	case 0:
		if (Scanner->parse(tkAND)) {
			Term = new right_expr_t(Scanner->Token.LineNo, Term, accept_expr2(Scanner, 1));
			goto start;
		};
	case 1:
		if (Scanner->parse(tkBACKSLASH)) {
			Term = new left_expr_t(Scanner->Token.LineNo, Term, accept_expr2(Scanner, 2));
			goto start;
		};
	case 2:
		if (Scanner->parse(tkEXACTLY)) {
			Term = new comp_expr_t(Scanner->Token.LineNo, true, Term, accept_expr2(Scanner, 3));
			goto start;
		};
		if (Scanner->parse(tkNOTEXACTLY)) {
			Term = new comp_expr_t(Scanner->Token.LineNo, false, Term, accept_expr2(Scanner, 3));
			goto start;
		};
	case 3:
		INFIX(EQUAL, 3);
		INFIX(NOTEQ, 3);
		INFIX(LESS, 3);
		INFIX(GREATER, 3);
		INFIX(LSEQ, 3);
		INFIX(GREQ, 3);
		INFIX(IN, 3);
		INFIX(SUBTYPE, 3);
	case 4:
		INFIX(PLUS, 4);
		INFIX(MINUS, 4);
	case 5:
		INFIX(MULTIPLY, 5);
		INFIX(DIVIDE, 5);
		INFIX(MODULO, 5);
	case 6:
		INFIX(POWER, 6);
	case 7:
		INFIX(PARTIAL, 7);
		INFIX(QUERY, 7);
	case 8:
		if (Scanner->parse(tkOR)) {
			expr_t *Last = accept_term(Scanner);
			Term->Next = Last;
			while (Scanner->parse(tkOR)) {
				Last->Next = accept_term(Scanner);
				Last = Last->Next;
			};
			Term = new sequence_expr_t(Scanner->Token.LineNo, Term);
			goto start;
		};
		if (Scanner->parse(tkEXCLAIM)) {
			expr_t *Last = accept_term(Scanner);
			Term->Next = Last;
			while (Scanner->parse(tkEXCLAIM)) {
				Last->Next = accept_term(Scanner);
				Last = Last->Next;
			};
			Term = new parallel_expr_t(Scanner->Token.LineNo, Term);
			goto start;
		};
	case 9:
		if (Scanner->parse(tkOF)) {
			Term = new limit_expr_t(Scanner->Token.LineNo, Term, accept_term(Scanner));
			goto start;
		};
	case 10:
		if (Scanner->parse(tkSKIP)) {
			Term = new skip_expr_t(Scanner->Token.LineNo, Term, accept_term(Scanner));
			goto start;
		};
	};
	return Term;
};

static expr_t *accept_expr2(scanner_t *Scanner, int Precedence) {
	expr_t *Expr = parse_expr2(Scanner, Precedence);
	if (Expr) return Expr;
	Scanner->raise_error(Scanner->Token.LineNo, "Error: expected expression not %s\n", Tokens[Scanner->NextToken.Type]);
};

expr_t *accept_expr(scanner_t *Scanner);

static expr_t *parse_expr(scanner_t *Scanner) {
	expr_t *Expr = parse_expr2(Scanner);
	if (Expr == 0) return 0;
	//if (Scanner->parse(tkEXCLAIM)) return new parallel_expr_t(Scanner->Token.LineNo, Expr, accept_expr(Scanner));
	if (Scanner->parse(tkASSIGN)) return new assign_expr_t(Scanner->Token.LineNo, Expr, accept_expr(Scanner));
	if (Scanner->parse(tkTHEN)) {
		expr_t *Expr2 = accept_expr2(Scanner);
		if (Scanner->parse(tkELSE)) return new cond_expr_t(Scanner->Token.LineNo, Expr, Expr2, accept_expr(Scanner));
		return new cond_expr_t(Scanner->Token.LineNo, Expr, Expr2, 0);
	};
	if (Scanner->parse(tkELSE)) return new cond_expr_t(Scanner->Token.LineNo, Expr, 0, accept_expr(Scanner));
	return Expr;
};

static expr_t *accept_expr(scanner_t *Scanner) {
	expr_t *Expr = parse_expr(Scanner);
	if (Expr) return Expr;
	Scanner->raise_error(Scanner->Token.LineNo, "Error: expected expression not %s\n", Tokens[Scanner->NextToken.Type]);
};

static module_expr_t *accept_globalstatement(scanner_t *Scanner);

static module_expr_t *accept_globalvar(scanner_t *Scanner) {
	module_expr_t::globalvar_t *Var = new module_expr_t::globalvar_t;
	Var->LineNo = Scanner->Token.LineNo;
	Scanner->accept(tkIDENT);
	Var->Name = Scanner->Token.Ident;
	Var->Exported = Scanner->parse(tkEXCLAIM);
	if (Scanner->parse(tkASSIGN)) {
		ident_expr_t *Ident = new ident_expr_t(Scanner->Token.LineNo, Var->Name);
		assign_expr_t *Assign = new assign_expr_t(Scanner->Token.LineNo, Ident, accept_expr(Scanner));
		if (Scanner->parse(tkCOMMA)) {
			module_expr_t *Module = accept_globalvar(Scanner);
			Var->Next = Module->Vars;
			Module->Vars = Var;
			Assign->Next = Module->Body;
			Module->Body = Assign;
			return Module;
		} else {
			Scanner->accept(tkSEMICOLON);
			module_expr_t *Module = accept_globalstatement(Scanner);
			Var->Next = Module->Vars;
			Module->Vars = Var;
			Assign->Next = Module->Body;
			Module->Body = Assign;
			return Module;
		};
	} else if (Scanner->parse(tkLPAREN)) {
		func_expr_t::parameter_t *Parameters = accept_parameters(Scanner);
		Scanner->accept(tkRPAREN);
		func_expr_t *Func = new func_expr_t(Scanner->Token.LineNo, Parameters, accept_expr(Scanner));
		ident_expr_t *Ident = new ident_expr_t(Scanner->Token.LineNo, Var->Name);
		assign_expr_t *Assign = new assign_expr_t(Scanner->Token.LineNo, Ident, Func);
		if (Scanner->parse(tkCOMMA)) {
			module_expr_t *Module = accept_globalvar(Scanner);
			Var->Next = Module->Vars;
			Module->Vars = Var;
			Assign->Next = Module->Body;
			Module->Body = Assign;
			return Module;
		} else {
			Scanner->accept(tkSEMICOLON);
			module_expr_t *Module = accept_globalstatement(Scanner);
			Var->Next = Module->Vars;
			Module->Vars = Var;
			Assign->Next = Module->Body;
			Module->Body = Assign;
			return Module;
		};
	} else {
		if (Scanner->parse(tkCOMMA)) {
			module_expr_t *Module = accept_globalvar(Scanner);
			Var->Next = Module->Vars;
			Module->Vars = Var;
			return Module;
		} else {
			Scanner->accept(tkSEMICOLON);
			module_expr_t *Module = accept_globalstatement(Scanner);
			Var->Next = Module->Vars;
			Module->Vars = Var;
			return Module;
		};
	};
};

static module_expr_t *accept_globaldef(scanner_t *Scanner) {
	module_expr_t::globaldef_t *Def = new module_expr_t::globaldef_t;
	Def->LineNo = Scanner->Token.LineNo;
	Scanner->accept(tkIDENT);
	Def->Name = Scanner->Token.Ident;
	Def->Exported = Scanner->parse(tkEXCLAIM);
	if (Scanner->parse(tkLPAREN)) {
		func_expr_t::parameter_t *Parameters = accept_parameters(Scanner);
		Scanner->accept(tkRPAREN);
		Def->Value = new func_expr_t(Scanner->Token.LineNo, Parameters, accept_expr(Scanner));
	} else {
		Scanner->accept(tkASSIGN);
		Def->Value = accept_expr(Scanner);
	};
	module_expr_t *Module;
	if (Scanner->parse(tkCOMMA)) {
		Module = accept_globaldef(Scanner);
	} else {
		Scanner->accept(tkSEMICOLON);
		Module = accept_globalstatement(Scanner);
	};
	Def->Next = Module->Defs;
	Module->Defs = Def;
	return Module;
};

static module_expr_t::globalimp_t::uselist_t *accept_globalimp_uses(scanner_t *Scanner) {
	module_expr_t::globalimp_t::uselist_t *Uses = new module_expr_t::globalimp_t::uselist_t;
	Scanner->accept(tkIDENT);
	Uses->LineNo = Scanner->Token.LineNo;
	Uses->Name = Scanner->Token.Ident;
	if (Scanner->parse(tkCOMMA)) Uses->Next = accept_globalimp_uses(Scanner);
	return Uses;
};

static module_expr_t::globalimp_t::path_t *accept_globalimp_path(scanner_t *Scanner) {
	module_expr_t::globalimp_t::path_t *Path = new module_expr_t::globalimp_t::path_t;
	Scanner->accept(tkIDENT);
	Path->Part = Scanner->Token.Ident;
	if (Scanner->parse(tkDOT)) Path->Next = accept_globalimp_path(Scanner);
	return Path;
};

static module_expr_t *accept_globalimp(scanner_t *Scanner) {
	module_expr_t::globalimp_t *Imp = new module_expr_t::globalimp_t;
	Imp->LineNo = Scanner->Token.LineNo;
	Imp->Relative = Scanner->parse(tkDOT);
	Imp->Path = accept_globalimp_path(Scanner);
	if (Scanner->parse(tkAS)) {
		Scanner->accept(tkIDENT);
		Imp->Alias = Scanner->Token.Ident;
	} else {
		module_expr_t::globalimp_t::path_t *Path = Imp->Path;
		while (Path->Next) Path = Path->Next;
		Imp->Alias = Path->Part;
	};
	if (Scanner->parse(tkEXCLAIM)) Imp->Exported = true;
	if (Scanner->parse(tkUSE)) Imp->Uses = accept_globalimp_uses(Scanner);
	if (Scanner->parse(tkCOMMA)) {
		module_expr_t *Module = accept_globalimp(Scanner);
		Imp->Next = Module->Imps;
		Module->Imps = Imp;
		return Module;
	} else {
		Scanner->accept(tkSEMICOLON);
		module_expr_t *Module = accept_globalstatement(Scanner);
		Imp->Next = Module->Imps;
		Module->Imps = Imp;
		return Module;
	};
};

static module_expr_t *accept_globalstatement(scanner_t *Scanner) {
	if (Scanner->parse(tkIMP)) return accept_globalimp(Scanner);
	if (Scanner->parse(tkDEF)) return accept_globaldef(Scanner);
	if (Scanner->parse(tkVAR)) return accept_globalvar(Scanner);
	expr_t *Expr = parse_expr(Scanner);
	if (Expr) {
		Scanner->accept(tkSEMICOLON);
		module_expr_t *Module = accept_globalstatement(Scanner);
		Expr->Next = Module->Body;
		Module->Body = Expr;
		return Module;
	};
	return new module_expr_t;
};

module_expr_t *accept_module(scanner_t *Scanner, Sys$Module_t *Module) {
	bool Nested = (Module == 0);
	const char *Name;
	if (Nested) {
		Module = Sys$Module$new();
		Name = "<anonymous>";
	} else {
		Scanner->accept(tkMOD);
		Scanner->accept(tkIDENT);
		Name = Scanner->Token.Ident;
		Scanner->accept(tkSEMICOLON);
	};

	int LineNo = Scanner->Token.LineNo;
	module_expr_t *Expr = accept_globalstatement(Scanner);
	Expr->LineNo = LineNo;
	Expr->Module = Module;
	Expr->Name = Name;

	Scanner->accept(tkEND);
	if (!Nested) {
		Scanner->accept(tkIDENT);
		Scanner->accept(tkDOT);
	};

	return Expr;
};

module_expr_t *parse_module(scanner_t *Scanner, Sys$Module_t *Module) {
	const char *Name;
	if (Scanner->parse(tkMOD)) {
		Scanner->accept(tkIDENT);
		Name = Scanner->Token.Ident;
		Scanner->accept(tkSEMICOLON);

		int LineNo = Scanner->Token.LineNo;
		module_expr_t *Expr = accept_globalstatement(Scanner);
		Expr->LineNo = LineNo;
		Expr->Module = Module;
		Expr->Name = Name;

		Scanner->accept(tkEND);
		Scanner->accept(tkIDENT);
		Scanner->accept(tkDOT);
		return Expr;
	} else {
		return 0;
	};
};

static command_expr_t *accept_commandvar(scanner_t *Scanner) {
	command_expr_t::globalvar_t *Var = new command_expr_t::globalvar_t;
	Var->LineNo = Scanner->Token.LineNo;
	Scanner->accept(tkIDENT);
	Var->Name = Scanner->Token.Ident;
	if (Scanner->parse(tkASSIGN)) {
		ident_expr_t *Ident = new ident_expr_t(Scanner->Token.LineNo, Var->Name);
		assign_expr_t *Assign = new assign_expr_t(Scanner->Token.LineNo, Ident, accept_expr(Scanner));
		if (Scanner->parse(tkCOMMA)) {
			command_expr_t *Module = accept_commandvar(Scanner);
			Var->Next = Module->Vars;
			Module->Vars = Var;
			Assign->Next = Module->Body;
			Module->Body = Assign;
			return Module;
		} else {
			Scanner->accept(tkSEMICOLON);
			command_expr_t *Module = new command_expr_t;
			Module->Vars = Var;
			Module->Body = Assign;
			return Module;
		};
	} else if (Scanner->parse(tkLPAREN)) {
		func_expr_t::parameter_t *Parameters = accept_parameters(Scanner);
		Scanner->accept(tkRPAREN);
		func_expr_t *Func = new func_expr_t(Scanner->Token.LineNo, Parameters, accept_expr(Scanner));
		ident_expr_t *Ident = new ident_expr_t(Scanner->Token.LineNo, Var->Name);
		assign_expr_t *Assign = new assign_expr_t(Scanner->Token.LineNo, Ident, Func);
		if (Scanner->parse(tkCOMMA)) {
			command_expr_t *Module = accept_commandvar(Scanner);
			Var->Next = Module->Vars;
			Module->Vars = Var;
			Assign->Next = Module->Body;
			Module->Body = Assign;
			return Module;
		} else {
			Scanner->accept(tkSEMICOLON);
			command_expr_t *Module = new command_expr_t;
			Module->Vars = Var;
			Module->Body = Assign;
			return Module;
		};
	} else {
		if (Scanner->parse(tkCOMMA)) {
			command_expr_t *Module = accept_commandvar(Scanner);
			Var->Next = Module->Vars;
			Module->Vars = Var;
			return Module;
		} else {
			Scanner->accept(tkSEMICOLON);
			command_expr_t *Module = new command_expr_t;
			Module->Vars = Var;
			return Module;
		};
	};
};

static command_expr_t *accept_commanddef(scanner_t *Scanner) {
	command_expr_t::globaldef_t *Def = new command_expr_t::globaldef_t;
	Def->LineNo = Scanner->Token.LineNo;
	Scanner->accept(tkIDENT);
	Def->Name = Scanner->Token.Ident;
	if (Scanner->parse(tkASSIGN)) {
		Def->Value = accept_expr(Scanner);
	} else if (Scanner->parse(tkLPAREN)) {
		func_expr_t::parameter_t *Parameters = accept_parameters(Scanner);
		Scanner->accept(tkRPAREN);
		Def->Value = new func_expr_t(Scanner->Token.LineNo, Parameters, accept_expr(Scanner));
	};
	if (Scanner->parse(tkCOMMA)) {
		command_expr_t *Module = accept_commanddef(Scanner);
		Def->Next = Module->Defs;
		Module->Defs = Def;
		return Module;
	} else {
		Scanner->accept(tkSEMICOLON);
		command_expr_t *Module = new command_expr_t;
		Module->Defs = Def;
		return Module;
	};
};

static command_expr_t::globalimp_t::uselist_t *accept_commandimp_uses(scanner_t *Scanner) {
	command_expr_t::globalimp_t::uselist_t *Uses = new command_expr_t::globalimp_t::uselist_t;
	Scanner->accept(tkIDENT);
	Uses->LineNo = Scanner->Token.LineNo;
	Uses->Name = Scanner->Token.Ident;
	if (Scanner->parse(tkCOMMA)) Uses->Next = accept_commandimp_uses(Scanner);
	return Uses;
};

static command_expr_t::globalimp_t::path_t *accept_commandimp_path(scanner_t *Scanner) {
	command_expr_t::globalimp_t::path_t *Path = new command_expr_t::globalimp_t::path_t;
	Scanner->accept(tkIDENT);
	Path->Part = Scanner->Token.Ident;
	if (Scanner->parse(tkDOT)) Path->Next = accept_commandimp_path(Scanner);
	return Path;
};

static command_expr_t *accept_commandimp(scanner_t *Scanner) {
	command_expr_t::globalimp_t *Imp = new command_expr_t::globalimp_t;
	Imp->LineNo = Scanner->Token.LineNo;
	Imp->Relative = Scanner->parse(tkDOT);
	Imp->Path = accept_commandimp_path(Scanner);
	if (Scanner->parse(tkAS)) {
		Scanner->accept(tkIDENT);
		Imp->Alias = Scanner->Token.Ident;
	} else {
		command_expr_t::globalimp_t::path_t *Path = Imp->Path;
		while (Path->Next) Path = Path->Next;
		Imp->Alias = Path->Part;
	};
	if (Scanner->parse(tkUSE)) Imp->Uses = accept_commandimp_uses(Scanner);
	if (Scanner->parse(tkCOMMA)) {
		command_expr_t *Module = accept_commandimp(Scanner);
		Imp->Next = Module->Imps;
		Module->Imps = Imp;
		return Module;
	} else {
		Scanner->accept(tkSEMICOLON);
		command_expr_t *Module = new command_expr_t;
		Module->Imps = Imp;
		return Module;
	};
};

command_expr_t *accept_command(scanner_t *Scanner) {
	if (Scanner->parse(tkIMP)) return accept_commandimp(Scanner);
	if (Scanner->parse(tkDEF)) return accept_commanddef(Scanner);
	if (Scanner->parse(tkVAR)) return accept_commandvar(Scanner);
	expr_t *Expr = accept_expr(Scanner);
	Scanner->accept(tkSEMICOLON);
	command_expr_t *Module = new command_expr_t;
	Module->Body = Expr;
	return Module;
};

