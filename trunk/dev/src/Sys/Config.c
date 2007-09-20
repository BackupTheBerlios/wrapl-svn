#include <Std.h>
#include <Riva/Config.h>

GLOBAL_FUNCTION(Get, 1) {
	const char *Value = Riva$Config$get(Std$String$flatten(Args[0].Val));
	if (Value) {
		Result->Val = Std$String$new(Value);
		return SUCCESS;
	} else {
		return FAILURE;
	};
};

GLOBAL_FUNCTION(Set, 2) {
	Riva$Config$set(Std$String$flatten(Args[0].Val), Std$String$flatten(Args[1].Val));
	return SUCCESS;
};
