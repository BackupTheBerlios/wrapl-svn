#ifndef Gtk_PaperSize_H
#define Gtk_PaperSize_H

#define RIVA_MODULE Gtk$Gtk$PaperSize
#include <Std.h>

#include <Riva-Header.h>

typedef struct Gtk$Gtk$PaperSize_t {
	Std$Type_t *Type;
	GtkPaperSize *Value;
} Gtk$Gtk$PaperSize_t;

extern Std$Type_t Gtk$Gtk$PaperSize$T[];

#undef RIVA_MODULE

#endif
