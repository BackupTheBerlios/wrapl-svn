#include <Gtk/Gdk/Pixdata.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 4
#include <Gtk/Gdk/Pixbuf.h>
#include <Std/Boolean.h>
#include <Gtk/Gdk/Pixdata.h>
#include <Gtk/GObject/Object.h>
/***********************************/
TYPE(T);

METHOD("Deserialize", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Object$T, TYP, Std$Object$T) {
	GdkPixdata * self= &((Gtk$Gdk$Pixdata_t *)Args[0].Val)->Value;
	int stream_length = ((Std$Integer_smallt *)Args[1].Val)->Value;
	const guint8* stream = 0;
	GError** error = 0;
	int result = gdk_pixdata_deserialize(self, stream_length, stream, error);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("FromPixbuf", TYP, T, TYP, Gtk$Gdk$Pixbuf$T, TYP, Std$Symbol$T) {
	GdkPixdata * self= &((Gtk$Gdk$Pixdata_t *)Args[0].Val)->Value;
	GdkPixbuf * pixbuf = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int use_rle = Args[2].Val == $true;
	void * result = gdk_pixdata_from_pixbuf(self, pixbuf, use_rle);
	Result->Val = Std$Address$new(result);
	return SUCCESS;
};

METHOD("Serialize", TYP, T, TYP, Std$Object$T) {
	GdkPixdata * self= &((Gtk$Gdk$Pixdata_t *)Args[0].Val)->Value;
	guint* stream_length_p = 0;
	guint8* result = gdk_pixdata_serialize(self, stream_length_p);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

METHOD("ToCsource", TYP, T, TYP, Std$String$T, TYP, Std$Integer$SmallT) {
	GdkPixdata * self= &((Gtk$Gdk$Pixdata_t *)Args[0].Val)->Value;
	char *name = Std$String$flatten(Args[1].Val);
	int dump_type = ((Std$Integer_smallt *)Args[2].Val)->Value;
	GString* result = gdk_pixdata_to_csource(self, name, dump_type);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

