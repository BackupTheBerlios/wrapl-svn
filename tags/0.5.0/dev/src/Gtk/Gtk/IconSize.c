#include <Gtk/Gtk/IconSize.h>
#include <Lang.h>
#include <gtk/gtk.h>

Lang$Integer_smallt MENU[] = {{Lang$Integer$SmallT, GTK_ICON_SIZE_MENU}};
Lang$Integer_smallt SMALL_TOOLBAR[] = {{Lang$Integer$SmallT, GTK_ICON_SIZE_SMALL_TOOLBAR}};
Lang$Integer_smallt LARGE[] = {{Lang$Integer$SmallT, GTK_ICON_SIZE_LARGE_TOOLBAR}};
Lang$Integer_smallt BUTTON[] = {{Lang$Integer$SmallT, GTK_ICON_SIZE_BUTTON}};
Lang$Integer_smallt DND[] = {{Lang$Integer$SmallT, GTK_ICON_SIZE_DND}};
Lang$Integer_smallt DIALOG[] = {{Lang$Integer$SmallT, GTK_ICON_SIZE_DIALOG}};

GLOBAL_FUNCTION(Lookup, 1) {
	int Width, Height;
	gtk_icon_size_lookup(((Lang$Integer_smallt *)Args[0].Val)->Value, &Width, &Height);
	Result->Val = Lang$List$new(2, Lang$Integer$new_small(Width), Lang$Integer$new_small(Height));
	return SUCCESS;
};
