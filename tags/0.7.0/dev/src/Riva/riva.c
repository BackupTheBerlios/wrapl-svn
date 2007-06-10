#include "riva.h"
#include "module.h"
#include "log.h"
#include "stringtable.h"
#include "symbol.h"
#include <stdio.h>
#include <string.h>
#include <zlib.h>
#include <gc/gc.h>
#include <stdint.h>
#include <setjmp.h>

#define new(T) (T *)GC_malloc(sizeof(T))
#define unew(T) (T *)GC_malloc_uncollectable(sizeof(T))

#define SECT_GENERIC	0
#define SECT_CODE		1
#define SECT_LIBRARY	2
#define SECT_IMPORT		3
#define SECT_BSS		4
#define SECT_SYMBOL		5

#define RELOC_ABS	0
#define RELOC_REL	1

#define LIBRARY_ABS	0
#define LIBRARY_REL	1

#define EXP_CONSTANT	0
#define EXP_VARIABLE	1

#define FLAG_GC		1

typedef struct reloc_t {
	uint32_t Size;
	uint32_t Flags;
	uint32_t Position;
	struct section_t *Section;
} reloc_t;

#define UNLOADED	0
#define LOADING		1
#define LOADED		2

typedef struct section_t {
	uint32_t (*Fixup)(struct section_t *, const char *);
	uint32_t Flags;
	uint32_t State;
	uint8_t *Data;
	union {
		struct {
			uint32_t NoOfRelocs;
			reloc_t *Relocs;
		};
		struct {
			char *Name;
			union {
				struct section_t *Library;
				char *Path;
			};
		};
	};
} section_t;

typedef struct export_t {
	uint32_t Flags;
	section_t *Section;
	uint32_t Offset;
} export_t;

typedef struct riva_t {
	stringtable_t Exports;
	section_t **Sections;
} riva_t;

static uint32_t fixup_code_section(section_t *Section, jmp_buf *OnError) {
	if (Section->State == UNLOADED) {
		Section->State = LOADING;
		uint8_t *Data = Section->Data;
		for (int I = 0; I < Section->NoOfRelocs; ++I) {
			const reloc_t *Reloc = &Section->Relocs[I];
			uint32_t Value = Reloc->Section->Fixup(Reloc->Section, OnError);
			if (Reloc->Flags == RELOC_REL) Value -= (uint32_t)Data;
			switch (Reloc->Size) {
			case 1:
				*(uint8_t *)(Section->Data + Reloc->Position) += Value;
				break;
			case 2:
				*(uint16_t *)(Section->Data + Reloc->Position) += Value;
				break;
			case 4:
				*(uint32_t *)(Section->Data + Reloc->Position) += Value;
				break;
			};
		};
		Section->State = LOADED;
	};
	return (uint32_t)Section->Data;
};

static uint32_t fixup_library_section(section_t *Section, jmp_buf *OnError) {
	if (Section->State == UNLOADED) {
		Section->State = LOADING;
		Section->Data = (uint8_t *)module_load(Section->Path, Section->Name);
		if (Section->Data == 0) {
			log_errorf("Error: module not found %s\n", Section->Name);
			longjmp(OnError, 1);
		};
		Section->State = LOADED;
	};
	return (uint32_t)Section->Data;
};

static uint32_t fixup_import_section(section_t *Section, jmp_buf *OnError) {
	if (Section->State == UNLOADED) {
		Section->State = LOADING;
		module_t *Module = (module_t *)Section->Library->Fixup(Section->Library, OnError);
		int IsRef;
		if (module_import(Module, Section->Name, &IsRef, (void **)&Section->Data)) {
			Section->State = LOADED;
		} else {
			log_errorf("Error: symbol %s not exported from %s\n", Section->Name, Section->Library->Name);
			longjmp(OnError, 1);
		};
	};
	return (uint32_t)Section->Data;
};

static uint32_t fixup_bss_section(section_t *Section, jmp_buf *OnError) {
	if (Section->State == UNLOADED) Section->State = LOADED;
	return (uint32_t)Section->Data;
};

static uint32_t fixup_symbol_section(section_t *Section, jmp_buf *OnError) {
	if (Section->State == UNLOADED) {
		Section->State = LOADING;
		int IsRef;
		module_import(Symbol, Section->Name, &IsRef, (void **)&Section->Data);
		Section->State = LOADED;
	};
	return (uint32_t)Section->Data;
};

static void *check_import(riva_t *Riva, const char *Symbol, jmp_buf *OnError) {
	const export_t *Export = stringtable_get(Riva->Exports, Symbol);
	if (Export) {
		void *Data = Export->Section->Data + Export->Offset;
		Export->Section->Fixup(Export->Section, OnError);
		return Data;
	} else {
		return 0;
	};
};

static int riva_import(riva_t *Riva, const char *Symbol, int *IsRef, void **Data) {
	const export_t *Export = stringtable_get(Riva->Exports, Symbol);
	if (Export) {
		jmp_buf OnError[1];
		if (setjmp(OnError)) return 0;
		*IsRef = Export->Flags & EXP_VARIABLE;
		*Data = Export->Section->Data + Export->Offset;
		Export->Section->Fixup(Export->Section, OnError);
		return 1;
	} else {
		return 0;
	};
};

static int riva_load(module_t *Module, const char *FileName) {
	riva_t *Riva = unew(riva_t); // This really should be new...
	module_setup(Module, Riva, (module_importer)riva_import);

	gzFile File = gzopen(FileName, "rb");
	char *LoadPath;
	for (int I = strlen(FileName) - 1; I >= 0; --I) {
		if (FileName[I] == PATHCHR) {
			strncpy(LoadPath = (char *)GC_malloc_atomic(I + 2), FileName, I + 1);
			break;
		};
	};
	module_set_path(Module, LoadPath);

	uint32_t Magic; gzread(File, &Magic, 4);
	if (Magic != 0x41564952) {
		log_errorf("Error: %s is not a valid riva module\n", FileName);
		return 0;
	};

	uint32_t NoOfSections; gzread(File, &NoOfSections, 4);
	uint32_t NoOfExports; gzread(File, &NoOfExports, 4);
	uint32_t NoOfRequires; gzread(File, &NoOfRequires, 4);

	jmp_buf OnError[1];

	if (setjmp(OnError)) return 0;
	section_t **Sections = (Riva->Sections = (section_t **)GC_malloc(NoOfSections * sizeof(section_t *)));
	for (int I = 0; I < NoOfSections; ++I) Sections[I] = new(section_t);
	for (int I = 0; I < NoOfSections; ++I) {
		section_t *Section = Sections[I];
		uint8_t Type; gzread(File, &Type, 1);
		switch (Type) {
		case SECT_CODE: {
			Section->Fixup = fixup_code_section;
			gzread(File, &Section->Flags, 1);
			uint32_t Length; gzread(File, &Length, 4);
			uint32_t NoOfRelocs; gzread(File, &NoOfRelocs, 4);
			Section->NoOfRelocs = NoOfRelocs;
			reloc_t *Relocs = (Section->Relocs = (reloc_t *)GC_malloc_uncollectable(NoOfRelocs * sizeof(reloc_t)));
			if (Section->Flags & FLAG_GC) {
				Section->Data = GC_malloc_uncollectable(Length);
			} else {
				Section->Data = GC_malloc_atomic_uncollectable(Length);
			};
			gzread(File, Section->Data, Length);
			for (int J = 0; J < NoOfRelocs; ++J) {
				reloc_t *Reloc = &Relocs[J];
				gzread(File, &Reloc->Size, 1);
				gzread(File, &Reloc->Flags, 1);
				gzread(File, &Reloc->Position, 4);
				uint32_t Index; gzread(File, &Index, 4);
				Reloc->Section = Sections[Index];
			};
		break;};
		case SECT_LIBRARY: {
			Section->Fixup = fixup_library_section;
			gzread(File, &Section->Flags, 1);
			uint32_t Length; gzread(File, &Length, 4);
			gzread(File, Section->Name = (char *)GC_malloc_atomic(Length + 1), Length);
			Section->Name[Length] = 0;
			if (Section->Flags == LIBRARY_ABS) {
				Section->Path = 0;
			} else if (Section->Flags == LIBRARY_REL) {
				Section->Path = LoadPath;
			};
			for (char *P = Section->Name; *P; ++P) if (*P == '/') *P = PATHCHR;
		break;};
		case SECT_IMPORT: {
			Section->Fixup = fixup_import_section;
			gzread(File, &Section->Flags, 1);
			uint32_t Index; gzread(File, &Index, 4);
			Section->Library = Sections[Index];
			uint32_t Length; gzread(File, &Length, 4);
			gzread(File, Section->Name = (char *)GC_malloc_atomic(Length + 1), Length);
			Section->Name[Length] = 0;
		break;};
		case SECT_BSS: {
			Section->Fixup = fixup_bss_section;
			gzread(File, &Section->Flags, 1);
			uint32_t Size; gzread(File, &Size, 4);
			Section->Data = (uint8_t *)GC_malloc(Size);
		break;};
		case SECT_SYMBOL: {
			Section->Fixup = fixup_symbol_section;
			gzread(File, &Section->Flags, 1);
			uint32_t Length; gzread(File, &Length, 4);
			gzread(File, Section->Name = (char *)GC_malloc_atomic(Length + 1), Length);
			Section->Name[Length] = 0;
		break;};
		};
	};
	for (int I = 0; I < NoOfExports; ++I) {
		export_t *Export = new(export_t);
		gzread(File, &Export->Flags, 1);
		uint32_t Index; gzread(File, &Index, 4);
		Export->Section = Sections[Index];
		gzread(File, &Export->Offset, 4);
		uint32_t Length; gzread(File, &Length, 4);
		char *Name = (char *)GC_malloc_atomic(Length + 1);
		gzread(File, Name, Length);
		Name[Length] = 0;
		stringtable_put(Riva->Exports, Name, Export);
	};
	for (int I = 0; I < NoOfRequires; ++I) {
		uint8_t Flags; gzread(File, &Flags, 1);
		uint32_t Length; gzread(File, &Length, 4);
		char *Name = (char *)GC_malloc_atomic(Length + 1);
		char *Path = 0;
		gzread(File, Name, Length);
		Name[Length] = 0;
		if (Flags == LIBRARY_REL) Path = LoadPath;
		for (char *P = Name; *P; ++P) if (*P == '/') *P = PATHCHR;
		module_load(Path, Name);
	};
	gzclose(File);

	void (*__init)(module_t *) = check_import(Riva, "__init", OnError);
 	if (__init) __init(Module);
 	void *Methods = check_import(Riva, "__methods", OnError);
 	if (Methods) add_methods(Methods);
	return 1;
};

void riva_init(void) {
	module_add_loader(".riva", riva_load);
};
