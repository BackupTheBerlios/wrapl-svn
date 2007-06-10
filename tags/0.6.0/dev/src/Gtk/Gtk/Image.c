#include <Gtk/Gtk/Image.h>

TYPE(T, Gtk$Gtk$Misc$T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(NewFromStock, 2) {
	GtkWidget *Handle = gtk_image_new();
	Result->Val = Gtk$GObject$Object$new(Handle, T);
	return SUCCESS;
};

/*
GtkWidget*          gtk_image_new_from_file             (const gchar *filename);
GtkWidget*          gtk_image_new_from_icon_set         (GtkIconSet *icon_set,
                                                         GtkIconSize size);
GtkWidget*          gtk_image_new_from_image            (GdkImage *image,
                                                         GdkBitmap *mask);
GtkWidget*          gtk_image_new_from_pixbuf           (GdkPixbuf *pixbuf);
GtkWidget*          gtk_image_new_from_pixmap           (GdkPixmap *pixmap,
                                                         GdkBitmap *mask);
GtkWidget*          gtk_image_new_from_stock            (const gchar *stock_id,
                                                         GtkIconSize size);
GtkWidget*          gtk_image_new_from_animation        (GdkPixbufAnimation *animation);
GtkWidget*          gtk_image_new_from_icon_name        (const gchar *icon_name,
                                                         GtkIconSize size);
*/
