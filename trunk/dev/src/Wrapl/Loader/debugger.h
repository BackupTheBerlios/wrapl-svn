#ifndef DEBUGGER_H
#define DEBUGGER_H

struct debugger_t {
	void *(*add_module)(const char *Name);
	void (*add_line)(void *Module, const char *Line);
	void (*add_global)(void *Module, const char *Name, Std$Object_t **Address);
	void *(*add_function)(void *Module, int LineNo);
	void (*add_breakpoints)(void *Function, int MaxLine);
	void *(*add_scope)(void *Function, int Index);
	void (*add_local)(void *Scope, const char *Name, int Index);
	
	void (*enter_function)(void *Function, void *Frame);
	void (*exit_function)(void);
	void (*enter_scope)(void *Scope, Std$Object_t **Address);
	void (*exit_scope)(void);
	void (*break_line)(int LineNo);
};

extern debugger_t *Debugger;

#endif
