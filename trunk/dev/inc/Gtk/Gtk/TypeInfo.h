#ifndef Gtk_TypeInfo_H
#define Gtk_TypeInfo_H

#define RIVA_MODULE Gtk$Gtk$TypeInfo
#include <Std.h>

#include <Riva-Header.h>

typedef struct Gtk$Gtk$TypeInfo_t {
	Std$Type_t *Type;
	GtkTypeInfo Value;
} Gtk$Gtk$TypeInfo_t;

extern Std$Type_t Gtk$Gtk$TypeInfo$T[];

#undef RIVA_MODULE

#endif
