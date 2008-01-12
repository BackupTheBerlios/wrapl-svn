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
	uint32_t NoOfFixups;
	uint8_t *Data;

	//uint32_t NoOfFixups2;
	//const char *FileName;
	//uint32_t Index;

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

	const char *FileName;
} riva_t;

//static int level = 0;

static uint32_t fixup_code_section(section_t *Section, jmp_buf *OnError) {
	//for (int I = level; --I >= 0;) printf("  ");
	//printf("start %d %s[%d] (%d)\n", level++, Section->FileName, Section->Index, Section->NoOfFixups);
	uint8_t *Data = Section->Data;
	while (Section->NoOfFixups) {
		const reloc_t *Reloc = &Section->Relocs[Section->NoOfRelocs - Section->NoOfFixups--];
		uint32_t Value;
		if (Reloc->Section == Section) {
			Value = (uint32_t)Data;
		} else {
			Value = Reloc->Section->Fixup(Reloc->Section, OnError);
			//for (int I = level; --I >= 0;) printf("  ");
			//printf("%s[%d] has %d fixups remaining\n", Reloc->Section->FileName, Reloc->Section->Index, Reloc->Section->NoOfFixups2);
		};
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
		//--Section->NoOfFixups2;
	};
	//for (int I = --level; --I >= 0;) printf("  ");
	//printf("end %d\n", level);
	return (uint32_t)Data;
};

static uint32_t fixup_library_section(section_t *Section, jmp_buf *OnError) {
	if (Section->NoOfFixups) {
		Section->Data = (uint8_t *)module_load(Section->Path, Section->Name);
		if (Section->Data == 0) {
			log_errorf("Error: module not found %s\n", Section->Name);
			longjmp(OnError, 1);
		};
		Section->NoOfFixups = 0;
	};
	return (uint32_t)Section->Data;
};

static uint32_t fixup_import_section(section_t *Section, jmp_buf *OnError) {
	if (Section->NoOfFixups) {
		module_t *Module = (module_t *)Section->Library->Fixup(Section->Library, OnError);
		int IsRef;
		if (module_import(Module, Section->Name, &IsRef, (void **)&Section->Data)) {
			Section->NoOfFixups = 0;
		} else {
			log_errorf("Error: symbol %s not exported from %s\n", Section->Name, Section->Library->Name);
			longjmp(OnError, 1);
		};
	};
	return (uint32_t)Section->Data;
};

static uint32_t fixup_bss_section(section_t *Section, jmp_buf *OnError) {
	return (uint32_t)Section->Data;
};

static uint32_t fixup_symbol_section(section_t *Section, jmp_buf *OnError) {
	if (Section->NoOfFixups) {
		int IsRef;
		module_import(Symbol, Section->Name, &IsRef, (void **)&Section->Data);
		Section->NoOfFixups = 0;
	};
	return (uint32_t)Section->Data;
};

static void *check_import(riva_t *Riva, const char *Symbol, jmp_buf *OnError) {
	const export_t *Export = stringtable_get(Riva->Exports, Symbol);
	if (Export) {
		//for (int I = level; --I >= 0;) printf("  ");
		//printf("starting check_import(%s.%s)\n", Riva->FileName, Symbol);
		void *Data = Export->Section->Data + Export->Offset;
		Export->Section->Fixup(Export->Section, OnError);
		if (Export->Section->NoOfFixups) log_errorf("(check_import) Section still has %d unapplied fixups.\n", Export->Section->NoOfFixups);
		//for (int I = level; --I >= 0;) printf("  ");
		//printf("ending check_import(%s.%s)\n", Riva->FileName, Symbol);
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
		//for (int I = level; --I >= 0;) printf("  ");
		//printf("starting riva_import(%s.%s)\n", Riva->FileName, Symbol);
		Export->Section->Fixup(Export->Section, OnError);
		if (Export->Section->NoOfFixups) log_errorf("(riva_import) Section still has %d unapplied fixups.\n", Export->Section->NoOfFixups);
		//for (int I = level; --I >= 0;) printf("  ");
		//printf("ending riva_import(%s.%s)\n", Riva->FileName, Symbol);
		*Data = Export->Section->Data + Export->Offset;		
		return 1;
	} else {
		return 0;
	};
};

static int riva_load(module_t *Module, const char *FileName) {
	//riva_t *Riva = unew(riva_t); // This really should be new...
	riva_t *Riva = new(riva_t);

	Riva->FileName = FileName;

	module_setup(Module, Riva, (module_importer)riva_import);

	gzFile File = gzopen(FileName, "rb");

	uint32_t Magic; gzread(File, &Magic, 4);
	if (Magic != 0x41564952) return 0;

	uint32_t NoOfSections; gzread(File, &NoOfSections, 4);
	uint32_t NoOfExports; gzread(File, &NoOfExports, 4);
	uint32_t NoOfRequires; gzread(File, &NoOfRequires, 4);

	jmp_buf OnError[1];

	if (setjmp(OnError)) return 0;
	section_t **Sections = (Riva->Sections = (section_t **)GC_malloc(NoOfSections * sizeof(section_t *)));
	for (int I = 0; I < NoOfSections; ++I) Sections[I] = new(section_t);
	for (int I = 0; I < NoOfSections; ++I) {
		section_t *Section = Sections[I];

		//Section->FileName = FileName;
		//Section->Index = I;

		uint8_t Type; gzread(File, &Type, 1);
		switch (Type) {
		case SECT_CODE: {
			Section->Fixup = fixup_code_section;
			gzread(File, &Section->Flags, 1);
			uint32_t Length; gzread(File, &Length, 4);
			uint32_t NoOfRelocs; gzread(File, &NoOfRelocs, 4);
			Section->NoOfRelocs = NoOfRelocs;
			Section->NoOfFixups = NoOfRelocs;

			//Section->NoOfFixups2 = NoOfRelocs;

			reloc_t *Relocs = (Section->Relocs = (reloc_t *)GC_malloc_uncollectable(NoOfRelocs * sizeof(reloc_t)));
			if (Section->Flags & FLAG_GC) {
				Section->Data = GC_malloc_uncollectable(Length);
				//Section->Data = GC_malloc(Length);
			} else {
				Section->Data = GC_malloc_atomic_uncollectable(Length);
				//Section->Data = GC_malloc_atomic(Length);
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
			Section->NoOfFixups = 1;
			if (Section->Flags == LIBRARY_ABS) {
				Section->Path = 0;
			} else if (Section->Flags == LIBRARY_REL) {
				Section->Path = module_get_path(Module);
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
			Section->NoOfFixups = 1;
		break;};
		case SECT_BSS: {
			Section->Fixup = fixup_bss_section;
			gzread(File, &Section->Flags, 1);
			uint32_t Size; gzread(File, &Size, 4);
			Section->Data = (uint8_t *)GC_malloc(Size);
			Section->NoOfFixups = 0;
		break;};
		case SECT_SYMBOL: {
			Section->Fixup = fixup_symbol_section;
			gzread(File, &Section->Flags, 1);
			uint32_t Length; gzread(File, &Length, 4);
			gzread(File, Section->Name = (char *)GC_malloc_atomic(Length + 1), Length);
			Section->Name[Length] = 0;
			Section->NoOfFixups = 1;
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
		if (Flags == LIBRARY_REL) Path = module_get_path(Module);
		for (char *P = Name; *P; ++P) if (*P == '/') *P = PATHCHR;
		module_load(Path, Name);
	};
	gzclose(File);

	void (*__init)(module_t *) = check_import(Riva, "__init", OnError);
 	if (__init) {
		log_writef("Initializing %s\n", FileName);
		__init(Module);
	};
 	void *Methods = check_import(Riva, "__methods", OnError);
 	if (Methods) {
		log_writef("Adding methods for %s\n", FileName);
		add_methods(Methods);
	};
	return 1;
};

void riva_init(void) {
	module_add_loader(".riva", riva_load);
};
