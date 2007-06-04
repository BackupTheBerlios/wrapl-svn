#ifndef Gtk_FileSystemError_H
#define Gtk_FileSystemError_H

#include <Std/Type.h>
#include <gtk/gtk.h>

#define RIVA_MODULE Gtk$Gtk$FileSystemError
#include <Riva-Header.h>

typedef struct Gtk$Gtk$FileSystemError_t {
	Std$Type_t *Type;
	GtkFileSystemError Value;
} Gtk$Gtk$FileSystemError_t;

extern Std$Type_t Gtk$Gtk$FileSystemError$T[];

#undef RIVA_MODULE

#endif
