#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <confuse.h>

#include <unistd.h>

#ifdef WINDOWS
#include <windows.h>
#else
#include <pthread.h>
#endif

#include <gc/gc.h>

#include "module.h"
#include "memory.h"
#include "log.h"
#include "symbol.h"
#include "thread.h"
#include "riva.h"
#include "native.h"

static void path_init(void) {
	char Cwd[256];
    getcwd(Cwd, 255);
    strcat(Cwd, PATHSTR);
	{char *Temp = getenv("RIVA"); if (Temp) module_add_directory(Temp);};
	module_add_directory("/usr/lib/");
	module_add_directory("/usr/local/lib/");
	module_add_directory("/usr/lib/riva/");
	module_add_directory("/usr/local/lib/riva/");
	module_add_directory(Cwd);
};

static int BatchMode = 0;

static void read_config(void) {
	char Conf[1024];
#ifdef WINDOWS
    int Length = GetModuleFileName(0, Conf, 1024);
    for (int I = Length; --I;) {
		if (Conf[I] == '\\') {
			strcpy(Conf + I + 1, "riva.conf");
			break;
		};
	};
#else
    char Link[1024];
	sprintf(Link, "/proc/%i/exe", getpid());
	int Length = readlink(Link, Conf, 1024);
	for (int I = Length; --I;) {
		if (Conf[I] == '/') {
			strcpy(Conf + I + 1, "riva.conf");
			break;
		};
	};
#endif

    log_writef("Loading config file: %s\n", Conf);

	static cfg_opt_t OptsMain[] = {
		CFG_STR_LIST("library", 0, CFGF_NONE),
		CFG_STR_LIST("modules", 0, CFGF_NONE),
		CFG_BOOL("batch", 0, CFGF_NONE),
		CFG_END()
	};
	cfg_t *Cfg = cfg_init(OptsMain, CFGF_NONE);
	if (cfg_parse(Cfg, Conf) == CFG_PARSE_ERROR) {
		log_errorf("Error: configuration file not present or corrupt\n");
		exit(1);
	};
	for (int I = 0; I < cfg_size(Cfg, "library"); ++I) {
		const char *Path = cfg_getnstr(Cfg, "library", I);
		module_add_directory(Path);
	};
	for (int I = 0; I < cfg_size(Cfg, "modules"); ++I) {
		const char *Path = cfg_getnstr(Cfg, "modules", I);
		log_writef("Preloading module: %s\n", Path);
		if (module_load(0, Path) == 0) {
		    log_errorf("Error: module %s not found\n", Path);
        };
	};
	BatchMode = cfg_getbool(Cfg, "batch");
};

int main(int Argc, char **Argv) {
	GC_init();
	//GC_disable();
	//path_init();
	module_init();
	memory_init();
	log_init();
	thread_init();
	native_init();
	riva_init();
	symbol_init();

	char *Module = "Main";
	for (int I = 1; I < Argc; ++I) {
		if (strcmp(Argv[I], "-nogc") == 0) {
			log_writef("Note: running without garbage collector\n");
			GC_disable();
		} else if (Argv[I][0] == '-') switch (Argv[I][1]) {
		case 'L': {
			if (Argv[I][2]) {
				module_add_directory(Argv[I] + 2);
			} else if (Argc > ++I) {
				module_add_directory(Argv[I]);
			} else {
				puts("Error: -L must be followed by a path");
				return 1;
			};
			break;
		};
		case 'v': {
			log_enable();
			break;
		};
		default: {
			printf("Error: unknown option %s\n", Argv[I]);
			break;
		};
		} else {
			Module = Argv[I];
			break;
		};
	};
	read_config();
	if (!BatchMode) {
		if (module_load(0, Module) == 0) printf("Error: module %s not found\n", Module);
	};
#ifdef WINDOWS
    ExitThread(0);
#else
	pthread_exit(0);
#endif
};
