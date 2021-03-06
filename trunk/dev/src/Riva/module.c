#include "module.h"
#include "riva.h"
#include "native.h"
#include "log.h"
#include "stringtable.h"
#include <stdio.h>
//#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <sys/stat.h>
#include <gc/gc.h>

#define new(T) (T *)GC_malloc(sizeof(T))
#define unew(T) (T *)GC_malloc_uncollectable(sizeof(T))

#ifdef WINDOWS
#include <windows.h>
#endif

#ifdef WINDOWS
static inline const char *module_fixup_path(const char *Path) {
    if (strchr(Path, '/')) {
        char *NewPath = strdup(Path);
        for (char *P = NewPath; *P; ++P) if (*P == '/') *P = PATHCHR;
        return NewPath;
    } else {
        return Path;
    };
};
    #define FIXUP_PATH(x) x = module_fixup_path(x)

#else
    #define FIXUP_PATH(x) 0
#endif

typedef struct export_t {
	int IsRef;
	void *Data;
} export_t;

struct module_t {
	const char *Path, *Name;
	void *Data;
	stringtable_t Symbols;
	module_importer Import;
};

static int default_import(void *Module, const char *Symbol, int *IsRef, void **Data) {
	return 0;
};

static stringtable_t Modules = {{0, 0, 0}};

typedef struct path_node {
    struct path_node *Next;
    char Dir[];
} path_node;

static path_node *Library = 0;

char *concat2(const char *A, const char *B) {
	int Length = strlen(A) + strlen(B);
	char *R = GC_malloc_atomic(Length + 1);
	stpcpy(stpcpy(R, A), B);
	R[Length] = 0;
	return R;
};

char *concat3(const char *A, const char *B, const char *C) {
	int Length = strlen(A) + strlen(B) + strlen(C);
	char *R = GC_malloc_atomic(Length + 1);
	stpcpy(stpcpy(stpcpy(R, A), B), C);
	R[Length] = 0;
	return R;
};

void module_add_directory(const char *Dir) {
#ifdef LINUX
	Dir = canonicalize_file_name(Dir);
#else
	FIXUP_PATH(Dir);
#endif
    log_writef("Adding %s to library search path.\n", Dir);
    long Length = strlen(Dir);
    path_node *Node;
    if (Dir[Length - 1] == PATHCHR) {
    	Node = (path_node *)GC_malloc_stubborn(sizeof(path_node) + Length + 1);
		strcpy(Node->Dir, Dir);
    } else {
    	Node = (path_node *)GC_malloc_stubborn(sizeof(path_node) + Length + 2);
		char *End = stpcpy(Node->Dir, Dir);
		End[0] = PATHCHR;
		End[1] = 0;
    };
    Node->Next = Library;
    GC_end_stubborn_change(Node);
    Library = Node;
};

typedef struct loader_node {
	struct loader_node *Next;
	module_loader _load;
	char Extension[];
} loader_node;

static loader_node *Loaders = 0;

void module_add_loader(const char *Extension, module_loader _load) {
	long Length = strlen(Extension) + 1;
	loader_node *Node = GC_malloc_stubborn(sizeof(loader_node) + Length);
	memcpy(Node->Extension, Extension, Length);
    Node->_load = _load;
    Node->Next = Loaders;
	GC_end_stubborn_change(Node);
	Loaders = Node;
};

int module_lookup(void *Address, const char **ModuleName, const char **SymbolName) {
	if (Address == 0) return 0;
	for (int I = 0; I < Modules->Size; ++I) {
		if (Modules->Entries[I].Key) {
			module_t *Module = Modules->Entries[I].Value;
			struct stringtable_t *Symbols = Module->Symbols;
			for (int J = 0; J < Symbols->Size; ++J) {
				if (Symbols->Entries[J].Key) {
					export_t *Export = Symbols->Entries[J].Value;
					if (Export->Data == Address) {
						*ModuleName = Module->Name;
						*SymbolName = Symbols->Entries[J].Key;
						return 1;
					};
				};
			};
		};
	};
	return 0;
};

static module_t *do_run(const char *Path, const char *Name) {
    return 0;
};

static int ModuleLevel = 0;
#define MODULE_NOT_FOUND (module_t *)0xFFFFFFFF

module_t *module_run(const char *Name, const char *Path) {
	return 0;
};

static module_t *module_try_load(const char *Key, loader_node *Loader) {
	const char *File = concat2(Key, Loader->Extension);
	struct stat Stat;
	if (stat(File, &Stat) == 0) {
		char *Base = basename(File);
		int Length = Base - File;
		char *Path = GC_malloc_atomic(Length + 1);
		memcpy(Path, File, Length);
		Path[Length] = 0;
		for (int I = ++ModuleLevel; --I;) log_writef("|   ");
		log_writef("Loading: %s\n", File);
		module_t *Module = new(module_t);
		Module->Name = Key;
		Module->Import = default_import;
		Module->Path = Path;
		stringtable_put(Modules, Key, Module);
		if (Loader->_load(Module, File) == 0) {
			log_errorf("Error: error loading %s\n", File);
			return 0;
		};
		for (int I = ModuleLevel--; --I;) log_writef("|   ");
		log_writef("Loaded: %s\n", File);
		return Module;
	} else {
		return 0;
	};
};

module_t *module_load(const char *Path, const char *Name) {
	FIXUP_PATH(Name);	module_t *Module;
	if (Path) {
#ifdef LINUX
		Path = canonicalize_file_name(Path);
		if (Path == 0) return 0;
#else
#endif
		const char *Key = concat3(Path, PATHSTR, Name);
		Module = stringtable_get(Modules, Key);
		if (Module) return Module;
		for (loader_node *Loader = Loaders; Loader; Loader = Loader->Next) {
			Module = module_try_load(Key, Loader);
			if (Module) return Module;
		};
		return 0;
	};
	Module = stringtable_get(Modules, Name);
	if (Module) return Module;
	for (path_node *Node = Library; Node; Node = Node->Next) {
		Module = stringtable_get(Modules, concat2(Node->Dir, Name));
		if (Module) return Module;
	};
	for (loader_node *Loader = Loaders; Loader; Loader = Loader->Next) {
		for (path_node *Node = Library; Node; Node = Node->Next) {
			Module = module_try_load(concat2(Node->Dir, Name), Loader);
			if (Module) return Module;
		};
	};
	return 0;
};

module_t *module_load_file(const char *FileName) {
	struct stat Stat;
	if (stat(FileName, &Stat) == 0) {
		char *Base = basename(FileName);
		int Length = Base - FileName;
		char *Path = GC_malloc_atomic(Length + 1);
		memcpy(Path, FileName, Length);
		Path[Length] = 0;
		module_t *Module = new(module_t);
		Module->Name = FileName;
		Module->Path = Path;
		Module->Import = default_import;
		for (loader_node *Loader = Loaders; Loader; Loader = Loader->Next) {
			if (Loader->_load(Module, FileName)) return Module;
		};
	};
	return 0;
};

module_t *module_load_file_type(const char *FileName, const char *Type) {
	struct stat Stat;
	if (stat(FileName, &Stat) == 0) {
		char *Base = basename(FileName);
		int Length = Base - FileName;
		char *Path = GC_malloc_atomic(Length + 1);
		memcpy(Path, FileName, Length);
		Path[Length] = 0;
		module_t *Module = new(module_t);
		Module->Name = FileName;
		Module->Path = Path;
		Module->Import = default_import;
		for (loader_node *Loader = Loaders; Loader; Loader = Loader->Next) {
			if (strcmp(Loader->Extension, Type) == 0) {
				if (Loader->_load(Module, FileName)) return Module;
			};
		};
	};
	return 0;
};

int module_import(module_t *Module, const char *Symbol, int *IsRef, void **Data) {
	export_t *Export = stringtable_get(Module->Symbols, Symbol);
	if (Export) {
		*IsRef = Export->IsRef;
		*Data = Export->Data;
		return 1;
	};
	Symbol = GC_strdup(Symbol);
	if (Module->Import(Module->Data, Symbol, IsRef, Data)) {
		export_t *Export = new(export_t);
		Export->IsRef = *IsRef;
		Export->Data = *Data;
		stringtable_put(Module->Symbols, Symbol, Export);
		return 1;
	} else {
		//log_errorf("Symbol %s not exported from %s\n", Symbol, Module->Name);
		return 0;
	};
};

void module_export(module_t *Module, const char *Name, int IsRef, void *Data) {
	export_t *Export = new(export_t);
	Export->IsRef = IsRef;
	Export->Data = Data;
	stringtable_put(Module->Symbols, Name, Export);
};

module_t *module_setup(module_t *Module, void *Data, module_importer Import) {
	Module->Data = Data;
	Module->Import = Import;
	return Module;
};

module_t *module_alias(const char *Name) {
    FIXUP_PATH(Name);
	module_t *Module = new(module_t);
	Module->Name = Name;
	Module->Import = default_import;
	stringtable_put(Modules, Name, Module);
	return Module;
};

void module_set_path(module_t *Module, const char *Path) {
    FIXUP_PATH(Path);
	Module->Path = Path;
};

const char *module_get_path(module_t *Module) {
	return Module->Path;
};

void module_init(void) {
	module_t *Module = module_alias("Riva/Module");
	module_export(Module, "_import", 0, module_import);
	module_export(Module, "_export", 0, module_export);
	module_export(Module, "_lookup", 0, module_lookup);
	module_export(Module, "_setup", 0, module_setup);
	module_export(Module, "_alias", 0, module_alias);
	module_export(Module, "_load", 0, module_load);
	module_export(Module, "_run", 0, module_run);
	module_export(Module, "_load_file", 0, module_load_file);
	module_export(Module, "_add_loader", 0, module_add_loader);
	module_export(Module, "_add_directory", 0, module_add_directory);
	module_export(Module, "_set_path", 0, module_set_path);
	module_export(Module, "_get_path", 0, module_get_path);
};
