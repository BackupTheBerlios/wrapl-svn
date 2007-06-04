#include <Gtk/Gtk/Preview.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 11
#include <Gtk/Gdk/Visual.h>
#include <Gtk/Gdk/Window.h>
#include <Std/Boolean.h>
#include <Gtk/Gdk/GC.h>
#include <Gtk/Gtk/Preview.h>
#include <Gtk/Gdk/Colormap.h>
#include <Gtk/Gtk/PreviewType.h>
#include <Gtk/Gtk/PreviewInfo.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gdk/RgbDither.h>
/***********************************/
TYPE(T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 1) {
	GtkPreviewType type = ((Std$Integer_smallt *)Args[0].Val)->Value;
	GtkPreview * result = gtk_preview_new(type);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetCmap, 0) {
	GdkColormap * result = gtk_preview_get_cmap();
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetInfo, 0) {
	GtkPreviewInfo * result = gtk_preview_get_info();
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gtk_preview_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetVisual, 0) {
	GdkVisual * result = gtk_preview_get_visual();
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(Reset, 0) {
	gtk_preview_reset();
	return SUCCESS;
};

GLOBAL_FUNCTION(SetColorCube, 4) {
	int nred_shades = ((Std$Integer_smallt *)Args[0].Val)->Value;
	int ngreen_shades = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int nblue_shades = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int ngray_shades = ((Std$Integer_smallt *)Args[3].Val)->Value;
	gtk_preview_set_color_cube(nred_shades, ngreen_shades, nblue_shades, ngray_shades);
	return SUCCESS;
};

GLOBAL_FUNCTION(SetGamma, 1) {
	double gamma_ = ((Std$Real_t *)Args[0].Val)->Value;
	gtk_preview_set_gamma(gamma_);
	return SUCCESS;
};

GLOBAL_FUNCTION(SetInstallCmap, 1) {
	int install_cmap = ((Std$Integer_smallt *)Args[0].Val)->Value;
	gtk_preview_set_install_cmap(install_cmap);
	return SUCCESS;
};

GLOBAL_FUNCTION(SetReserved, 1) {
	int nreserved = ((Std$Integer_smallt *)Args[0].Val)->Value;
	gtk_preview_set_reserved(nreserved);
	return SUCCESS;
};

GLOBAL_FUNCTION(Uninit, 0) {
	gtk_preview_uninit();
	return SUCCESS;
};

METHOD("DrawRow", TYP, T, TYP, Std$String$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GtkPreview * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *data = Std$String$flatten(Args[1].Val);
	int x = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int y = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int w = ((Std$Integer_smallt *)Args[4].Val)->Value;
	gtk_preview_draw_row(self, data, x, y, w);
	return SUCCESS;
};

METHOD("Put", TYP, T, TYP, Gtk$Gdk$Window$T, TYP, Gtk$Gdk$GC$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GtkPreview * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkWindow * window = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GdkGC * gc = ((Gtk$GObject$Object_t *)Args[2].Val)->Handle;
	int srcx = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int srcy = ((Std$Integer_smallt *)Args[4].Val)->Value;
	int destx = ((Std$Integer_smallt *)Args[5].Val)->Value;
	int desty = ((Std$Integer_smallt *)Args[6].Val)->Value;
	int width = ((Std$Integer_smallt *)Args[7].Val)->Value;
	int height = ((Std$Integer_smallt *)Args[8].Val)->Value;
	gtk_preview_put(self, window, gc, srcx, srcy, destx, desty, width, height);
	return SUCCESS;
};

METHOD("SetDither", TYP, T, TYP, Gtk$Gdk$RgbDither$T) {
	GtkPreview * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkRgbDither dither = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gtk_preview_set_dither(self, dither);
	return SUCCESS;
};

METHOD("SetExpand", TYP, T, TYP, Std$Symbol$T) {
	GtkPreview * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int expand = Args[1].Val == $true;
	gtk_preview_set_expand(self, expand);
	return SUCCESS;
};

METHOD("Size", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GtkPreview * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int width = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int height = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gtk_preview_size(self, width, height);
	return SUCCESS;
};

