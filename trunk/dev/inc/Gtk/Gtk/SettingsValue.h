#ifndef Gtk_SettingsValue_H
#define Gtk_SettingsValue_H

#define RIVA_MODULE Gtk$Gtk$SettingsValue
#include <Std.h>

#include <Riva-Header.h>

typedef struct Gtk$Gtk$SettingsValue_t {
	Std$Type_t *Type;
	GtkSettingsValue Value;
} Gtk$Gtk$SettingsValue_t;

extern Std$Type_t Gtk$Gtk$SettingsValue$T[];

#undef RIVA_MODULE

#endif
