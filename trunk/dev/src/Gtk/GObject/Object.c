#include <Gtk/GObject/Init.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/GObject/Closure.h>
#include <Gtk/GObject/Value.h>
#include <Riva.h>

SYMBOL($true, "true");

TYPE(T);

Gtk$GObject$Object_t Nil[] = {{T, 0}};

static void finalize(Gtk$GObject$Object_t *Object, void *Data) {
	g_object_unref(Object->Handle);
};

static GQuark RivaQuark;

inline Gtk$GObject$Object_t *_new(GObject *Handle, Std$Type_t *Type) {
	Gtk$GObject$Object_t *Object = new(Gtk$GObject$Object_t);
	Object->Type = Type;
	Object->Handle = Handle;
	g_object_set_qdata(Handle, RivaQuark, Object);	
//	g_object_ref_sink(Handle);
//	Riva$Memory$register_finalizer(Object, finalize, 0, 0, 0);
	return Object;
};

Gtk$GObject$Object_t *_to_riva(GObject *Handle) {
	if (Handle == 0) return Nil;
	Gtk$GObject$Object_t *Object = g_object_get_qdata(Handle, RivaQuark);
	if (Object) return Object;
	Std$Type_t *Type = Gtk$GObject$Type$to_riva(G_OBJECT_TYPE(Handle));
	if (Type == 0) return 0;
	return _new(Handle, Type);
};

METHOD("Connect", TYP, T, TYP, Std$String$T, TYP, Gtk$GObject$Closure$T) {
	Gtk$GObject$Object_t *Object = Args[0].Val;
	const char *Signal = Std$String$flatten(Args[1].Val);
	Gtk$GObject$Closure_t *Closure = Args[2].Val;
	gboolean After = (Count > 3) && (Args[3].Val == $true);
	g_signal_connect_closure(Object->Handle, Signal, Closure->Handle, After);
	Result->Arg = Args[0];
	return SUCCESS;
};

METHOD("Connect", TYP, T, TYP, Std$String$T, TYP, Std$Function$T) {
	Gtk$GObject$Object_t *Object = Args[0].Val;
	const char *Signal = Std$String$flatten(Args[1].Val);
	Gtk$GObject$Closure_t *Closure = Gtk$GObject$Closure$from_val(Args[2].Val);
	gboolean After = (Count > 3) && (Args[3].Val == $true);
	g_signal_connect_closure(Object->Handle, Signal, Closure->Handle, After);
	Result->Arg = Args[0];
	return SUCCESS;
};

METHOD("GetProperty", TYP, T, TYP, Std$String$T) {
	Gtk$GObject$Object_t *Object = Args[0].Val;
	const char *Prop = Std$String$flatten(Args[1].Val);
	GValue Value[1] = {{0,}};
	g_object_get_property(Object->Handle, Prop, Value);
	Result->Val = Gtk$GObject$Value$to_riva(Value);
	return SUCCESS;
};

METHOD("SetProperty", TYP, T, TYP, Std$String$T, ANY) {
	Gtk$GObject$Object_t *Object = Args[0].Val;
	const char *Prop = Std$String$flatten(Args[1].Val);
	GValue Value[1] = {{0,}};
	Gtk$GObject$Value$to_gtk(Args[2].Val, Value);
	g_object_set_property(Object->Handle, Prop, Value);
	return SUCCESS;
};

METHOD("GetData", TYP, T, TYP, Std$String$T) {
	Gtk$GObject$Object_t *Object = Args[0].Val;
	const char *Prop = Std$String$flatten(Args[1].Val);
	if (Result->Val = g_object_get_data(Object->Handle, Prop)) {
		return SUCCESS;
	} else {
		return FAILURE;
	};
};

METHOD("SetData", TYP, T, TYP, Std$String$T, ANY) {
	Gtk$GObject$Object_t *Object = Args[0].Val;
	const char *Prop = Std$String$flatten(Args[1].Val);
	g_object_set_data(Object->Handle, Prop, Args[2].Val);
	return SUCCESS;
};

METHOD("=", TYP, T, TYP, T) {
    Gtk$GObject$Object_t *A = Args[0].Val;
    Gtk$GObject$Object_t *B = Args[1].Val;
    if (A->Handle == B->Handle) {
        Result->Arg = Args[1];
        return SUCCESS;
    } else {
        return FAILURE;
    };
};

METHOD("~=", TYP, T, TYP, T) {
    Gtk$GObject$Object_t *A = Args[0].Val;
    Gtk$GObject$Object_t *B = Args[1].Val;
    if (A->Handle != B->Handle) {
        Result->Arg = Args[1];
        return SUCCESS;
    } else {
        return FAILURE;
    };
};

void __init(Riva$Module_t *Module) {
	RivaQuark = g_quark_from_static_string("<<riva>>");
};
