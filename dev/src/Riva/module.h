#ifndef MODULE_H
#define MODULE_H

#ifdef WINDOWS
	#define PATHSTR "\\"
	#define PATHCHR '\\'
	#define STDLANG "std\\lang\\"
	#define STD "std\\"
	#define SYSEXT ".dll"
#else
	#define PATHSTR "/"
	#define PATHCHR '/'
	#define STDLANG "std/lang/"
	#define STD "std/"
	#define SYSEXT ".so"
#endif

typedef struct module_t module_t;
typedef int (*module_loader)(module_t *, const char *);
typedef int (*module_importer)(void *, const char *, int *, void **);

extern module_t *module_load(const char *Path, const char *Name);
extern module_t *module_setup(module_t *, void *, module_importer);
extern module_t *module_alias(const char *);
extern module_t *module_run(const char *Path, const char *Name);

extern int module_import(module_t *, const char *Name, int *IsRef, void **Data);
extern void module_export(module_t *, const char *Name, int IsRef, void *Data);
extern int module_lookup(void *, const char **, const char **);

extern void module_set_path(module_t *, const char *Path);
extern const char *module_get_path(module_t *);

extern void module_add_loader(const char *Extension, module_loader);
extern void module_add_directory(const char *Dir);

extern void module_init(void);

#endif
