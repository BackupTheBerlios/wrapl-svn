#ifndef Gtk_FileFilterInfo_H
#define Gtk_FileFilterInfo_H

#define RIVA_MODULE Gtk$Gtk$FileFilterInfo
#include <Std.h>

#include <Riva-Header.h>

typedef struct Gtk$Gtk$FileFilterInfo_t {
	Std$Type_t *Type;
	GtkFileFilterInfo Value;
} Gtk$Gtk$FileFilterInfo_t;

extern Std$Type_t Gtk$Gtk$FileFilterInfo$T[];

#undef RIVA_MODULE

#endif
