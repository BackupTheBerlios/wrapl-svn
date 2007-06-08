#include <Gtk/GObject/Init.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/GObject/Object.h>
#include <Riva.h>
#include <Util/StringTable.h>
#include <Util/ObjectTable.h>
#include <stdio.h>

TYPE(T, Gtk$GObject$Object$T);

METHOD("@", TYP, T, VAL, Std$String$T) {
	Gtk$GObject$Type_t *Type = Args[0].Val;
	Result->Val = Std$String$new(g_type_name(Type->Value));
	return SUCCESS;
};

Gtk$GObject$Type_t INVALID[] = {{T, G_TYPE_INVALID}};
Gtk$GObject$Type_t NONE[] = {{T, G_TYPE_NONE}};
Gtk$GObject$Type_t INTERFACE[] = {{T, G_TYPE_INTERFACE}};
Gtk$GObject$Type_t CHAR[] = {{T, G_TYPE_CHAR}};
Gtk$GObject$Type_t UCHAR[] = {{T, G_TYPE_UCHAR}};
Gtk$GObject$Type_t BOOLEAN[] = {{T, G_TYPE_BOOLEAN}};
Gtk$GObject$Type_t INT[] = {{T, G_TYPE_INT}};
Gtk$GObject$Type_t UINT[] = {{T, G_TYPE_UINT}};
Gtk$GObject$Type_t LONG[] = {{T, G_TYPE_LONG}};
Gtk$GObject$Type_t ULONG[] = {{T, G_TYPE_ULONG}};
Gtk$GObject$Type_t INT64[] = {{T, G_TYPE_INT64}};
Gtk$GObject$Type_t UINT64[] = {{T, G_TYPE_UINT64}};
Gtk$GObject$Type_t ENUM[] = {{T, G_TYPE_ENUM}};
Gtk$GObject$Type_t FLAGS[] = {{T, G_TYPE_FLAGS}};
Gtk$GObject$Type_t FLOAT[] = {{T, G_TYPE_FLOAT}};
Gtk$GObject$Type_t DOUBLE[] = {{T, G_TYPE_DOUBLE}};
Gtk$GObject$Type_t STRING[] = {{T, G_TYPE_STRING}};
Gtk$GObject$Type_t POINTER[] = {{T, G_TYPE_POINTER}};
Gtk$GObject$Type_t BOXED[] = {{T, G_TYPE_BOXED}};
Gtk$GObject$Type_t PARAM[] = {{T, G_TYPE_PARAM}};
Gtk$GObject$Type_t OBJECT[] = {{T, G_TYPE_OBJECT}};

static Util$ObjectTable_t GTypeToRiva[] = {Util$ObjectTable$INIT};
static Util$StringTable_t GTypeModules[] = {Util$StringTable$INIT};

Std$Type_t *_to_riva(GType GtkType) {
	Std$Type_t *RivaType = Util$ObjectTable$get(GTypeToRiva, GtkType);
	if (RivaType != (Std$Type_t *)0xFFFFFFFF) return RivaType;
	const char *GtkName = g_type_name(GtkType);
	const char *RivaName = Util$StringTable$get(GTypeModules, GtkName);
	if (RivaName == 0) {
		Riva$Log$errorf("Error: Gtk type is not mapped: %s\n", GtkName);
		return 0;
	};
	Riva$Module_t *Module = Riva$Module$load(0, RivaName);
	if (Module == 0) {
		Riva$Log$errorf("Error: Module not found: %s\n", RivaName);
		return 0;
	};
	int Flag;
	if (Riva$Module$import(Module, "T", &Flag, (void **)&RivaType) == 0) {
		Riva$Log$errorf("Error: Export not found: %s.t\n", RivaName);
		return 0;
	};
	Util$ObjectTable$put(GTypeToRiva, GtkType, RivaType);
	return RivaType;
};

void __init(Riva$Module_t *Module) {
	g_type_init();
	char MapFileName[256];
	sprintf(MapFileName, "%sTypes.map", Riva$Module$get_path(Module));
	Riva$Log$writef("Loading type map from %s\n", MapFileName);
	FILE *MapFile = fopen(MapFileName, "r");
	while (!feof(MapFile)) {
		const char *GtkName, *RivaName;
		if (fscanf(MapFile, "%a[a-zA-Z0-9] = %a[^\n]\n", &GtkName, &RivaName) == 2) {
			Riva$Log$writef("Adding type: %s -> %s\n", GtkName, RivaName);
			Util$StringTable$put(GTypeModules, GtkName, (void *)RivaName);
		};
	};
	fclose(MapFile);
};
