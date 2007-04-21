#include <Lang.h>
#include <Riva/Memory.h>
#include <Riva/Thread.h>

TYPE(T);
TYPE(KeyT);
TYPE(MutexT);

static Riva$Thread_key *ThreadKey;

typedef struct thread {
	Lang$Type_t *Type;
	Riva$Thread_t *Handle;
	Lang$Function_result Result;
	long Return;
	Lang$Object_t *Function;
	Lang$Function_argument *Args;
	unsigned long Count;
} thread;

typedef struct mutex {
	Lang$Type_t *Type;
	Riva$Thread_mutex *Handle;
} mutex;

typedef struct key {
	Lang$Type_t *Type;
	Riva$Thread_key *Handle;
} key;

/*static long invoke_suspend(c_fun *Fun, unsigned long Count, argument *Args, result *Result) {
	Result->Val = integer$new_small(SuspendThread(((thread *)Args[0].Val)->Handle));
	Result->Ref = 0;
	return SUCCESS;
};

static long invoke_resume(c_fun *Fun, unsigned long Count, argument *Args, result *Result) {
	Result->Val = integer$new_small(ResumeThread(((thread *)Args[0].Val)->Handle));
	Result->Ref = 0;
	return SUCCESS;
};*/

/*local_function(_result) {
	thread *Thread = Args[0].Val;
	//if (Thread->Result.Val == 0) pthread_join(Thread->Handle, 0);
	*Result = Thread->Result;
	return Thread->Return;
};*/

static void *thread_func(thread *Thread) {
	Riva$Thread$key_set(ThreadKey, Thread);
	Lang$Function$invoke(Thread->Function, Thread->Count, &Thread->Result, Thread->Args);
};

GLOBAL_FUNCTION(New, 1) {
	thread *Thread = new(thread);
	Thread->Type = T;
	Thread->Function = Args[0].Val;
	Thread->Count = Count - 1;
	Thread->Args = Riva$Memory$alloc(Thread->Count * sizeof(Lang$Function_argument));
	__builtin_memcpy(Thread->Args, &Args[1], Thread->Count * sizeof(Lang$Function_argument));
	Thread->Handle = Riva$Thread$new(thread_func, Thread);
	Result->Val = Thread;
	return SUCCESS;
};

GLOBAL_FUNCTION(Self, 0) {
	Result->Val = Riva$Thread$key_get(ThreadKey);
	return SUCCESS;
};

GLOBAL_FUNCTION(MutexNew, 0) {
	mutex *Mutex = new(mutex);
	Mutex->Type = MutexT;
	Mutex->Handle = Riva$Thread$mutex_new();
	Result->Val = Mutex;
	return SUCCESS;
};

METHOD("lock", TYP, MutexT) {
	Riva$Thread_mutex *Mutex = ((mutex *)Args[0].Val)->Handle;
	if (Riva$Thread$mutex_lock(Mutex)) {
		Result->Val = Lang$String$new("Error locking mutex");
		return MESSAGE;
	};
	return SUCCESS;
};

METHOD("trylock", TYP, MutexT) {
	Riva$Thread_mutex *Mutex = ((mutex *)Args[0].Val)->Handle;
	return Riva$Thread$mutex_trylock(Mutex) ? FAILURE : SUCCESS;
};

METHOD("lock", TYP, MutexT) {
	Riva$Thread_mutex *Mutex = ((mutex *)Args[0].Val)->Handle;
	if (Riva$Thread$mutex_unlock(Mutex)) {
		Result->Val = Lang$String$new("Error unlocking mutex");
		return MESSAGE;
	};
	return SUCCESS;
};

GLOBAL_FUNCTION(key_new, 0) {
	key *Key = new(key);
	Key->Type = KeyT;
	Key->Handle = Riva$Thread$key_new(0);
	Result->Val = Key;
	return SUCCESS;
};

METHOD("get", TYP, KeyT) {
	Riva$Thread_key *Key = ((key *)Args[0].Val)->Handle;
	void *Value = Riva$Thread$key_get(Key);
	if (Value) {
		Result->Val = Value;
		return SUCCESS;
	} else {
		return FAILURE;
	};
};

METHOD("set", TYP, KeyT, SKP) {
	Riva$Thread_key *Key = ((key *)Args[0].Val)->Handle;
	Riva$Thread$key_set(Key, Args[1].Val);
	return SUCCESS;
};

void __init (void *Module) {
	ThreadKey = Riva$Thread$key_new(0);
	thread *Thread = new(thread);
	Thread->Type = T;
	Thread->Handle = Riva$Thread$self();
	Riva$Thread$key_set(ThreadKey, Thread);
};
