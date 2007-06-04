#include <Gtk/Gtk/RcProperty.h>
#include <Riva/Memory.h>
/***********************************/
// Number of included files = 3
#include <Std/Boolean.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/GObject/Value.h>
/***********************************/
TYPE(T);

GLOBAL_FUNCTION(ParseBorder, 3) {
	const GParamSpec* pspec = 0;
	const GString* gstring = 0;
	GValue property_value[1];
	Gtk$GObject$Value$to_gtk(Args[2].Val, property_value);
	int result = gtk_rc_property_parse_border(pspec, gstring, property_value);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

GLOBAL_FUNCTION(ParseColor, 3) {
	const GParamSpec* pspec = 0;
	const GString* gstring = 0;
	GValue property_value[1];
	Gtk$GObject$Value$to_gtk(Args[2].Val, property_value);
	int result = gtk_rc_property_parse_color(pspec, gstring, property_value);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

GLOBAL_FUNCTION(ParseEnum, 3) {
	const GParamSpec* pspec = 0;
	const GString* gstring = 0;
	GValue property_value[1];
	Gtk$GObject$Value$to_gtk(Args[2].Val, property_value);
	int result = gtk_rc_property_parse_enum(pspec, gstring, property_value);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

GLOBAL_FUNCTION(ParseFlags, 3) {
	const GParamSpec* pspec = 0;
	const GString* gstring = 0;
	GValue property_value[1];
	Gtk$GObject$Value$to_gtk(Args[2].Val, property_value);
	int result = gtk_rc_property_parse_flags(pspec, gstring, property_value);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

GLOBAL_FUNCTION(ParseRequisition, 3) {
	const GParamSpec* pspec = 0;
	const GString* gstring = 0;
	GValue property_value[1];
	Gtk$GObject$Value$to_gtk(Args[2].Val, property_value);
	int result = gtk_rc_property_parse_requisition(pspec, gstring, property_value);
	Result->Val = result ? $true : $false;
	return SUCCESS;
};

