#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <bfd.h>
#include <zlib.h>
#include <sys/stat.h>

#include <udis86.h>

#ifdef LINUX
#include <lua5.1/lua.h>
#include <lua5.1/lauxlib.h>
#else
#include <lua.h>
#include <lauxlib.h>
#endif

#define new(T) ((T *)malloc(sizeof(T)))

#include "stringtable.h"

#define SECT_GENERIC	0
#define SECT_CODE		1
#define SECT_LIBRARY	2
#define SECT_IMPORT		3
#define SECT_BSS		4
#define SECT_SYMBOL		5
#define SECT_CONSTANT	6

#define EXP_CONSTANT 0
#define EXP_VARIABLE 1

#define RELOC_ABS	0
#define RELOC_REL	1

#define LIBRARY_ABS	0
#define LIBRARY_REL	1

#define FLAG_GC		1

#define SEC_UNUSED 0xFFFFFFFF

typedef struct section_t section_t;
typedef struct relocation_t relocation_t;
typedef struct export_t export_t;

typedef struct section_methods {
	void (*setup)(section_t *Section);
	void (*relocate)(section_t *Section, relocation_t *Relocation, uint32_t *Target);
	void (*export)(section_t *Section, uint32_t Offset, export_t *Export);
	void (*debug)(section_t *Section, FILE *File);
	void (*write)(section_t *Section, gzFile File);
} section_methods;

struct section_t {
	section_t *Next;
	section_methods *Methods;
	uint32_t Index;
};

struct relocation_t {
	uint32_t Flags;
	uint32_t Position;
	uint32_t Size;
	section_t *Section;
};

struct export_t {
	export_t *Next;
	section_t *Section;
	const char *Internal, *External;
	uint32_t Flags;
	uint32_t Offset;
};

typedef struct require_t require_t;

struct require_t {
	require_t *Next;
	uint32_t Flags;
	const char *Library;
};

static struct {section_t *Head, *Tail;} Sections = {0, 0};
static struct {export_t *Head, *Tail;} Exports = {0, 0};
static struct {require_t *Head, *Tail;} Requires = {0, 0};

static uint32_t NoOfSections = 0, NoOfExports = 0, NoOfRequires = 0;

#ifdef WINDOWS
static const char *Platform = "WINDOWS";
#else
#ifdef LINUX
static const char *Platform = "LINUX";
#else
static const char *Platform = "GENERIC";
#endif
#endif

static void new_require(uint32_t Flags, const char *Library) {
	require_t *Require = new(require_t);
	Require->Library = Library;
	Require->Flags = Flags;
	Require->Next = 0;
	++NoOfRequires;
	if (Requires.Head) {
		Requires.Tail->Next = Require;
		Requires.Tail = Require;
	} else {
		Requires.Head = Requires.Tail = Require;
	};
};

static void new_export(const char *Internal, const char *External, uint32_t Flags) {
	export_t *Export = new(export_t);
	Export->Internal = Internal;
	Export->External = External;
	Export->Flags = Flags;
	Export->Section = 0;
	Export->Next = 0;
	++NoOfExports;
	if (Exports.Head) {
		Exports.Tail->Next = Export;
		Exports.Tail = Export;
	} else {
		Exports.Head = Exports.Tail = Export;
	};
};

static inline void section_require(section_t *Section) {
	if (Section->Index != SEC_UNUSED) return;
	Section->Index = NoOfSections;
	NoOfSections++;
	Section->Next = 0;
	if (Sections.Head) {
		Sections.Tail->Next = Section;
		Sections.Tail = Section;
	} else {
		Sections.Head = Sections.Tail = Section;
	};
	Section->Methods->setup(Section);
};

static inline void section_write(section_t *Section, gzFile File) {
	Section->Methods->write(Section, File);
};

static inline void section_debug(section_t *Section, FILE *File) {
	Section->Methods->debug(Section, File);
};

static inline void section_relocate(section_t *Section, relocation_t *Relocation, uint32_t *Target) {
	Section->Methods->relocate(Section, Relocation, Target);
};

static inline void section_export(section_t *Section, uint32_t Offset, export_t *Export) {
	Section->Methods->export(Section, Offset, Export);
};

static void default_section_setup(section_t *Section) {
};

static void invalid_section_setup(section_t *Section) {
	printf("%s: internal failure at line %d.\n", __FILE__, __LINE__);
	exit(1);
};

static void default_section_relocate(section_t *Section, relocation_t *Relocation, uint32_t *Target) {
	section_require(Section);
	Relocation->Section = Section;
};

static void invalid_section_relocate(section_t *Section, relocation_t *Relocation, uint32_t *Target) {
	printf("%s: internal failure at line %d.\n", __FILE__, __LINE__);
	exit(1);
};

static void default_section_export(section_t *Section, uint32_t Offset, export_t *Export) {
	section_require(Export->Section = Section);
	Export->Offset = Offset;
};

static void invalid_section_export(section_t *Section, uint32_t Offset, export_t *Export) {
	printf("%s: internal failure at line %d.\n", __FILE__, __LINE__);
	exit(1);
};

typedef struct symbol_t {
	const char *Name;
	section_t *Section;
	uint32_t Offset;
} symbol_t;

static symbol_t *new_symbol(const char *Name, section_t *Section, uint32_t Offset) {
	symbol_t *Symbol = new(symbol_t);
	Symbol->Name = Name;
	Symbol->Section = Section;
	Symbol->Offset = Offset;
	return Symbol;
};

static stringtable_t LibraryTable = {0, 0, 0, 0};
static stringtable_t GlobalTable = {0, 0, 0, 0};
static stringtable_t WeakTable = {0, 0, 0, 0};
static stringtable_t SymbolTable = {0, 0, 0, 0};

typedef struct code_section_t {
	section_t Base;
	uint32_t Flags;
	uint32_t Size;
	uint32_t NoOfRelocs;
	uint8_t *Text;
	relocation_t Relocs[];
} code_section_t;

typedef struct library_section_t {
	section_t Base;
	uint32_t Flags;
	const char *Path;
	stringtable_t Imports;
} library_section_t;

static void library_section_debug(library_section_t *Section, FILE *File) {
	fprintf(File, "%d: library section: %s\n", ((section_t *)Section)->Index, Section->Path);
};

static void library_section_write(library_section_t *Section, gzFile File) {
	uint32_t Temp = SECT_LIBRARY; gzwrite(File, &Temp, 1);
	if (Section->Path[0] == '.') {
		Temp = LIBRARY_REL; gzwrite(File, &Temp, 1);
		Temp = strlen(Section->Path); gzwrite(File, &Temp, 4);
		gzwrite(File, Section->Path + 1, Temp);
	} else {
		Temp = LIBRARY_ABS; gzwrite(File, &Temp, 1);
		Temp = strlen(Section->Path) + 1; gzwrite(File, &Temp, 4);
		gzwrite(File, Section->Path, Temp);
	};
};

static library_section_t *new_library_section(const char *Path) {
	static section_methods Methods = {
		default_section_setup,
		default_section_relocate,
		default_section_export,
		(void (*)(section_t *, FILE *))library_section_debug,
		(void (*)(section_t *, gzFile ))library_section_write
	};
	library_section_t *Section = new(library_section_t);
	((section_t *)Section)->Index = SEC_UNUSED;
	((section_t *)Section)->Methods = &Methods;
	memset(Section->Imports, 0, sizeof(Section->Imports));
	Section->Path = Path;
	stringtable_put(LibraryTable, Path, Section);
	return Section;
};

typedef struct import_section_t {
	section_t Base;
	library_section_t *Library;
	const char *Name;
	uint32_t Type;
} import_section_t;

static void import_section_setup(import_section_t *Section) {
	section_require((section_t *)Section->Library);
};

static void import_section_debug(import_section_t *Section, FILE *File) {
	fprintf(File, "%d: import section: %d.%s\n", ((section_t *)Section)->Index, ((section_t *)Section->Library)->Index, Section->Name);
};

static void import_section_write(import_section_t *Section, gzFile File) {
	uint32_t Temp = SECT_IMPORT; gzwrite(File, &Temp, 1);
	Temp = 0; gzwrite(File, &Temp, 1);
	Temp = ((section_t *)Section->Library)->Index; gzwrite(File, &Temp, 4);
	Temp = strlen(Section->Name) + 1; gzwrite(File, &Temp, 4);
	gzwrite(File, Section->Name, Temp);
};

static import_section_t *new_import_section(library_section_t *Library, const char *Name, int Type) {
	static section_methods Methods = {
		(void (*)(section_t *))import_section_setup,
		default_section_relocate,
		default_section_export,
		(void (*)(section_t *, FILE *))import_section_debug,
		(void (*)(section_t *, gzFile ))import_section_write
	};
	import_section_t *Section = new(import_section_t);
	((section_t *)Section)->Index = SEC_UNUSED;
	((section_t *)Section)->Methods = &Methods;
	Section->Name = Name;
	Section->Library = Library;
	Section->Type = Type;
	stringtable_put(Library->Imports, Name, Section);
	return Section;
};

typedef struct bss_section_t {
	section_t Base;
	uint32_t Size;
} bss_section_t;

static void bss_section_debug(bss_section_t *Section, FILE *File) {
	fprintf(File, "%d: bss section: %d\n", ((section_t *)Section)->Index, Section->Size);
};

static void bss_section_write(bss_section_t *Section, gzFile File) {
	uint32_t Temp = SECT_BSS; gzwrite(File, &Temp, 1);
	Temp = 0; gzwrite(File, &Temp, 1);
	Temp = Section->Size; gzwrite(File, &Temp, 4);
};

static bss_section_t *new_bss_section(uint32_t Size) {
	static section_methods Methods = {
		default_section_setup,
		default_section_relocate,
		default_section_export,
		(void (*)(section_t *, FILE *))bss_section_debug,
		(void (*)(section_t *, gzFile ))bss_section_write
	};
	bss_section_t *Section = new(bss_section_t);
	((section_t *)Section)->Index = SEC_UNUSED;
	((section_t *)Section)->Methods = &Methods;
	Section->Size = Size;
	return Section;
};

typedef struct symbol_section_t {
	section_t Base;
	const char *Name;
} symbol_section_t;

static void symbol_section_debug(symbol_section_t *Section, FILE *File) {
	fprintf(File, "%d: symbol section: \"%s\"\n", ((section_t *)Section)->Index, Section->Name);
};

static void symbol_section_write(symbol_section_t *Section, gzFile File) {
	uint32_t Temp = SECT_SYMBOL; gzwrite(File, &Temp, 1);
	Temp = 0; gzwrite(File, &Temp, 1);
	Temp = strlen(Section->Name) + 1; gzwrite(File, &Temp, 4);
	gzwrite(File, Section->Name, Temp);
};

static symbol_section_t *new_symbol_section(const char *Name) {
	static section_methods Methods = {
		default_section_setup,
		invalid_section_relocate,
		default_section_export,
		(void (*)(section_t *, FILE *))symbol_section_debug,
		(void (*)(section_t *, gzFile ))symbol_section_write
	};
	symbol_section_t *Section = new(symbol_section_t);
	((section_t *)Section)->Index = SEC_UNUSED;
	((section_t *)Section)->Methods = &Methods;
	Section->Name = Name;
	return Section;
};

typedef struct symbols_section_t {
	section_t Base;
	const char *Symbols;
} symbols_section_t;

static void symbols_section_relocate(symbols_section_t *Section, relocation_t *Relocation, uint32_t *Target) {
	const char *Name = Section->Symbols + *Target;
	*Target = 0;
	section_t *Symbol = (section_t *)stringtable_get(SymbolTable, Name);
	if (!Symbol) {
		Name = strdup(Name);
		Symbol = (section_t *)new_symbol_section(Name);
		stringtable_put(SymbolTable, Name, Symbol);
	};
	section_require(Symbol);
	Relocation->Section = Symbol;
};

static symbols_section_t *new_symbols_section(asection *Sect, bfd *Bfd) {
	static section_methods Methods = {
		invalid_section_setup,
		(void (*)(section_t *, relocation_t *, uint32_t *))symbols_section_relocate,
		0,
		0,
		0
	};
	symbols_section_t *Section = new(symbols_section_t);
	((section_t *)Section)->Index = SEC_UNUSED;
	((section_t *)Section)->Methods = &Methods;
	bfd_malloc_and_get_section(Bfd, Sect, (bfd_byte **)&Section->Symbols);
	return Section;
};

typedef struct bfd_info_t {
	const char *FileName;
	stringtable_t LocalTable;
	asymbol **Symbols;
} bfd_info_t;

typedef struct bfd_section_t bfd_section_t;

struct bfd_section_t {
	section_t Base;
	bfd *Bfd;
	bfd_info_t *BfdInfo;
	asection *Sect;
	uint32_t Flags;
	uint32_t Size;
	uint8_t *Code;
	uint32_t NoOfRelocs;
	relocation_t *Relocs;
	bfd_section_t *Next;
};

static void bfd_section_setup(bfd_section_t *Section) {
	bfd *Bfd = Section->Bfd;
	bfd_info_t *BfdInfo = Section->BfdInfo;
	asection *Sect = Section->Sect;
	Section->Size = bfd_get_section_size(Sect);
	bfd_malloc_and_get_section(Bfd, Sect, &Section->Code);
	arelent **Relocs = (arelent **)malloc(bfd_get_reloc_upper_bound(Bfd, Sect));
	Section->NoOfRelocs = bfd_canonicalize_reloc(Bfd, Sect, Relocs, BfdInfo->Symbols);
	Section->Relocs = (relocation_t *)malloc(sizeof(relocation_t) * Section->NoOfRelocs);
	for (int I = Section->NoOfRelocs - 1; I >= 0; --I) {
		relocation_t *Relocation = Section->Relocs + I;
		asymbol *Sym = *(Relocs[I]->sym_ptr_ptr);
		reloc_howto_type *Type = Relocs[I]->howto;
		Relocation->Position = Relocs[I]->address;
		Relocation->Size = bfd_get_reloc_size(Type);
		Relocation->Flags = Type->pc_relative ? RELOC_REL : RELOC_ABS;
		uint32_t *Target = (uint32_t *)(Section->Code + Relocs[I]->address);
		if (Type->pc_relative) {
#ifdef WINDOWS
			*(long *)(Section->Code + Relocs[I]->address) -= Relocs[I]->address + 4;// why oh why is this here???
#else
            *(long *)(Section->Code + Relocs[I]->address) -= Relocs[I]->address;// + 4 on windows platforms ???;
#endif
		};
		if (Sym->section == bfd_und_section_ptr) {
			symbol_t *Symbol;
			do {
				Symbol = (symbol_t *)stringtable_get(BfdInfo->LocalTable, Sym->name);
				if (Symbol) break;
				Symbol = (symbol_t *)stringtable_get(GlobalTable, Sym->name);
				if (Symbol) break;
				Symbol = (symbol_t *)stringtable_get(WeakTable, Sym->name);
				if (Symbol) break;
#ifdef WINDOWS
                char *WindowsSizeHint = strrchr(Sym->name, '@');
                if (WindowsSizeHint) {
                    *WindowsSizeHint = 0;
                    Symbol = (symbol_t *)stringtable_get(BfdInfo->LocalTable, Sym->name);
                    if (Symbol) break;
                    Symbol = (symbol_t *)stringtable_get(GlobalTable, Sym->name);
                    if (Symbol) break;
                    Symbol = (symbol_t *)stringtable_get(WeakTable, Sym->name);
                    if (Symbol) break;
                }
#endif
				printf("%s: unresolved symbol %s.\n", Bfd->filename, Sym->name);
				exit(1);
			} while (0);
			section_t *Section2 = Symbol->Section;
			section_relocate(Section2, Relocation, Target);
			if (Type->partial_inplace) *Target += (uint32_t)Symbol->Offset;
		} else if (Sym->section->userdata) {
			section_t *Section2 = (section_t *)Sym->section->userdata;
			section_relocate(Section2, Relocation, Target);
			if (Type->partial_inplace) *Target += (uint32_t)Sym->value;
		};
	};
};

static void bfd_section_debug(bfd_section_t *Section, FILE *File) {
	fprintf(File, "%d: text section: %d[%s]\n", ((section_t *)Section)->Index, Section->Size, (Section->Flags & FLAG_GC) ? "GC" : "NOGC");

	if (!(Section->Flags & FLAG_GC)) {
		ud_t UD[1];
		ud_init(UD);
		ud_set_mode(UD, 32);
		ud_set_syntax(UD, UD_SYN_INTEL);
		ud_set_input_buffer(UD, Section->Code, Section->Size);
		while (ud_disassemble(UD)) fprintf(File, "\t%6d: %s\n", (uint32_t)ud_insn_off(UD), ud_insn_asm(UD));
	};

	for (unsigned long I = 0; I < Section->NoOfRelocs; ++I) {
		relocation_t *Reloc = &Section->Relocs[I];
		fprintf(File, "\t%4x:\t%d[%d|%d]\n", Reloc->Position, Reloc->Section->Index, Reloc->Size, Reloc->Flags);
	};
};

static void bfd_section_write(bfd_section_t *Section, gzFile File) {
	uint32_t Temp = SECT_CODE; gzwrite(File, &Temp, 1);
	Temp = Section->Flags; gzwrite(File, &Temp, 1);
	Temp = Section->Size; gzwrite(File, &Temp, 4);
	Temp = Section->NoOfRelocs; gzwrite(File, &Temp, 4);
	gzwrite(File, Section->Code, Section->Size);
	for (unsigned long I = 0; I < Section->NoOfRelocs; ++I) {
		relocation_t *Reloc = &Section->Relocs[I];
		Temp = Reloc->Size; gzwrite(File, &Temp, 1);
		Temp = Reloc->Flags; gzwrite(File, &Temp, 1);
		Temp = Reloc->Position; gzwrite(File, &Temp, 4);
		Temp = Reloc->Section->Index; gzwrite(File, &Temp, 4);
	};
};

static bfd_section_t *new_bfd_section(asection *Sect, bfd *Bfd, bfd_info_t *BfdInfo) {
	static section_methods Methods = {
		(void (*)(section_t *))bfd_section_setup,
		default_section_relocate,
		default_section_export,
		(void (*)(section_t *, FILE *))bfd_section_debug,
		(void (*)(section_t *, gzFile ))bfd_section_write
	};
	bfd_section_t *Section = new(bfd_section_t);
	((section_t *)Section)->Index = SEC_UNUSED;
	((section_t *)Section)->Methods = &Methods;
	Section->Bfd = Bfd;
	Section->BfdInfo = BfdInfo;
	Section->Sect = Sect;
	Section->Next = 0;
	Section->Flags = 0;
	if (Sect->flags & SEC_DATA) Section->Flags |= FLAG_GC;
	return Section;
};

typedef struct method_section_t {
	section_t Base;
	bfd_section_t *Blocks;
	uint32_t Size;
	uint32_t NoOfRelocs;
} method_section_t;

static method_section_t *MethodSection = 0;

static void method_section_setup(method_section_t *Section) {
	for (bfd_section_t *Block = Section->Blocks; Block; Block = Block->Next) {
		bfd_section_setup(Block);
		Section->Size += Block->Size;
		Section->NoOfRelocs += Block->NoOfRelocs;
	};
};

static void method_section_debug(method_section_t *Section, FILE *File) {
	fprintf(File, "%d: methods section: %d\n", ((section_t *)Section)->Index, Section->Size);
};

static void method_section_write(method_section_t *Section, gzFile File) {
	uint32_t Temp = SECT_CODE; gzwrite(File, &Temp, 1);
	Temp = 0; gzwrite(File, &Temp, 1);
	Temp = Section->Size + 4; gzwrite(File, &Temp, 4);
	Temp = Section->NoOfRelocs; gzwrite(File, &Temp, 4);
	for (bfd_section_t *Block = Section->Blocks; Block; Block = Block->Next) gzwrite(File, Block->Code, Block->Size);
	Temp = 0xFFFFFFFF; gzwrite(File, &Temp, 4);
	uint32_t Offset = 0;
	for (bfd_section_t *Block = Section->Blocks; Block; Block = Block->Next) {
		for (unsigned long I = 0; I < Block->NoOfRelocs; ++I) {
			relocation_t *Reloc = &Block->Relocs[I];
			Temp = Reloc->Size; gzwrite(File, &Temp, 1);
			Temp = Reloc->Flags; gzwrite(File, &Temp, 1);
			Temp = Reloc->Position + Offset; gzwrite(File, &Temp, 4);
			Temp = Reloc->Section->Index; gzwrite(File, &Temp, 4);
		};
		Offset += Block->Size;
	};
};

static method_section_t *new_method_section() {
	static section_methods Methods = {
		(void (*)(section_t *))method_section_setup,
		invalid_section_relocate,
		default_section_export,
		(void (*)(section_t *, FILE *))method_section_debug,
		(void (*)(section_t *, gzFile ))method_section_write
	};
	if (MethodSection == 0) {
		MethodSection = new(method_section_t);
		((section_t *)MethodSection)->Methods = &Methods;
		((section_t *)MethodSection)->Index = SEC_UNUSED;
		MethodSection->Blocks = 0;
		MethodSection->Size = 0;
		MethodSection->NoOfRelocs = 0;
		new_export("<methods>", "__methods", EXP_CONSTANT);
		symbol_t *Symbol = new_symbol("<methods>", (section_t *)MethodSection, 0);
		stringtable_put(GlobalTable, "<methods>", Symbol);
	};
	return MethodSection;
};

typedef struct constant_section_t {
	section_t Base;
	uint32_t Flags;
	section_t *Init;
	uint32_t Offset;
} constant_section_t;

static void constant_section_debug(constant_section_t *Section, FILE *File) {
	fprintf(File, "%d: constant section: %d[%d]\n", ((section_t *)Section)->Index, Section->Init->Index, Section->Offset);
};

static void constant_section_write(constant_section_t *Section, gzFile File) {
	uint32_t Temp = SECT_CONSTANT; gzwrite(File, &Temp, 1);
	Temp = 0; gzwrite(File, &Temp, 1);
	Temp = ((section_t *)Section->Init)->Index; gzwrite(File, &Temp, 4);
	Temp = Section->Offset; gzwrite(File, &Temp, 4);
};

static void constant_section_setup(constant_section_t *Section) {
	section_require(Section->Init);
};

static constant_section_t *new_constant_section(void) {
	static section_methods Methods = {
		(void (*)(section_t *))constant_section_setup,
		default_section_relocate,
		default_section_export,
		(void (*)(section_t *, FILE *))constant_section_debug,
		(void (*)(section_t *, gzFile ))constant_section_write
	};
	constant_section_t *Section = new(constant_section_t);
	((section_t *)Section)->Index = SEC_UNUSED;
	((section_t *)Section)->Methods = &Methods;
	Section->Flags = 0;
	return Section;
};

typedef struct constants_section_t {
	section_t Base;
	asection *Sect;
	bfd *Bfd;
	bfd_info_t *BfdInfo;
	uint32_t NoOfConstants;
	constant_section_t **Constants;
} constants_section_t;

static void constants_section_relocate(constants_section_t *Section, relocation_t *Relocation, uint32_t *Target) {
	if (Section->Sect) {
		asection *Sect = Section->Sect;
		bfd *Bfd = Section->Bfd;
		bfd_info_t *BfdInfo = Section->BfdInfo;
		int Count = bfd_get_section_size(Sect) / 4;
		Section->Constants = malloc(sizeof(constant_section_t *) * Count);
		for (int I = 0; I < Count; I++) Section->Constants[I] = new_constant_section();
		uint8_t *Code;
		bfd_malloc_and_get_section(Bfd, Sect, &Code);
		arelent **Relocs = (arelent **)malloc(bfd_get_reloc_upper_bound(Bfd, Sect));
		for (int I = bfd_canonicalize_reloc(Bfd, Sect, Relocs, BfdInfo->Symbols) - 1; I >= 0; --I) {
			asymbol *Sym = *(Relocs[I]->sym_ptr_ptr);
			reloc_howto_type *Type = Relocs[I]->howto;
			constant_section_t *Constant = Section->Constants[Relocs[I]->address / 4];
			uint32_t *Target = (uint32_t *)(Code + Relocs[I]->address);
			if (Type->partial_inplace) *Target += (uint32_t)Sym->value;
			Constant->Init = (section_t *)Sym->section->userdata;
			Constant->Offset = *Target;
		};
		Section->Sect = 0;
	};
	constant_section_t *Constant = Section->Constants[*Target / 4];
	*Target = 0;
	section_require(Constant);
	Relocation->Section = Constant;
};

static void constants_section_export(constants_section_t *Section, uint32_t Offset, export_t *Export) {
	if (Section->Sect) {
		asection *Sect = Section->Sect;
		bfd *Bfd = Section->Bfd;
		bfd_info_t *BfdInfo = Section->BfdInfo;
		int Count = bfd_get_section_size(Sect) / 4;
		Section->Constants = malloc(sizeof(constant_section_t *) * Count);
		for (int I = 0; I < Count; I++) Section->Constants[I] = new_constant_section();
		uint8_t *Code;
		bfd_malloc_and_get_section(Bfd, Sect, &Code);
		arelent **Relocs = (arelent **)malloc(bfd_get_reloc_upper_bound(Bfd, Sect));
		for (int I = bfd_canonicalize_reloc(Bfd, Sect, Relocs, BfdInfo->Symbols) - 1; I >= 0; --I) {
			asymbol *Sym = *(Relocs[I]->sym_ptr_ptr);
			reloc_howto_type *Type = Relocs[I]->howto;
			constant_section_t *Constant = Section->Constants[Relocs[I]->address / 4];
			uint32_t *Target = (uint32_t *)(Code + Relocs[I]->address);
			if (Type->partial_inplace) *Target += (uint32_t)Sym->value;
			Constant->Init = (section_t *)Sym->section->userdata;
			Constant->Offset = *Target;
		};
		Section->Sect = 0;
	};
	constant_section_t *Constant = Section->Constants[Offset / 4];
	section_require(Constant);
	Export->Section = Constant;
	Export->Offset = 0;
};

static constants_section_t *new_constants_section(asection *Sect, bfd *Bfd, bfd_info_t *BfdInfo) {
	static section_methods Methods = {
		invalid_section_setup,
		(void (*)(section_t *, relocation_t *, uint32_t *))constants_section_relocate,
		(void (*)(section_t *, uint32_t, export_t *))constants_section_export,
		0,
		0
	};
	constants_section_t *Section = new(constants_section_t);
	((section_t *)Section)->Index = SEC_UNUSED;
	((section_t *)Section)->Methods = &Methods;
	Section->Sect = Sect;
	Section->Bfd = Bfd;
	Section->BfdInfo = BfdInfo;
	return Section;
};

static void add_bfd_section(bfd *Bfd, asection *Sect, bfd_info_t *BfdInfo) {
	if (strcmp(Sect->name, ".symbols") == 0) {
		if (Sect->size) Sect->userdata = new_symbols_section(Sect, Bfd);
	} else if (strcmp(Sect->name, ".methods") == 0) {
		if (Sect->size) {
			method_section_t *Section = new_method_section();
			bfd_section_t *Block = new_bfd_section(Sect, Bfd, BfdInfo);
			Block->Next = Section->Blocks;
			Section->Blocks = Block;
			Sect->userdata = Block;
		};
	} else if (strcmp(Sect->name, ".constants") == 0) {
		if (Sect->size) Sect->userdata = new_constants_section(Sect, Bfd, BfdInfo);
	} else if (Sect->flags & SEC_THREAD_LOCAL) {
		printf("Thread local storage not supported yet!\n");
		exit(1);
	} else if (Sect->flags & SEC_LOAD) {
		Sect->userdata = new_bfd_section(Sect, Bfd, BfdInfo);
	} else if (Sect->flags & SEC_ALLOC) {
		Sect->userdata = new_bss_section(bfd_get_section_size(Sect));
	};
};

typedef void (*bfd_map)(bfd *, asection *, void *);

static void add_bfd(bfd *Bfd) {
	if (bfd_check_format(Bfd, bfd_object)) {
		bfd_info_t *BfdInfo = new(bfd_info_t);
		BfdInfo->FileName = Bfd->filename;
		memset(BfdInfo->LocalTable, 0, sizeof(BfdInfo->LocalTable));
		BfdInfo->Symbols = (asymbol **)malloc(bfd_get_symtab_upper_bound(Bfd));
		int NoOfSymbols = bfd_canonicalize_symtab(Bfd, BfdInfo->Symbols);
		bfd_map_over_sections(Bfd, (bfd_map)add_bfd_section, BfdInfo);
		for (int I = NoOfSymbols - 1; I >= 0; --I) {
			asymbol *Sym = BfdInfo->Symbols[I];
			if (Sym->flags & BSF_GLOBAL) {
				const char *Name = strdup(Sym->name);
				symbol_t *Symbol = new_symbol(Name, (section_t *)Sym->section->userdata, Sym->value);
				stringtable_put(BfdInfo->LocalTable, Name, Symbol);
				stringtable_put(GlobalTable, Name, Symbol);
			} else if (Sym->section == bfd_com_section_ptr) {
				symbol_t *Symbol = (symbol_t *)stringtable_get(GlobalTable, Sym->name);
				bss_section_t *Section;
				if (!Symbol) {
					const char *Name = strdup(Sym->name);
					Section = new_bss_section(0);
					Symbol = new_symbol(Name, (section_t *)Section, 0);
					stringtable_put(GlobalTable, Name, Symbol);
					stringtable_put(BfdInfo->LocalTable, Name, Symbol);
				} else {
					Section = (bss_section_t *)Symbol->Section;
				};
				if (Sym->value > Section->Size) Section->Size = Sym->value;
			} else if (Sym->flags & BSF_LOCAL) {
				const char *Name = strdup(Sym->name);
				symbol_t *Symbol = new_symbol(Name, (section_t *)Sym->section->userdata, Sym->value);
				stringtable_put(BfdInfo->LocalTable, Name, Symbol);
			} else if (Sym->flags & BSF_WEAK) {
				const char *Name = strdup(Sym->name);
				symbol_t *Symbol = new_symbol(Name, (section_t *)Sym->section->userdata, Sym->value);
				stringtable_put(WeakTable, Name, Symbol);
			} else if (Sym->section == bfd_und_section_ptr) {
			} else if (Sym->flags & BSF_DEBUGGING) {
			    // This may be supported later
			} else {
				printf("%s: unknown symbol type: %8x.\n", Bfd->filename, Sym->flags);
				exit(1);
			};
		};
	} else if (bfd_check_format(Bfd, bfd_archive)) {
		bfd *Bfd2 = 0;
		while ((Bfd2 = bfd_openr_next_archived_file(Bfd, Bfd2))) add_bfd(Bfd2);
	};
};

static void add_object_file(const char *FileName) {
	bfd *Bfd = bfd_openr(FileName, 0);
	if (Bfd == 0) {
		printf("%s: error reading file.\n", FileName);
		return;
	};
	add_bfd(Bfd);
};

static const char EXPORT_CONSTANT[] = "CONSTANT";
static const char EXPORT_VARIABLE[] = "VARIABLE";

typedef struct export_type {
    const char *Name;
    int Flags;
} export_type;

static export_type ExportTypes[] = {
    {EXPORT_CONSTANT, 0},
    {EXPORT_VARIABLE, 1},
    {0, 0}
};

static const char *Platforms[] = {
    "WINDOWS",
    "LINUX",
    0
};

typedef struct library_file_t {
    const char *FileName;
    const char *Prefix;
    library_section_t *Section;
} library_file_t;

static int library_file_module(lua_State *State) {
    int NoOfArgs = lua_gettop(State);
    lua_getglobal(State, "Library");
    library_file_t *Library = lua_touserdata(State, -1);
    lua_pop(State, 1);

    int PathSize = 0;
    for (int I = 1; I <= NoOfArgs; ++I) PathSize += strlen(lua_tostring(State, I)) + 1;
    char *Path = (char *)malloc(PathSize), *PathPtr = Path;
#ifdef WINDOWS
    char *Name = (char *)malloc(PathSize + 1), *NamePtr = Name + 1;
    Name[0] = '_';
#else
	char *Name = (char *)malloc(PathSize), *NamePtr = Name;
#endif
    for (int I = 1; I <= NoOfArgs; ++I) {
        char *Temp = lua_tostring(State, I);
		PathPtr = stpcpy(PathPtr, Temp);
		*(PathPtr++) = '/';
		NamePtr = stpcpy(NamePtr, Temp);
		*(NamePtr++) = '$';
    };
    PathPtr[-1] = 0;
	NamePtr[-1] = 0;

	library_section_t *LibrarySection = (library_section_t *)stringtable_get(LibraryTable, Path);
	if (LibrarySection == 0) {
        LibrarySection = new_library_section(Path);
        symbol_t *Symbol = new(symbol_t);
        Symbol->Name = Name;
        Symbol->Section = (section_t *)LibrarySection;
        Symbol->Offset = 0;
        stringtable_put(GlobalTable, Name, Symbol);
	};

    Library->Section = LibrarySection;
    return 0;
};

static int library_file_prefix(lua_State *State) {
    lua_getglobal(State, "Library");
    library_file_t *Library = lua_touserdata(State, -1);
    lua_pop(State, 1);
    Library->Prefix = strdup(lua_tostring(State, 1));
    return 0;
};

static int library_file_export(lua_State *State) {
    int NoOfArgs = lua_gettop(State);
    lua_getglobal(State, "Library");
    library_file_t *Library = lua_touserdata(State, -1);
    lua_pop(State, 1);
    int Flags = 0;
    const char *Internal = 0;
    const char *External = 0;
    for (int I = 1; I <= NoOfArgs; ++I) {
        if (lua_isstring(State, I)) {
            if (Internal == 0) {
                Internal = strdup(lua_tostring(State, I));
            } else {
                External = strdup(lua_tostring(State, I));
            };
        } else if (lua_isuserdata(State, I)) {
            void *Name = lua_touserdata(State, I);
            for (export_type *E = ExportTypes; E->Name; ++E) {
                if (E->Name == Name) {
                    Flags = E->Flags;
                    break;
                };
            };
        };
    };
    if (External == 0) asprintf(&External, "%s%s", Library->Prefix, Internal);

    //printf("Adding export: %s -> %s\n", Internal, External);

    import_section_t *ImportSection = (import_section_t *)stringtable_get(Library->Section->Imports, Internal);
    if (ImportSection == 0) {
        ImportSection = new_import_section(Library->Section, Internal, Flags);
    };
    symbol_t *Symbol = new_symbol(External, (section_t *)ImportSection, 0);
    stringtable_put(GlobalTable, External, Symbol);
    return 0;
};

static void add_file(const char *FileName);

static int library_file_include(lua_State *State) {
	add_file(lua_tostring(State, 1));
	return 0;
};

static void add_library_file(const char *FileName) {
    lua_State *State = luaL_newstate();
    lua_register(State, "module", library_file_module);
    lua_register(State, "prefix", library_file_prefix);
    lua_register(State, "export", library_file_export);
    lua_register(State, "include", library_file_include);
    lua_pushstring(State, Platform);
    lua_setglobal(State, "Platform");
    for (const char **P = Platforms; *P; ++P) {
        lua_pushboolean(State, strcmp(Platform, *P) == 0);
        lua_setglobal(State, *P);
    };
    for (export_type *E = ExportTypes; E->Name; ++E) {
        lua_pushlightuserdata(State, E->Name);
        lua_setglobal(State, E->Name);
    };

    library_file_t *Library = new(library_file_t);
    Library->FileName = FileName;
    Library->Prefix = "";
    Library->Section = 0;
    lua_pushlightuserdata(State, Library);
    lua_setglobal(State, "Library");

    if (luaL_dofile(State, FileName)) {
        printf("%s: error parsing file.\n", FileName);
    };
};

static int definition_file_library(lua_State *State) {
	add_file(lua_tostring(State, 1));
	return 0;
};

static int definition_file_export(lua_State *State) {
    const char *Internal = 0;
    const char *External = 0;
    int Flags = 0;
    int NoOfArgs = lua_gettop(State);
    for (int I = 1; I <= NoOfArgs; ++I) {
        if (lua_isstring(State, I)) {
            if (Internal == 0) {
                External = Internal = strdup(lua_tostring(State, I));
            } else {
                External = strdup(lua_tostring(State, I));
            };
        } else if (lua_isuserdata(State, I)) {
            void *Name = lua_touserdata(State, I);
            for (export_type *E = ExportTypes; E->Name; ++E) {
                if (E->Name == Name) {
                    Flags = E->Flags;
                    break;
                };
            };
        };
    };
    //printf("Adding export %s -> %s[%d]\n", Internal, External, Flags);
    new_export(Internal, External, Flags);
    return 0;
};

static int definition_file_symbol(lua_State *State) {
    const char *Internal = strdup(lua_tostring(State, 1));
    const char *External = strdup(lua_tostring(State, 2));
 
    //printf("Adding symbol: %s -> %s\n", Internal, External);

    section_t *Symbol = (section_t *)stringtable_get(SymbolTable, Internal);
	if (!Symbol) {
		Internal = strdup(Internal);
		Symbol = (section_t *)new_symbol_section(Internal);
		stringtable_put(SymbolTable, Internal, Symbol);
	};
	section_require(Symbol);
	export_t *Export = new(export_t);
	Export->Internal = Internal;
	Export->External = External;
	Export->Section = Symbol;
	Export->Offset = 0;
	Export->Flags = 0;
	Export->Next = 0;
	++NoOfExports;
	if (Exports.Head) {
		Exports.Tail->Next = Export;
		Exports.Tail = Export;
	} else {
		Exports.Head = Exports.Tail = Export;
	};
    return 0;
};

static int definition_file_require(lua_State *State) {
	char *Library = lua_tostring(State, 1);
	if (Library[0] == '.') {
		new_require(LIBRARY_REL, strdup(Library + 1));
	} else {
		new_require(LIBRARY_ABS, strdup(Library));
	};
	return 0;
};

static void add_definition_file(const char *FileName) {
    lua_State *State = luaL_newstate();
    lua_register(State, "export", definition_file_export);
	lua_register(State, "symbol", definition_file_symbol);
    lua_register(State, "library", definition_file_library);
    lua_register(State, "require", definition_file_require);
    lua_pushstring(State, Platform);
    lua_setglobal(State, "Platform");
    for (const char **P = Platforms; *P; ++P) {
        lua_pushboolean(State, strcmp(Platform, *P) == 0);
        lua_setglobal(State, *P);
    };
    for (export_type *E = ExportTypes; E->Name; ++E) {
        lua_pushlightuserdata(State, E->Name);
        lua_setglobal(State, E->Name);
    };
    if (luaL_dofile(State, FileName)) {
        printf("%s: error parsing file.\n", FileName);
    };
};

static stringtable_t SupportedFiles = {0, 0, 0, 0};

typedef void (*file_adder)(const char *);

typedef struct search_path_t {
	const char *Path;
	struct search_path_t *Next;
} search_path_t;

static search_path_t SearchPath = {"", 0};
static search_path_t *SearchPathTail = &SearchPath;

static void add_path(const char *Path) {
	search_path_t *Node = new(search_path_t);
	Node->Path = strdup(Path);
	Node->Next = 0;
	SearchPathTail->Next = Node;
	SearchPathTail = Node;
};

static void add_file(const char *FileName) {
	const char *Extension = strrchr(FileName, '.');
	if (Extension == 0) {
		printf("%s: filename must include extension.\n", FileName);
		return;
	};
	file_adder _add = (file_adder)stringtable_get(SupportedFiles, Extension);
	if (_add == 0) {
		printf("%s: unable to determine file type from extension.\n", FileName);
		return;
	};
	struct stat Stat;
	char FullFileName[256];
	for (search_path_t *Node = &SearchPath; Node; Node = Node->Next) {
		sprintf(FullFileName, "%s%s", Node->Path, FileName);
		if (stat(FullFileName, &Stat) == 0) {
			_add(strdup(FullFileName));
			return;
		};
	};
	printf("%s: file not found.\n", FileName);
	exit(1);
};


int main(int Argc, char **Argv) {
	if (Argc < 2) {
		puts("Usage: rlink [-o output] [-l listing] inputs ... ");
	} else {
		bfd_init();
		stringtable_put(SupportedFiles, ".rlib", (void *)add_library_file);
		stringtable_put(SupportedFiles, ".rdef", (void *)add_definition_file);
		stringtable_put(SupportedFiles, ".a", (void *)add_object_file);
		stringtable_put(SupportedFiles, ".o", (void *)add_object_file);
		stringtable_put(SupportedFiles, ".obj", (void *)add_object_file);
		stringtable_put(SupportedFiles, ".mo", (void *)add_object_file);
		stringtable_put(SupportedFiles, ".io", (void *)add_object_file);
		char *OutFile = 0;
		char *ListFile = 0;
		for (int I = 1; I < Argc; ++I) {
			if (Argv[I][0] == '-') {
				switch (Argv[I][1]) {
				case 'o':
					OutFile = Argv[I] + 2;
					break;
				case 'l':
					add_file(Argv[I] + 2);
					break;
				case 'L':
					add_path(Argv[I] + 2);
				case 's':
					break;
                case 'm':
                    Platform = Argv[I] + 2;
				case '?':
					ListFile = Argv[I] + 2;
					break;
				};
			} else {
				add_file(Argv[I]);
			};
		};
		for (export_t *Export = Exports.Head; Export; Export = Export->Next) {
			if (Export->Section == 0) {
				symbol_t *Symbol = (symbol_t *)stringtable_get(GlobalTable, Export->Internal);
				if (Symbol == 0) Symbol = (symbol_t *)stringtable_get(WeakTable, Export->Internal);
				if (Symbol) {
					section_export(Symbol->Section, Symbol->Offset, Export);
				} else {
					printf("exported symbol not found: %s.\n", Export->Internal);
					exit(1);
				};
			};
		};
		if (ListFile) {
			FILE *File = fopen(ListFile, "w");
			for (section_t *Section = Sections.Head; Section; Section = Section->Next) section_debug(Section, File);
			for (export_t *Export = Exports.Head; Export; Export = Export->Next) {
				fprintf(File, "export: %s -> %d[%d]\n", Export->External, Export->Section->Index, Export->Offset);
			};
			for (require_t *Require = Requires.Head; Require; Require = Require->Next) {
				fprintf(File, "require: %s[%d]\n", Require->Library, Require->Flags);
			};
			fclose(File);
		};
		if (OutFile) {
			uint32_t Temp;
			gzFile File = gzopen(OutFile, "wb9");
			gzwrite(File, "RIVA", 4);
			Temp = NoOfSections; gzwrite(File, &Temp, 4);
			Temp = NoOfExports; gzwrite(File, &Temp, 4);
			Temp = NoOfRequires; gzwrite(File, &Temp, 4);
			for (section_t *Section = Sections.Head; Section; Section = Section->Next) section_write(Section, File);
			for (export_t *Export = Exports.Head; Export; Export = Export->Next) {
				Temp = Export->Flags; gzwrite(File, &Temp, 1);
				Temp = Export->Section->Index; gzwrite(File, &Temp, 4);
				Temp = Export->Offset; gzwrite(File, &Temp, 4);
				Temp = strlen(Export->External); gzwrite(File, &Temp, 4);
				gzwrite(File, Export->External, Temp);
			};
			for (require_t *Require = Requires.Head; Require; Require = Require->Next) {
				Temp = Require->Flags; gzwrite(File, &Temp, 1);
				Temp = strlen(Require->Library); gzwrite(File, &Temp, 4);
				gzwrite(File, Require->Library, Temp);
			};
			gzclose(File);
		};
	};
};
