#include <Gtk/Gtk/Targets.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 4
#include <Gtk/Gtk/TextBuffer.h>
#include <Std/Boolean.h>
#include <Gtk/Gdk/Atom.h>
#include <Gtk/GObject/Object.h>
/***********************************/
GLOBAL_FUNCTION(IncludeImage, 3) {
	GdkAtom * targets= ((Gtk$Gdk$Atom_t *)Args[0].Val)->Value;
	int n_targets = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int writable = Args[2].Val == $true;
	int result = gtk_targets_include_image(targets, n_targets, writable);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

GLOBAL_FUNCTION(IncludeRichText, 3) {
	GdkAtom * targets= ((Gtk$Gdk$Atom_t *)Args[0].Val)->Value;
	int n_targets = ((Std$Integer_smallt *)Args[1].Val)->Value;
	GtkTextBuffer * buffer = ((Gtk$GObject$Object_t *)Args[2].Val)->Handle;
	int result = gtk_targets_include_rich_text(targets, n_targets, buffer);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

GLOBAL_FUNCTION(IncludeText, 2) {
	GdkAtom * targets= ((Gtk$Gdk$Atom_t *)Args[0].Val)->Value;
	int n_targets = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int result = gtk_targets_include_text(targets, n_targets);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

GLOBAL_FUNCTION(IncludeUri, 2) {
	GdkAtom * targets= ((Gtk$Gdk$Atom_t *)Args[0].Val)->Value;
	int n_targets = ((Std$Integer_smallt *)Args[1].Val)->Value;
	int result = gtk_targets_include_uri(targets, n_targets);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

