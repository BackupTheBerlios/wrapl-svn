#include <Gtk/Gdk/Drop.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 3
#include <Std/Boolean.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/Gdk/DragContext.h>
/***********************************/
GLOBAL_FUNCTION(Finish, 3) {
	GdkDragContext * context = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int success = Args[1].Val == $true;
	int time_ = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gdk_drop_finish(context, success, time_);
	return SUCCESS;
};

GLOBAL_FUNCTION(Reply, 3) {
	GdkDragContext * context = ((Gtk$GObject$Object_t *)Args[0].Val)->Handle;
	int ok = Args[1].Val == $true;
	int time_ = ((Std$Integer_smallt *)Args[2].Val)->Value;
	gdk_drop_reply(context, ok, time_);
	return SUCCESS;
};

