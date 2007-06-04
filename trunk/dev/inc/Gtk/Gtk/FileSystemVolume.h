#ifndef Gtk_FileSystemVolume_H
#define Gtk_FileSystemVolume_H

#define RIVA_MODULE Gtk$Gtk$FileSystemVolume
#include <Std.h>

#include <Riva-Header.h>

typedef struct Gtk$Gtk$FileSystemVolume_t {
	Std$Type_t *Type;
	GtkFileSystemVolume *Value;
} Gtk$Gtk$FileSystemVolume_t;

extern Std$Type_t Gtk$Gtk$FileSystemVolume$T[];

#undef RIVA_MODULE

#endif
