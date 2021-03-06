#include <Riva.h>
#include <Std.h>
#include <Sys/Module.h>
#include <Gtk/GObject/Closure.h>
#include <Gtk/GObject/Object.h>
#include <glade/glade.h>
#include <string.h>

#ifdef WINDOWS

#define PATHSTR "\\"
#define PATHCHR '\\'

#else

#define PATHSTR "/"
#define PATHCHR '/'

#endif

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

static void glade_connect_func(const gchar *HandlerName, GObject *Object, const gchar *SignalName, const gchar *SignalData, GObject *ConnectObject, gboolean After, const char *LoadPath) {
	int Length = strlen(HandlerName);
	char HandlerModule[Length + 1];
	strcpy(HandlerModule, HandlerName);
	char *HandlerImport = strchr(HandlerModule, '.');
	Riva$Module_t *Module;
	if (HandlerImport) {
		*(HandlerImport++) = 0;
		if (HandlerModule[0] == '@') {
			Module = Riva$Module$load(LoadPath, HandlerModule + 1);
		} else {
			Module = Riva$Module$load(0, HandlerModule);
		};
	} else {
		HandlerImport = HandlerModule;
	};
	if (Module) {
		Std$Function_t *Function;
		int IsRef;
		if (Riva$Module$import(Module, HandlerImport, &IsRef, &Function)) {
			if (IsRef) {
				g_signal_connect_closure(Object, SignalName, Gtk$GObject$Closure$from_ref(Function)->Handle, 0);
			} else {
				g_signal_connect_closure(Object, SignalName, Gtk$GObject$Closure$from_val(Function)->Handle, 0);
			};
			return;
		};
	};
	printf("Warning: handler %s not found.\n", HandlerName);
};

static int glade_load(Riva$Module_t *Module, const char *Path) {
	GladeXML *Handle = glade_xml_new(Path, 0, 0);
	if (Handle == 0) return 0;
	Riva$Module$setup(Module, Handle, glade_import);
	glade_xml_signal_autoconnect_full(Handle, glade_connect_func, Riva$Module$get_path(Module));
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

GLOBAL_FUNCTION(New, 1) {
	Std$String_t *Buffer = Args[0].Val;
	GladeXML *Handle = glade_xml_new_from_buffer(Std$String$flatten(Buffer), Buffer->Length.Value, 0, 0);
	if (Handle == 0) return FAILURE;
	glade_xml_signal_autoconnect_full(Handle, glade_connect_func, (Count > 1) ? ((Sys$Module_t *)Args[1].Val)->Handle : 0);
	Sys$Module_t *Module = Sys$Module$new();
	Riva$Module$setup(Module->Handle, Handle, glade_import);
	Result->Val = Module;
	return SUCCESS;
};

void __init(Riva$Module_t *Module) {
	gtk_init(0, 0);
	Riva$Module$add_loader(".glade", glade_load);
};
