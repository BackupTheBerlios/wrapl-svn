#ifndef Pango_Item_H
#define Pango_Item_H

#define RIVA_MODULE Gtk$Pango$Item
#include <Std.h>

#include <Riva-Header.h>

typedef struct Gtk$Pango$Item_t {
	Std$Type_t *Type;
	PangoItem *Value;
} Gtk$Pango$Item_t;

extern Std$Type_t Gtk$Pango$Item$T[];

#undef RIVA_MODULE

#endif
