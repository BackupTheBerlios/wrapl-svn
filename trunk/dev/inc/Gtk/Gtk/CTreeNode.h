#ifndef Gtk_CTreeNode_H
#define Gtk_CTreeNode_H

#define RIVA_MODULE Gtk$Gtk$CTreeNode
#include <Std.h>

#include <Riva-Header.h>

typedef struct Gtk$Gtk$CTreeNode_t {
	Std$Type_t *Type;
	GtkCTreeNode Value;
} Gtk$Gtk$CTreeNode_t;

extern Std$Type_t Gtk$Gtk$CTreeNode$T[];

#undef RIVA_MODULE

#endif
