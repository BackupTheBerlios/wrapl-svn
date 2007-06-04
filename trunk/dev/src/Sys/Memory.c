#include <Std.h>
#include <Riva/Memory.h>

GLOBAL_FUNCTION(Collect, 0) {
	Riva$Memory$collect();
	return SUCCESS;
};
