#ifndef Gdk_PropertyState_H
#define Gdk_PropertyState_H

#include <Std.h>
#define RIVA_MODULE Gtk$Gdk$PropertyState
#include <Riva-Header.h>

typedef struct Gtk$Gdk$PropertyState_t {
	Std$Type_t *Type;
	GdkPropertyState Value;
} Gtk$Gdk$PropertyState_t;

extern Std$Type_t Gtk$Gdk$PropertyState$T[];

#undef RIVA_MODULE

#endif
