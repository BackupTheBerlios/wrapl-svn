#include "native.h"
#include "module.h"
#include <stdio.h>
#include "log.h"

#ifdef WINDOWS
#include <windows.h>

static int native_import(void *Handle, const char *Symbol, int *IsRef, void **Data) {
	void *Address = GetProcAddress(Handle, Symbol);
	if (Address) {
		*Data = Address;
		*IsRef = 0;
		return TRUE;
	} else {
		char Buffer[256];
        FormatMessage(
            FORMAT_MESSAGE_FROM_SYSTEM, 0, GetLastError(),
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), Buffer, 256, 0
        );
        log_errorf("Error: %s\n", Buffer);
		return 0;
	};
};

static int native_load(module_t *Module, const char *FileName) {
	HANDLE Handle = LoadLibraryA(FileName);
	if (Handle) {
	    module_setup(Module, Handle, native_import);
	    return 1;
	}
	char Buffer[256];
	FormatMessage(
		FORMAT_MESSAGE_FROM_SYSTEM, 0, GetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), Buffer, 256, 0
	);
	return 0;
};

void native_init(void) {
	module_add_loader(".dll", native_load);
	native_load(module_alias("libc"), "msvcrt.dll");
};

#else

#include <pthread.h>
#include <dlfcn.h>
#include <unistd.h>
#include <string.h>
#include <gc/gc.h>

static int native_import(void *Handle, const char *Symbol, int *IsRef, void **Data) {
	void *Address = dlsym(Handle, Symbol);
	if (Address) {
		*Data = Address;
		*IsRef = 0;
		return 1;
	} else {
		log_errorf("Error: %s\n", dlerror());
		return 0;
	};
};

static int native_load(module_t *Module, const char *FileName) {
	void *Handle = GC_dlopen(FileName, RTLD_LOCAL | RTLD_LAZY);
	if (Handle) {
		module_setup(Module, Handle, native_import);
		return 1;
	};
	return 0;
};

void native_init(void) {
	module_add_loader(".so", native_load);
	void *Handle = GC_dlopen(0, RTLD_LOCAL | RTLD_LAZY);
	module_setup(module_alias("libc"), Handle, native_import);
	module_setup(module_alias("libgcc"), Handle, native_import);
	//module_setup(module_alias("libpthread"), Handle, native_import);
};

#endif
