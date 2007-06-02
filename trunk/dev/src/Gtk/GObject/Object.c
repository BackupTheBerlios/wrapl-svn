#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/GObject/Closure.h>
#include <Gtk/GObject/Value.h>
#include <Riva.h>

SYMBOL($true, "true");

TYPE(T);

static GQuark RivaQuark;

inline Gtk$GObject$Object_t *_new(GObject *Handle, Std$Type_t *Type) {
	Gtk$GObject$Object_t *Object = new(Gtk$GObject$Object_t);
	Object->Type = Type;
	Object->Handle = Handle;
	g_object_set_qdata(Handle, RivaQuark, Object);
	return Object;
};

Gtk$GObject$Object_t *_to_riva(GObject *Handle) {
	Gtk$GObject$Object_t *Object = g_object_get_qdata(Handle, RivaQuark);
	if (Object) return Object;
	Std$Type_t *Type = Gtk$GObject$Type$to_riva(G_OBJECT_TYPE(Handle));
	if (Type == 0) return 0;
	return _new(Handle, Type);
};

METHOD("connect", TYP, T, TYP, Std$String$T, TYP, Gtk$GObject$Closure$T) {
	Gtk$GObject$Object_t *Object = Args[0].Val;
	const char *Signal = Std$String$flatten(Args[1].Val);
	Gtk$GObject$Closure_t *Closure = Args[2].Val;
	gboolean After = (Count > 3) && (Args[3].Val == $true);
	g_signal_connect_closure(Object->Handle, Signal, Closure->Handle, After);
	Result->Arg = Args[0];
	return SUCCESS;
};

METHOD("connect", TYP, T, TYP, Std$String$T, TYP, Std$Function$T) {
	Gtk$GObject$Object_t *Object = Args[0].Val;
	const char *Signal = Std$String$flatten(Args[1].Val);
	Gtk$GObject$Closure_t *Closure = Gtk$GObject$Closure$new(Args[2].Val);
	gboolean After = (Count > 3) && (Args[3].Val == $true);
	g_signal_connect_closure(Object->Handle, Signal, Closure->Handle, After);
	Result->Arg = Args[0];
	return SUCCESS;
};

METHOD("get", TYP, T, TYP, Std$String$T) {
	Gtk$GObject$Object_t *Object = Args[0].Val;
	const char *Prop = Std$String$flatten(Args[1].Val);
	GValue Value[1] = {{0,}};
	g_object_get_property(Object->Handle, Prop, Value);
	Result->Val = Gtk$GObject$Value$to_riva(Value);
	return SUCCESS;
};

METHOD("set", TYP, T, TYP, Std$String$T, ANY) {
	Gtk$GObject$Object_t *Object = Args[0].Val;
	const char *Prop = Std$String$flatten(Args[1].Val);
	GValue Value[1] = {{0,}};
	Gtk$GObject$Value$to_gtk(Args[2].Val, Value);
	g_object_set_property(Object->Handle, Prop, Value);
	Result->Arg = Args[0];
	return SUCCESS;
};

void __init(Riva$Module_t *Module) {
	RivaQuark = g_quark_from_static_string("<<riva>>");
};
