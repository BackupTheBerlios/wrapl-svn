#include <Riva.h>
#include <Std.h>

#include <glib-object.h>

static void __free(void *P) {};
static void *__calloc(gsize N, gsize M) {return Riva$Memory$alloc(N * M);};

static GMemVTable MemVTable = {
	Riva$Memory$alloc,
	Riva$Memory$realloc,
	__free,
	__calloc,
	Riva$Memory$alloc,
	Riva$Memory$realloc
};

void __init(void) {
//	Riva$Log$writes("Initializing glib-gobject interface...");
	g_slice_set_config(G_SLICE_CONFIG_ALWAYS_MALLOC, 1);
	//g_thread_init(0);
	g_mem_set_vtable(&MemVTable);
//	Riva$Log$writes("done.\n");
};
