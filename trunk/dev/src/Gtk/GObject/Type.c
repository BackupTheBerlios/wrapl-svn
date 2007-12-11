#include <Gtk/GObject/Init.h>
#include <Gtk/GObject/Type.h>
#include <Gtk/GObject/Object.h>
#include <Gtk/TypeMap.h>
#include <Riva.h>
#include <Util/StringTable.h>
#include <Util/ObjectTable.h>
#include <stdio.h>

#include <gobject/gvaluecollector.h>

TYPE(T, Gtk$GObject$Object$T);

METHOD("@", TYP, T, VAL, Std$String$T) {
	Gtk$GObject$Type_t *Type = Args[0].Val;
	Result->Val = Std$String$new(g_type_name(Type->Value));
	return SUCCESS;
};

Gtk$GObject$Type_t INVALID[] = {{T, G_TYPE_INVALID}};
Gtk$GObject$Type_t NONE[] = {{T, G_TYPE_NONE}};
Gtk$GObject$Type_t INTERFACE[] = {{T, G_TYPE_INTERFACE}};
Gtk$GObject$Type_t CHAR[] = {{T, G_TYPE_CHAR}};
Gtk$GObject$Type_t UCHAR[] = {{T, G_TYPE_UCHAR}};
Gtk$GObject$Type_t BOOLEAN[] = {{T, G_TYPE_BOOLEAN}};
Gtk$GObject$Type_t INT[] = {{T, G_TYPE_INT}};
Gtk$GObject$Type_t UINT[] = {{T, G_TYPE_UINT}};
Gtk$GObject$Type_t LONG[] = {{T, G_TYPE_LONG}};
Gtk$GObject$Type_t ULONG[] = {{T, G_TYPE_ULONG}};
Gtk$GObject$Type_t INT64[] = {{T, G_TYPE_INT64}};
Gtk$GObject$Type_t UINT64[] = {{T, G_TYPE_UINT64}};
Gtk$GObject$Type_t ENUM[] = {{T, G_TYPE_ENUM}};
Gtk$GObject$Type_t FLAGS[] = {{T, G_TYPE_FLAGS}};
Gtk$GObject$Type_t FLOAT[] = {{T, G_TYPE_FLOAT}};
Gtk$GObject$Type_t DOUBLE[] = {{T, G_TYPE_DOUBLE}};
Gtk$GObject$Type_t STRING[] = {{T, G_TYPE_STRING}};
Gtk$GObject$Type_t POINTER[] = {{T, G_TYPE_POINTER}};
Gtk$GObject$Type_t BOXED[] = {{T, G_TYPE_BOXED}};
Gtk$GObject$Type_t PARAM[] = {{T, G_TYPE_PARAM}};
Gtk$GObject$Type_t OBJECT[] = {{T, G_TYPE_OBJECT}};
Gtk$GObject$Type_t RIVA[] = {{T, G_TYPE_INVALID}};

static Util$ObjectTable_t GTypeToRiva[] = {Util$ObjectTable$INIT};

Std$Type_t *_to_riva(GType GtkType) {
	Std$Type_t *RivaType = Util$ObjectTable$get(GTypeToRiva, GtkType);
	if (RivaType != (Std$Type_t *)0xFFFFFFFF) return RivaType;
	const char *GtkName = g_type_name(GtkType);
	const char *RivaName = Util$StringTable$get(Gtk$TypeMap$Table, GtkName);
	if (RivaName == 0) {
		Riva$Log$errorf("Warning: Gtk type is not mapped: %s\n", GtkName);
		return 0;
	};
	Riva$Module_t *Module = Riva$Module$load(0, RivaName);
	if (Module == 0) {
		Riva$Log$errorf("Error: Module not found: %s\n", RivaName);
		return 0;
	};
	int Flag;
	if (Riva$Module$import(Module, "T", &Flag, (void **)&RivaType) == 0) {
		Riva$Log$errorf("Error: Export not found: %s.t\n", RivaName);
		return 0;
	};
	Util$ObjectTable$put(GTypeToRiva, GtkType, RivaType);
	return RivaType;
};

static void riva_value_init(GValue *Value) {
};

static void riva_value_free(GValue *Value) {
};

static void riva_value_copy(const GValue *Src, GValue *Dst) {
    Dst->data[0].v_pointer = Src->data[0].v_pointer;
};

static gpointer riva_value_peek_pointer(const GValue *Value) {
    return Value->data[0].v_pointer;
};

static gchar *riva_collect_value(GValue *Value, guint N, GTypeCValue *Values, guint Flags) {
    Value->data[0].v_pointer = Values[0].v_pointer;
    return 0;
};

static gchar *riva_lcopy_value(const GValue *Value, guint N, GTypeCValue *Values, guint Flags) {
    Std$Object_t **p = Values[0].v_pointer;
    *p = Value->data[0].v_pointer;
    return 0;
};

static void riva_instance_init(GTypeInstance *instance, gpointer g_class) {
};

void __init(Riva$Module_t *Module) {
    g_type_init();
    RIVA->Value = g_type_fundamental_next();
    GTypeValueTable ValueTable = {
	.value_init = riva_value_init,
	.value_free = riva_value_free,
	.value_copy = riva_value_copy,
	.value_peek_pointer = riva_value_peek_pointer,
	.collect_format = "p",
	.collect_value = riva_collect_value,
	.lcopy_format = "p",
	.lcopy_value = riva_lcopy_value
    };
    GTypeInfo Info = {0,};
    Info.class_size = sizeof(Info);
    Info.instance_size = 4;
    Info.value_table = &ValueTable;
    Info.instance_init = riva_instance_init;
    GTypeFundamentalInfo FundamentalInfo = {0,};
    FundamentalInfo.type_flags = G_TYPE_FLAG_INSTANTIATABLE | G_TYPE_FLAG_CLASSED;
    g_type_register_fundamental(RIVA->Value, "riva", &Info, &FundamentalInfo, 0);
};
