#include "module.h"
#ifdef LINUX
#include <malloc.h>
#include <gc/gc_local_alloc.h>
#else
#include <gc/gc.h>
#endif

void memory_init(void) {
	module_t *Module = module_alias("Riva/Memory");
	module_export(Module, "_collect", 0, GC_gcollect);
	module_export(Module, "_alloc", 0, GC_malloc);
	module_export(Module, "_alloc_atomic", 0, GC_malloc_atomic);
	module_export(Module, "_alloc_uncollectable", 0, GC_malloc_uncollectable);
#ifdef LINUX
	module_export(Module, "_alloc_small", 0, GC_local_malloc);
#else
    module_export(Module, "_alloc_small", 0, GC_malloc);
#endif
	module_export(Module, "_realloc", 0, GC_realloc);
	module_export(Module, "_free", 0, GC_free);
	module_export(Module, "_base", 0, GC_base);
	module_export(Module, "_register_finalizer", 0, GC_register_finalizer);
	module_export(Module, "_register_finalizer_ignore_self", 0, GC_register_finalizer_ignore_self);
	module_export(Module, "_register_disappearing_link", 0, GC_register_disappearing_link);
	module_export(Module, "_is_visible", 0, GC_is_visible);
	module_export(Module, "_size", 0, GC_size);
};
