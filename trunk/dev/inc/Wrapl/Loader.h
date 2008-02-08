#ifndef WRAPL_LOADER_H
#define WRAPL_LOADER_H

#include <Std/Object.h>

#define RIVA_MODULE Wrapl$Loader
#include <Riva-Header.h>

typedef struct Wrapl$Loader_debugger {
	void *(*add_module)(const char *Name);
	void (*add_line)(void *Module, const char *Line);
	void (*add_global)(void *Module, const char *Name, Std$Object_t **Address);
	void *(*add_function)(void *Module, int LineNo);
	void (*add_breakpoints)(void *Function, int MaxLine);
	void *(*add_scope)(void *Function, int Index);
	void (*add_local)(void *Scope, const char *Name, int Index);
	
	void (*enter_function)(void *Function, void *Frame);
	void (*exit_function)(void *Function);
	void (*enter_scope)(void *Scope, Std$Object_t **Address);
	void (*exit_scope)(void);
	void (*break_line)(int LineNo);
} Wrapl$Loader_debugger;

RIVA_CFUN(void, enable_debug, const Wrapl$Loader_debugger *);
RIVA_CFUN(void, disable_debug, void);

#undef RIVA_MODULE

#endif
