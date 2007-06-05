#include <Gtk/GObject/Type.h>
#include <Gtk/GObject/Object.h>
#include <Riva.h>
#include <Util/StringTable.h>
#include <stdio.h>

TYPE(T, Gtk$GObject$Object$T);

static Util$StringTable_t TypeTable[] = {Util$StringTable$INIT};

Std$Type_t *_to_riva(GType GtkType) {
	const char *GtkName = g_type_name(GtkType);
	const char *RivaName = Util$StringTable$get(TypeTable, GtkName);
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
	Std$Type_t *RivaType;
	if (Riva$Module$import(Module, "T", &Flag, (void **)&RivaType) == 0) {
		Riva$Log$errorf("Error: Export not found: %s.t\n", RivaName);
		return 0;
	};
	return RivaType;
};

static void __free(void *Ignore) {};
static void *__calloc(gsize N, gsize M) {return Riva$Memory$alloc(N * M);};

static GMemVTable MemVTable = {
	Riva$Memory$alloc,
	Riva$Memory$realloc,
	__free,
	__calloc,
	Riva$Memory$alloc,
	Riva$Memory$realloc
};

void __init(Riva$Module_t *Module) {
	g_mem_set_vtable(&MemVTable);
	g_type_init();
	char MapFileName[256];
	sprintf(MapFileName, "%sTypes.map", Riva$Module$get_path(Module));
	Riva$Log$writef("Loading type map from %s\n", MapFileName);
	FILE *MapFile = fopen(MapFileName, "r");
	while (!feof(MapFile)) {
		const char *GtkName, *RivaName;
		if (fscanf(MapFile, "%a[a-zA-Z0-9] = %a[^\n]\n", &GtkName, &RivaName) == 2) {
			Riva$Log$writef("Adding type: %s -> %s\n", GtkName, RivaName);
			Util$StringTable$put(TypeTable, GtkName, (void *)RivaName);
		};
	};
	fclose(MapFile);
};
