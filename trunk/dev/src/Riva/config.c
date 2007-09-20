#include "module.h"
#include "stringtable.h"

static stringtable_t Config = {{0, 0, 0}};

const char *config_get(const char *Key) {
	return stringtable_get(Config, Key);
};

void config_set(const char *Key, const char *Value) {
	stringtable_put(Config, Key, Value);
};

void config_init(void) {
	module_t *Module = module_alias("Riva/Config");
	module_export(Module, "_get", 0, config_get);
	module_export(Module, "_set", 0, config_set);
};
