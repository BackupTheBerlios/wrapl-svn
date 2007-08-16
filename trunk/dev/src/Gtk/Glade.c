#include <Riva.h>
#include <Sys/Module.h>
#include <Gtk/GObject/Closure.h>
#include <Gtk/GObject/Object.h>
#include <glade/glade.h>

static int glade_import(GladeXML *Handle, const char *Symbol, int *IsRef, void **Data) {
	GtkWidget *Widget = glade_xml_get_widget(Handle, Symbol);
	if (Widget) {
		*IsRef = 0;
		*Data = Gtk$GObject$Object$to_riva(Widget);
		return 1;
	} else {
		return 0;
	};
};

static void glade_connect_func(const gchar *HandlerName, GObject *Object, const gchar *SignalName, const gchar *SignalData, GObject *ConnectObject, gboolean After, Riva$Module_t *Module) {
	int Length = strlen(HandlerName);
	char HandlerModule[Length + 1];
	strcpy(HandlerModule, HandlerName);
	char *HandlerImport = strchr(HandlerModule, '.');
	if (HandlerImport) {
		*(HandlerImport++) = 0;
		Module = Riva$Module$load(0, HandlerModule);
	} else {
		HandlerImport = HandlerModule;
	};
	if (Module) {
		Std$Function_t *Function;
		int IsRef;
		if (Riva$Module$import(Module, HandlerImport, &IsRef, &Function)) {
			g_signal_connect_closure(Object, SignalName, Gtk$GObject$Closure$new(Function)->Handle, 0);
			return;
		};
	};
	printf("Warning: handler %s not found.\n", HandlerName);
};

static int glade_load(Riva$Module_t *Module, const char *Path) {
	GladeXML *Handle = glade_xml_new(Path, 0, 0);
	if (Handle == 0) return 0;
	glade_xml_signal_autoconnect_full(Handle, glade_connect_func, 0);
	Riva$Module$setup(Module, Handle, glade_import);
	return 1;
};

GLOBAL_FUNCTION(Load, 1) {
	GladeXML *Handle = glade_xml_new(Std$String$flatten(Args[0].Val), 0, 0);
	if (Handle == 0) return FAILURE;
	glade_xml_signal_autoconnect_full(Handle, glade_connect_func, (Count > 1) ? ((Sys$Module_t *)Args[1].Val)->Handle : 0);
	Sys$Module_t *Module = Sys$Module$new();
	Riva$Module$setup(Module->Handle, Handle, glade_import);
	Result->Val = Module;
	return SUCCESS;
};

void __init(Riva$Module_t *Module) {
	gtk_init(0, 0);
	//Riva$Module$add_loader(".glade", glade_load);
};
