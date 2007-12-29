#ifndef LANG_SYMBOL_H
#define LANG_SYMBOL_H

#include <Std/Type.h>
#include <Std/String.h>
#include <Std/Function.h>

#define RIVA_MODULE Std$Symbol
#include <Riva-Header.h>

typedef struct Std$Symbol_t {
	Std$Type_t *Type;
	long Reserved[8];
	Std$String_t *Name;
} Std$Symbol_t;

extern Std$Type_t Std$Symbol$T[];

extern Std$Object_t Std$Symbol$Set[];
extern Std$Object_t Std$Symbol$In[];
extern Std$Object_t Std$Symbol$Is[];

RIVA_CFUN(Std$Symbol_t *, new, void);
RIVA_CFUN(Std$Symbol_t *, new_string, char *);

#ifdef DOCUMENTING

#define SYMBOL(ARGS...) SYMBOL(__LINE__, ARGS)
#define METHOD(ARGS...) METHOD(__LINE__, ARGS)
#define SET_METHOD(ARGS...) SET_METHOD(__LINE__, ARGS)

#else

#define SYMBOL(Name, Value)\
	static char Name[] __attribute__ ((section (".symbols"))) = Value;

#define ANY (void *)1
#define SKP (void *)1
#define VAL (void *)2
#define TYP (void *)3

#define method_hint2(X, Y) __ ## X ## Y
#define method_hint(X, Y) method_hint2(X, Y)
#define METHOD(SYMBOL, SIGNATURE...)\
	static char method_hint(symbol, __LINE__)[] __attribute__ ((section (".symbols"))) = SYMBOL;\
	static long method_hint(invoke, __LINE__)(Std$Function_ct *Fun, unsigned long Count, Std$Function_argument *Args, Std$Function_result *Result);\
	static Std$Function_ct method_hint(method, __LINE__) = {Std$Function$CT, method_hint(invoke, __LINE__)};\
	union {void *Adr; long Val;} method_hint(instance, __LINE__)[] __attribute__ ((section (".methods"))) = {\
		method_hint(symbol, __LINE__), SIGNATURE, 0, &method_hint(method, __LINE__)\
	};\
	static long method_hint(invoke, __LINE__)(Std$Function_ct *Fun, unsigned long Count, Std$Function_argument *Args, Std$Function_result *Result)

#define SET_METHOD(SYMBOL, FUNCTION, SIGNATURE...)\
	static char method_hint(symbol, __LINE__)[] __attribute__ ((section (".symbols"))) = SYMBOL;\
	union {void *Adr; long Val;} method_hint(instance, __LINE__)[] __attribute__ ((section (".methods"))) = {\
		method_hint(symbol, __LINE__), SIGNATURE, 0, &FUNCTION\
	};

#endif

#undef RIVA_MODULE

#endif
