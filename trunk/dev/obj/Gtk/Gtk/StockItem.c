#include <Gtk/Gtk/StockItem.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 2
#include <Gtk/GObject/Object.h>
#include <Gtk/Gtk/StockItem.h>
/***********************************/
TYPE(T);

METHOD("Copy", TYP, T) {
	GtkStockItem * self= &((Gtk$Gtk$StockItem_t *)Args[0].Val)->Value;
	GtkStockItem * result = gtk_stock_item_copy(self);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("Free", TYP, T) {
	GtkStockItem * self= &((Gtk$Gtk$StockItem_t *)Args[0].Val)->Value;
	gtk_stock_item_free(self);
	return SUCCESS;
};

