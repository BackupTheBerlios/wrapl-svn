#ifndef Gtk_FileInfo_H
#define Gtk_FileInfo_H

#define RIVA_MODULE Gtk$Gtk$FileInfo
#include <Std.h>

#include <Riva-Header.h>

typedef struct Gtk$Gtk$FileInfo_t {
	Std$Type_t *Type;
	GtkFileInfo *Value;
} Gtk$Gtk$FileInfo_t;

extern Std$Type_t Gtk$Gtk$FileInfo$T[];

#undef RIVA_MODULE

#endif
