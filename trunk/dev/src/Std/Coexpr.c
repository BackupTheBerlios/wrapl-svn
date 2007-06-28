#include <Std.h>
#include <Riva/Memory.h>
#include <Riva/Thread.h>
#include <string.h>

TYPE(T);

#ifdef WINDOWS

#include <windows.h>

#else

#include <ucontext.h>

static Riva$Thread_key *CoexprKey;

#endif

typedef struct coexpr_t {
	Std$Type_t *Type;
	struct coexpr_t *Caller;
	Std$Function_argument Transfer;
	int Status;
#ifdef WINDOWS
    void *Fiber;
    Std$Function_argument *Args;
    int Count;
    Std$Object_t *Func;
#else
	ucontext_t Context;
#endif
} coexpr_t;

static coexpr_t *switch_coexpr(coexpr_t *Old, coexpr_t *New, int Status, Std$Function_argument Transfer) {
    New->Transfer = Transfer;
	New->Status = Status;
	New->Caller = Old;
#ifdef WINDOWS
    SwitchToFiber(New->Fiber);
#else
	Riva$Thread$key_set(CoexprKey, New);
	swapcontext(&Old->Context, &New->Context);
#endif
	return Old;
};

#ifdef WINDOWS

static void __stdcall coexpr_func(coexpr_t *Callee) {
	Std$Function_result Result;
	int Status = Std$Function$invoke(Callee->Func, Callee->Count, &Result, Callee->Args);
	coexpr_t *Caller = Callee->Caller;
	for (;;) switch (Status) {
	case SUSPEND:
		Caller = switch_coexpr(Callee, Caller, SUCCESS, Result.Arg);
		Result.Arg = Caller->Transfer;
		Status = Std$Function$resume(&Result);
		continue;
	case SUCCESS:
		Caller = switch_coexpr(Callee, Caller, SUCCESS, Result.Arg);
	case FAILURE:
		for (;;) Caller = switch_coexpr(Callee, Caller, FAILURE, (Std$Function_argument){0, 0});
	case MESSAGE:
		for (;;) Caller = switch_coexpr(Callee, Caller, MESSAGE, Result.Arg);
	};
};

GLOBAL_FUNCTION(New, 1) {
	coexpr_t *Coexpr = new(coexpr_t);
	Coexpr->Type = T;
	Coexpr->Fiber = CreateFiber(0, coexpr_func, Coexpr);
	Std$Function_argument *Arguments = Riva$Memory$alloc(sizeof(Std$Function_argument *) * (Count - 1));
	memcpy(Arguments, Args + 1, sizeof(Std$Function_argument *) * (Count - 1));
	Coexpr->Count = Count - 1;
	Coexpr->Args = Arguments;
	Coexpr->Func = Args[0].Val;
	Result->Val = Coexpr;
	return SUCCESS;
};

#else

static void coexpr_func(coexpr_t *Callee, Std$Object_t *Fun, long Count, Std$Function_argument *Args) {
	Std$Function_result Result;
	int Status = Std$Function$invoke(Fun, Count, &Result, Args);
	coexpr_t *Caller = Callee->Caller;
	for (;;) switch (Status) {
	case SUSPEND:
		Caller = switch_coexpr(Callee, Caller, SUCCESS, Result.Arg);
		Result.Arg = Caller->Transfer;
		Status = Std$Function$resume(&Result);
		continue;
	case SUCCESS:
		Caller = switch_coexpr(Callee, Caller, SUCCESS, Result.Arg);
	case FAILURE:
		for (;;) Caller = switch_coexpr(Callee, Caller, FAILURE, (Std$Function_argument){0, 0});
	case MESSAGE:
		for (;;) Caller = switch_coexpr(Callee, Caller, MESSAGE, Result.Arg);
	};
};

GLOBAL_FUNCTION(New, 1) {
	coexpr_t *Coexpr = Riva$Memory$alloc(SIGSTKSZ - 32);
	Coexpr->Type = T;
	getcontext(&Coexpr->Context);
	Coexpr->Context.uc_stack.ss_sp = Coexpr;
	Coexpr->Context.uc_stack.ss_size = Riva$Memory$size(Coexpr);
	Std$Function_argument *Arguments = Riva$Memory$alloc(sizeof(Std$Function_argument *) * (Count - 1));
	memcpy(Arguments, Args + 1, sizeof(Std$Function_argument *) * (Count - 1));
	makecontext(&Coexpr->Context, coexpr_func, 4, Coexpr, Args[0].Val, Count - 1, Arguments);
	Result->Val = Coexpr;
	return SUCCESS;
};

#endif

GLOBAL_FUNCTION(Self, 0) {
#ifdef WINDOWS
    Result->Val = GetFiberData();
#else
	Result->Val = Riva$Thread$key_get(CoexprKey);
#endif
	return SUCCESS;
};

GLOBAL_FUNCTION(Yield, 1) {
#ifdef WINDOWS
    coexpr_t *Caller = GetFiberData();
#else
	coexpr_t *Caller = Riva$Thread$key_get(CoexprKey);
#endif
	coexpr_t *Callee = Caller->Caller;
	switch_coexpr(Caller, Callee, SUCCESS, Args[0]);
	Result->Arg = Caller->Transfer;
	return SUCCESS;
};

METHOD("^", SKP, TYP, T) {
#ifdef WINDOWS
    coexpr_t *Caller = GetFiberData();
#else
	coexpr_t *Caller = Riva$Thread$key_get(CoexprKey);
#endif
	coexpr_t *Callee = Args[1].Val;
	switch_coexpr(Caller, Callee, SUCCESS, Args[0]);
	Result->Arg = Caller->Transfer;
	return Caller->Status;
};

METHOD("^", TYP, T) {
#ifdef WINDOWS
    coexpr_t *Caller = GetFiberData();
#else
	coexpr_t *Caller = Riva$Thread$key_get(CoexprKey);
#endif
	coexpr_t *Callee = Args[0].Val;
	switch_coexpr(Caller, Callee, SUCCESS, (Std$Function_argument){Std$Object$Nil, 0});
	Result->Arg = Caller->Transfer;
	return Caller->Status;
};

METHOD("%", TYP, T) {
#ifdef WINDOWS
    coexpr_t *Coexpr = GetFiberData();
#else
	coexpr_t *Coexpr = Riva$Thread$key_get(CoexprKey);
#endif
	if (Coexpr->Caller) {
		Result->Val = Coexpr->Caller;
		return SUCCESS;
	} else {
		return FAILURE;
	};
};

METHOD("collect", TYP, T) {
#ifdef WINDOWS
    coexpr_t *Caller = GetFiberData();
#else
	coexpr_t *Caller = Riva$Thread$key_get(CoexprKey);
#endif
	coexpr_t *Callee = Args[0].Val;
	Std$List_t *List = new(Std$List_t);
	List->Type = Std$List$T;
	List->Lower = List->Upper = 0;
	List->Access = 4;
	Result->Val = List;
	Std$List_node *Node, *Prev;
	unsigned long NoOfElements;
	Callee = switch_coexpr(Caller, Callee, SUCCESS, Args[0]);
	switch (Caller->Status) {
	case SUSPEND:
	case SUCCESS:
		Node = new(Std$List_node);
		NoOfElements = 1;
		Node->Value = Caller->Transfer.Val;
		List->Head = Node;
		List->Cache = Node;
		List->Index = 1;
		for (;;) {
			Callee = switch_coexpr(Caller, Callee, SUCCESS, Args[0]);
			switch (Caller->Status) {
			case SUCCESS:
			case SUSPEND:
				++NoOfElements;
				Prev = Node;
				Node = new(Std$List_node);
				(Node->Prev = Prev)->Next = Node;
				Node->Value = Caller->Transfer.Val;
				break;
			case MESSAGE:
				Result->Val = Caller->Transfer.Val;
				return MESSAGE;
			case FAILURE:
				List->Tail = Node;
				List->Length = NoOfElements;
				return SUCCESS;
			};
		};
	case MESSAGE:
		Result->Val = Caller->Transfer.Val;
		return MESSAGE;
	case FAILURE:
		return SUCCESS;
	};
};

void __init(void *Module) {
	coexpr_t *Coexpr = new(coexpr_t);
	Coexpr->Type = T;
#ifdef WINDOWS
    Coexpr->Fiber = ConvertThreadToFiber(Coexpr);
#else
	CoexprKey = Riva$Thread$key_new(0);
	Riva$Thread$key_set(CoexprKey, Coexpr);
#endif
	//switch_coexpr(Coexpr, Coexpr, SUCCESS, (Std$Function_argument){Std$Object$Nil, 0});
	Coexpr->Caller = Coexpr;
};
