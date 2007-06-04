#include <Gtk/Gdk/Pixbuf.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 18
#include <Std/Boolean.h>
#include <Gtk/Gdk/PixbufFormat.h>
#include <Gtk/Gdk/GC.h>
#include <Gtk/Gdk/PixbufDestroyNotify.h>
#include <Gtk/Gdk/Pixdata.h>
#include <Gtk/Gdk/PixbufRotation.h>
#include <Gtk/Gdk/PixbufSaveFunc.h>
#include <Gtk/Gdk/Colormap.h>
#include <Gtk/Gdk/Colorspace.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Gdk/Drawable.h>
#include <Gtk/Gdk/PixbufAlphaMode.h>
#include <Gtk/Gdk/Image.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/Gdk/RgbDither.h>
#include <Gtk/Gdk/InterpType.h>
#include <Gtk/Gdk/Pixbuf.h>
#include <Gtk/Gdk/Bitmap.h>
/***********************************/
TYPE(T, Gtk$GObject$Object$T);

GLOBAL_FUNCTION(New, 5) {
	GdkColorspace colorspace = ((Std$Integer_smallt *)Args[0].Val)->Value;
	int has_alpha = Args[1].Val == $true;
	int bits_per_sample = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int width = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int height = ((Std$Integer_smallt *)Args[4].Val)->Value;
	GdkPixbuf * result = gdk_pixbuf_new(colorspace, has_alpha, bits_per_sample, width, height);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(NewFromData, 9) {
	char *data = Std$String$flatten(Args[0].Val);
	GdkColorspace colorspace = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int has_alpha = Args[2].Val == $true;
	int bits_per_sample = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int width = ((Std$Integer_smallt *)Args[4].Val)->Value;
	int height = ((Std$Integer_smallt *)Args[5].Val)->Value;
	int rowstride = ((Std$Integer_smallt *)Args[6].Val)->Value;
	GdkPixbufDestroyNotify destroy_fn = Gtk$Gdk$PixbufDestroyNotify$new(Args[7].Val);
	void *destroy_fn_data = ((Std$Address_t *)Args[8].Val)->Value;
	GdkPixbuf * result = gdk_pixbuf_new_from_data(data, colorspace, has_alpha, bits_per_sample, width, height, rowstride, destroy_fn, destroy_fn_data);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(NewFromFile, 2) {
	char *filename = Std$String$flatten(Args[0].Val);
	GError** error = 0;
	GdkPixbuf * result = gdk_pixbuf_new_from_file(filename, error);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(NewFromFileAtScale, 5) {
	char *filename = Std$String$flatten(Args[0].Val);
	int width = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int height = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int preserve_aspect_ratio = Args[3].Val == $true;
	GError** error = 0;
	GdkPixbuf * result = gdk_pixbuf_new_from_file_at_scale(filename, width, height, preserve_aspect_ratio, error);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(NewFromFileAtSize, 4) {
	char *filename = Std$String$flatten(Args[0].Val);
	int width = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int height = ((Std$Integer_smallt *)Args[2].Val)->Value;
	GError** error = 0;
	GdkPixbuf * result = gdk_pixbuf_new_from_file_at_size(filename, width, height, error);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(NewFromInline, 4) {
	int data_length = ((Std$Integer_smallt *)Args[0].Val)->Value;
	const guint8* data = 0;
	int copy_pixels = Args[2].Val == $true;
	GError** error = 0;
	GdkPixbuf * result = gdk_pixbuf_new_from_inline(data_length, data, copy_pixels, error);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(NewFromXpmData, 1) {
	const char** data = 0;
	GdkPixbuf * result = gdk_pixbuf_new_from_xpm_data(data);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(NewSubpixbuf, 5) {
	GdkPixbuf * src_pixbuf = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int src_x = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int src_y = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int width = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int height = ((Std$Integer_smallt *)Args[4].Val)->Value;
	GdkPixbuf * result = gdk_pixbuf_new_subpixbuf(src_pixbuf, src_x, src_y, width, height);
	Result->Val= Gtk$GObject$Object$new(result, T);
	return SUCCESS;
};

GLOBAL_FUNCTION(ErrorQuark, 0) {
	GQuark result = gdk_pixbuf_error_quark();
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

GLOBAL_FUNCTION(FromPixdata, 3) {
	GdkPixdata * pixdata= &((Gtk$Gdk$Pixdata_t *)Args[0].Val)->Value;
	int copy_pixels = Args[1].Val == $true;
	GError** error = 0;
	GdkPixbuf * result = gdk_pixbuf_from_pixdata(pixdata, copy_pixels, error);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetFileInfo, 3) {
	char *filename = Std$String$flatten(Args[0].Val);
	gint* width = 0;
	gint* height = 0;
	GdkPixbufFormat * result = gdk_pixbuf_get_file_info(filename, width, height);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

GLOBAL_FUNCTION(GetFormats, 0) {
	GSList* result = gdk_pixbuf_get_formats();
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

GLOBAL_FUNCTION(GetType, 0) {
	GType result = gdk_pixbuf_get_type();
	Result->Val = Gtk$GObject$Type$to_riva(result);
	return SUCCESS;
};

METHOD("AddAlpha", TYP, T, TYP, Std$Symbol$T, TYP, Std$String$T, TYP, Std$String$T, TYP, Std$String$T) {
	GdkPixbuf * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int substitute_color = Args[1].Val == $true;
	char r = ((char *)((Std$String_t *)Args[2].Val)->Blocks[0].Chars.Value)[0];
	char g = ((char *)((Std$String_t *)Args[3].Val)->Blocks[0].Chars.Value)[0];
	char b = ((char *)((Std$String_t *)Args[4].Val)->Blocks[0].Chars.Value)[0];
	GdkPixbuf * result = gdk_pixbuf_add_alpha(self, substitute_color, r, g, b);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("Composite", TYP, T, TYP, Gtk$Gdk$Pixbuf$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Real$T, TYP, Std$Real$T, TYP, Std$Real$T, TYP, Std$Real$T, TYP, Gtk$Gdk$InterpType$T, TYP, Std$Integer$SmallT) {
	GdkPixbuf * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkPixbuf * dest = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int dest_x = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int dest_y = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int dest_width = ((Std$Integer_smallt *)Args[4].Val)->Value;
	int dest_height = ((Std$Integer_smallt *)Args[5].Val)->Value;
	double offset_x = ((Std$Real_t *)Args[6].Val)->Value;
	double offset_y = ((Std$Real_t *)Args[7].Val)->Value;
	double scale_x = ((Std$Real_t *)Args[8].Val)->Value;
	double scale_y = ((Std$Real_t *)Args[9].Val)->Value;
	GdkInterpType interp_type = ((Std$Integer_smallt *)Args[10].Val)->Value;
	int overall_alpha = ((Std$Integer_smallt *)Args[11].Val)->Value;
	gdk_pixbuf_composite(self, dest, dest_x, dest_y, dest_width, dest_height, offset_x, offset_y, scale_x, scale_y, interp_type, overall_alpha);
	return SUCCESS;
};

METHOD("CompositeColor", TYP, T, TYP, Gtk$Gdk$Pixbuf$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Real$T, TYP, Std$Real$T, TYP, Std$Real$T, TYP, Std$Real$T, TYP, Gtk$Gdk$InterpType$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GdkPixbuf * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkPixbuf * dest = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int dest_x = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int dest_y = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int dest_width = ((Std$Integer_smallt *)Args[4].Val)->Value;
	int dest_height = ((Std$Integer_smallt *)Args[5].Val)->Value;
	double offset_x = ((Std$Real_t *)Args[6].Val)->Value;
	double offset_y = ((Std$Real_t *)Args[7].Val)->Value;
	double scale_x = ((Std$Real_t *)Args[8].Val)->Value;
	double scale_y = ((Std$Real_t *)Args[9].Val)->Value;
	GdkInterpType interp_type = ((Std$Integer_smallt *)Args[10].Val)->Value;
	int overall_alpha = ((Std$Integer_smallt *)Args[11].Val)->Value;
	int check_x = ((Std$Integer_smallt *)Args[12].Val)->Value;
	int check_y = ((Std$Integer_smallt *)Args[13].Val)->Value;
	int check_size = ((Std$Integer_smallt *)Args[14].Val)->Value;
	int color1 = ((Std$Integer_smallt *)Args[15].Val)->Value;
	int color2 = ((Std$Integer_smallt *)Args[16].Val)->Value;
	gdk_pixbuf_composite_color(self, dest, dest_x, dest_y, dest_width, dest_height, offset_x, offset_y, scale_x, scale_y, interp_type, overall_alpha, check_x, check_y, check_size, color1, color2);
	return SUCCESS;
};

METHOD("CompositeColorSimple", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Gtk$Gdk$InterpType$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GdkPixbuf * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int dest_width = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int dest_height = ((Std$Integer_smallt *)Args[2].Val)->Value;
	GdkInterpType interp_type = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int overall_alpha = ((Std$Integer_smallt *)Args[4].Val)->Value;
	int check_size = ((Std$Integer_smallt *)Args[5].Val)->Value;
	int color1 = ((Std$Integer_smallt *)Args[6].Val)->Value;
	int color2 = ((Std$Integer_smallt *)Args[7].Val)->Value;
	GdkPixbuf * result = gdk_pixbuf_composite_color_simple(self, dest_width, dest_height, interp_type, overall_alpha, check_size, color1, color2);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("Copy", TYP, T) {
	GdkPixbuf * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkPixbuf * result = gdk_pixbuf_copy(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("CopyArea", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Gtk$Gdk$Pixbuf$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GdkPixbuf * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int src_x = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int src_y = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int width = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int height = ((Std$Integer_smallt *)Args[4].Val)->Value;
	GdkPixbuf * dest_pixbuf = ((Gtk$GObject$Object_t *)Args[5].Val)->Handle;
	int dest_x = ((Std$Integer_smallt *)Args[6].Val)->Value;
	int dest_y = ((Std$Integer_smallt *)Args[7].Val)->Value;
	gdk_pixbuf_copy_area(self, src_x, src_y, width, height, dest_pixbuf, dest_x, dest_y);
	return SUCCESS;
};

METHOD("Fill", TYP, T, TYP, Std$Integer$SmallT) {
	GdkPixbuf * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int pixel = ((Std$Integer_smallt *)Args[1].Val)->Value;
	gdk_pixbuf_fill(self, pixel);
	return SUCCESS;
};

METHOD("Flip", TYP, T, TYP, Std$Symbol$T) {
	GdkPixbuf * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int horizontal = Args[1].Val == $true;
	GdkPixbuf * result = gdk_pixbuf_flip(self, horizontal);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetBitsPerSample", TYP, T) {
	GdkPixbuf * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gdk_pixbuf_get_bits_per_sample(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetColorspace", TYP, T) {
	GdkPixbuf * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkColorspace result = gdk_pixbuf_get_colorspace(self);
	Gtk$Gdk$Colorspace_t *_result = new(Gtk$Gdk$Colorspace_t);
	_result->Type = Gtk$Gdk$Colorspace$T;
	_result->Value = result;
	Result->Val = _result;
	return SUCCESS;
};

METHOD("GetFromDrawable", TYP, T, TYP, Gtk$Gdk$Drawable$T, TYP, Gtk$Gdk$Colormap$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GdkPixbuf * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkDrawable * src = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GdkColormap * cmap = ((Gtk$GObject$Object_t *)Args[2].Val)->Handle;
	int src_x = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int src_y = ((Std$Integer_smallt *)Args[4].Val)->Value;
	int dest_x = ((Std$Integer_smallt *)Args[5].Val)->Value;
	int dest_y = ((Std$Integer_smallt *)Args[6].Val)->Value;
	int width = ((Std$Integer_smallt *)Args[7].Val)->Value;
	int height = ((Std$Integer_smallt *)Args[8].Val)->Value;
	GdkPixbuf * result = gdk_pixbuf_get_from_drawable(self, src, cmap, src_x, src_y, dest_x, dest_y, width, height);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetFromImage", TYP, T, TYP, Gtk$Gdk$Image$T, TYP, Gtk$Gdk$Colormap$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GdkPixbuf * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkImage * src = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GdkColormap * cmap = ((Gtk$GObject$Object_t *)Args[2].Val)->Handle;
	int src_x = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int src_y = ((Std$Integer_smallt *)Args[4].Val)->Value;
	int dest_x = ((Std$Integer_smallt *)Args[5].Val)->Value;
	int dest_y = ((Std$Integer_smallt *)Args[6].Val)->Value;
	int width = ((Std$Integer_smallt *)Args[7].Val)->Value;
	int height = ((Std$Integer_smallt *)Args[8].Val)->Value;
	GdkPixbuf * result = gdk_pixbuf_get_from_image(self, src, cmap, src_x, src_y, dest_x, dest_y, width, height);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("GetHasAlpha", TYP, T) {
	GdkPixbuf * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gdk_pixbuf_get_has_alpha(self);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("GetHeight", TYP, T) {
	GdkPixbuf * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gdk_pixbuf_get_height(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetNChannels", TYP, T) {
	GdkPixbuf * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gdk_pixbuf_get_n_channels(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetOption", TYP, T, TYP, Std$String$T) {
	GdkPixbuf * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *key = Std$String$flatten(Args[1].Val);
	const char * result = gdk_pixbuf_get_option(self, key);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$copy(result);
	return SUCCESS;
};

METHOD("GetPixels", TYP, T) {
	GdkPixbuf * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char * result = gdk_pixbuf_get_pixels(self);
	if (result == 0) return FAILURE;
	Result->Val = Std$String$new(result);
	return SUCCESS;
};

METHOD("GetRowstride", TYP, T) {
	GdkPixbuf * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gdk_pixbuf_get_rowstride(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("GetWidth", TYP, T) {
	GdkPixbuf * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gdk_pixbuf_get_width(self);
	Result->Val = Std$Integer$new_small(result);
	return SUCCESS;
};

METHOD("Ref", TYP, T) {
	GdkPixbuf * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkPixbuf * result = gdk_pixbuf_ref(self);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("RenderPixmapAndMask", TYP, T, TYP, Std$Object$T, TYP, Std$Object$T, TYP, Std$Integer$SmallT) {
	GdkPixbuf * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkPixmap** pixmap_return = 0;
	GdkBitmap** mask_return = 0;
	int alpha_threshold = ((Std$Integer_smallt *)Args[3].Val)->Value;
	gdk_pixbuf_render_pixmap_and_mask(self, pixmap_return, mask_return, alpha_threshold);
	return SUCCESS;
};

METHOD("RenderPixmapAndMaskForColormap", TYP, T, TYP, Gtk$Gdk$Colormap$T, TYP, Std$Object$T, TYP, Std$Object$T, TYP, Std$Integer$SmallT) {
	GdkPixbuf * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkColormap * colormap = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GdkPixmap** pixmap_return = 0;
	GdkBitmap** mask_return = 0;
	int alpha_threshold = ((Std$Integer_smallt *)Args[4].Val)->Value;
	gdk_pixbuf_render_pixmap_and_mask_for_colormap(self, colormap, pixmap_return, mask_return, alpha_threshold);
	return SUCCESS;
};

METHOD("RenderThresholdAlpha", TYP, T, TYP, Gtk$Gdk$Bitmap$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GdkPixbuf * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkBitmap * bitmap = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int src_x = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int src_y = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int dest_x = ((Std$Integer_smallt *)Args[4].Val)->Value;
	int dest_y = ((Std$Integer_smallt *)Args[5].Val)->Value;
	int width = ((Std$Integer_smallt *)Args[6].Val)->Value;
	int height = ((Std$Integer_smallt *)Args[7].Val)->Value;
	int alpha_threshold = ((Std$Integer_smallt *)Args[8].Val)->Value;
	gdk_pixbuf_render_threshold_alpha(self, bitmap, src_x, src_y, dest_x, dest_y, width, height, alpha_threshold);
	return SUCCESS;
};

METHOD("RenderToDrawable", TYP, T, TYP, Gtk$Gdk$Drawable$T, TYP, Gtk$Gdk$GC$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Gtk$Gdk$RgbDither$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GdkPixbuf * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkDrawable * drawable = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GdkGC * gc = ((Gtk$GObject$Object_t *)Args[2].Val)->Handle;
	int src_x = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int src_y = ((Std$Integer_smallt *)Args[4].Val)->Value;
	int dest_x = ((Std$Integer_smallt *)Args[5].Val)->Value;
	int dest_y = ((Std$Integer_smallt *)Args[6].Val)->Value;
	int width = ((Std$Integer_smallt *)Args[7].Val)->Value;
	int height = ((Std$Integer_smallt *)Args[8].Val)->Value;
	GdkRgbDither dither = ((Std$Integer_smallt *)Args[9].Val)->Value;
	int x_dither = ((Std$Integer_smallt *)Args[10].Val)->Value;
	int y_dither = ((Std$Integer_smallt *)Args[11].Val)->Value;
	gdk_pixbuf_render_to_drawable(self, drawable, gc, src_x, src_y, dest_x, dest_y, width, height, dither, x_dither, y_dither);
	return SUCCESS;
};

METHOD("RenderToDrawableAlpha", TYP, T, TYP, Gtk$Gdk$Drawable$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Gtk$Gdk$PixbufAlphaMode$T, TYP, Std$Integer$SmallT, TYP, Gtk$Gdk$RgbDither$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	GdkPixbuf * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkDrawable * drawable = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int src_x = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int src_y = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int dest_x = ((Std$Integer_smallt *)Args[4].Val)->Value;
	int dest_y = ((Std$Integer_smallt *)Args[5].Val)->Value;
	int width = ((Std$Integer_smallt *)Args[6].Val)->Value;
	int height = ((Std$Integer_smallt *)Args[7].Val)->Value;
	GdkPixbufAlphaMode alpha_mode = ((Std$Integer_smallt *)Args[8].Val)->Value;
	int alpha_threshold = ((Std$Integer_smallt *)Args[9].Val)->Value;
	GdkRgbDither dither = ((Std$Integer_smallt *)Args[10].Val)->Value;
	int x_dither = ((Std$Integer_smallt *)Args[11].Val)->Value;
	int y_dither = ((Std$Integer_smallt *)Args[12].Val)->Value;
	gdk_pixbuf_render_to_drawable_alpha(self, drawable, src_x, src_y, dest_x, dest_y, width, height, alpha_mode, alpha_threshold, dither, x_dither, y_dither);
	return SUCCESS;
};

METHOD("RotateSimple", TYP, T, TYP, Gtk$Gdk$PixbufRotation$T) {
	GdkPixbuf * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkPixbufRotation angle = ((Std$Integer_smallt *)Args[1].Val)->Value;
	GdkPixbuf * result = gdk_pixbuf_rotate_simple(self, angle);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("SaturateAndPixelate", TYP, T, TYP, Gtk$Gdk$Pixbuf$T, TYP, Std$Real$T, TYP, Std$Symbol$T) {
	GdkPixbuf * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkPixbuf * dest = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	double saturation = ((Std$Real_t *)Args[2].Val)->Value;
	int pixelate = Args[3].Val == $true;
	gdk_pixbuf_saturate_and_pixelate(self, dest, saturation, pixelate);
	return SUCCESS;
};

METHOD("Save", TYP, T, TYP, Std$String$T, TYP, Std$String$T, TYP, Std$Object$T, TYP, Std$Object$T) {
	GdkPixbuf * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *filename = Std$String$flatten(Args[1].Val);
	char *type = Std$String$flatten(Args[2].Val);
	GError** error = 0;
	char *___ = 0;
	int result = gdk_pixbuf_save(self, filename, type, error, ___);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("SaveToBuffer", TYP, T, TYP, Std$List$T, TYP, Std$Object$T, TYP, Std$String$T, TYP, Std$Object$T, TYP, Std$Object$T) {
	GdkPixbuf * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	const char * const * buffer;
	gsize* buffer_size = 0;
	char *type = Std$String$flatten(Args[3].Val);
	GError** error = 0;
	char *___ = 0;
	int result = gdk_pixbuf_save_to_buffer(self, buffer, buffer_size, type, error, ___);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("SaveToBufferv", TYP, T, TYP, Std$List$T, TYP, Std$Object$T, TYP, Std$String$T, TYP, Std$List$T, TYP, Std$List$T, TYP, Std$Object$T) {
	GdkPixbuf * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	const char * const * buffer;
	gsize* buffer_size = 0;
	char *type = Std$String$flatten(Args[3].Val);
	const char * const * option_keys;
	const char * const * option_values;
	GError** error = 0;
	int result = gdk_pixbuf_save_to_bufferv(self, buffer, buffer_size, type, option_keys, option_values, error);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("SaveToCallback", TYP, T, TYP, Std$Function$T, TYP, Std$Address$T, TYP, Std$String$T, TYP, Std$Object$T, TYP, Std$Object$T) {
	GdkPixbuf * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkPixbufSaveFunc save_func = Gtk$Gdk$PixbufSaveFunc$new(Args[1].Val);
	void *user_data = ((Std$Address_t *)Args[2].Val)->Value;
	char *type = Std$String$flatten(Args[3].Val);
	GError** error = 0;
	char *___ = 0;
	int result = gdk_pixbuf_save_to_callback(self, save_func, user_data, type, error, ___);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("SaveToCallbackv", TYP, T, TYP, Std$Function$T, TYP, Std$Address$T, TYP, Std$String$T, TYP, Std$List$T, TYP, Std$List$T, TYP, Std$Object$T) {
	GdkPixbuf * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkPixbufSaveFunc save_func = Gtk$Gdk$PixbufSaveFunc$new(Args[1].Val);
	void *user_data = ((Std$Address_t *)Args[2].Val)->Value;
	char *type = Std$String$flatten(Args[3].Val);
	const char * const * option_keys;
	const char * const * option_values;
	GError** error = 0;
	int result = gdk_pixbuf_save_to_callbackv(self, save_func, user_data, type, option_keys, option_values, error);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("Savev", TYP, T, TYP, Std$String$T, TYP, Std$String$T, TYP, Std$List$T, TYP, Std$List$T, TYP, Std$Object$T) {
	GdkPixbuf * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *filename = Std$String$flatten(Args[1].Val);
	char *type = Std$String$flatten(Args[2].Val);
	const char * const * option_keys;
	const char * const * option_values;
	GError** error = 0;
	int result = gdk_pixbuf_savev(self, filename, type, option_keys, option_values, error);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

METHOD("Scale", TYP, T, TYP, Gtk$Gdk$Pixbuf$T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Std$Real$T, TYP, Std$Real$T, TYP, Std$Real$T, TYP, Std$Real$T, TYP, Gtk$Gdk$InterpType$T) {
	GdkPixbuf * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkPixbuf * dest = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int dest_x = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int dest_y = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int dest_width = ((Std$Integer_smallt *)Args[4].Val)->Value;
	int dest_height = ((Std$Integer_smallt *)Args[5].Val)->Value;
	double offset_x = ((Std$Real_t *)Args[6].Val)->Value;
	double offset_y = ((Std$Real_t *)Args[7].Val)->Value;
	double scale_x = ((Std$Real_t *)Args[8].Val)->Value;
	double scale_y = ((Std$Real_t *)Args[9].Val)->Value;
	GdkInterpType interp_type = ((Std$Integer_smallt *)Args[10].Val)->Value;
	gdk_pixbuf_scale(self, dest, dest_x, dest_y, dest_width, dest_height, offset_x, offset_y, scale_x, scale_y, interp_type);
	return SUCCESS;
};

METHOD("ScaleSimple", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT, TYP, Gtk$Gdk$InterpType$T) {
	GdkPixbuf * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int dest_width = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int dest_height = ((Std$Integer_smallt *)Args[2].Val)->Value;
	GdkInterpType interp_type = ((Std$Integer_smallt *)Args[3].Val)->Value;
	GdkPixbuf * result = gdk_pixbuf_scale_simple(self, dest_width, dest_height, interp_type);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

METHOD("Unref", TYP, T) {
	GdkPixbuf * self = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gdk_pixbuf_unref(self);
	return SUCCESS;
};

