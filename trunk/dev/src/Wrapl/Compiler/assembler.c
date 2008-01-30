#include "assembler.h"
#include "missing.h"
#include <Std.h>
#include <string.h>

struct state_t {
	void *Run;
	state_t *Chain;
	void *Resume;
};

struct bstate_t {
	void *Run;
	state_t *Chain;
	void *Resume;
	Std$Object_t *Val;
	Std$Object_t **Ref;
	void *Code;
	void *Handler;
	void *Data;
};

operand_t Register[] = {{
	0, operand_t::REGR
}};

#ifdef ASSEMBLER_LISTING

#include <udis86.h>

static const char *listop(operand_t *Operand) {
	char *List;
	switch (Operand->Type) {
	case operand_t::CNST: {
		char *Module, *Import;
		if (Riva$Module$lookup(Operand->Value, &Module, &Import)) {
			asprintf(&List, "CNST:%s.%s", Module, Import);
		} else {
			asprintf(&List, "CNST:%x", Operand->Value);
		};
		return List;
	};
	case operand_t::GVAR: asprintf(&List, "GVAR:%x", Operand->Address); return List;
	case operand_t::LVAR: asprintf(&List, "LVAR:%d[%d]", Operand->Loop, Operand->Index); return List;
	case operand_t::LREF: asprintf(&List, "LREF:%d[%d]", Operand->Loop, Operand->Index); return List;
	case operand_t::TEMP: asprintf(&List, "TEMP:%d", Operand->Index); return List;
	case operand_t::CLSR: asprintf(&List, "CLSR:%x", Operand->Value); return List;
	case operand_t::FUTR: asprintf(&List, "FUTR"); return List;
	case operand_t::REGR: asprintf(&List, "REGR"); return List;
	};
};

#endif

void inst_t::find_breakpoints() {
	if (Next && (Next->LineNo != LineNo)) Next->IsPotentialBreakpoint = true;
};

struct link_inst_t : inst_t {
	label_t *Link;
#ifdef ASSEMBLER_LISTING
	void list() {
		if (IsPotentialBreakpoint) printf("*");
		printf("%d:\tlink %x\n", LineNo, Link->final());
	};
#endif
	void add_source(load_inst_t *Load) {
		Link->add_source(Load);
	};
	void encode(assembler_t *Assembler);
};

static void use_label(label_t *Start, label_t *Next, bool Follow) {
	if (!Follow) Next->final()->Referenced = true;
	if (Next->Done) {
		if (Follow) {
			link_inst_t *Inst = new link_inst_t;
			Inst->Link = Next;
			Inst->LineNo = Next->LineNo;
			Next->final()->Referenced = true;
			Start->append(Inst);
		};
	} else {
		Next->Done = true;
		if (Next->Next) {
			if (Start->Tail) {
				Start->Tail->Next = Next;
			} else {
				Start->Next = Next;
			};
			Start->Tail = Next->Tail;
			label_t *Link = Next->Link;
			if (Link) use_label(Start, Link, true);
			inst_t *Tail = Next->Tail;
			inst_t *Inst = Next;
			do {
				Inst = Inst->Next;
				Inst->append_links(Start);
			} while (Inst != Tail);
		} else {
			use_label(Start, Next->Link, Follow);
		};
	};
};

struct scope_inst_t : inst_t {
	uint32_t Index, Size;
#ifdef ASSEMBLER_LISTING
	void list() {
		if (IsPotentialBreakpoint) printf("*");
		printf("%d:\tscope %d <- %d\n", LineNo, Index, Size);
	};
#endif
	void encode(assembler_t *Assembler);
};

void label_t::scope(uint32_t LineNo, uint32_t Index, uint32_t Size) {
	scope_inst_t *Inst = new scope_inst_t;
	Inst->Index = Index;
	Inst->Size = Size;
	Inst->LineNo = LineNo;
	Inst->IsPotentialBreakpoint = false;
	append(Inst);
};

struct init_trap_inst_t : inst_t {
	uint32_t Trap;
	label_t *Failure;
	state_t *State;

	int noof_consts() {return 1;};
	void **get_consts(void **);


	void append_links(label_t *Start) {
		use_label(Start, Failure, false);
	};
	void find_breakpoints() {
		if (Next->LineNo != LineNo) Next->IsPotentialBreakpoint = true;
		Failure->IsPotentialBreakpoint = true;
	};
#ifdef ASSEMBLER_LISTING
	void list() {
		if (IsPotentialBreakpoint) printf("*");
		printf("%d:\tzero %d <- %x\n", LineNo, Trap, Failure->final());
	};
#endif
	void encode(assembler_t *Assembler);
};

void **init_trap_inst_t::get_consts(void **Ptr) {
	Ptr[0] = State;
	return Ptr + 1;
};

void label_t::init_trap(uint32_t LineNo, uint32_t Trap, label_t *Failure) {
	init_trap_inst_t *Inst = new init_trap_inst_t;
	Inst->Trap = Trap;
	label_t *Failure0 = new label_t();
	Failure0->resume(LineNo);
	Failure0->link(LineNo, Failure);
	Inst->Failure = Failure0;
	Inst->State = new state_t;
	Inst->LineNo = LineNo;
	Inst->IsPotentialBreakpoint = false;
	append(Inst);
};

struct push_trap_inst_t : inst_t {
	uint32_t Trap;
	label_t *Failure;
	uint32_t Temp;

	void append_links(label_t *Start) {
		use_label(Start, Failure, false);
	};
	void find_breakpoints() {
		if (Next->LineNo != LineNo) Next->IsPotentialBreakpoint = true;
		Failure->IsPotentialBreakpoint = true;
	};
#ifdef ASSEMBLER_LISTING
	void list() {
		if (IsPotentialBreakpoint) printf("*");
		printf("%d:\ttrap %d <- %x\n", LineNo, Trap, Failure);
	};
#endif
	void encode(assembler_t *Assembler);
};

void label_t::push_trap(uint32_t LineNo, uint32_t Trap, label_t *Failure, uint32_t Temp) {
	push_trap_inst_t *Inst = new push_trap_inst_t;
	Inst->Trap = Trap;
	Inst->Temp = Temp;
	label_t *Failure0 = new label_t();
	Failure0->resume(LineNo);
	Failure0->link(LineNo, Failure);
	Inst->Failure = Failure0;
	Inst->LineNo = LineNo;
	Inst->IsPotentialBreakpoint = false;
	append(Inst);
};

struct resume_inst_t : inst_t {
#ifdef ASSEMBLER_LISTING
	void list() {
		if (IsPotentialBreakpoint) printf("*");
		printf("%d:\tresume\n", LineNo);
	};
#endif
	void encode(assembler_t *Assembler);
};

void label_t::resume(uint32_t LineNo) {
	resume_inst_t *Inst = new resume_inst_t;
	Inst->LineNo = LineNo;
	Inst->IsPotentialBreakpoint = false;
	append(Inst);
};

void load_inst_t::load_val() {
	switch (Type) {
	case LOAD_NONE: Type = LOAD_VAL; return;
	case LOAD_VAL: return;
	case LOAD_REF: Type = LOAD_BOTH; return;
	case LOAD_BOTH: return;
	case LOAD_ARG: Type = LOAD_BOTH; return;
	};
};

void load_inst_t::load_ref() {
	switch (Type) {
	case LOAD_NONE: Type = LOAD_REF; return;
	case LOAD_VAL: Type = LOAD_BOTH; return;
	case LOAD_REF: return;
	case LOAD_BOTH: return;
	case LOAD_ARG: return;
	};
};

void load_inst_t::load_both() {
	Type = LOAD_BOTH;
};

void load_inst_t::load_arg() {
	switch (Type) {
	case LOAD_NONE: Type = LOAD_ARG; return;
	case LOAD_VAL: Type = LOAD_BOTH; return;
	case LOAD_REF: Type = LOAD_ARG; return;
	case LOAD_BOTH: return;
	case LOAD_ARG: return;
	};
};

int load_inst_t::noof_consts() {
	switch (Operand->Type) {
	case operand_t::CNST: return 1;
	case operand_t::GVAR: return 1;
	case operand_t::CLSR: return 1;
	default: return 0;
	};
};

void **load_inst_t::get_consts(void **Ptr) {
	switch (Operand->Type) {
	case operand_t::CNST:
		Ptr[0] = Operand->Value;
		return Ptr + 1;
	case operand_t::GVAR:
		Ptr[0] = Operand->Address;
		return Ptr + 1;
	case operand_t::CLSR:
		Ptr[0] = Operand->Entry;
		return Ptr + 1;
	default: return Ptr;
	};
};

#ifdef ASSEMBLER_LISTING
void load_inst_t::list() {
	if (IsPotentialBreakpoint) printf("*");
	static const char *Types[] = {
		"_none", "_val", "_ref", "_both", "_arg"
	};
	printf("%d:\tload%s %s\n", LineNo, Types[Type], listop(Operand));
};
#endif

void label_t::load(uint32_t LineNo, operand_t *Operand) {
	if (Operand == Register) return;
	load_inst_t *Inst = new load_inst_t;
	Inst->Operand = Operand;
	Inst->LineNo = LineNo;
	Inst->IsPotentialBreakpoint = false;
	append(Inst);
};

struct store_con_inst_t : load_inst_t {
	const char *Value;
#ifdef ASSEMBLER_LISTING
	void list() {
		if (IsPotentialBreakpoint) printf("*");
		printf("%d:\tstore_con %s <- %s\n", LineNo, listop(Operand), Value);
	};
#endif
	int noof_consts() {return 1;};
	void **get_consts(void **Ptr) {Ptr[0] = Value; return Ptr + 1;};
	void encode(assembler_t *Assembler);
};

void label_t::store_con(uint32_t LineNo, operand_t *Operand, const char *Value) {
	store_con_inst_t *Inst = new store_con_inst_t;
	Inst->Operand = Operand;
	Inst->Value = Value;
	Inst->LineNo = LineNo;
	Inst->IsPotentialBreakpoint = false;
	append(Inst);
};

struct store_val_inst_t : inst_t {
	operand_t *Operand;
	void add_source(load_inst_t *Load) {
		Load->load_val();
		Next->add_source(Load);
	};
#ifdef ASSEMBLER_LISTING
	void list() {
		if (IsPotentialBreakpoint) printf("*");
		printf("%d:\tstore_val %s\n", LineNo, listop(Operand));
	};
#endif
	void encode(assembler_t *Assembler);
};

struct store_ref_inst_t : inst_t {
	operand_t *Operand;
	void add_source(load_inst_t *Load) {
		Load->load_ref();
		Next->add_source(Load);
	};
#ifdef ASSEMBLER_LISTING
	void list() {
		if (IsPotentialBreakpoint) printf("*");
		printf("%d:\tstore_ref %s\n", LineNo, listop(Operand));
	};
#endif
	void encode(assembler_t *Assembler);
};

struct store_tmp_inst_t : inst_t {
	uint32_t Index;
	void add_source(load_inst_t *Load) {
		Load->load_both();
		Next->add_source(Load);
	};
#ifdef ASSEMBLER_LISTING
	void list() {
		if (IsPotentialBreakpoint) printf("*");
		printf("%d:\tstore_tmp %d\n", LineNo, Index);
	};
#endif
	void encode(assembler_t *Assembler);
};

void label_t::store_val(uint32_t LineNo, operand_t *Operand) {
	store_val_inst_t *Inst = new store_val_inst_t;
	Inst->Operand = Operand;
	Inst->LineNo = LineNo;
	Inst->IsPotentialBreakpoint = false;
	append(Inst);
};

void label_t::store_ref(uint32_t LineNo, operand_t *Operand) {
	store_ref_inst_t *Inst = new store_ref_inst_t;
	Inst->Operand = Operand;
	Inst->LineNo = LineNo;
	Inst->IsPotentialBreakpoint = false;
	append(Inst);
};

void label_t::store_tmp(uint32_t LineNo, uint32_t Index) {
	store_tmp_inst_t *Inst = new store_tmp_inst_t;
	Inst->Index = Index;
	Inst->LineNo = LineNo;
	Inst->IsPotentialBreakpoint = false;
	append(Inst);
};

struct flush_inst_t : inst_t {
#ifdef ASSEMBLER_LISTING
	void list() {
		if (IsPotentialBreakpoint) printf("*");
		printf("%d:\tflush\n", LineNo);
	};
#endif
	void encode(assembler_t *Assembler);
};

void label_t::flush(uint32_t LineNo) {
	flush_inst_t *Inst = new flush_inst_t;
	Inst->LineNo = LineNo;
	Inst->IsPotentialBreakpoint = false;
	append(Inst);
};

struct store_arg_inst_t : inst_t {
	uint32_t Index;
	operand_t *Operand;
	void add_source(load_inst_t *Load) {
		if (Operand == Register) Load->load_arg();
	};
#ifdef ASSEMBLER_LISTING
	void list() {
		if (IsPotentialBreakpoint) printf("*");
		printf("%d:\tstore_arg %d <- %s\n", LineNo, Index, listop(Operand));
	};
#endif
	int noof_consts();
	void **get_consts(void **);
	void encode(assembler_t *Assembler);
};

int store_arg_inst_t::noof_consts() {
	switch (Operand->Type) {
	case operand_t::CNST: return 1;
	case operand_t::GVAR: return 1;
	case operand_t::CLSR: return 1;
	default: return 0;
	};
};


void **store_arg_inst_t::get_consts(void **Ptr) {
	switch (Operand->Type) {
	case operand_t::CNST:
		Ptr[0] = Operand->Value;
		return Ptr + 1;
	case operand_t::GVAR:
		Ptr[0] = Operand->Address;
		return Ptr + 1;
	case operand_t::CLSR:
		Ptr[0] = Operand->Entry;
		return Ptr + 1;
	default: return Ptr;
	};
};

void label_t::store_arg(uint32_t LineNo, uint32_t Index, operand_t *Operand) {
	store_arg_inst_t *Inst = new store_arg_inst_t;
	Inst->Index = Index;
	Inst->Operand = Operand;
	Inst->LineNo = LineNo;
	Inst->IsPotentialBreakpoint = false;
	append(Inst);
};

struct fixup_arg_inst_t : inst_t {
	uint32_t Index;
	operand_t *Operand;
#ifdef ASSEMBLER_LISTING
	void list() {
		if (IsPotentialBreakpoint) printf("*");
		printf("%d:\tfixup_arg %d <- %s\n", LineNo, Index, listop(Operand));
	};
#endif
	void encode(assembler_t *Assembler);
};

void label_t::fixup_arg(uint32_t LineNo, uint32_t Index, operand_t *Operand) {
	fixup_arg_inst_t *Inst = new fixup_arg_inst_t;
	Inst->Index = Index;
	Inst->Operand = Operand;
	Inst->LineNo = LineNo;
	Inst->IsPotentialBreakpoint = false;
	append(Inst);
};

struct invoke_inst_t : inst_t {
	uint32_t Trap, Args, Count;
	label_t *Fixup;
	void add_source(load_inst_t *Load) {Load->load_val();};
#ifdef ASSEMBLER_LISTING
	void list() {
		if (IsPotentialBreakpoint) printf("*");
		printf("%d:\tinvoke %d, %d, %d\n", LineNo, Trap, Args, Count);
	};
#endif
	void encode(assembler_t *Assembler);
	void append_links(label_t *Start) {
		use_label(Start, Fixup, false);
	};
};

void label_t::invoke(uint32_t LineNo, uint32_t Trap, uint32_t Args, uint32_t Count, label_t *Fixup) {
	invoke_inst_t *Inst = new invoke_inst_t;
	Inst->Trap = Trap;
	Inst->Args = Args;
	Inst->Count = Count;
	Inst->Fixup = Fixup;
	Inst->LineNo = LineNo;
	Inst->IsPotentialBreakpoint = false;
	append(Inst);
};

struct back_inst_t : inst_t {
	uint32_t Trap;
#ifdef ASSEMBLER_LISTING
	void list() {
		if (IsPotentialBreakpoint) printf("*");
		printf("%d:\tback %d\n", LineNo, Trap);
	};
#endif
	void encode(assembler_t *Assembler);
};

void label_t::back(uint32_t LineNo, uint32_t Trap) {
	back_inst_t *Inst = new back_inst_t;
	Inst->Trap = Trap;
	Inst->LineNo = LineNo;
	Inst->IsPotentialBreakpoint = false;
	append(Inst);
};

struct fail_inst_t : inst_t {
#ifdef ASSEMBLER_LISTING
	void list() {
		if (IsPotentialBreakpoint) printf("*");
		printf("%d:\tfail\n", LineNo);
	};
#endif
	void encode(assembler_t *Assembler);
};

void label_t::fail(uint32_t LineNo) {
	fail_inst_t *Inst = new fail_inst_t;
	Inst->LineNo = LineNo;
	Inst->IsPotentialBreakpoint = false;
	append(Inst);
};

struct ret_inst_t : inst_t {
	void add_source(load_inst_t *Load) {
		Load->load_both();
	};
#ifdef ASSEMBLER_LISTING
	void list() {
		if (IsPotentialBreakpoint) printf("*");
		printf("%d:\tret\n", LineNo);
	};
#endif
	void encode(assembler_t *Assembler);
};

void label_t::ret(uint32_t LineNo) {
	ret_inst_t *Inst = new ret_inst_t;
	Inst->LineNo = LineNo;
	Inst->IsPotentialBreakpoint = false;
	append(Inst);
};

struct susp_inst_t : inst_t {
	void add_source(load_inst_t *Load) {
		Load->load_both();
		Next->add_source(Load);
	};
#ifdef ASSEMBLER_LISTING
	void list() {
		if (IsPotentialBreakpoint) printf("*");
		printf("%d:\tsusp\n", LineNo);
	};
#endif
	void encode(assembler_t *Assembler);
};

void label_t::susp(uint32_t LineNo) {
	susp_inst_t *Inst = new susp_inst_t;
	Inst->LineNo = LineNo;
	Inst->IsPotentialBreakpoint = false;
	append(Inst);
};

struct recv_inst_t : inst_t {
	label_t *Handler;

	void append_links(label_t *Start) {
		if (Handler) {
			use_label(Start, Handler, false);
		};
	};
	void find_breakpoints() {
		if (Next->LineNo != LineNo) Next->IsPotentialBreakpoint = true;
		if (Handler) Handler->IsPotentialBreakpoint = true;
	};
	void add_source(load_inst_t *Load) {Next->add_source(Load);};
#ifdef ASSEMBLER_LISTING
	void list() {
		if (IsPotentialBreakpoint) printf("*");
		printf("%d:\trecv %x\n", LineNo, Handler ? Handler->final() : 0);
	};
#endif
	void encode(assembler_t *Assembler);
};

void label_t::recv(uint32_t LineNo, label_t *Handler) {
	recv_inst_t *Inst = new recv_inst_t;
	Inst->Handler = Handler;
	Inst->LineNo = LineNo;
	Inst->IsPotentialBreakpoint = false;
	append(Inst);
};

struct send_inst_t : inst_t {
	void add_source(load_inst_t *Load) {Load->load_val();};
#ifdef ASSEMBLER_LISTING
	void list() {
		if (IsPotentialBreakpoint) printf("*");
		printf("%d:\tsend\n", LineNo);
	};
#endif
	void encode(assembler_t *Assembler);
};

void label_t::send(uint32_t LineNo) {
	send_inst_t *Inst = new send_inst_t;
	Inst->LineNo = LineNo;
	Inst->IsPotentialBreakpoint = false;
	append(Inst);
};

struct store_link_inst_t : inst_t {
	uint32_t Temp;
	label_t *Target;
#ifdef ASSEMBLER_LISTING
	void list() {
		if (IsPotentialBreakpoint) printf("*");
		printf("%d:\tstore_link %d, %x\n", LineNo, Temp, Target);
	};
#endif
	void append_links(label_t *Start) {
		use_label(Start, Target, false);
	};
	void find_breakpoints() {
		if (Next->LineNo != LineNo) Next->IsPotentialBreakpoint = true;
		Target->IsPotentialBreakpoint = true;
	};
	void encode(assembler_t *Assembler);
};

void label_t::store_link(uint32_t LineNo, uint32_t Temp, label_t *Target) {
	store_link_inst_t *Inst = new store_link_inst_t;
	Inst->Temp = Temp;
	Inst->Target = Target;
	Inst->LineNo = LineNo;
	Inst->IsPotentialBreakpoint = false;
	append(Inst);
};

struct jump_link_inst_t : inst_t {
	uint32_t Temp;
#ifdef ASSEMBLER_LISTING
	void list() {
		if (IsPotentialBreakpoint) printf("*");
		printf("%d:\tjump_link %d\n", LineNo, Temp);
	};
#endif
	void encode(assembler_t *Assembler);
};

void label_t::jump_link(uint32_t LineNo, uint32_t Temp) {
	jump_link_inst_t *Inst = new jump_link_inst_t;
	Inst->Temp = Temp;
	Inst->LineNo = LineNo;
	Inst->IsPotentialBreakpoint = false;
	append(Inst);
};

struct limit_inst_t : inst_t {
	uint32_t Trap, Temp;
	void add_source(load_inst_t *Load) {Load->load_val();};
#ifdef ASSEMBLER_LISTING
	void list() {
		if (IsPotentialBreakpoint) printf("*");
		printf("%d:\tlimit %d, %d\n", LineNo, Trap, Temp);
	};
#endif
	void encode(assembler_t *Assembler);
};

void label_t::limit(uint32_t LineNo, uint32_t Trap, uint32_t Temp) {
	limit_inst_t *Inst = new limit_inst_t;
	Inst->Trap = Trap;
	Inst->Temp = Temp;
	Inst->LineNo = LineNo;
	Inst->IsPotentialBreakpoint = false;
	append(Inst);
};

struct test_limit_inst_t : inst_t {
	uint32_t Temp;
	label_t *Target;
	void add_source(load_inst_t *Load) {Load->load_val();};
	void append_links(label_t *Start) {
		use_label(Start, Target, false);
	};
	void find_breakpoints() {
		if (Next->LineNo != LineNo) Next->IsPotentialBreakpoint = true;
		Target->IsPotentialBreakpoint = true;
	};
#ifdef ASSEMBLER_LISTING
	void list() {
		if (IsPotentialBreakpoint) printf("*");
		printf("%d:\tlimit %d, %x\n", LineNo, Temp, Target);
	};
#endif
	void encode(assembler_t *Assembler);
};

void label_t::test_limit(uint32_t LineNo, uint32_t Temp, label_t *Target) {
	test_limit_inst_t *Inst = new test_limit_inst_t;
	Inst->Target = Target;
	Inst->Temp = Temp;
	Inst->LineNo = LineNo;
	Inst->IsPotentialBreakpoint = false;
	append(Inst);
};

struct skip_inst_t : inst_t {
	uint32_t Temp;
	void add_source(load_inst_t *Load) {Load->load_val();};
#ifdef ASSEMBLER_LISTING
	void list() {
		if (IsPotentialBreakpoint) printf("*");
		printf("%d:\tskip %d, %x\n", LineNo, Temp);
	};
#endif
	void encode(assembler_t *Assembler);
};

void label_t::skip(uint32_t LineNo, uint32_t Temp) {
	skip_inst_t *Inst = new skip_inst_t;
	Inst->Temp = Temp;
	Inst->LineNo = LineNo;
	Inst->IsPotentialBreakpoint = false;
	append(Inst);
};

struct test_skip_inst_t : inst_t {
	uint32_t Temp;
	uint32_t Trap;
#ifdef ASSEMBLER_LISTING
	void list() {
		if (IsPotentialBreakpoint) printf("*");
		printf("%d:\ttest_skip %d, %d\n", LineNo, Temp, Trap);
	};
#endif
	void encode(assembler_t *Assembler);
};

void label_t::test_skip(uint32_t LineNo, uint32_t Trap, uint32_t Temp) {
	test_skip_inst_t *Inst = new test_skip_inst_t;
	Inst->Trap = Trap;
	Inst->Temp = Temp;
	Inst->LineNo = LineNo;
	Inst->IsPotentialBreakpoint = false;
	append(Inst);
};

struct comp_inst_t : inst_t {
	operand_t *Operand;
	label_t *Failure;
	int Equal;
	void append_links(label_t *Start) {
		use_label(Start, Failure, false);
	};
	void find_breakpoints() {
		if (Next->LineNo != LineNo) Next->IsPotentialBreakpoint = true;
		Failure->IsPotentialBreakpoint = true;
	};
	void add_source(load_inst_t *Load) {
		Load->load_val();
		Next->add_source(Load);
	};
#ifdef ASSEMBLER_LISTING
	void list() {
		if (IsPotentialBreakpoint) printf("*");
		printf("%d:\tcomp %s %s // %x\n", LineNo, Equal ? "==" : "~==", listop(Operand), Failure);
	};
#endif
	void encode(assembler_t *Assembler);
};

void label_t::comp(uint32_t LineNo, int Equal, operand_t *Operand, label_t *Failure) {
	comp_inst_t *Inst = new comp_inst_t;
	Inst->Operand = Operand;
	Inst->Failure = Failure;
	Inst->Equal = Equal;
	Inst->LineNo = LineNo;
	Inst->IsPotentialBreakpoint = false;
	append(Inst);
};

#ifdef ASSEMBLER_LISTING
void select_integer_inst_t::list() {
	if (IsPotentialBreakpoint) printf("*");
	printf("%d:\tselect_integer\n", LineNo);
	for (case_t *Case = Cases; Case; Case = Case->Next) {
		printf("\t\t%x .. %x => %x\n", Case->Min, Case->Max, Case->Body->final());
	};
	printf("\t\telse %x\n", Default->final());
};
#endif

void select_integer_inst_t::append_links(label_t *Start) {
	for (case_t *Case = Cases; Case; Case = Case->Next) use_label(Start, Case->Body, false);
	use_label(Start, Default, false);
};

void select_integer_inst_t::find_breakpoints() {
	for (case_t *Case = Cases; Case; Case = Case->Next) Case->Body->IsPotentialBreakpoint = true;
	Default->IsPotentialBreakpoint = true;
};

void label_t::select_integer(uint32_t LineNo, select_integer_inst_t::case_t *Cases, label_t *Default) {
	select_integer_inst_t *Inst = new select_integer_inst_t;
	Inst->Cases = Cases;
	Inst->Default = Default;
	Inst->LineNo = LineNo;
	Inst->IsPotentialBreakpoint = false;
	append(Inst);
};

#ifdef ASSEMBLER_LISTING
void select_string_inst_t::list() {
	if (IsPotentialBreakpoint) printf("*");
	printf("%d:\tselect_string\n", LineNo);
	for (case_t *Case = Cases; Case; Case = Case->Next) {
		printf("\t\t%.*s => %x\n", Case->Length, Case->Key, Case->Body->final());
	};
	printf("\t\telse %x\n", Default->final());
};
#endif

void select_string_inst_t::append_links(label_t *Start) {
	for (case_t *Case = Cases; Case; Case = Case->Next) use_label(Start, Case->Body, false);
	use_label(Start, Default, false);
};

void select_string_inst_t::find_breakpoints() {
	for (case_t *Case = Cases; Case; Case = Case->Next) Case->Body->IsPotentialBreakpoint = true;
	Default->IsPotentialBreakpoint = true;
};

int select_string_inst_t::noof_consts() {
	int Count = 0;
	for (case_t *Case = Cases; Case; Case = Case->Next) ++Count;
	return Count;
};

void **select_string_inst_t::get_consts(void **Ptr) {
	for (case_t *Case = Cases; Case; Case = Case->Next) *(Ptr++) = Case->Key;
	return Ptr;
};

void label_t::select_string(uint32_t LineNo, select_string_inst_t::case_t *Cases, label_t *Default) {
	// Should sort strings into increasing size, and ensure there is at most one empty string case
	select_string_inst_t *Inst = new select_string_inst_t;
	Inst->Cases = Cases;
	Inst->Default = Default;
	Inst->LineNo = LineNo;
	Inst->IsPotentialBreakpoint = false;
	append(Inst);
};

#ifdef ASSEMBLER_LISTING
void select_object_inst_t::list() {
	if (IsPotentialBreakpoint) printf("*");
	printf("%d:\tselect_object\n", LineNo);
	for (case_t *Case = Cases; Case; Case = Case->Next) {
		printf("\t\t%x => %x\n", Case->Object, Case->Body->final());
	};
	printf("\t\telse %x\n", Default->final());
};
#endif

void select_object_inst_t::append_links(label_t *Start) {
	use_label(Start, Default, true);
	for (case_t *Case = Cases; Case; Case = Case->Next) use_label(Start, Case->Body, false);
};

void select_object_inst_t::find_breakpoints() {
	for (case_t *Case = Cases; Case; Case = Case->Next) Case->Body->IsPotentialBreakpoint = true;
	Default->IsPotentialBreakpoint = true;
};

int select_object_inst_t::noof_consts() {
	int Count = 0;
	for (case_t *Case = Cases; Case; Case = Case->Next) ++Count;
	return Count;
};

void **select_object_inst_t::get_consts(void **Ptr) {
	for (case_t *Case = Cases; Case; Case = Case->Next) *(Ptr++) = Case->Object;
	return Ptr;
};

void label_t::select_object(uint32_t LineNo, select_object_inst_t::case_t *Cases, label_t *Default) {
	select_object_inst_t *Inst = new select_object_inst_t;
	Inst->Cases = Cases;
	Inst->Default = Default;
	Inst->LineNo = LineNo;
	Inst->IsPotentialBreakpoint = false;
	append(Inst);
};

struct type_of_inst_t : load_inst_t {
	int noof_consts() {return 0;};
	void **get_consts(void **Ptr) {return Ptr;};
	void add_source(load_inst_t *Load) {
		Load->load_val();
	};
#ifdef ASSEMBLER_LISTING
	void list() {
		if (IsPotentialBreakpoint) printf("*");
		printf("%d:\ttype_of\n", LineNo);
	};
#endif
	void encode(assembler_t *Assembler);
};

void label_t::type_of(uint32_t LineNo) {
	type_of_inst_t *Inst = new type_of_inst_t;
	Inst->LineNo = LineNo;
	Inst->IsPotentialBreakpoint = false;
	append(Inst);
};

struct new_list_inst_t : inst_t {
	uint32_t Index;
#ifdef ASSEMBLER_LISTING
	void list() {
		if (IsPotentialBreakpoint) printf("*");
		printf("%d:\tnew_list %d\n", LineNo, Index);
	};
#endif
	void encode(assembler_t *Assembler);
};

void label_t::new_list(uint32_t LineNo, uint32_t Index) {
	new_list_inst_t *Inst = new new_list_inst_t;
	Inst->Index = Index;
	Inst->LineNo = LineNo;
	Inst->IsPotentialBreakpoint = false;
	append(Inst);
};

struct store_list_inst_t : inst_t {
	uint32_t Index;
#ifdef ASSEMBLER_LISTING
	void list() {
		if (IsPotentialBreakpoint) printf("*");
		printf("%d:\tstore_list %d\n", LineNo, Index);
	};
#endif
	void add_source(load_inst_t *Load) {
		Load->load_val();
	};
	void encode(assembler_t *Assembler);
};

void label_t::store_list(uint32_t LineNo, uint32_t Index) {
	store_list_inst_t *Inst = new store_list_inst_t;
	Inst->Index = Index;
	Inst->LineNo = LineNo;
	Inst->IsPotentialBreakpoint = false;
	append(Inst);
};

label_t *label_t::final() {
	if (Link == 0) return this;
	if (Next) return this;
	return Link->final();
};

void label_t::append(inst_t *Inst) {
	if (Tail) {
		Tail->Next = Inst;
	} else {
		Next = Inst;
		LineNo = Inst->LineNo;
	};
	Tail = Inst;
};

void label_t::add_source(load_inst_t *Load) {
	if (Next) {
		Next->add_source(Load);
	} else {
		Link->add_source(Load);
	};
};

#ifdef ASSEMBLER_LISTING
void label_t::list() {
	if (IsPotentialBreakpoint) printf("*");
	//if (Referenced) {
		printf("%d:%x:\n", LineNo, this);
	//};
};
#endif

struct assembler_t {
	IO$Stream_t *Output;
	uint32_t Size;
	uint32_t Temps;
	uint32_t Locals;
	uint32_t UpScopes;
	uint32_t Scopes;
	uint32_t NoOfUpScopes;
	uint32_t NoOfParams;
	uint32_t NoOfLocals;
};

typedef struct code_header_t {
	void **Consts;
	unsigned long Size;
} code_header_t;

#include "assembler-internal.c"

operand_t *label_t::assemble(const frame_t *Frame, IO$Stream_t *Output, operand_t *Operand) {
	label_t Assembly;
	memset(&Assembly, 0, sizeof(Assembly));
#ifdef ASSEMBLER_LISTING
	printf("Arranging labels...\n");
#endif
	use_label(&Assembly, this, true);
#ifdef ASSEMBLER_LISTING
	printf("done.\n");
#endif	
	for (inst_t *Inst = Assembly.Next; Inst; Inst = Inst->Next) Inst->add_sources();

	int NoOfConsts = 0;
	for (inst_t *Inst = Assembly.Next; Inst; Inst = Inst->Next) NoOfConsts += Inst->noof_consts();

	//if (DebuggerMode) {
	//	Assembly.Next->IsPotentialBreakpoint = true;
	//	for (inst_t *Inst = Assembly.Next; Inst; Inst = Inst->Next) Inst->find_breakpoints();
	//};

	assembler_t *Assembler = new assembler_t;
	Assembler->UpScopes = sizeof(bstate_t);
	Assembler->Scopes = Assembler->UpScopes + 4 * Frame->NoOfUpScopes;
	Assembler->Temps = Assembler->Scopes + 4 * Frame->NoOfScopes;
	Assembler->Locals = Assembler->Temps + 8 * Frame->NoOfTemps;
	Assembler->Size = Assembler->Locals + 8 * Frame->NoOfLocals;
	Assembler->NoOfParams = Frame->NoOfParams;
	Assembler->NoOfUpScopes = Frame->NoOfUpScopes;
	Assembler->NoOfLocals = Frame->NoOfLocals;
	Assembler->Output = Output;

#ifdef ASSEMBLER_LISTING
	printf("ASSEMBLY\n");
		for (inst_t *Inst = Assembly.Next; Inst; Inst = Inst->Next) Inst->list();
	printf("END\n");
	printf("NoOfTemps = %d\n", Frame->NoOfTemps);
	printf("UpScopes = %d\n", Assembler->UpScopes);
	printf("Scopes = %d\n", Assembler->Scopes);
	printf("Temps = %d\n", Assembler->Temps);
	printf("Locals = %d\n", Assembler->Locals);
	printf("Size = %d\n", Assembler->Size);
	printf("NoOfParams = %d\n", Assembler->NoOfParams);
	printf("NoOfUpScopes = %d\n", Assembler->NoOfUpScopes);
	printf("NoOfLocals = %d\n", Assembler->NoOfLocals);
#endif

	if (Operand) {
		//Make sure Operand->Value doesn't use surrounding dynamic scopes
		//if (Function->UpScopes) ERROR;
		emit("\n\n;line %d", LineNo);
		emit("datasect");
		emit("%s:", Operand->Value);
		emit("\tdd Wrapl$Runtime$WraplT");
		emit("\tdd ..@E%x", Operand);
	} else if (Assembler->NoOfUpScopes == 0) {
		Operand = new operand_t;
		Operand->Type = operand_t::CNST;
		asprintf(&Operand->Value, "..@F%x", Operand);
		emit("\n\n;line %d", LineNo);
		emit("datasect");
		emit("%s:", Operand->Value);
		emit("\tdd Wrapl$Runtime$WraplT");
		emit("\tdd ..@E%x", Operand);
	} else {
		Operand = new operand_t;
		Operand->Type = operand_t::CLSR;
		asprintf(&Operand->Entry, "..@E%x", Operand);
		Operand->UpScopes = Frame->UpScopes;
	};
	emit("textsect");
	emit("..@E%x:", Operand);
	encode_entry(Assembler);
	for (inst_t *Inst = Assembly.Next; Inst; Inst = Inst->Next) {
		//if (DebuggerMode) {
		//	if (Inst->IsPotentialBreakpoint) {
		//		encode_potential_breakpoint(Assembler, Inst->LineNo);
		//	};
		//};
		Inst->encode(Assembler);
	};
	uint32_t Size;

	code_header_t *Header = (code_header_t *)Riva$Memory$alloc(Size + sizeof(code_header_t));
	uint8_t *Code = (uint8_t *)(Header + 1);
	Header->Consts = new void *[NoOfConsts];
	void **ConstPtr = Header->Consts;
	for (inst_t *Inst = Assembly.Next; Inst; Inst = Inst->Next) ConstPtr = Inst->get_consts(ConstPtr);
	Header->Size = Size;

#ifdef ASSEMBLER_LISTING
	ud_t UD;
	ud_init(&UD);
	ud_set_input_buffer(&UD, Code, Size);
	ud_set_mode(&UD, 32);
	ud_set_pc(&UD, (uint64_t)Code);
	ud_set_syntax(&UD, UD_SYN_INTEL);
	while (ud_disassemble(&UD)) printf("%8x: %s\n", (uint32_t)ud_insn_off(&UD), ud_insn_asm(&UD));
#endif
	return Operand;
};
