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

GLOBAL_FUNCTION(Compile, 2) {
	IO$Stream_t *Source = Args[0].Val;
	IO$Stream_t *Output = Args[1].Val;
	scanner_t *Scanner = new scanner_t(Source);
	if (setjmp(Scanner->Error.Handler)) {
		errormessage_t *Error = new errormessage_t;
		Error->Type = ErrorMessageT;
		Error->LineNo = Scanner->Error.LineNo;
		Error->Message = Scanner->Error.Message;
		Result->Val = (Std$Object_t *)Error;
		return MESSAGE;
	};
	module_expr_t *Expr = accept_module(Scanner, Sys$Module$new());
#ifdef PARSER_LISTING
	Expr->print(0);
#endif
	compiler_t *Compiler = new compiler_t(Output);
	if (setjmp(Compiler->Error.Handler)) {
		errormessage_t *Error = new errormessage_t;
		Error->Type = ErrorMessageT;
		Error->LineNo = Compiler->Error.LineNo;
		Error->Message = Compiler->Error.Message;
		Result->Val = (Std$Object_t *)Error;
		return MESSAGE;
	};
	Expr->compile(Compiler);
	return SUCCESS;
};

extern "C" void __init(Riva$Module_t *Module);
void __init(Riva$Module_t *Module) {
	detect_cpu_features();
};
