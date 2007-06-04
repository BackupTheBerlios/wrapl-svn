#ifndef Gtk_StockItem_H
#define Gtk_StockItem_H

#define RIVA_MODULE Gtk$Gtk$StockItem
#include <Std.h>

#include <Riva-Header.h>

typedef struct Gtk$Gtk$StockItem_t {
	Std$Type_t *Type;
	GtkStockItem Value;
} Gtk$Gtk$StockItem_t;

extern Std$Type_t Gtk$Gtk$StockItem$T[];

#undef RIVA_MODULE

#endif
