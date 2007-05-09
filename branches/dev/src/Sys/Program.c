#include <Lang.h>
#include <Riva/Memory.h>
#include <Riva/Thread.h>
#include <Riva/System.h>

GLOBAL_FUNCTION(Exit, 0) {
	exit(Count ? ((Lang$Integer_smallt *)Args[0].Val)->Value : 0);
};

GLOBAL_FUNCTION(Break, 0) {
	asm("int3");
	return SUCCESS;
};

Lang$List_t Args[] = {{
	Lang$List$T,
	0, 0, 0, 0,
	0,
	0, 0, 0, 4
}};

void __init(void) {
	if (Riva$System$_NoOfArgs > 0) {
		Lang$List_node *Node = new(Lang$List_node);
		Node->Value = Lang$String$new(Riva$System$_Args[0]);
		Args->Head = Node;
		Args->Cache = Node;
		Args->Index = 1;
		for (int I = 1; I < Riva$System$_NoOfArgs; ++I) {
			Lang$List_node *Prev = Node;
			Node = new(Lang$List_node);
			(Node->Prev = Prev)->Next = Node;
			Node->Value = Lang$String$new(Riva$System$_Args[I]);
		};
		Args->Tail = Node;
		Node->Next = 0;
		Args->Length = Riva$System$_NoOfArgs;
	};
};