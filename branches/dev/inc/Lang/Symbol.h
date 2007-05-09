#ifndef LANG_SYMBOL_H
#define LANG_SYMBOL_H

#include <Lang/Type.h>
#include <Lang/String.h>
#include <Lang/Function.h>

#define RIVA_MODULE Lang$Symbol
#include <Riva-Header.h>

typedef struct Lang$Symbol_t {
	Lang$Type_t *Type;
	long Reserved[8];
	Lang$String_t *Name;
} Lang$Symbol_t;

extern Lang$Type_t Lang$Symbol$T[];

extern Lang$Object_t Lang$Symbol$Set[];
extern Lang$Object_t Lang$Symbol$In[];
extern Lang$Object_t Lang$Symbol$Is[];

RIVA_CFUN(Lang$Symbol_t *, new, void);
RIVA_CFUN(Lang$Symbol_t *, new_string, char *);

#define SYMBOL(Name, Value)\
	static char Name[] __attribute__ ((section (".symbols"))) = Value;

#define ANY 1
#define SKP 1
#define VAL 2
#define TYP 3

#define method_hint2(X, Y) __ ## X ## Y
#define method_hint(X, Y) method_hint2(X, Y)
#define METHOD(SYMBOL, SIGNATURE...)\
	static char method_hint(symbol, __LINE__)[] __attribute__ ((section (".symbols"))) = SYMBOL;\
	static long method_hint(invoke, __LINE__)(Lang$Function_ct *Fun, unsigned long Count, Lang$Function_argument *Args, Lang$Function_result *Result);\
	static Lang$Function_ct method_hint(method, __LINE__) = {Lang$Function$CT, method_hint(invoke, __LINE__)};\
	union {void *Adr; long Val;} method_hint(instance, __LINE__)[] __attribute__ ((section (".methods"))) = {\
		method_hint(symbol, __LINE__), SIGNATURE, 0, &method_hint(method, __LINE__)\
	};\
	static long method_hint(invoke, __LINE__)(Lang$Function_ct *Fun, unsigned long Count, Lang$Function_argument *Args, Lang$Function_result *Result)

#define SET_METHOD(SYMBOL, FUNCTION, SIGNATURE...)\
	static char method_hint(symbol, __LINE__)[] __attribute__ ((section (".symbols"))) = SYMBOL;\
	union {void *Adr; long Val;} method_hint(instance, __LINE__)[] __attribute__ ((section (".methods"))) = {\
		method_hint(symbol, __LINE__), SIGNATURE, 0, &FUNCTION\
	};

#undef RIVA_MODULE

#endif
