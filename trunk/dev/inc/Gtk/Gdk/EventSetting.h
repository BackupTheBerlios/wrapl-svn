#ifndef Gdk_EventSetting_H
#define Gdk_EventSetting_H

#define RIVA_MODULE Gtk$Gdk$EventSetting
#include <Std.h>

#include <Riva-Header.h>

typedef struct Gtk$Gdk$EventSetting_t {
	Std$Type_t *Type;
	GdkEventSetting Value;
} Gtk$Gdk$EventSetting_t;

extern Std$Type_t Gtk$Gdk$EventSetting$T[];

#undef RIVA_MODULE

#endif
