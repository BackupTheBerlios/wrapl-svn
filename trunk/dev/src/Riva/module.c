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
    if (Path == 0) return 0;
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

void module_add_directory(const char *Dir) {
    FIXUP_PATH(Dir);
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
	char FullPath[256];
	sprintf(FullPath, "%s%s", Path, Name);
	long Length = strlen(FullPath);
	char *Ext = FullPath + Length;
	struct stat Stat;

	for (loader_node *Loader = Loaders; Loader; Loader = Loader->Next) {
		strcpy(Ext, Loader->Extension);
		if (stat(FullPath, &Stat) == 0) {
			log_writef("Loading: %s\n", FullPath);
			char *Key = GC_malloc_atomic(Length + 1);
			memcpy(Key, FullPath, Length);
			Key[Length] = 0;
			module_t *Module = new(module_t);
			Module->Name = Name;
			Module->Import = default_import;
			if (Loader->_load(Module, FullPath) == 0) log_errorf("Error: error loading %s\n", FullPath);
			return Module;
		};
	};
    return 0;
};

static int ModuleLevel = 0;
#define MODULE_NOT_FOUND (module_t *)0xFFFFFFFF

module_t *module_run(const char *Name, const char *Path) {
    FIXUP_PATH(Name);
    FIXUP_PATH(Path);
    if (Path) {
		module_t *Module = do_run(Path, Name);
		if (Module == MODULE_NOT_FOUND) {
			log_errorf("Error: module not found %s%s\n", Path, Name);
		};
		return Module;
	} else {
		module_t *Module = do_run("", Name);
		if (Module != MODULE_NOT_FOUND) return Module;
	    for (path_node *Node = Library; Node; Node = Node->Next) {
	        module_t *Module = do_run(Node->Dir, Name);
	        if (Module != MODULE_NOT_FOUND) return Module;
	    };
        log_errorf("Error: module not found %s\n", Name);
        return 0;
	};
};

static module_t *module_try_load(const char *Path, const char *Name, loader_node *Loader) {
	char FullPath[256];
	char *ExtPtr = stpcpy(stpcpy(FullPath, Path), Name);
	stpcpy(ExtPtr, Loader->Extension);
	struct stat Stat;
	if (stat(FullPath, &Stat) == 0) {
		int Length = ExtPtr - FullPath;
		char *Key = GC_malloc_atomic(Length + 1);
		memcpy(Key, FullPath, Length);
		Key[Length] = 0;
		int Level = ModuleLevel++;
		for (int I = 0; I < Level; ++I) log_writef("|   ");
		log_writef("Loading: %s\n", FullPath);
		module_t *Module = new(module_t);
		Module->Name = Name;
		Module->Import = default_import;
		stringtable_put(Modules, Key, Module);
		if (Loader->_load(Module, FullPath) == 0) {
			log_errorf("Error: error loading %s\n", FullPath);
			return 0;
		};
		for (int I = 0; I < Level; ++I) log_writef("|   ");
		log_writef("Loaded: %s\n", FullPath);
		ModuleLevel--;
		return Module;
	} else {
		return 0;
	};
};

module_t *module_load(const char *Path, const char *Name) {
	FIXUP_PATH(Name);
	FIXUP_PATH(Path);
	module_t *Module;
	char FullPath[256];
	if (Path) {
		stpcpy(stpcpy(FullPath, Path), Name);
		Module = stringtable_get(Modules, FullPath);
		if (Module) return Module;
		for (loader_node *Loader = Loaders; Loader; Loader = Loader->Next) {
			Module = module_try_load(Path, Name, Loader);
			if (Module) return Module;
		};
		return 0;
	};
	Module = stringtable_get(Modules, Name);
	if (Module) return Module;
	for (path_node *Node = Library; Node; Node = Node->Next) {
		stpcpy(stpcpy(FullPath, Node->Dir), Name);
		Module = stringtable_get(Modules, FullPath);
		if (Module) return Module;
	};
	for (loader_node *Loader = Loaders; Loader; Loader = Loader->Next) {
		//Module = module_try_load("", Name, Loader);
		//if (Module) return Module;
		for (path_node *Node = Library; Node; Node = Node->Next) {
			Module = module_try_load(Node->Dir, Name, Loader);
			if (Module) return Module;
		};
	};
	return 0;
};

module_t *module_load_file(const char *FileName) {
	struct stat Stat;
	if (stat(FileName, &Stat) == 0) {
		module_t *Module = new(module_t);
		Module->Name = FileName;
		Module->Import = default_import;
		for (loader_node *Loader = Loaders; Loader; Loader = Loader->Next) {
			if (Loader->_load(Module, FileName)) return Module;
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
	module_export(Module, "_add_loader", 0, module_add_loader);
	module_export(Module, "_add_directory", 0, module_add_directory);
	module_export(Module, "_set_path", 0, module_set_path);
	module_export(Module, "_get_path", 0, module_get_path);
};
