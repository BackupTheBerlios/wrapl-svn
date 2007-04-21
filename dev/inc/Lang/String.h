#ifndef LANG_STRING_H
#define LANG_STRING_H

#include <Lang/Integer.h>
#include <Lang/Address.h>

#define RIVA_MODULE Lang$String
#include <Riva-Header.h>

typedef struct Lang$String_block {
	Lang$Integer_smallt Length;
	Lang$Address_t Chars;
} Lang$String_block;

typedef struct Lang$String_t {
	Lang$Type_t *Type;
	Lang$Integer_smallt Length;
	unsigned long Count;
	Lang$String_block Blocks[];
} Lang$String_t;

extern Lang$Type_t Lang$String$T[];

RIVA_CFUN(char *, flatten, Lang$String_t *);
RIVA_CFUN(void, flatten_to, Lang$String_t *, char *);
RIVA_CFUN(Lang$String_t *, new, const char *);
RIVA_CFUN(Lang$String_t *, new_length, const char *, long);
RIVA_CFUN(Lang$String_t *, new_char, char);

#undef RIVA_MODULE

#endif
