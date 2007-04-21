#include <Lang.h>
#include <Riva/Memory.h>
#include <Riva/Thread.h>

#include <stdlib.h>
#include <string.h>

GLOBAL_FUNCTION(Get, 1) {
	char *Value = getenv(Lang$String$flatten(Args[0].Val));
	if (Value == 0) return FAILURE;
	int Length = strlen(Value);
	char *Buffer = Riva$Memory$alloc(Length);
	strcpy(Buffer, Value);
	Result->Val = Lang$String$new_length(Buffer, Length);
	return SUCCESS;
};
