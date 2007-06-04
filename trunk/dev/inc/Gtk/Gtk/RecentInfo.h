#ifndef Gtk_RecentInfo_H
#define Gtk_RecentInfo_H

#define RIVA_MODULE Gtk$Gtk$RecentInfo
#include <Std.h>

#include <Riva-Header.h>

typedef struct Gtk$Gtk$RecentInfo_t {
	Std$Type_t *Type;
	GtkRecentInfo *Value;
} Gtk$Gtk$RecentInfo_t;

extern Std$Type_t Gtk$Gtk$RecentInfo$T[];

#undef RIVA_MODULE

#endif
