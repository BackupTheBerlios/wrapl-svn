#ifndef Gtk_FilePath_H
#define Gtk_FilePath_H

#define RIVA_MODULE Gtk$Gtk$FilePath
#include <Std.h>

#include <Riva-Header.h>

typedef struct Gtk$Gtk$FilePath_t {
	Std$Type_t *Type;
	GtkFilePath *Value;
} Gtk$Gtk$FilePath_t;

extern Std$Type_t Gtk$Gtk$FilePath$T[];

#undef RIVA_MODULE

#endif
