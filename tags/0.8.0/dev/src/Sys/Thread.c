#include <Std.h>
#include <Riva/Memory.h>

TYPE(T);
TYPE(KeyT);
TYPE(MutexT);

#ifdef WINDOWS
#else

#include <pthread.h>

static pthread_key_t ThreadKey;

typedef struct thread_t {
	Std$Type_t *Type;
	pthread_t Handle;
	Std$Function_result Result;
	long Status;
	Std$Object_t *Function;
	Std$Function_argument *Args;
	unsigned long Count;
} thread_t;

typedef struct mutex_t {
	Std$Type_t *Type;
	pthread_mutex_t Handle;
} mutex_t;

typedef struct key_t {
	Std$Type_t *Type;
	pthread_key_t Handle;
} key_t;

static void *thread_func(thread_t *Thread) {
	pthread_setspecific(ThreadKey, Thread);
	Std$Function$invoke(Thread->Function, Thread->Count, &Thread->Result, Thread->Args);
};

GLOBAL_FUNCTION(New, 1) {
	thread_t *Thread = new(thread_t);
	Thread->Type = T;
	Thread->Function = Args[0].Val;
	Thread->Count = Count - 1;
	Thread->Args = Riva$Memory$alloc(Thread->Count * sizeof(Std$Function_argument));
	memcpy(Thread->Args, &Args[1], Thread->Count * sizeof(Std$Function_argument));
	pthread_create(&Thread->Handle, 0, thread_func, Thread);
	Result->Val = Thread;
	return SUCCESS;
};

GLOBAL_FUNCTION(Self, 0) {
	Result->Val = pthread_getspecific(ThreadKey);
	return SUCCESS;
};

GLOBAL_FUNCTION(MutexNew, 0) {
	mutex_t *Mutex = new(mutex_t);
	Mutex->Type = MutexT;
	pthread_mutex_init(&Mutex->Handle, 0);
	Result->Val = Mutex;
	return SUCCESS;
};

METHOD("lock", TYP, MutexT) {
	mutex_t *Mutex = Args[0].Val;
	if (pthread_mutex_lock(&Mutex->Handle)) {
		Result->Val = Std$String$new("Error locking mutex");
		return MESSAGE;
	};
	return SUCCESS;
};

METHOD("trylock", TYP, MutexT) {
	mutex_t *Mutex = Args[0].Val;
	return pthread_mutex_trylock(&Mutex->Handle) ? FAILURE : SUCCESS;
};

METHOD("lock", TYP, MutexT) {
	mutex_t *Mutex = Args[0].Val;
	if (pthread_mutex_unlock(&Mutex->Handle)) {
		Result->Val = Std$String$new("Error locking mutex");
		return MESSAGE;
	};
	return SUCCESS;
};

GLOBAL_FUNCTION(key_new, 0) {
	key_t *Key = new(key_t);
	Key->Type = KeyT;
	pthread_key_create(&Key->Handle, 0);
	Result->Val = Key;
	return SUCCESS;
};

METHOD("get", TYP, KeyT) {
	key_t *Key = Args[0].Val;
	void *Value = pthread_getspecific(Key->Handle);
	if (Value) {
		Result->Val = Value;
		return SUCCESS;
	} else {
		return FAILURE;
	};
};

METHOD("set", TYP, KeyT, SKP) {
	key_t *Key = Args[0].Val;
	pthread_setspecific(Key->Handle, Args[1].Val);
	return SUCCESS;
};

void __init (void *Module) {
	pthread_key_create(&ThreadKey, 0);
	thread_t *Thread = new(thread_t);
	Thread->Type = T;
	Thread->Handle = pthread_self();
	pthread_setspecific(ThreadKey, Thread);
};

#endif
