#include "module.h"
#include <stdint.h>
#ifdef LINUX
#include <malloc.h>
#include <gc/gc_local_alloc.h>
#else
#include <gc/gc.h>
#endif

#ifdef LINUX

static memory_alloc_debug(size_t Size) {
	return GC_debug_malloc(Size, GC_EXTRAS);
};

static memory_realloc_debug(void *Ptr, size_t Size) {
	if (Ptr == 0x83ab0f0) asm("int3");
	return GC_debug_realloc(Ptr, Size, GC_EXTRAS);
};

static memory_memalign_debug(size_t Alignment, size_t Size, const void *Caller) {
	uint8_t *Result = GC_debug_malloc(Size + Alignment, GC_EXTRAS);
	uint32_t Offset = (uint32_t)Result % Alignment;
	if (Offset) Result += (Alignment - Offset);
	return Result;
};

static memory_free() {
};

static memory_memalign(size_t Alignment, size_t Size, const void *Caller) {
	uint8_t *Result = GC_malloc(Size + Alignment);
	uint32_t Offset = (uint32_t)Result % Alignment;
	if (Offset) Result += (Alignment - Offset);
	return Result;
};

static void memory_init_hook (void) {
	//__malloc_hook = GC_malloc;
	//__realloc_hook = GC_realloc;
	__malloc_hook = memory_alloc_debug;
	__realloc_hook = memory_realloc_debug;
	__free_hook = memory_free;
	//__memalign_hook = memory_memalign;
	__memalign_hook = memory_memalign_debug;
}

void (*__malloc_initialize_hook)(void) = memory_init_hook;
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
	module_export(Module, "_is_visible", 0, GC_is_visible);
	module_export(Module, "_size", 0, GC_size);
};
