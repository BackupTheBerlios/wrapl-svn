#ifndef Gtk_SettingsPropertyValue_H
#define Gtk_SettingsPropertyValue_H

#define RIVA_MODULE Gtk$Gtk$SettingsPropertyValue
#include <Std.h>

#include <Riva-Header.h>

typedef struct Gtk$Gtk$SettingsPropertyValue_t {
	Std$Type_t *Type;
	GtkSettingsPropertyValue *Value;
} Gtk$Gtk$SettingsPropertyValue_t;

extern Std$Type_t Gtk$Gtk$SettingsPropertyValue$T[];

#undef RIVA_MODULE

#endif
