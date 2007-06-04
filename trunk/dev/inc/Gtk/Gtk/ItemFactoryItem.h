#ifndef Gtk_ItemFactoryItem_H
#define Gtk_ItemFactoryItem_H

#define RIVA_MODULE Gtk$Gtk$ItemFactoryItem
#include <Std.h>

#include <Riva-Header.h>

typedef struct Gtk$Gtk$ItemFactoryItem_t {
	Std$Type_t *Type;
	GtkItemFactoryItem Value;
} Gtk$Gtk$ItemFactoryItem_t;

extern Std$Type_t Gtk$Gtk$ItemFactoryItem$T[];

#undef RIVA_MODULE

#endif
