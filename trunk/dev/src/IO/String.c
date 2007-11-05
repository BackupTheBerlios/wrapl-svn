#include "IO/String.h"
#include <stdint.h>

struct IO$String_t {
	Std$Type_t *Type;
	Std$String_t *LastString;
	uint32_t BlockIndex;
	uint32_t BlockOffset;
	uint32_t Offset;
};

TYPE(T, IO$Stream$Reader$T, IO$Stream$SeekerT, IO$Stream$T);


