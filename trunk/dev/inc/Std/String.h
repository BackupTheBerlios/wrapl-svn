#ifndef LANG_STRING_H
#define LANG_STRING_H

#include <Std/Integer.h>
#include <Std/Address.h>

#define RIVA_MODULE Std$String
#include <Riva-Header.h>

typedef struct Std$String_block {
	Std$Integer_smallt Length;
	Std$Address_t Chars;
} Std$String_block;

typedef struct Std$String_t {
	Std$Type_t *Type;
	Std$Integer_smallt Length;
	unsigned long Count;
	Std$String_block Blocks[];
} Std$String_t;

extern Std$Type_t Std$String$T[];
extern Std$Function_t Std$String$Add[];

RIVA_CFUN(char *, flatten, Std$String_t *);
RIVA_CFUN(void, flatten_to, Std$String_t *, char *);
RIVA_CFUN(Std$String_t *, new, char *);
RIVA_CFUN(Std$String_t *, copy, const char *);
RIVA_CFUN(Std$String_t *, new_length, char *, long);
RIVA_CFUN(Std$String_t *, copy_length, const char *, long);
RIVA_CFUN(Std$String_t *, new_format, const char *, ...);
RIVA_CFUN(Std$String_t *, new_char, char);

#undef RIVA_MODULE

#endif
