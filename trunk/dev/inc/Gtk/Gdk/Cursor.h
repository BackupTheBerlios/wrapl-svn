#ifndef Gdk_Cursor_H
#define Gdk_Cursor_H

#define RIVA_MODULE Gtk$Gdk$Cursor
#include <Std.h>

#include <Riva-Header.h>

typedef struct Gtk$Gdk$Cursor_t {
	Std$Type_t *Type;
	GdkCursor *Value;
} Gtk$Gdk$Cursor_t;

extern Std$Type_t Gtk$Gdk$Cursor$T[];

#undef RIVA_MODULE

#endif
