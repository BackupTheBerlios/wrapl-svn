#ifndef Gtk_IconInfo_H
#define Gtk_IconInfo_H

#define RIVA_MODULE Gtk$Gtk$IconInfo
#include <Std.h>

#include <Riva-Header.h>

typedef struct Gtk$Gtk$IconInfo_t {
	Std$Type_t *Type;
	GtkIconInfo *Value;
} Gtk$Gtk$IconInfo_t;

extern Std$Type_t Gtk$Gtk$IconInfo$T[];

#undef RIVA_MODULE

#endif
