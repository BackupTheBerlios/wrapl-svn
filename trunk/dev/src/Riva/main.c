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

static int BatchMode = 0;
static int ParseArgs = 0;
static char *MainModule;

static int add_config(cfg_t *Cfg, cfg_opt_t *Opt, int Argc, const char **Argv) {
	if (Argc == 1) {
		config_set(GC_strdup(Argv[0]), "");
	} else if (Argc == 2) {
		config_set(GC_strdup(Argv[0]), GC_strdup(Argv[1]));
	} else {
		cfg_error(Cfg, "Error: invalid number of arguments to config() in configuration file\n");
		return -1;
	};
	return 0;
};

static void read_config(void) {
	char Conf[1024];
#ifdef WINDOWS
    int Length = GetModuleFileName(0, Conf, 1024);
    strcpy(strrchr(Conf, '.'), ".conf");
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
		CFG_FUNC("config", add_config),
		CFG_END()
	};
	cfg_t *Cfg = cfg_init(OptsMain, CFGF_NONE);
	switch (cfg_parse(Cfg, Conf)) {
	case CFG_FILE_ERROR:
		log_errorf("Error: configuration file %s not present\n", Conf);
		exit(1);
	case CFG_PARSE_ERROR:
		log_errorf("Error: configuration file %s corrupt\n", Conf);
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
	module_init();
	memory_init();
	log_init();
	config_init();
	//log_enable();
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
			case 'P': {
				if (Argv[I][2]) {
					module_load(0, Argv[I] + 2);
				} else if (Argc > ++I) {
					module_load(0, Argv[I]);
				} else {
					puts("Error: -P must be followed by a module");
					return 1;
				};
				break;
			};
			case 'D': {
				char *Key, *Value;
				if (Argv[I][2]) {
					char *Tmp = strchr(Argv[I], '=');
					if (Tmp) {
						int KeyLen = Tmp - Argv[I] - 2;
						Key = GC_malloc_atomic(KeyLen + 1);
						memcpy(Key, Argv[I] + 2, KeyLen);
						Key[KeyLen] = 0;
						Value = GC_strdup(Tmp + 1);
					} else {
						Key = GC_strdup(Argv[I] + 2);
						Value = "";
					}
				} else if (Argc > ++I) {
					char *Tmp = strchr(Argv[I], '=');
					if (Tmp) {
						int KeyLen = Tmp - Argv[I];
						Key = GC_malloc_atomic(KeyLen + 1);
						memcpy(Key, Argv[I], KeyLen);
						Key[KeyLen] = 0;
						Value = GC_strdup(Tmp + 1);
					} else {
						Key = GC_strdup(Argv[I]);
						Value = "";
					};
				} else {
					puts("Error: -D must be followed by a key/value pair");
					return 1;
				};
				config_set(Key, Value);
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
	module_t *Module = module_load_file(MainModule);
	if (Module == 0) Module = module_load(0, MainModule);
	if (Module == 0) printf("Error: module %s not found\n", MainModule);
#ifdef WINDOWS
#undef ExitThread
    ExitThread(0);
#else
	pthread_exit(0);
#endif
};
