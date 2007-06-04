#ifndef Gtk_ItemFactoryEntry_H
#define Gtk_ItemFactoryEntry_H

#define RIVA_MODULE Gtk$Gtk$ItemFactoryEntry
#include <Std.h>

#include <Riva-Header.h>

typedef struct Gtk$Gtk$ItemFactoryEntry_t {
	Std$Type_t *Type;
	GtkItemFactoryEntry Value;
} Gtk$Gtk$ItemFactoryEntry_t;

extern Std$Type_t Gtk$Gtk$ItemFactoryEntry$T[];

#undef RIVA_MODULE

#endif
