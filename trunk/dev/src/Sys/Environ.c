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

GLOBAL_FUNCTION(GetCwd, 0) {
	Result->Val = Lang$String$new(getcwd(0, 0));
	return SUCCESS;
};

GLOBAL_FUNCTION(SetCwd, 1) {
	char DirName[((Lang$String_t *)Args[0].Val)->Length.Value + 1];
	Lang$String$flatten_to(Args[0].Val, DirName);
	if (chdir(DirName)) {
		return SUCCESS;
	} else {
		Result->Val = "Error changing directory";
		return FAILURE;
	};
};
