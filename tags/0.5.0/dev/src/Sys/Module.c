#include <Sys/Module.h>
#include <Lang.h>
#include <Riva/Memory.h>
#include <string.h>

TYPE(T);

GLOBAL_FUNCTION(FromVal, 1) {
	char *ModuleName, *SymbolName;
	if (Riva$Module$lookup(Args[0].Val, &ModuleName, &SymbolName)) {
		Result->Val = Lang$List$new(2, Lang$String$new(ModuleName), Lang$String$new(SymbolName));
		return SUCCESS;
	} else {
		return FAILURE;
	};
};

GLOBAL_FUNCTION(FromRef, 1) {
	char *ModuleName, *SymbolName;
	if (Riva$Module$lookup(Args[0].Ref, &ModuleName, &SymbolName)) {
		Result->Val = Lang$List$new(2, Lang$String$new(ModuleName), Lang$String$new(SymbolName));
		return SUCCESS;
	} else {
		return FAILURE;
	};
};

Sys$Module_t *_new() {
	Sys$Module_t *Module = new(Sys$Module_t);
	Module->Type = T;
	char *Name;
	asprintf(&Name, "<Unnamed Module: %x>", Module);
	Module->Handle = Riva$Module$alias(Name, 0, 0);
	return Module;
};

Sys$Module_t *_load(const char *Path, const char *Name) {
	Riva$Module_t *Handle = Riva$Module$load(Path, Name);
	if (Handle) {
		Sys$Module_t *Module = new(Sys$Module_t);
		Module->Type = T;
		Module->Handle = Handle;
		return Module;
	} else {
		return 0;
	};
};

int _import(Sys$Module_t *Module, const char *Name, int *IsRef, void **Data) {
	return Riva$Module$import(Module->Handle, Name, IsRef, Data);
};

void _export(Sys$Module_t *Module, const char *Name, int IsRef, void *Data) {
	Riva$Module$export(Module->Handle, Name, IsRef, Data);
};

void _set_path(Sys$Module_t *Module, const char *Path) {
	Riva$Module$set_path(Module, Path);
};

const char *_get_path(Sys$Module_t *Module) {
	return Riva$Module$get_path(Module);
};

GLOBAL_FUNCTION(Load, 2) {
	char *Path = (Args[0].Val == Lang$Object$Nil) ? 0 :Lang$String$flatten(Args[0].Val);
	char *Name = Lang$String$flatten(Args[1].Val);
	Sys$Module_t *Handle = Riva$Module$load(Path, Name);
	if (Handle) {
		Sys$Module_t *Module = new(Sys$Module_t);
		Module->Type = T;
		Module->Handle = Handle;
		Result->Val = Module;
		return SUCCESS;
	} else {
		Result->Val = Lang$String$new("Module not found");
		return MESSAGE;
	};
};

GLOBAL_FUNCTION(Run, 2) {
	char *Path = (Args[0].Val == Lang$Object$Nil) ? 0 : Lang$String$flatten(Args[0].Val);
	char *Name = Lang$String$flatten(Args[1].Val);
	Sys$Module_t *Handle = Riva$Module$run(Path, Name);
	if (Handle) {
		Sys$Module_t *Module = new(Sys$Module_t);
		Module->Type = T;
		Module->Handle = Handle;
		Result->Val = Module;
		return SUCCESS;
	} else {
		Result->Val = Lang$String$new("Module not found");
		return MESSAGE;
	};
};

METHOD("import", TYP, T, ANY) {
	char *Symbol = Lang$String$flatten(Args[1].Val);
	Riva$Module_t *Module = ((Sys$Module_t *)Args[0].Val)->Handle;
	int IsRef; void *Data;
	if (Riva$Module$import(Module, Symbol, &IsRef, &Data)) {
		if (IsRef) {
			Result->Val = *(Result->Ref = Data);
		} else {
			Result->Val = Data;
			Result->Ref = 0;
		};
		return SUCCESS;
	} else {
		Result->Val = Lang$String$new("Import not found");
		return MESSAGE;
	};
};

METHOD("name", TYP, T) {
	/*module_t *Module = ((module *)Args[0].Val)->Handle;
	Result->Val = string$new(Module->Name);*/
	return SUCCESS;
};

METHOD("path", TYP, T) {
	/*module_t *Module = ((module *)Args[0].Val)->Handle;
	Result->Val = string$new(Module->Path);*/
	return SUCCESS;
};