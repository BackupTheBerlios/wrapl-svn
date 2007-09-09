#include "assembler.h"
#include "missing.h"
#include <Std.h>
#include <string.h>
//#include <udis86.h>

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

struct link_inst_t : inst_t {
	label_t *Link;
#ifdef ASSEMBLER_LISTING
	void list() {
		printf("\tlink %x\n", Link->final());
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
		printf("\tscope %d <- %d\n", Index, Size);
	};
#endif
	void encode(assembler_t *Assembler);
};

void label_t::scope(uint32_t Index, uint32_t Size) {
	scope_inst_t *Inst = new scope_inst_t;
	Inst->Index = Index;
	Inst->Size = Size;
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
#ifdef ASSEMBLER_LISTING
	void list() {
		printf("\tzero %d <- %x\n", Trap, Failure->final());
	};
#endif
	void encode(assembler_t *Assembler);
};

void **init_trap_inst_t::get_consts(void **Ptr) {
	Ptr[0] = State;
	return Ptr + 1;
};

void label_t::init_trap(uint32_t Trap, label_t *Failure) {
	init_trap_inst_t *Inst = new init_trap_inst_t;
	Inst->Trap = Trap;
	label_t *Failure0 = new label_t();
	Failure0->resume();
	Failure0->link(Failure);
	Inst->Failure = Failure0;
	Inst->State = new state_t;
	append(Inst);
};

struct push_trap_inst_t : inst_t {
	uint32_t Trap;
	label_t *Failure;
	uint32_t Temp;

	void append_links(label_t *Start) {
		use_label(Start, Failure, false);
	};
#ifdef ASSEMBLER_LISTING
	void list() {
		printf("\ttrap %d <- %x\n", Trap, Failure);
	};
#endif
	void encode(assembler_t *Assembler);
};

void label_t::push_trap(uint32_t Trap, label_t *Failure, uint32_t Temp) {
	push_trap_inst_t *Inst = new push_trap_inst_t;
	Inst->Trap = Trap;
	Inst->Temp = Temp;
	label_t *Failure0 = new label_t();
	Failure0->resume();
	Failure0->link(Failure);
	Inst->Failure = Failure0;
	append(Inst);
};

struct resume_inst_t : inst_t {
#ifdef ASSEMBLER_LISTING
	void list() {
		printf("\tresume\n");
	};
#endif
	void encode(assembler_t *Assembler);
};

void label_t::resume() {
	resume_inst_t *Inst = new resume_inst_t;
	append(Inst);
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
	static const char *Types[] = {
		"_none", "_val", "_ref", "_both", "_arg"
	};
	printf("\tload%s %s\n", Types[Type], listop(Operand));
};
#endif

void label_t::load(operand_t *Operand) {
	if (Operand == Register) return;
	load_inst_t *Inst = new load_inst_t;
	Inst->Operand = Operand;
	append(Inst);
};

struct store_con_inst_t : load_inst_t {
	Std$Object_t *Value;
#ifdef ASSEMBLER_LISTING
	void list() {
		printf("\tstore_con %s <- %x\n", listop(Operand), Value);
	};
#endif
	int noof_consts() {return 1;};
	void **get_consts(void **Ptr) {Ptr[0] = Value; return Ptr + 1;};
	void encode(assembler_t *Assembler);
};

void label_t::store_con(operand_t *Operand, Std$Object_t *Value) {
	store_con_inst_t *Inst = new store_con_inst_t;
	Inst->Operand = Operand;
	Inst->Value = Value;
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
		printf("\tstore_val %s\n", listop(Operand));
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
		printf("\tstore_ref %s\n", listop(Operand));
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
		printf("\tstore_tmp %d\n", Index);
	};
#endif
	void encode(assembler_t *Assembler);
};

void label_t::store_val(operand_t *Operand) {
	store_val_inst_t *Inst = new store_val_inst_t;
	Inst->Operand = Operand;
	append(Inst);
};

void label_t::store_ref(operand_t *Operand) {
	store_ref_inst_t *Inst = new store_ref_inst_t;
	Inst->Operand = Operand;
	append(Inst);
};

void label_t::store_tmp(uint32_t Index) {
	store_tmp_inst_t *Inst = new store_tmp_inst_t;
	Inst->Index = Index;
	append(Inst);
};

struct flush_inst_t : inst_t {
#ifdef ASSEMBLER_LISTING
	void list() {
		printf("\tflush\n");
	};
#endif
	void encode(assembler_t *Assembler);
};

void label_t::flush() {
	append(new flush_inst_t);
};

struct store_arg_inst_t : inst_t {
	uint32_t Index;
	operand_t *Operand;
	void add_source(load_inst_t *Load) {
		if (Operand == Register) Load->load_arg();
	};
#ifdef ASSEMBLER_LISTING
	void list() {
		printf("\tstore_arg %d <- %s\n", Index, listop(Operand));
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

void label_t::store_arg(uint32_t Index, operand_t *Operand) {
	store_arg_inst_t *Inst = new store_arg_inst_t;
	Inst->Index = Index;
	Inst->Operand = Operand;
	append(Inst);
};

struct fixup_arg_inst_t : inst_t {
	uint32_t Index;
	operand_t *Operand;
#ifdef ASSEMBLER_LISTING
	void list() {
		printf("\tfixup_arg %d <- %s\n", Index, listop(Operand));
	};
#endif
	void encode(assembler_t *Assembler);
};

void label_t::fixup_arg(uint32_t Index, operand_t *Operand) {
	fixup_arg_inst_t *Inst = new fixup_arg_inst_t;
	Inst->Index = Index;
	Inst->Operand = Operand;
	append(Inst);
};

struct invoke_inst_t : inst_t {
	uint32_t Trap, Args, Count;
	label_t *Fixup;
	void add_source(load_inst_t *Load) {Load->load_val();};
#ifdef ASSEMBLER_LISTING
	void list() {
		printf("\tinvoke %d, %d, %d\n", Trap, Args, Count);
	};
#endif
	void encode(assembler_t *Assembler);
	void append_links(label_t *Start) {use_label(Start, Fixup, false);};
};

void label_t::invoke(uint32_t Trap, uint32_t Args, uint32_t Count, label_t *Fixup) {
	invoke_inst_t *Inst = new invoke_inst_t;
	Inst->Trap = Trap;
	Inst->Args = Args;
	Inst->Count = Count;
	Inst->Fixup = Fixup;
	append(Inst);
};

struct back_inst_t : inst_t {
	uint32_t Trap;
#ifdef ASSEMBLER_LISTING
	void list() {
		printf("\tback %d\n", Trap);
	};
#endif
	void encode(assembler_t *Assembler);
};

void label_t::back(uint32_t Trap) {
	back_inst_t *Inst = new back_inst_t;
	Inst->Trap = Trap;
	append(Inst);
};

struct fail_inst_t : inst_t {
#ifdef ASSEMBLER_LISTING
	void list() {
		printf("\tfail\n");
	};
#endif
	void encode(assembler_t *Assembler);
};

void label_t::fail() {
	append(new fail_inst_t);
};

struct ret_inst_t : inst_t {
	void add_source(load_inst_t *Load) {
		Load->load_both();
	};
#ifdef ASSEMBLER_LISTING
	void list() {
		printf("\tret\n");
	};
#endif
	void encode(assembler_t *Assembler);
};

void label_t::ret() {
	append(new ret_inst_t);
};

struct susp_inst_t : inst_t {
	void add_source(load_inst_t *Load) {
		Load->load_both();
		Next->add_source(Load);
	};
#ifdef ASSEMBLER_LISTING
	void list() {
		printf("\tsusp\n");
	};
#endif
	void encode(assembler_t *Assembler);
};

void label_t::susp() {
	append(new susp_inst_t);
};

struct recv_inst_t : inst_t {
	label_t *Handler;

	void append_links(label_t *Start) {
		if (Handler) {
			use_label(Start, Handler, false);
		};
	};
	void add_source(load_inst_t *Load) {Next->add_source(Load);};
#ifdef ASSEMBLER_LISTING
	void list() {
		printf("\trecv %x\n", Handler ? Handler->final() : 0);
	};
#endif
	void encode(assembler_t *Assembler);
};

void label_t::recv(label_t *Handler) {
	recv_inst_t *Inst = new recv_inst_t;
	Inst->Handler = Handler;
	append(Inst);
};

struct send_inst_t : inst_t {
	void add_source(load_inst_t *Load) {Load->load_val();};
#ifdef ASSEMBLER_LISTING
	void list() {
		printf("\tsend\n");
	};
#endif
	void encode(assembler_t *Assembler);
};

void label_t::send() {
	append(new send_inst_t);
};

struct store_link_inst_t : inst_t {
	uint32_t Temp;
	label_t *Target;
#ifdef ASSEMBLER_LISTING
	void list() {
		printf("\tstore_link %d, %x\n", Temp, Target);
	};
#endif
	void append_links(label_t *Start) {
		use_label(Start, Target, false);
	};
	void encode(assembler_t *Assembler);
};

void label_t::store_link(uint32_t Temp, label_t *Target) {
	store_link_inst_t *Inst = new store_link_inst_t;
	Inst->Temp = Temp;
	Inst->Target = Target;
	append(Inst);
};

struct jump_link_inst_t : inst_t {
	uint32_t Temp;
#ifdef ASSEMBLER_LISTING
	void list() {
		printf("\tjump_link %d\n", Temp);
	};
#endif
	void encode(assembler_t *Assembler);
};

void label_t::jump_link(uint32_t Temp) {
	jump_link_inst_t *Inst = new jump_link_inst_t;
	Inst->Temp = Temp;
	append(Inst);
};

struct limit_inst_t : inst_t {
	uint32_t Trap, Temp;
	void add_source(load_inst_t *Load) {Load->load_val();};
#ifdef ASSEMBLER_LISTING
	void list() {
		printf("\tlimit %d, %d\n", Trap, Temp);
	};
#endif
	void encode(assembler_t *Assembler);
};

void label_t::limit(uint32_t Trap, uint32_t Temp) {
	limit_inst_t *Inst = new limit_inst_t;
	Inst->Trap = Trap;
	Inst->Temp = Temp;
	append(Inst);
};

struct test_limit_inst_t : inst_t {
	uint32_t Temp;
	label_t *Target;
	void add_source(load_inst_t *Load) {Load->load_val();};
	void append_links(label_t *Start) {
		use_label(Start, Target, false);
	};
#ifdef ASSEMBLER_LISTING
	void list() {
		printf("\tlimit %d, %x\n", Temp, Target);
	};
#endif
	void encode(assembler_t *Assembler);
};

void label_t::test_limit(uint32_t Temp, label_t *Target) {
	test_limit_inst_t *Inst = new test_limit_inst_t;
	Inst->Target = Target;
	Inst->Temp = Temp;
	append(Inst);
};

struct skip_inst_t : inst_t {
	uint32_t Temp;
	void add_source(load_inst_t *Load) {Load->load_val();};
#ifdef ASSEMBLER_LISTING
	void list() {
		printf("\tskip %d, %x\n", Temp);
	};
#endif
	void encode(assembler_t *Assembler);
};

void label_t::skip(uint32_t Temp) {
	skip_inst_t *Inst = new skip_inst_t;
	Inst->Temp = Temp;
	append(Inst);
};

struct test_skip_inst_t : inst_t {
	uint32_t Temp;
	uint32_t Trap;
#ifdef ASSEMBLER_LISTING
	void list() {
		printf("\ttest_skip %d, %d\n", Temp, Trap);
	};
#endif
	void encode(assembler_t *Assembler);
};

void label_t::test_skip(uint32_t Trap, uint32_t Temp) {
	test_skip_inst_t *Inst = new test_skip_inst_t;
	Inst->Trap = Trap;
	Inst->Temp = Temp;
	append(Inst);
};

struct comp_inst_t : inst_t {
	operand_t *Operand;
	label_t *Failure;
	int Equal;
	void append_links(label_t *Start) {
		use_label(Start, Failure, false);
	};
	void add_source(load_inst_t *Load) {
		Load->load_val();
		Next->add_source(Load);
	};
#ifdef ASSEMBLER_LISTING
	void list() {
		printf("\tcomp %s %s // %x\n", Equal ? "==" : "~==", listop(Operand), Failure);
	};
#endif
	void encode(assembler_t *Assembler);
};

void label_t::comp(int Equal, operand_t *Operand, label_t *Failure) {
	comp_inst_t *Inst = new comp_inst_t;
	Inst->Operand = Operand;
	Inst->Failure = Failure;
	Inst->Equal = Equal;
	append(Inst);
};

#ifdef ASSEMBLER_LISTING
void select_integer_inst_t::list() {
	printf("\tselect_integer\n");
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

void label_t::select_integer(select_integer_inst_t::case_t *Cases, label_t *Default) {
	select_integer_inst_t *Inst = new select_integer_inst_t;
	Inst->Cases = Cases;
	Inst->Default = Default;
	append(Inst);
};

#ifdef ASSEMBLER_LISTING
void select_string_inst_t::list() {
	printf("\tselect_string\n");
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

int select_string_inst_t::noof_consts() {
	int Count = 0;
	for (case_t *Case = Cases; Case; Case = Case->Next) ++Count;
	return Count;
};

void **select_string_inst_t::get_consts(void **Ptr) {
	for (case_t *Case = Cases; Case; Case = Case->Next) *(Ptr++) = Case->Key;
	return Ptr;
};

void label_t::select_string(select_string_inst_t::case_t *Cases, label_t *Default) {
	// Should sort strings into increasing size, and ensure there is at most one empty string case
	select_string_inst_t *Inst = new select_string_inst_t;
	Inst->Cases = Cases;
	Inst->Default = Default;
	append(Inst);
};

#ifdef ASSEMBLER_LISTING
void select_object_inst_t::list() {
	printf("\tselect_object\n");
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

int select_object_inst_t::noof_consts() {
	int Count = 0;
	for (case_t *Case = Cases; Case; Case = Case->Next) ++Count;
	return Count;
};

void **select_object_inst_t::get_consts(void **Ptr) {
	for (case_t *Case = Cases; Case; Case = Case->Next) *(Ptr++) = Case->Object;
	return Ptr;
};

void label_t::select_object(select_object_inst_t::case_t *Cases, label_t *Default) {
	select_object_inst_t *Inst = new select_object_inst_t;
	Inst->Cases = Cases;
	Inst->Default = Default;
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
		printf("\ttype_of\n");
	};
#endif
	void encode(assembler_t *Assembler);
};

void label_t::type_of() {
	type_of_inst_t *Inst = new type_of_inst_t;
	append(Inst);
};

struct new_list_inst_t : inst_t {
	uint32_t Index;
#ifdef ASSEMBLER_LISTING
	void list() {
		printf("\tnew_list %d\n", Index);
	};
#endif
	void encode(assembler_t *Assembler);
};

void label_t::new_list(uint32_t Index) {
	new_list_inst_t *Inst = new new_list_inst_t;
	Inst->Index = Index;
	append(Inst);
};

struct store_list_inst_t : inst_t {
	uint32_t Index;
#ifdef ASSEMBLER_LISTING
	void list() {
		printf("\tstore_list %d\n", Index);
	};
#endif
	void add_source(load_inst_t *Load) {
		Load->load_val();
	};
	void encode(assembler_t *Assembler);
};

void label_t::store_list(uint32_t Index) {
	store_list_inst_t *Inst = new store_list_inst_t;
	Inst->Index = Index;
	append(Inst);
};

struct assembler_t {
	struct dasm_State *Dynasm;
	uint32_t Size;
	uint32_t Temps;
	uint32_t Locals;
	uint32_t UpScopes;
	uint32_t Scopes;
	uint32_t NoOfUpScopes;
	uint32_t NoOfParams;
	uint32_t NoOfLocals;
};

#define Dst			Assembler
#define Dst_DECL	assembler_t *Assembler
#define Dst_REF		Assembler->Dynasm

static void dasm_m_grow(Dst_DECL, void **pp, size_t *szp, int need) {
  size_t sz = *szp;
  if (sz >= need) return;
  if (sz < 16) sz = 16;
  while (sz < need) sz += sz;
  *pp = Riva$Memory$realloc(*pp, sz);
  *szp = sz;
}

static void dasm_m_free(Dst_DECL, void *p, size_t sz) {
}

typedef struct code_header_t {
	void **Consts;
	unsigned long Size;
} code_header_t;

#include "dasm_proto.h"
#include "dasm_x86.h"
#include "assembler-internal.c"

operand_t *label_t::assemble(const frame_t *Frame, operand_t *Operand) {
	label_t Assembly;
	memset(&Assembly, 0, sizeof(Assembly));
	use_label(&Assembly, this, true);
	for (inst_t *Inst = Assembly.Next; Inst; Inst = Inst->Next) Inst->add_sources();

	int NoOfConsts = 0;
	for (inst_t *Inst = Assembly.Next; Inst; Inst = Inst->Next) NoOfConsts += Inst->noof_consts();


	assembler_t *Assembler = new assembler_t;
	Assembler->UpScopes = sizeof(bstate_t);
	Assembler->Scopes = Assembler->UpScopes + 4 * Frame->NoOfUpScopes;
	Assembler->Temps = Assembler->Scopes + 4 * Frame->NoOfScopes;
	Assembler->Locals = Assembler->Temps + 8 * Frame->NoOfTemps;
	Assembler->Size = Assembler->Locals + 8 * Frame->NoOfLocals;
	Assembler->NoOfParams = Frame->NoOfParams;
	Assembler->NoOfUpScopes = Frame->NoOfUpScopes;
	Assembler->NoOfLocals = Frame->NoOfLocals;

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

	dasm_init(Dst, DASM_MAXSECTION);
	void **Globals = new void *[20];
	dasm_setupglobal(Dst, Globals, 20);
	dasm_setup(Dst, ActionList);
	encode_entry(Assembler);
	for (inst_t *Inst = Assembly.Next; Inst; Inst = Inst->Next) Inst->encode(Assembler);
	uint32_t Size;
	dasm_link(Dst, &Size);
	code_header_t *Header = (code_header_t *)Riva$Memory$alloc(Size + sizeof(code_header_t));
	uint8_t *Code = (uint8_t *)(Header + 1);
	Header->Consts = new void *[NoOfConsts];
	void **ConstPtr = Header->Consts;
	for (inst_t *Inst = Assembly.Next; Inst; Inst = Inst->Next) ConstPtr = Inst->get_consts(ConstPtr);
	Header->Size = Size;
	dasm_encode(Assembler, Code);

/*
	ud_t UD;
	ud_init(&UD);
	ud_set_input_buffer(&UD, Code, Size);
	ud_set_mode(&UD, 32);
	ud_set_pc(&UD, (uint64_t)Code);
	ud_set_syntax(&UD, UD_SYN_INTEL);
	while (ud_disassemble(&UD)) printf("%8x: %s\n", (uint32_t)ud_insn_off(&UD), ud_insn_asm(&UD));
*/

	if (Operand) {
		// Make sure Operand->Value doesn't use surrounding dynamic scopes
		//if (Function->UpScopes) ERROR;
		closure_t *Closure = (closure_t *)Operand->Value;
		Closure->Type = WraplT;
		Closure->Entry = Code;
	} else if (Assembler->NoOfUpScopes == 0) {
		closure_t *Closure = new closure_t;
		Closure->Type = WraplT;
		Closure->Entry = Code;
		Operand = new operand_t;
		Operand->Type = operand_t::CNST;
		Operand->Value = (Std$Object_t *)Closure;
	} else {
		Operand = new operand_t;
		Operand->Type = operand_t::CLSR;
		Operand->Entry = Code;
		Operand->UpScopes = Frame->UpScopes;
	};
	return Operand;
};
