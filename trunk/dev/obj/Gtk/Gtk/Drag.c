#include <Gtk/Gtk/Drag.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 12
#include <Gtk/GObject/Object.h>
#include <Gtk/Gdk/DragProtocol.h>
#include <Gtk/Gdk/Pixbuf.h>
#include <Gtk/Gdk/Bitmap.h>
#include <Gtk/Gdk/Pixmap.h>
#include <Gtk/Gdk/Window.h>
#include <Gtk/Gtk/Widget.h>
#include <Gtk/Gdk/DragContext.h>
#include <Gtk/Gtk/TargetList.h>
#include <Std/Boolean.h>
#include <Gtk/Gtk/TargetEntry.h>
#include <Gtk/Gdk/Colormap.h>
/***********************************/
GLOBAL_FUNCTION(Begin, 5) {
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTargetList * targets= ((Gtk$Gtk$TargetList_t *)Args[1].Val)->Value;
	int actions = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int button = ((Std$Integer_smallt *)Args[3].Val)->Value;
	GdkEvent* event = 0;
	GdkDragContext * result = gtk_drag_begin(widget, targets, actions, button, event);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(CheckThreshold, 5) {
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int start_x = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int start_y = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int current_x = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int current_y = ((Std$Integer_smallt *)Args[4].Val)->Value;
	int result = gtk_drag_check_threshold(widget, start_x, start_y, current_x, current_y);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

GLOBAL_FUNCTION(DestAddImageTargets, 1) {
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_drag_dest_add_image_targets(widget);
	return SUCCESS;
};

GLOBAL_FUNCTION(DestAddTextTargets, 1) {
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_drag_dest_add_text_targets(widget);
	return SUCCESS;
};

GLOBAL_FUNCTION(DestAddUriTargets, 1) {
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_drag_dest_add_uri_targets(widget);
	return SUCCESS;
};

GLOBAL_FUNCTION(DestFindTarget, 3) {
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkDragContext * context = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GtkTargetList * target_list= ((Gtk$Gtk$TargetList_t *)Args[2].Val)->Value;
	GdkAtom result = gtk_drag_dest_find_target(widget, context, target_list);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

GLOBAL_FUNCTION(DestGetTargetList, 1) {
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTargetList * result = gtk_drag_dest_get_target_list(widget);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

GLOBAL_FUNCTION(DestGetTrackMotion, 1) {
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int result = gtk_drag_dest_get_track_motion(widget);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

GLOBAL_FUNCTION(DestSet, 5) {
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int flags = ((Std$Integer_smallt *)Args[1].Val)->Value;
	GtkTargetEntry * targets= &((Gtk$Gtk$TargetEntry_t *)Args[2].Val)->Value;
	int n_targets = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int actions = ((Std$Integer_smallt *)Args[4].Val)->Value;
	gtk_drag_dest_set(widget, flags, targets, n_targets, actions);
	return SUCCESS;
};

GLOBAL_FUNCTION(DestSetProxy, 4) {
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkWindow * proxy_window = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GdkDragProtocol protocol = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int use_coordinates = Args[3].Val == $true;
	gtk_drag_dest_set_proxy(widget, proxy_window, protocol, use_coordinates);
	return SUCCESS;
};

GLOBAL_FUNCTION(DestSetTargetList, 2) {
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTargetList * target_list= ((Gtk$Gtk$TargetList_t *)Args[1].Val)->Value;
	gtk_drag_dest_set_target_list(widget, target_list);
	return SUCCESS;
};

GLOBAL_FUNCTION(DestSetTrackMotion, 2) {
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int track_motion = Args[1].Val == $true;
	gtk_drag_dest_set_track_motion(widget, track_motion);
	return SUCCESS;
};

GLOBAL_FUNCTION(DestUnset, 1) {
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_drag_dest_unset(widget);
	return SUCCESS;
};

GLOBAL_FUNCTION(Finish, 4) {
	GdkDragContext * context = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int success = Args[1].Val == $true;
	int del = Args[2].Val == $true;
	int time_ = ((Std$Integer_smallt *)Args[3].Val)->Value;
	gtk_drag_finish(context, success, del, time_);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetData, 4) {
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkDragContext * context = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GdkAtom target = 0;
	int time_ = ((Std$Integer_smallt *)Args[3].Val)->Value;
	gtk_drag_get_data(widget, context, target, time_);
	return SUCCESS;
};

GLOBAL_FUNCTION(GetSourceWidget, 1) {
	GdkDragContext * context = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * result = gtk_drag_get_source_widget(context);
	if (result == 0) return FAILURE;
	Result->Val = Gtk$GObject$Object$to_riva(result);
	return SUCCESS;
};

GLOBAL_FUNCTION(Highlight, 1) {
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_drag_highlight(widget);
	return SUCCESS;
};

GLOBAL_FUNCTION(SetDefaultIcon, 5) {
	GdkColormap * colormap = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkPixmap * pixmap = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GdkBitmap * mask = ((Gtk$GObject$Object_t *)Args[2].Val)->Handle;
	int hot_x = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int hot_y = ((Std$Integer_smallt *)Args[4].Val)->Value;
	gtk_drag_set_default_icon(colormap, pixmap, mask, hot_x, hot_y);
	return SUCCESS;
};

GLOBAL_FUNCTION(SetIconDefault, 1) {
	GdkDragContext * context = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_drag_set_icon_default(context);
	return SUCCESS;
};

GLOBAL_FUNCTION(SetIconName, 4) {
	GdkDragContext * context = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *icon_name = Std$String$flatten(Args[1].Val);
	int hot_x = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int hot_y = ((Std$Integer_smallt *)Args[3].Val)->Value;
	gtk_drag_set_icon_name(context, icon_name, hot_x, hot_y);
	return SUCCESS;
};

GLOBAL_FUNCTION(SetIconPixbuf, 4) {
	GdkDragContext * context = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkPixbuf * pixbuf = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int hot_x = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int hot_y = ((Std$Integer_smallt *)Args[3].Val)->Value;
	gtk_drag_set_icon_pixbuf(context, pixbuf, hot_x, hot_y);
	return SUCCESS;
};

GLOBAL_FUNCTION(SetIconPixmap, 6) {
	GdkDragContext * context = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkColormap * colormap = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GdkPixmap * pixmap = ((Gtk$GObject$Object_t *)Args[2].Val)->Handle;
	GdkBitmap * mask = ((Gtk$GObject$Object_t *)Args[3].Val)->Handle;
	int hot_x = ((Std$Integer_smallt *)Args[4].Val)->Value;
	int hot_y = ((Std$Integer_smallt *)Args[5].Val)->Value;
	gtk_drag_set_icon_pixmap(context, colormap, pixmap, mask, hot_x, hot_y);
	return SUCCESS;
};

GLOBAL_FUNCTION(SetIconStock, 4) {
	GdkDragContext * context = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *stock_id = Std$String$flatten(Args[1].Val);
	int hot_x = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int hot_y = ((Std$Integer_smallt *)Args[3].Val)->Value;
	gtk_drag_set_icon_stock(context, stock_id, hot_x, hot_y);
	return SUCCESS;
};

GLOBAL_FUNCTION(SetIconWidget, 4) {
	GdkDragContext * context = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	int hot_x = ((Std$Integer_smallt *)Args[2].Val)->Value;
	int hot_y = ((Std$Integer_smallt *)Args[3].Val)->Value;
	gtk_drag_set_icon_widget(context, widget, hot_x, hot_y);
	return SUCCESS;
};

GLOBAL_FUNCTION(SourceAddImageTargets, 1) {
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_drag_source_add_image_targets(widget);
	return SUCCESS;
};

GLOBAL_FUNCTION(SourceAddTextTargets, 1) {
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_drag_source_add_text_targets(widget);
	return SUCCESS;
};

GLOBAL_FUNCTION(SourceAddUriTargets, 1) {
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_drag_source_add_uri_targets(widget);
	return SUCCESS;
};

GLOBAL_FUNCTION(SourceGetTargetList, 1) {
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTargetList * result = gtk_drag_source_get_target_list(widget);
	Result->Val = Std$String$new_format("Incomplete GTK function: %s:%d", __FILE__, __LINE__);
	return MESSAGE;
	return SUCCESS;
};

GLOBAL_FUNCTION(SourceSet, 5) {
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int start_button_mask = ((Std$Integer_smallt *)Args[1].Val)->Value;
	GtkTargetEntry * targets= &((Gtk$Gtk$TargetEntry_t *)Args[2].Val)->Value;
	int n_targets = ((Std$Integer_smallt *)Args[3].Val)->Value;
	int actions = ((Std$Integer_smallt *)Args[4].Val)->Value;
	gtk_drag_source_set(widget, start_button_mask, targets, n_targets, actions);
	return SUCCESS;
};

GLOBAL_FUNCTION(SourceSetIcon, 4) {
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkColormap * colormap = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	GdkPixmap * pixmap = ((Gtk$GObject$Object_t *)Args[2].Val)->Handle;
	GdkBitmap * mask = ((Gtk$GObject$Object_t *)Args[3].Val)->Handle;
	gtk_drag_source_set_icon(widget, colormap, pixmap, mask);
	return SUCCESS;
};

GLOBAL_FUNCTION(SourceSetIconName, 2) {
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *icon_name = Std$String$flatten(Args[1].Val);
	gtk_drag_source_set_icon_name(widget, icon_name);
	return SUCCESS;
};

GLOBAL_FUNCTION(SourceSetIconPixbuf, 2) {
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GdkPixbuf * pixbuf = ((Gtk$GObject$Object_t *)Args[1].Val)->Handle;
	gtk_drag_source_set_icon_pixbuf(widget, pixbuf);
	return SUCCESS;
};

GLOBAL_FUNCTION(SourceSetIconStock, 2) {
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	char *stock_id = Std$String$flatten(Args[1].Val);
	gtk_drag_source_set_icon_stock(widget, stock_id);
	return SUCCESS;
};

GLOBAL_FUNCTION(SourceSetTargetList, 2) {
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	GtkTargetList * target_list= ((Gtk$Gtk$TargetList_t *)Args[1].Val)->Value;
	gtk_drag_source_set_target_list(widget, target_list);
	return SUCCESS;
};

GLOBAL_FUNCTION(SourceUnset, 1) {
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_drag_source_unset(widget);
	return SUCCESS;
};

GLOBAL_FUNCTION(Unhighlight, 1) {
	GtkWidget * widget = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	gtk_drag_unhighlight(widget);
	return SUCCESS;
};

