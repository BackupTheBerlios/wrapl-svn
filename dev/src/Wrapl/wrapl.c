#include <Riva.h>
#include <Lang.h>
#include <IO/File.h>
#include <string.h>
#include <Sys/Module.h>

#include "parser.h"
#include "compiler.h"

static int wrapl_load(Riva$Module_t *Module, const char *Path) {
	char *LoadPath;
	for (int I = strlen(Path) - 1; I >= 0; --I) {
		if (Path[I] == '/') {
			memcpy(LoadPath = (char *)Riva$Memory$alloc_atomic(I + 2), Path, I + 1);
			break;
		};
	};
	Riva$Module$set_path(Module, LoadPath);
	Sys$Module_t *Module0 = new Sys$Module_t;
	Module0->Type = Sys$Module$T;
	Module0->Handle = Module;

	IO$Stream_t *Source = (IO$Stream_t *)IO$File$open(Path, IO$File$OPENREAD | IO$File$OPENTEXT);
	scanner_t *Scanner = new scanner_t(Source);
	if (setjmp(Scanner->Error.Handler)) {
		printf("%s(%d): %s\n", Path, Scanner->Error.LineNo, Scanner->Error.Message);
		return 0;
	};
	module_expr_t *Expr = accept_module(Scanner, Module0);
	//Expr->print(0);
	compiler_t *Compiler = new compiler_t();
	if (setjmp(Compiler->Error.Handler)) {
		printf("%s(%d): %s\n", Path, Compiler->Error.LineNo, Compiler->Error.Message);
		return 0;
	};
	Expr->compile(Compiler);
	return 1;
};

struct session_t {
	Lang$Type_t *Type;
	scanner_t *Scanner;
	compiler_t *Compiler;
};

TYPE(SessionT);
TYPE(ErrorMessageT);

struct errormessage_t {
	Lang$Type_t *Type;
	int LineNo;
	const char *Message;
};

METHOD("@", TYP, ErrorMessageT, VAL, Lang$String$T) {
	errormessage_t *Error = (errormessage_t *)Args[0].Val;
	char *Buffer;
	Result->Val = (Lang$Object_t *)Lang$String$new_length(Buffer, asprintf(&Buffer, "(%d): %s", Error->LineNo, Error->Message));
	return SUCCESS;
};

GLOBAL_FUNCTION(SessionNew, 1) {
	session_t *Session = new session_t;
	Session->Type = SessionT;
	Session->Scanner = new scanner_t(Args[0].Val);
	Session->Compiler = new compiler_t();
	Result->Val = (Lang$Object_t *)Session;
	return SUCCESS;
};

METHOD("eval", TYP, SessionT) {
	session_t *Session = (session_t *)Args[0].Val;
	if (setjmp(Session->Scanner->Error.Handler)) {
		errormessage_t *Error = new errormessage_t;
		Error->Type = ErrorMessageT;
		Error->LineNo = Session->Scanner->Error.LineNo;
		Error->Message = Session->Scanner->Error.Message;
		Result->Val = (Lang$Object_t *)Error;
		return MESSAGE;
	};
	command_expr_t *Command = accept_command(Session->Scanner);
	//Command->print(0);
	if (setjmp(Session->Compiler->Error.Handler)) {
		errormessage_t *Error = new errormessage_t;
		Error->Type = ErrorMessageT;
		Error->LineNo = Session->Compiler->Error.LineNo;
		Error->Message = Session->Compiler->Error.Message;
		Result->Val = (Lang$Object_t *)Error;
		return MESSAGE;
	};
	return Command->compile(Session->Compiler, Result);
};

extern "C" void __init(Riva$Module_t *Module);
void __init(Riva$Module_t *Module) {
	Riva$Module$export(Module, "Version", 0, Lang$String$new("0.2.1"));
	Riva$Module$add_loader(".wrapl", wrapl_load);
};
