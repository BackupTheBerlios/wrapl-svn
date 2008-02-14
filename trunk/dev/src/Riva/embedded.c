#include <gc/gc.h>
#include "module.h"
#include "memory.h"
#include "log.h"
#include "symbol.h"
#include "thread.h"
#include "riva.h"
#include "native.h"
#include "directory.h"
#include "fileset.h"

void init(void) {
	GC_init();
	//GC_disable();
	module_init();
	memory_init();
	log_init();
	config_init();
	//log_enable();
	thread_init();
	directory_init();
	native_init();
	fileset_init();
	riva_init();
	symbol_init();
};
