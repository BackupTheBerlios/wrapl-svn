#include <Lang.h>
#include <Riva/Memory.h>
#include <Riva/Thread.h>
#include <ucontext.h>
#include <string.h>

TYPE(T);

static Riva$Thread_key *CoexprKey;

typedef struct coexpr_t {
	Lang$Type_t *Type;
	struct coexpr_t *Caller;
	Lang$Function_argument Transfer;
	int Status;
	ucontext_t Context;
} coexpr_t;

static void switch_coexpr(coexpr_t *Old, coexpr_t *New) {
	Riva$Thread$key_set(CoexprKey, New);
	swapcontext(&Old->Context, &New->Context);
	Riva$Thread$key_set(CoexprKey, Old);
};

static void coexpr_func(coexpr_t *Callee, Lang$Object_t *Fun, long Count, Lang$Function_argument *Args) {
	coexpr_t *Caller = Callee->Caller;
	Lang$Function_result Result;
	int Status = Lang$Function$invoke(Fun, Count, &Result, Args);
	loop: switch (Status) {
	case SUSPEND:
		Caller->Transfer = Result.Arg;
		Caller->Status = SUCCESS;
		switch_coexpr(Callee, Caller);
		Result.Arg = Caller->Transfer;
		Status = Lang$Function$resume(&Result);
		goto loop;
	case SUCCESS:
		Caller->Transfer = Result.Arg;
		Caller->Status = SUCCESS;
		switch_coexpr(Callee, Caller);
	case FAILURE: for (;;) {
		Caller->Status = FAILURE;
		switch_coexpr(Callee, Caller);
	};
	case MESSAGE: for (;;) {
		Caller->Status = MESSAGE;
		Caller->Transfer = Result.Arg;
		switch_coexpr(Callee, Caller);
	};
	};
};

GLOBAL_FUNCTION(New, 1) {
	coexpr_t *Coexpr = Riva$Memory$alloc(SIGSTKSZ - 32);
	Coexpr->Type = T;
	getcontext(&Coexpr->Context);
	Coexpr->Context.uc_stack.ss_sp = Coexpr;
	Coexpr->Context.uc_stack.ss_size = Riva$Memory$size(Coexpr);
	Lang$Function_argument *Arguments = Riva$Memory$alloc(sizeof(Lang$Function_argument *) * (Count - 1));
	memcpy(Arguments, Args + 1, sizeof(Lang$Function_argument *) * (Count - 1));
	makecontext(&Coexpr->Context, coexpr_func, 4, Coexpr, Args[0].Val, Count - 1, Arguments);
	Result->Val = Coexpr;
	return SUCCESS;
};

GLOBAL_FUNCTION(Self, 0) {
	Result->Val = Riva$Thread$key_get(CoexprKey);
	return SUCCESS;
};

GLOBAL_FUNCTION(Yield, 1) {
	coexpr_t *Caller = Riva$Thread$key_get(CoexprKey);
	coexpr_t *Callee = Caller->Caller;
	Callee->Transfer = Args[0];
	Callee->Status = SUCCESS;
	Callee->Caller = Caller;
	switch_coexpr(Caller, Callee);
	Result->Arg = Caller->Transfer;
	return SUCCESS;
};

METHOD("^", SKP, TYP, T) {
	coexpr_t *Caller = Riva$Thread$key_get(CoexprKey);
	coexpr_t *Callee = Args[1].Val;
	Callee->Transfer = Args[0];
	Callee->Caller = Caller;
	switch_coexpr(Caller, Callee);
	Result->Arg = Caller->Transfer;
	return Caller->Status;
};

METHOD("^", TYP, T) {
	coexpr_t *Caller = Riva$Thread$key_get(CoexprKey);
	coexpr_t *Callee = Args[0].Val;
	Callee->Transfer.Val = Lang$Object$Nil;
	Callee->Transfer.Ref = 0;
	Callee->Caller = Caller;
	switch_coexpr(Caller, Callee);
	Result->Arg = Caller->Transfer;
	return Caller->Status;
};

METHOD("%", TYP, T) {
	coexpr_t *Coexpr = Riva$Thread$key_get(CoexprKey);
	if (Coexpr->Caller) {
		Result->Val = Coexpr->Caller;
		return SUCCESS;
	} else {
		return FAILURE;
	};
};

void __init(void *Module) {
	CoexprKey = Riva$Thread$key_new(0);
	coexpr_t *Coexpr = new(coexpr_t);
	Coexpr->Type = T;
	Riva$Thread$key_set(CoexprKey, Coexpr);
};
