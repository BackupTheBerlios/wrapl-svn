#ifndef Gdk_SettingAction_H
#define Gdk_SettingAction_H

#include <Std.h>
#define RIVA_MODULE Gtk$Gdk$SettingAction
#include <Riva-Header.h>

typedef struct Gtk$Gdk$SettingAction_t {
	Std$Type_t *Type;
	GdkSettingAction Value;
} Gtk$Gdk$SettingAction_t;

extern Std$Type_t Gtk$Gdk$SettingAction$T[];

#undef RIVA_MODULE

#endif
