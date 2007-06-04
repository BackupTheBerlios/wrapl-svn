#ifndef Gdk_DeviceAxis_H
#define Gdk_DeviceAxis_H

#define RIVA_MODULE Gtk$Gdk$DeviceAxis
#include <Std.h>

#include <Riva-Header.h>

typedef struct Gtk$Gdk$DeviceAxis_t {
	Std$Type_t *Type;
	GdkDeviceAxis Value;
} Gtk$Gdk$DeviceAxis_t;

extern Std$Type_t Gtk$Gdk$DeviceAxis$T[];

#undef RIVA_MODULE

#endif
