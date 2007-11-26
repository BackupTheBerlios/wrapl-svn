#include "fileset.h"
#include "module.h"
#include "log.h"
#include <stdio.h>
#include <string.h>
#include <zlib.h>
#include <gc/gc.h>
#include <stdint.h>
#include <setjmp.h>
#include <dirent.h>

typedef struct fileset_t {
	uint32_t NoOfModules;
	module_t *Modules[];
} fileset_t;

static int fileset_import(fileset_t *FileSet, const char *Symbol, int *IsRef, void **Data) {
	for (int I = 0; I < FileSet->NoOfModules; ++I) {
		if (module_import(FileSet->Modules[I], Symbol, IsRef, Data)) return 1;
	};
	return 0;
};

static fileset_t *fileset_load_next(const char *Path, FILE *List, int Index) {
	char Name[256];
	if (fgets(Name, 256, List) && Name[0]) {
		char *End = Name + strlen(Name);
		while (*End < ' ') *(End--) = 0;
		module_t *Module = module_load(Path, Name);
		if (Module == 0) {
			log_errorf("Error: module not found %s%s\n", Path, Name);
			return 0;
		};
		fileset_t *FileSet = fileset_load_next(Path, List, Index + 1);
		if (FileSet == 0) return 0;
		FileSet->Modules[Index] = Module;
		return FileSet;
	} else {
		fileset_t *FileSet = GC_malloc(sizeof(fileset_t) + Index * sizeof(module_t *));
		FileSet->NoOfModules = Index;
	};
};

static int fileset_load(module_t *Module, const char *FileName) {
	char Path[256];
	char *Temp = stpcpy(Path, FileName);
	Temp[0] = PATHCHR;
	strcpy(Temp + 1, "list");
	FILE *List = fopen(Path, "r");
	if (List == 0) return 0;
	Temp[1] = 0;
	fileset_t *FileSet = fileset_load_next(Path, List, 0);
	fclose(List);
	if (FileSet == 0) return 0;
	module_setup(Module, FileSet, (module_importer)fileset_import);
	return 1;
}; 

void fileset_init(void) {
	module_add_loader(".fset", fileset_load);
};
