#include "directory.h"
#include "module.h"
#include <stdio.h>
#include "log.h"

static int directory_import(const char *Path, const char *Name, int *IsRef, void **Data) {
	static void *(*load_module)(const char *Path, const char *Name) = 0;
	if (load_module == 0) {
		module_t *SysModule = module_load(0, "Sys/Module");
		int IsRef0;
		module_import(SysModule, "_load", &IsRef0, (void **)&load_module);
	};
	void *Module = load_module(Path, Name);
	if (Module) {
		*IsRef = 0;
		*Data = Module;
		return 1;
	} else {
		return 0;
	};
};

#ifdef WINDOWS

#include <windows.h>

static int directory_load(module_t *Module, const char *FileName) {
    DWORD FileAttributes = GetFileAttributes(FileName);
    if (FileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
        int Length = strlen(FileName);
		char *Path = GC_malloc_atomic(Length + 2);
		strcpy(Path, FileName);
		Path[Length] = '\\';
		Path[Length + 1] = 0;
		module_setup(Module, Path, (module_importer)directory_import);
	} else {
		return 0;
    };
};

#else

#include <sys/stat.h>

static int directory_load(module_t *Module, const char *FileName) {
	struct stat Stat;
	stat(FileName, &Stat);
	if (S_ISDIR(Stat.st_mode)) {
		int Length = strlen(FileName);
		char *Path = GC_malloc_atomic(Length + 2);
		strcpy(Path, FileName);
		Path[Length] = '/';
		Path[Length + 1] = 0;
		module_setup(Module, Path, (module_importer)directory_import);
	} else {
		return 0;
	};
};

#endif

void directory_init(void) {
	module_add_loader("", directory_load);
};