#include "symbol.h"
#include "module.h"

static void *(*make_symbol)(const char *);
void (*add_methods)(void *);
module_t *Symbol;

static int symbol_import(void *Ignore, const char *Name, int *IsRef, void **Data) {
	*IsRef = 0;
	*Data = make_symbol(Name);
	return 1;
};

static int symbol_import0(void *Ignore, const char *Name, int *IsRef, void **Data) {
	module_t *LangSymbol = module_load(0, "Lang/Symbol");
	int IsRef0;
	module_import(LangSymbol, "_new_string", &IsRef0, (void **)&make_symbol);
	module_import(LangSymbol, "_add_methods", &IsRef0, (void **)&add_methods);
	module_setup(Symbol, 0, symbol_import);
	return symbol_import(0, Name, IsRef, Data);
};

void symbol_init(void) {
	Symbol = module_alias("Riva/Symbol");
	module_setup(Symbol, 0, symbol_import0);
};
