#include <Gtk/GObject/Closure.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Value.h>
#include <Riva.h>

TYPE(T);

typedef struct closure_t {
	GClosure Parent;
	Std$Object_t *Function;
	Gtk$GObject$Closure_t *Closure;
} closure_t;

static void __marshal(closure_t *Closure, GValue *Result, guint NoOfArgs, const GValue *Args, gpointer Hint, gpointer Data) {
	Std$Function_argument Args0[NoOfArgs];
	for (guint I = 0; I < NoOfArgs; ++I) Args0[I].Val = Gtk$GObject$Value$to_riva(Args + I);
	Std$Function_result Result0;
	if (Std$Function$invoke(Closure->Function, NoOfArgs, &Result0, Args0) >= FAILURE) return;
	if (Result) Gtk$GObject$Value$to_gtk(Result0.Val, Result);
};

Gtk$GObject$Object_t *_new(Std$Object_t *Function) {
	closure_t *Handle = g_closure_new_simple(sizeof(closure_t), 0);
	Handle->Function = Function;
	g_closure_set_marshal(Handle, __marshal);
	Gtk$GObject$Closure_t *Closure = new(Gtk$GObject$Closure_t);
	Closure->Type = T;
	Closure->Handle = Handle;
	Handle->Closure = Closure;
	return Closure;
};

GLOBAL_FUNCTION(New, 1) {
	Result->Val = _new(Args[0].Val);
	return SUCCESS;
};
