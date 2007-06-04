#include <Gtk/Gtk/Signal.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 8
#include <Gtk/Gtk/SignalRunType.h>
#include <Gtk/Gtk/Arg.h>
#include <Gtk/Gtk/SignalFunc.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Gtk/CallbackMarshal.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gtk/DestroyNotify.h>
#include <Gtk/Gtk/Object.h>
/***********************************/
GLOBAL_FUNCTION(CompatMatched, 5) {
	GtkObject * object = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkSignalFunc func = Gtk$Gtk$SignalFunc$new(Args[1].Val);
	void *data = ((Std$Address_t *)Args[2].Val)->Value;
	GSignalMatchType match = 0;
	int action = ((Std$Integer_smallt *)Args[4].Val)->Value;
	gtk_signal_compat_matched(object, func, data, match, action);
	return SUCCESS;
};

GLOBAL_FUNCTION(ConnectFull, 8) {
	GtkObject * object = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *name = Std$String$flatten(Args[1].Val);
	GtkSignalFunc func = Gtk$Gtk$SignalFunc$new(Args[2].Val);
	GtkCallbackMarshal unsupported = Gtk$Gtk$CallbackMarshal$new(Args[3].Val);
	void *data = ((Std$Address_t *)Args[4].Val)->Value;
	GtkDestroyNotify destroy_func = Gtk$Gtk$DestroyNotify$new(Args[5].Val);
	int object_signal = ((Std$Integer_smallt *)Args[6].Val)->Value;
	int after = ((Std$Integer_smallt *)Args[7].Val)->Value;
	int result = gtk_signal_connect_full(object, name, func, unsupported, data, destroy_func, object_signal, after);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(ConnectObjectWhileAlive, 4) {
	GtkObject * object = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *name = Std$String$flatten(Args[1].Val);
	GtkSignalFunc func = Gtk$Gtk$SignalFunc$new(Args[2].Val);
	GtkObject * alive_object = ((Gtk$GObject$Object_t *)Args[3].Val)->Handle;
	gtk_signal_connect_object_while_alive(object, name, func, alive_object);
	return SUCCESS;
};

GLOBAL_FUNCTION(ConnectWhileAlive, 5) {
	GtkObject * object = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *name = Std$String$flatten(Args[1].Val);
	GtkSignalFunc func = Gtk$Gtk$SignalFunc$new(Args[2].Val);
	void *func_data = ((Std$Address_t *)Args[3].Val)->Value;
	GtkObject * alive_object = ((Gtk$GObject$Object_t *)Args[4].Val)->Handle;
	gtk_signal_connect_while_alive(object, name, func, func_data, alive_object);
	return SUCCESS;
};

GLOBAL_FUNCTION(Emit, 3) {
	GtkObject * object = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int signal_id = ((Std$Integer_smallt *)Args[1].Val)->Value;
	char *___ = 0;
	gtk_signal_emit(object, signal_id, ___);
	return SUCCESS;
};

GLOBAL_FUNCTION(EmitByName, 3) {
	GtkObject * object = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *name = Std$String$flatten(Args[1].Val);
	char *___ = 0;
	gtk_signal_emit_by_name(object, name, ___);
	return SUCCESS;
};

GLOBAL_FUNCTION(EmitStopByName, 2) {
	GtkObject * object = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *name = Std$String$flatten(Args[1].Val);
	gtk_signal_emit_stop_by_name(object, name);
	return SUCCESS;
};

GLOBAL_FUNCTION(Emitv, 3) {
	GtkObject * object = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int signal_id = ((Std$Integer_smallt *)Args[1].Val)->Value;
	GtkArg * args= &((Gtk$Gtk$Arg_t *)Args[2].Val)->Value;
	gtk_signal_emitv(object, signal_id, args);
	return SUCCESS;
};

GLOBAL_FUNCTION(EmitvByName, 3) {
	GtkObject * object = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *name = Std$String$flatten(Args[1].Val);
	GtkArg * args= &((Gtk$Gtk$Arg_t *)Args[2].Val)->Value;
	gtk_signal_emitv_by_name(object, name, args);
	return SUCCESS;
};

GLOBAL_FUNCTION(New, 8) {
	char *name = Std$String$flatten(Args[0].Val);
	GtkSignalRunType signal_flags = ((Std$Integer_smallt *)Args[1].Val)->Value;
	GType object_type;
	int function_offset = ((Std$Integer_smallt *)Args[3].Val)->Value;
	GtkSignalMarshaller marshaller = 0;
	GType return_val;
	int n_args = ((Std$Integer_smallt *)Args[6].Val)->Value;
	char *___ = 0;
	int result = gtk_signal_new(name, signal_flags, object_type, function_offset, marshaller, return_val, n_args, ___);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(Newv, 8) {
	char *name = Std$String$flatten(Args[0].Val);
	GtkSignalRunType signal_flags = ((Std$Integer_smallt *)Args[1].Val)->Value;
	GType object_type;
	int function_offset = ((Std$Integer_smallt *)Args[3].Val)->Value;
	GtkSignalMarshaller marshaller = 0;
	GType return_val;
	int n_args = ((Std$Integer_smallt *)Args[6].Val)->Value;
	GtkType* args = 0;
	int result = gtk_signal_newv(name, signal_flags, object_type, function_offset, marshaller, return_val, n_args, args);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

