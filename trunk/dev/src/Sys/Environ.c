#include <Std.h>
#include <Riva/Memory.h>

#include <stdlib.h>
#include <string.h>

#ifdef WINDOWS
	#include <windows.h>
#endif

GLOBAL_FUNCTION(Get, 1) {
	char *Value = getenv(Std$String$flatten(Args[0].Val));
	if (Value == 0) return FAILURE;
	int Length = strlen(Value);
	char *Buffer = Riva$Memory$alloc(Length);
	strcpy(Buffer, Value);
	Result->Val = Std$String$new_length(Buffer, Length);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetCwd, 0) {
#ifdef WINDOWS
	int Length = GetCurrentDirectory(0, 0);
	char *Buffer = Riva$Memory$alloc_atomic(Length);
	GetCurrentDirectory(Length, Buffer);
	Result->Val = Std$String$new_length(Buffer, Length);
#else
	Result->Val = Std$String$new(getcwd(0, 0));
#endif
	return SUCCESS;
};

GLOBAL_FUNCTION(SetCwd, 1) {
#ifdef WINDOWS
	if (SetCurrentDirectory(Std$String$flatten(Args[0].Val))) {
#else
	char DirName[((Std$String_t *)Args[0].Val)->Length.Value + 1];
	Std$String$flatten_to(Args[0].Val, DirName);
	if (chdir(DirName)) {
#endif
		return SUCCESS;
	} else {
		Result->Val = "Error changing directory";
		return FAILURE;
	};
};
