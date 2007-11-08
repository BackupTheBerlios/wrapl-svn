#ifndef LANG_RATIONAL_H
#define LANG_RATIONAL_H

#include <gmp.h>
#include <Std/Object.h>
#include <Std/Function.h>

#define RIVA_MODULE Std$Rational
#include <Riva-Header.h>

typedef struct Std$Rational_t Std$Rational_t;

struct Std$Rational_t {
	Std$Type_t *Type;
	mpq_t Value;
};

extern Std$Type_t Std$Rational$T[];

RIVA_CFUN(Std$Object_t *, new, mpq_t);
RIVA_CFUN(Std$Object_t *, new_string, const char *);

#undef RIVA_MODULE

#endif
