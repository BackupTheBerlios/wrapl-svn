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
#include "directory.h"

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
static int ParseArgs = 0;
static char *MainModule;

static void read_config(void) {
	char Conf[1024];
#ifdef WINDOWS
    int Length = GetModuleFileName(0, Conf, 1024);
    for (int I = Length; --I;) {
		if (Conf[I] == '.') {
			strcpy(Conf + I + 1, "conf");
			break;
		};
	};
#else
    char Link[1024];
	sprintf(Link, "/proc/%i/exe", getpid());
	int Length = readlink(Link, Conf, 1024);
	strcpy(Conf + Length, ".conf");
#endif

	static cfg_opt_t OptsMain[] = {
		CFG_STR_LIST("library", 0, CFGF_NONE),
		CFG_STR_LIST("modules", 0, CFGF_NONE),
		CFG_BOOL("batch", 0, CFGF_NONE),
		CFG_BOOL("parseargs", 0, CFGF_NONE),
		CFG_STR("module", "Main", CFGF_NONE),
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
	ParseArgs = cfg_getbool(Cfg, "parseargs");
	MainModule = cfg_getstr(Cfg, "module");
};

static const char **Args;
static unsigned int NoOfArgs = 0;

int main(int Argc, char **Argv) {
	GC_init();
	//GC_disable();
	//path_init();
	module_init();
	memory_init();
	log_init();
	thread_init();
	directory_init();
	native_init();
	riva_init();
	symbol_init();

	read_config();
	if (ParseArgs) {
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
			case '-': {
				++I;
				Args = Argv + I;
				NoOfArgs = Argc - I;
				goto finished;
			};
			default: {
				printf("Error: unknown option %s\n", Argv[I]);
				break;
			};
			} else {
				MainModule = Argv[I];
				++I;
				Args = Argv + I;
				NoOfArgs = Argc - I;
				goto finished;
			};
		};
	} else {
		Args = Argv + 1;
		NoOfArgs = Argc - 1;
	};
finished: 0;
	module_t *System = module_alias("Riva/System");
	module_export(System, "_Args", 0, &Args);
	module_export(System, "_NoOfArgs", 0, &NoOfArgs);
	if (!module_load(0, MainModule)) printf("Error: module %s not found\n", MainModule);
#ifdef WINDOWS
#undef ExitThread
    ExitThread(0);
#else
	pthread_exit(0);
#endif
};
