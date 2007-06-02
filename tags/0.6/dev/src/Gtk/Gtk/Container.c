#include <Gtk/Gtk/Container.h>
#include <Riva/Memory.h>

TYPE(T, Gtk$Gtk$Widget$T, Gtk$Gtk$Object$T, Gtk$GObject$Object$T);

METHOD("add", TYP, T, TYP, Gtk$Gtk$Widget$T) {
	Gtk$GObject$Object_t *Object0 = Args[0].Val;
	Gtk$GObject$Object_t *Object1 = Args[1].Val;
	gtk_container_add(Object0->Handle, Object1->Handle);
	Result->Arg = Args[0];
	return SUCCESS;
};

METHOD("remove", TYP, T, TYP, Gtk$Gtk$Widget$T) {
	Gtk$GObject$Object_t *Object0 = Args[0].Val;
	Gtk$GObject$Object_t *Object1 = Args[1].Val;
	gtk_container_remove(Object0->Handle, Object1->Handle);
	Result->Arg = Args[0];
	return SUCCESS;
};

typedef struct children_generator {
	Lang$Function_cstate State;
	GList *Current;
} children_generator;

typedef struct children_resume_data {
	children_generator *Generator;
	Lang$Function_argument Result;
} children_resume_data;

static long children_resume(children_resume_data *Data) {
	GList *Node = Data->Generator->Current->next;
	if (Node != 0) {
		Data->Generator->Current = Node;
		Data->Result.Val = Gtk$GObject$Object$gtk_to_riva(Node->data);
		return SUSPEND;
	} else {
		return FAILURE;
	};
};

METHOD("children", TYP, T) {
	Gtk$GObject$Object_t *Container = Args[0].Val;
	GList *Children = gtk_container_get_children(Container->Handle);
	if (Children) {
		children_generator *Generator = new(children_generator);
		Generator->State.Run = Lang$Function$resume_c;
		Generator->State.Invoke = children_resume;
		Generator->Current = Children;
		Result->Val = Gtk$GObject$Object$gtk_to_riva(Children->data);
		Result->State = Generator;
		return SUSPEND;
	} else {
		return FAILURE;
	};
};
