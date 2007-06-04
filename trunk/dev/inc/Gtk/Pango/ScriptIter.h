#ifndef Pango_ScriptIter_H
#define Pango_ScriptIter_H

#define RIVA_MODULE Gtk$Pango$ScriptIter
#include <Std.h>

#include <Riva-Header.h>

typedef struct Gtk$Pango$ScriptIter_t {
	Std$Type_t *Type;
	PangoScriptIter *Value;
} Gtk$Pango$ScriptIter_t;

extern Std$Type_t Gtk$Pango$ScriptIter$T[];

#undef RIVA_MODULE

#endif
