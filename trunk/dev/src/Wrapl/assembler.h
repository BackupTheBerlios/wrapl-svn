#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <Riva/Memory.h>

#define TRACE {printf("%s:%d\n", __FILE__, __LINE__);}

#include <stdint.h>
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
	enum {CNST = 0, GVAR = 1, LVAR, LREF, TEMP, CLSR, FUTR, REGR} Type;
	union {
		struct {uint32_t Index; int32_t Loop;};
		Std$Object_t *Value;
		struct {void *Entry; upscope_t *UpScopes;};
		Std$Object_t **Address;
		struct {const char *Module, *Import;};
	};
};

extern operand_t Register[];

struct load_inst_t;

struct label_t;

struct inst_t {
	inst_t *Next;
	operand_t *Ecx, *Edx;
	int LineNo;

	virtual void list() {};
	virtual void add_sources() {};
	virtual void add_source(load_inst_t *Load) {};
	virtual void append_links(label_t *Start) {};
	virtual int noof_consts() {return 0;};
	virtual void **get_consts(void **Ptr) {return Ptr;};
	virtual void encode(assembler_t *Assembler) {};
};

struct load_inst_t : inst_t {
	enum {LOAD_NONE, LOAD_VAL, LOAD_REF, LOAD_BOTH, LOAD_ARG} Type;
	operand_t *Operand;

	void list();
	void add_sources() {Next->add_source(this);};
	int noof_consts();
	void **get_consts(void **);
	void encode(assembler_t *Assembler);

	void load_val() {
		switch (Type) {
		case LOAD_NONE: Type = LOAD_VAL; return;
		case LOAD_VAL: return;
		case LOAD_REF: Type = LOAD_BOTH; return;
		case LOAD_BOTH: return;
		case LOAD_ARG: Type = LOAD_BOTH; return;
		};
	};
	void load_ref() {
		switch (Type) {
		case LOAD_NONE: Type = LOAD_REF; return;
		case LOAD_VAL: Type = LOAD_BOTH; return;
		case LOAD_REF: return;
		case LOAD_BOTH: return;
		case LOAD_ARG: return;
		};
	};
	void load_both() {
		Type = LOAD_BOTH;
	};
	void load_arg() {
		switch (Type) {
		case LOAD_NONE: Type = LOAD_ARG; return;
		case LOAD_VAL: Type = LOAD_BOTH; return;
		case LOAD_REF: Type = LOAD_ARG; return;
		case LOAD_BOTH: return;
		case LOAD_ARG: return;
		};
	};
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
	
	void list();
	void add_source(load_inst_t *Load) {Load->load_val();};
	void append_links(label_t *Start);
	void encode(assembler_t *Assembler);
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
	
	void list();
	void add_source(load_inst_t *Load) {Load->load_val();};
	void append_links(label_t *Start);
	int noof_consts();
	void **get_consts(void **Ptr);
	void encode(assembler_t *Assembler);	
};

struct select_object_inst_t : inst_t {
	struct case_t {
		case_t *Next;
		label_t *Body;
		Std$Object_t *Object;
	};
	case_t *Cases;
	label_t *Default;
	
	void list();
	void add_source(load_inst_t *Load) {Load->load_val();};
	void append_links(label_t *Start);
	int noof_consts();
	void **get_consts(void **Ptr);
	void encode(assembler_t *Assembler);
};

struct label_t : inst_t {
	label_t *Link;
	inst_t *Tail;
	bool Done, Used;
	int Offset;

	label_t *final() {
		if (Link == 0) return this;
		if (Next) return this;
		return Link->final();
	};

	void list() {
		if (Next) printf("%x:\n", this);
	};

	void append(inst_t *Inst) {
		if (Tail) {
			Tail->Next = Inst;
		} else {
			Next = Inst;
		};
		Tail = Inst;
	};

	void link(label_t *U) {Link = U;};
	void scope(uint32_t Level, uint32_t Size);
	void zero(uint32_t Trap, label_t *Failure);
	void trap(uint32_t Trap, label_t *Failure);
	void resume();
	void load(operand_t *Operand);
	void store_val(operand_t *Operand);
	void store_ref(operand_t *Operand);
	void store_tmp(uint32_t Index);
	void store_con(operand_t *Operand, Std$Object_t *Value);
	void flush();
	void store_arg(uint32_t Index, operand_t *Operand);
	void fixup_arg(uint32_t Index, operand_t *Operand);
	void invoke(uint32_t Trap, uint32_t Args, uint32_t Count, label_t *Fixup);
	void back(uint32_t Trap);
	void fail();
	void ret();
	void susp();
	void recv(label_t *Handler);
	void send();
	void comp(int Equal, operand_t *Operand, label_t *Failure);
	void limit(uint32_t Trap, uint32_t Trap0, long Count);
	void select_integer(select_integer_inst_t::case_t *Cases, label_t *Default);
	void select_string(select_string_inst_t::case_t *Cases, label_t *Default);
	void select_object(select_object_inst_t::case_t *Cases, label_t *Default);
	void type_of();
	
	operand_t *assemble(const frame_t *Function, operand_t *Closure = 0);

	void add_source(load_inst_t *Load) {
		if (Next) {
			Next->add_source(Load);
		} else {
			Link->add_source(Load);
		};
	};
	void encode(assembler_t *Assembler);
};

#endif
