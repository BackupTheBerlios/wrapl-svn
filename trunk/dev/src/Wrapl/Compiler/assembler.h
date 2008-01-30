#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <Riva/Memory.h>

#define TRACE {printf("%s:%d\n", __FILE__, __LINE__);}
//#define ASSEMBLER_LISTING

#include <stdint.h>
#include <stdio.h>
#include <IO/Stream.h>
#include <Sys/Module.h>
#include "stringtable.h"

struct assembler_t;

struct closure_t {
	Std$Type_t *Type;
	void *Entry;
	void *Scopes[];
};

struct upscope_t {
	upscope_t *Next;
	uint32_t Index;
};

struct operand_t {
	operand_t *Next;
	enum {CNST = 0, GVAR = 1, LVAR, LREF, TEMP, CLSR, FUTR, REGR, EXTN} Type;
	union {
		struct {const char *Value; Std$Object_t *Simple;};
		const char *Address;
		struct {uint32_t Index; int32_t Loop;};
		struct {const char *Entry; upscope_t *UpScopes;};
		struct {const char *Path, *Name, *Import;};
		struct {const char *External; void *Module;};
	};
};

extern operand_t Register[];

struct load_inst_t;

struct label_t;

struct inst_t {
	inst_t *Next;
	operand_t *Ecx, *Edx;
	int LineNo;
	bool IsPotentialBreakpoint;

#ifdef ASSEMBLER_LISTING
	virtual void list() {printf("\tunknown\n");};
#endif
	virtual void add_sources() {};
	virtual void add_source(load_inst_t *Load) {};
	virtual void append_links(label_t *Start) {};
	virtual int noof_consts() {return 0;};
	virtual void **get_consts(void **Ptr) {return Ptr;};
	virtual void encode(assembler_t *Assembler) {};
	virtual void find_breakpoints();
};

struct load_inst_t : inst_t {
	enum {LOAD_NONE, LOAD_VAL, LOAD_REF, LOAD_BOTH, LOAD_ARG} Type;
	operand_t *Operand;

#ifdef ASSEMBLER_LISTING
	void list();
#endif
	void add_sources() {Next->add_source(this);};
	int noof_consts();
	void **get_consts(void **);
	void encode(assembler_t *Assembler);

	void load_val();
	void load_ref();
	void load_both();
	void load_arg();
};

struct select_case_t {
	select_case_t *Next;
	void *Value;
	label_t *Body;
};

struct frame_t {
	uint32_t NoOfLocals;
	uint32_t NoOfTemps;
	uint32_t NoOfScopes;
	uint32_t NoOfUpScopes;
	uint32_t NoOfTraps;
	uint32_t NoOfParams;
	bool Variadic;
	upscope_t *UpScopes;
};

#include <stdio.h>

struct select_integer_inst_t : inst_t {
	struct case_t {
		case_t *Next;
		label_t *Body;
		int32_t Min, Max;
	};
	case_t *Cases;
	label_t *Default;

#ifdef ASSEMBLER_LISTING
	void list();
#endif
	void add_source(load_inst_t *Load) {Load->load_val();};
	void append_links(label_t *Start);
	void encode(assembler_t *Assembler);
	void find_breakpoints();
};

struct select_string_inst_t : inst_t {
	struct case_t {
		case_t *Next;
		label_t *Body;
		const char *Key;
		uint32_t Length;
	};
	case_t *Cases;
	label_t *Default;

#ifdef ASSEMBLER_LISTING
	void list();
#endif
	void add_source(load_inst_t *Load) {Load->load_val();};
	void append_links(label_t *Start);
	int noof_consts();
	void **get_consts(void **Ptr);
	void encode(assembler_t *Assembler);
	void find_breakpoints();
};

struct select_object_inst_t : inst_t {
	struct case_t {
		case_t *Next;
		label_t *Body;
		const char *Object;
	};
	case_t *Cases;
	label_t *Default;

#ifdef ASSEMBLER_LISTING
	void list();
#endif
	void add_source(load_inst_t *Load) {Load->load_val();};
	void append_links(label_t *Start);
	int noof_consts();
	void **get_consts(void **Ptr);
	void encode(assembler_t *Assembler);
	void find_breakpoints();
};

struct label_t : inst_t {
	label_t *Link;
	inst_t *Tail;
	bool Done, Referenced;
	int Label;

	label_t *final();

#ifdef ASSEMBLER_LISTING
	void list();
#endif

	void append(inst_t *Inst);

	void link(uint32_t LineNo, label_t *U) {Link = U;};
	void scope(uint32_t LineNo, uint32_t Level, uint32_t Size);
	void init_trap(uint32_t LineNo, uint32_t Trap, label_t *Failure);
	void push_trap(uint32_t LineNo, uint32_t Trap, label_t *Failure, uint32_t Temp);
	void store_link(uint32_t LineNo, uint32_t Temp, label_t *Target);
	void jump_link(uint32_t LineNo, uint32_t Temp);
	void resume(uint32_t LineNo);
	void load(uint32_t LineNo, operand_t *Operand);
	void store_val(uint32_t LineNo, operand_t *Operand);
	void store_ref(uint32_t LineNo, operand_t *Operand);
	void store_tmp(uint32_t LineNo, uint32_t Index);
	void store_con(uint32_t LineNo, operand_t *Operand, const char *Value);
	void flush(uint32_t LineNo);
	void store_arg(uint32_t LineNo, uint32_t Index, operand_t *Operand);
	void fixup_arg(uint32_t LineNo, uint32_t Index, operand_t *Operand);
	void invoke(uint32_t LineNo, uint32_t Trap, uint32_t Args, uint32_t Count, label_t *Fixup);
	void back(uint32_t LineNo, uint32_t Trap);
	void fail(uint32_t LineNo);
	void ret(uint32_t LineNo);
	void susp(uint32_t LineNo);
	void recv(uint32_t LineNo, label_t *Handler);
	void send(uint32_t LineNo);
	void comp(uint32_t LineNo, int Equal, operand_t *Operand, label_t *Failure);
	void limit(uint32_t LineNo, uint32_t Trap, uint32_t Temp);
	void test_limit(uint32_t LineNo, uint32_t Temp, label_t *Failure);
	void skip(uint32_t LineNo, uint32_t Temp);
	void test_skip(uint32_t LineNo, uint32_t Trap, uint32_t Temp);
	void select_integer(uint32_t LineNo, select_integer_inst_t::case_t *Cases, label_t *Default);
	void select_string(uint32_t LineNo, select_string_inst_t::case_t *Cases, label_t *Default);
	void select_object(uint32_t LineNo, select_object_inst_t::case_t *Cases, label_t *Default);
	void type_of(uint32_t LineNo);
	void new_list(uint32_t LineNo, uint32_t Index);
	void store_list(uint32_t LineNo, uint32_t Index);

	operand_t *assemble(const frame_t *Function, IO$Stream_t *Output, operand_t *Closure = 0);

	void add_source(load_inst_t *Load);
	void encode(assembler_t *Assembler);
};

typedef struct debug_module_t {
	
} debug_module_t;

#endif
