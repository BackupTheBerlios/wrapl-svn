#include "IO/String.h"
#include <stdint.h>

struct IO$String_t {
	Lang$Type_t *Type;
	Lang$String_t *LastString;
	uint32_t BlockIndex;
	uint32_t BlockOffset;
	uint32_t Offset;
};
