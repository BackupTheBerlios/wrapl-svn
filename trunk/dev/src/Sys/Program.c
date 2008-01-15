#include <Std.h>
#include <IO/Socket.h>
#include <Riva/Memory.h>
#include <Riva/Thread.h>
#include <Riva/System.h>

GLOBAL_FUNCTION(Exit, 0) {
	exit(Count ? ((Std$Integer_smallt *)Args[0].Val)->Value : 0);
};

GLOBAL_FUNCTION(Break, 0) {
	asm("int3");
	return SUCCESS;
};

Std$List_t Args[] = {{
	Std$List$T,
	0, 0, 0, 0,
	0,
	0, 0, 0, 4
}};

void __init(void) {
	if (Riva$System$_NoOfArgs > 0) {
		Std$List_node *Node = new(Std$List_node);
		Node->Value = Std$String$new(Riva$System$_Args[0]);
		Args->Head = Node;
		Args->Cache = Node;
		Args->Index = 1;
		for (int I = 1; I < Riva$System$_NoOfArgs; ++I) {
			Std$List_node *Prev = Node;
			Node = new(Std$List_node);
			(Node->Prev = Prev)->Next = Node;
			Node->Value = Std$String$new(Riva$System$_Args[I]);
		};
		Args->Tail = Node;
		Node->Next = 0;
		Args->Length = Riva$System$_NoOfArgs;
	};
};
