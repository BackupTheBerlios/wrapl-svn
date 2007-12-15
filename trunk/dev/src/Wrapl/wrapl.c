#include <Riva.h>
#include <Std.h>
#include <IO/File.h>
#include <string.h>
#include <Sys/Module.h>

#include "parser.h"
#include "compiler.h"
#include "missing.h"
#include "system.h"
#include "assembler.h"

static int wrapl_load(Riva$Module_t *Module, const char *Path) {
	char *LoadPath = 0;
	for (int I = strlen(Path) - 1; I >= 0; --I) {
		if (Path[I] == PATHCHR) {
			memcpy(LoadPath = (char *)Riva$Memory$alloc_atomic(I + 2), Path, I + 1);
			LoadPath[I + 1] = 0;
			break;
		};
	};
	Riva$Module$set_path(Module, LoadPath);
	Sys$Module_t *Module0 = new Sys$Module_t;
	Module0->Type = Sys$Module$T;
	Module0->Handle = Module;
	IO$Stream_t *Source = (IO$Stream_t *)IO$File$open(Path, IO$File$OPENREAD | IO$File$OPENTEXT);
	IO$Stream_t_methods *Methods = (IO$Stream_t_methods *)Util$TypeTable$get(IO$Stream$T_Methods, Source->Type);
	scanner_t *Scanner = new scanner_t(Source);
	if (setjmp(Scanner->Error.Handler)) {
		Methods->close(Source);
		printf("%s(%d): %s\n", Path, Scanner->Error.LineNo, Scanner->Error.Message);
		return 0;
	};
	module_expr_t *Expr;
	if (Scanner->parse(tkHASH) || Scanner->parse(tkAT)) {
		Scanner->flush();
		Expr = parse_module(Scanner, Module0);
		Methods->close(Source);
		if (Expr == 0) return 0;
	} else {
		Expr = accept_module(Scanner, Module0);
		Methods->close(Source);
	};
#ifdef PARSER_LISTING
	Expr->print(0);
#endif
	compiler_t *Compiler = new compiler_t();
	if (setjmp(Compiler->Error.Handler)) {
		printf("%s(%d): %s\n", Path, Compiler->Error.LineNo, Compiler->Error.Message);
		return 0;
	};
	Expr->compile(Compiler);
	return 1;
};

struct session_t {
	Std$Type_t *Type;
	scanner_t *Scanner;
	compiler_t *Compiler;
};

TYPE(SessionT);
TYPE(ErrorMessageT);

struct errormessage_t {
	Std$Type_t *Type;
	int LineNo;
	const char *Message;
};

METHOD("@", TYP, ErrorMessageT, VAL, Std$String$T) {
	errormessage_t *Error = (errormessage_t *)Args[0].Val;
	char *Buffer;
	Result->Val = (Std$Object_t *)Std$String$new_length(Buffer, asprintf(&Buffer, "(%d): %s", Error->LineNo, Error->Message));
	return SUCCESS;
};

GLOBAL_FUNCTION(SessionNew, 1) {
	session_t *Session = new session_t;
	Session->Type = SessionT;
	Session->Scanner = new scanner_t(Args[0].Val);
	Session->Compiler = new compiler_t();
	Result->Val = (Std$Object_t *)Session;
	return SUCCESS;
};

GLOBAL_FUNCTION(SessionEval, 1) {
	session_t *Session = (session_t *)Args[0].Val;
	if (setjmp(Session->Scanner->Error.Handler)) {
		Session->Scanner->flush();
		errormessage_t *Error = new errormessage_t;
		Error->Type = ErrorMessageT;
		Error->LineNo = Session->Scanner->Error.LineNo;
		Error->Message = Session->Scanner->Error.Message;
		Result->Val = (Std$Object_t *)Error;
		return MESSAGE;
	};
	command_expr_t *Command = accept_command(Session->Scanner);
#ifdef PARSER_LISTING
	Command->print(0);
#endif
	if (setjmp(Session->Compiler->Error.Handler)) {
		errormessage_t *Error = new errormessage_t;
		Error->Type = ErrorMessageT;
		Error->LineNo = Session->Compiler->Error.LineNo;
		Error->Message = Session->Compiler->Error.Message;
		Result->Val = (Std$Object_t *)Error;
		return MESSAGE;
	};
	return Command->compile(Session->Compiler, Result);
};

GLOBAL_FUNCTION(SessionLine, 1) {
	session_t *Session = (session_t *)Args[0].Val;
	Result->Val = (Std$Object_t *)Std$String$new(Session->Scanner->NextChar);
	Session->Scanner->NextChar = "";
	return SUCCESS;
};

GLOBAL_FUNCTION(SessionDef, 3) {
	session_t *Session = (session_t *)Args[0].Val;
	operand_t *Operand = new operand_t;
	Operand->Type = operand_t::CNST;
	Operand->Value = Args[2].Val;
	Session->Compiler->declare(Std$String$flatten((Std$String_t *)Args[1].Val), Operand);
	return SUCCESS;
};

GLOBAL_FUNCTION(SessionVar, 3) {
	session_t *Session = (session_t *)Args[0].Val;
	operand_t *Operand = new operand_t;
	Operand->Type = operand_t::GVAR;
	Operand->Address = Args[2].Ref;
	Session->Compiler->declare(Std$String$flatten((Std$String_t *)Args[1].Val), Operand);
	return SUCCESS;
};

extern "C" void __init(Riva$Module_t *Module);
void __init(Riva$Module_t *Module) {
	Riva$Module$add_loader(".wrapl", wrapl_load);
	detect_cpu_features();
};
