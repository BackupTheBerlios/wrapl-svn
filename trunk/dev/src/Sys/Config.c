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

GLOBAL_FUNCTION(Set, 1) {
	if (Count > 1) {
		Riva$Config$set(Std$String$flatten(Args[0].Val), Std$String$flatten(Args[1].Val));
	} else {
		Riva$Config$set(Std$String$flatten(Args[0].Val), "");
	};
	return SUCCESS;
};

GLOBAL_FUNCTION(UnSet, 1) {
	Riva$Config$set(Std$String$flatten(Args[0].Val), 0);
	return SUCCESS;
};
