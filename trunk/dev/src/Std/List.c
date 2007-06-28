#include <Std.h>
#include <Riva/Memory.h>

typedef struct Std$List_t _list;
typedef struct Std$List_node _node;

TYPE(T);

GLOBAL_FUNCTION(New, 0) {
	_list *List = new(_list);
	List->Type = T;
	if (Count > 0) {
		long I, Size = ((Std$Integer_smallt *)Args[0].Val)->Value;
		Std$Object_t *Value = Std$Object$Nil;
		_node *Node = new(_node);
		if (Count > 1) Value = Args[1].Val;
		Node->Value = Value;
		List->Head = Node;
		List->Cache = Node;
		List->Index = 1;
		for (I = 1; I < Size; ++I) {
			_node *Prev = Node;
			Node = new(_node);
			(Node->Prev = Prev)->Next = Node;
			Node->Value = Value;
		};
		List->Tail = Node;
		List->Length = Size;
	} else {
		List->Length = 0;
	};
	List->Lower = List->Upper = 0;
	List->Access = 4;
	Result->Val = List;
	return SUCCESS;
};

Std$Object_t *_new(long Count, ...) {
	Std$Object_t **Values = (&Count + 1);
	_list *List = new(_list);
	List->Type = T;
	if (Count > 0) {
		_node *Node = new(_node);
		Node->Value = Values[0];
		List->Head = Node;
		List->Cache = Node;
		List->Index = 1;
		for (int I = 1; I < Count; ++I) {
			_node *Prev = Node;
			Node = new(_node);
			(Node->Prev = Prev)->Next = Node;
			Node->Value = Values[I];
		};
		List->Tail = Node;
		List->Length = Count;
	} else {
		List->Length = 0;
	};
	List->Lower = List->Upper = 0;
	List->Access = 4;
	return List;
};

Std$Object_t *_newv(long Count, Std$Object_t **Values) {
	_list *List = new(_list);
	List->Type = T;
	if (Count > 0) {
		_node *Node = new(_node);
		Node->Value = Values[0];
		List->Head = Node;
		List->Cache = Node;
		List->Index = 1;
		for (int I = 1; I < Count; ++I) {
			_node *Prev = Node;
			Node = new(_node);
			(Node->Prev = Prev)->Next = Node;
			Node->Value = Values[I];
		};
		List->Tail = Node;
		List->Length = Count;
	} else {
		List->Length = 0;
	};
	List->Lower = List->Upper = 0;
	List->Access = 4;
	return List;
};

GLOBAL_FUNCTION(Make, 0) {
	_list *List = new(_list);
	List->Type = T;
	if (Count > 0) {
		_node *Node = new(_node);
		Node->Value = Args[0].Val;
		List->Head = Node;
		List->Cache = Node;
		List->Index = 1;
		for (int I = 1; I < Count; ++I) {
			_node *Prev = Node;
			Node = new(_node);
			(Node->Prev = Prev)->Next = Node;
			Node->Value = Args[I].Val;
		};
		List->Tail = Node;
		List->Length = Count;
	} else {
		List->Length = 0;
	};
	List->Lower = List->Upper = 0;
	List->Access = 4;
	Result->Val = List;
	return SUCCESS;
};

METHOD("copy", TYP, T) {
	const _list *List0 = (_list *)Args[0].Val;
	_list *List = new(_list);
	List->Type = T;
	if (List0->Head) {
		_node *Temp = List0->Head;
		_node *Node = new(_node);
		List->Head = Node;
		Node->Value = Temp->Value;
		while (Temp = Temp->Next) {
			_node *Prev = Node;
			Node = new(_node);
			(Node->Prev = Prev)->Next = Node;
			Node->Value = Temp->Value;
		};
		List->Cache = Node;
		List->Index = List0->Length;
		List->Tail = Node;
	};
	List->Length = List0->Length;
	List->Lower = List->Upper = 0;
	List->Access = 4;
	Result->Val = List;
	return SUCCESS;
};

METHOD("+", TYP, T, TYP, T) {
	const _list *List0 = (_list *)Args[0].Val;
	const _list *List1 = (_list *)Args[1].Val;
	_list *List = new(_list);
	List->Type = T;
	if (List0->Head) {
		_node *Temp = List0->Head;
		_node *Node = new(_node);
		List->Head = Node;
		Node->Value = Temp->Value;
		while (Temp = Temp->Next) {
			_node *Prev = Node;
			Node = new(_node);
			(Node->Prev = Prev)->Next = Node;
			Node->Value = Temp->Value;
		};
		List->Cache = Node;
		List->Index = List0->Length;
		for (Temp = List1->Head; Temp; Temp = Temp->Next) {
			_node *Prev = Node;
			Node = new(_node);
			(Node->Prev = Prev)->Next = Node;
			Node->Value = Temp->Value;
		};
		List->Tail = Node;
	} else if (List1->Head) {
		_node *Temp = List1->Head;
		_node *Node = new(_node);
		List->Head = Node;
		List->Cache = Node;
		List->Index = 1;
		Node->Value = Temp->Value;
		while (Temp = Temp->Next) {
			_node *Prev = Node;
			Node = new(_node);
			(Node->Prev = Prev)->Next = Node;
			Node->Value = Temp->Value;
		};
		List->Tail = Node;
	};
	List->Length = List0->Length + List1->Length;
	List->Lower = List->Upper = 0;
	List->Access = 4;
	Result->Val = List;
	return SUCCESS;
};

METHOD("push", TYP, T, SKP) {
	_list *List = (_list *)Args[0].Val;
	_node *Node = new(_node);
	Node->Value = Count < 2 ? Std$Object$Nil : Args[1].Val;
	Node->Next = List->Head;
	if (List->Head) List->Head->Prev = Node; else List->Tail = Node;
	List->Head = Node;
	++List->Length;
	if (List->Array) {++List->Lower; ++List->Upper;};
	List->Index = 1; List->Cache = List->Head;
	List->Access = 4;
	Result->Arg = Args[0];
	return SUCCESS;
};

METHOD("put", TYP, T, SKP) {
	_list *List = (_list *)Args[0].Val;
	_node *Node = new(_node);
	Node->Value = Count < 2 ? Std$Object$Nil : Args[1].Val;
	Node->Prev = List->Tail;
	if (List->Tail) List->Tail->Next = Node; else List->Head = Node;
	List->Tail = Node;
	++List->Length;
	List->Index = 1; List->Cache = List->Head;
	List->Access = 4;
	Result->Arg = Args[0];
	return SUCCESS;
};

METHOD("pop", TYP, T) {
	_list *List = (_list *)Args[0].Val;
	_node *Node = List->Head;
	if (!Node) return FAILURE;
	if (List->Head = Node->Next) List->Head->Prev = 0; else List->Tail = 0;
	--List->Length;
	if (List->Array) {
		if (List->Lower > 1) --List->Lower; else ++List->Array;
		--List->Upper;
	};
	List->Index = 1; List->Cache = List->Head;
	List->Access = 4;
	Result->Val = Node->Value;
	return SUCCESS;
};

METHOD("pull", TYP, T) {
	_list *List = (_list *)Args[0].Val;
	_node *Node = List->Tail;
	if (!Node) return FAILURE;
	if (List->Tail = Node->Prev) List->Tail->Next = 0; else List->Head = 0;
	--List->Length;
	if (List->Array) {
		if (List->Upper > List->Length) --List->Upper;
	};
	List->Index = 1; List->Cache = List->Head;
	List->Access = 4;
	Result->Val = Node->Value;
	return SUCCESS;
};

static void build_index_array(_list *List) {
	_node **Array = (_node **)Riva$Memory$alloc(sizeof(_node *) * List->Length);
	_node **Address = Array;
	_node *Node = List->Head;
	while (Node) Node = (*Address++ = Node)->Next;
	List->Array = Array;
	List->Lower = 1;
	List->Upper = List->Length;
};

METHOD("[]", TYP, T, TYP, Std$Integer$SmallT) {
	_list *List = (_list *)Args[0].Val;
	long Index = ((Std$Integer_smallt *)Args[1].Val)->Value;
	long Cache = List->Index;
	long Length = List->Length;
	if (Index < 0) Index += Length + 1;
	if ((Index < 1) || (Length < Index)) return FAILURE;
	if (Index == 1) {Result->Val = *(Result->Ref = &(List->Head->Value)); return SUCCESS;};
	if (Index == Length) {Result->Val = *(Result->Ref = &(List->Tail->Value)); return SUCCESS;};
	switch (Index - Cache) {
	case -1: {
		List->Index = Index;
		Result->Val = *(Result->Ref = &(List->Cache = List->Cache->Prev)->Value);
		return SUCCESS;
	};
	case 0: {
		Result->Val = *(Result->Ref = &List->Cache->Value);
		return SUCCESS;
	};
	case 1: {
		List->Index = Index;
		Result->Val = *(Result->Ref = &(List->Cache = List->Cache->Next)->Value);
		return SUCCESS;
	};
	};
	if (List->Array && (List->Lower <= Index) && (Index <= List->Upper)) {
		Result->Val = *(Result->Ref = &List->Array[Index - List->Lower]->Value);
		return SUCCESS;
	} else if (--List->Access == 0) {
		build_index_array(List);
		Result->Val = *(Result->Ref = &List->Array[Index - 1]->Value);
		return SUCCESS;
	} else if (2 * Index < Cache) {
		_node *Node = List->Head;
		long Steps = Index - 1;
		do Node = Node->Next; while (--Steps);
		List->Index = Index;
		Result->Val = *(Result->Ref = &(List->Cache = Node)->Value);
		return SUCCESS;
	} else if (Index < Cache) {
		_node *Node = List->Cache;
		long Steps = Cache - Index;
		do Node = Node->Prev; while (--Steps);
		List->Index = Index;
		Result->Val = *(Result->Ref = &(List->Cache = Node)->Value);
		return SUCCESS;
	} else if (2 * Index < Cache + Length) {
		_node *Node = List->Cache;
		long Steps = Index - Cache;
		do Node = Node->Next; while (--Steps);
		List->Index = Index;
		Result->Val = *(Result->Ref = &(List->Cache = Node)->Value);
		return SUCCESS;
	} else {
		_node *Node = List->Tail;
		long Steps = Length - Index;
		do Node = Node->Prev; while (--Steps);
		List->Index = Index;
		Result->Val = *(Result->Ref = &(List->Cache = Node)->Value);
		return SUCCESS;
	};
};

static _node *find_node(_list *List, long Index) {
	long Cache = List->Index, Length = List->Length;
	if (Index == 1) return List->Head;
	if (Index == Length) return List->Tail;

	switch (Index - Cache) {
	case -1: {List->Index = Index; return (List->Cache = List->Cache->Prev);};
	case 0: {return List->Cache;};
	case 1: {List->Index = Index; return (List->Cache = List->Cache->Next);};
	};
	if (List->Array && (List->Lower <= Index) && (Index <= List->Upper)) {
		return List->Array[Index - List->Lower];
	} else if (--List->Access == 0) {
		build_index_array(List); return List->Array[Index - 1];
	} else if (2 * Index < Cache) {
		_node *Node = List->Head; long Steps = Index - 1;
		do Node = Node->Next; while (--Steps);
		List->Index = Index;
		return (List->Cache = Node);
	} else if (Index < Cache) {
		_node *Node = List->Cache; long Steps = Cache - Index;
		do Node = Node->Prev; while (--Steps);
		List->Index = Index;
		return (List->Cache = Node);
	} else if (2 * Index < Cache + Length) {
		_node *Node = List->Cache; long Steps = Index - Cache;
		do Node = Node->Next; while (--Steps);
		List->Index = Index;
		return (List->Cache = Node);
	} else {
		_node *Node = List->Tail; long Steps = Length - Index;
		do Node = Node->Prev; while (--Steps);
		List->Index = Index;
		return (List->Cache = Node);
	};
};

METHOD("[]", TYP, T, TYP, Std$Integer$SmallT, TYP, Std$Integer$SmallT) {
	_list *List = (_list *)Args[0].Val;
	long Length = List->Length;
	long Index0 = ((Std$Integer_smallt *)Args[1].Val)->Value;
	if (Index0 <= 0) Index0 += Length + 1;
	if ((Index0 < 1) || (Length < Index0)) return FAILURE;
	long Index1 = ((Std$Integer_smallt *)Args[2].Val)->Value;
	if (Index1 <= 0) Index1 += Length + 1;
	--Index1;
	if ((Index1 < 0) || (Length < Index1)) return FAILURE;
	if (Index0 > Index1) {
		_list *List2 = new(_list);
		List2->Type = T;
		List2->Length = 0;
		List2->Lower = List2->Upper = 0;
		List2->Access = 4;
		Result->Val = List2;
		return SUCCESS;
	};

	_node *Head = find_node(List, Index0);
	_node *Tail = find_node(List, Index1);

	_list *List2 = new(_list);
	List2->Type = T;
	_node *Node = new(_node);
	Node->Value = Head->Value;
	List2->Head = Node;
	List2->Cache = Node;
	List2->Index = 1;
	List2->Length = Index1 - Index0 + 1;
	if (Head != Tail) {
		_node *Temp = Head;
		do {
			Temp = Temp->Next;
			_node *Prev = Node;
			Node = new(_node);
			(Node->Prev = Prev)->Next = Node;
			Node->Value = Temp->Value;
		} while (Temp != Tail);
	};
	List2->Tail = Node;
	List2->Lower = List->Upper = 0;
	List2->Access = 4;
	Result->Val = List2;
	return SUCCESS;
};

static Std$Object_t *delete_node(_list *List, _node *Node) {
	(Node->Prev->Next = Node->Next)->Prev = Node->Prev;
	--List->Length;
	List->Array = 0;
	List->Access = 4;
	return Node->Value;
};

METHOD("delete", TYP, T) {
	_list *List = (_list *)Args[0].Val;
	long Index = ((Std$Integer_smallt *)Args[1].Val)->Value;
	long Cache = List->Index;
	long Length = List->Length;
	if (Index < 0) Index += Length + 1;
	if ((Index < 1) || (Length < Index)) return FAILURE;
	if (Index == 1) {
		_node *Node = List->Head;
		if (List->Head = Node->Next) List->Head->Prev = 0; else List->Tail = 0;
		--List->Length;
		if (List->Array) {
			if (List->Lower > 1) --List->Lower; else ++List->Array;
			--List->Upper;
		};
		List->Index = 1; List->Cache = List->Head;
		List->Access = 4;
		Result->Val = Node->Value;
		return SUCCESS;
	};
	if (Index == Length) {
		_node *Node = List->Tail;
		if (List->Tail = Node->Prev) List->Tail->Next = 0; else List->Head = 0;
		--List->Length;
		if (List->Array) {
			if (List->Upper > List->Length) --List->Upper;
		};
		List->Index = 1; List->Cache = List->Head;
		List->Access = 4;
		Result->Val = Node->Value;
		return SUCCESS;
	};
	switch (Index - Cache) {
	case -1: {
		Result->Val = delete_node(List, List->Cache->Prev);
		--List->Index;
		return SUCCESS;
	};
	case 0: {
		Result->Val = delete_node(List, List->Cache);
		List->Index = 1; List->Cache = List->Head;
		return SUCCESS;
	};
	case 1: {
		Result->Val = delete_node(List, List->Cache->Next);
		return SUCCESS;
	};
	};
	if (List->Array && (List->Lower <= Index) && (Index <= List->Upper)) {
		_node *Node = List->Array[Index - List->Lower];
		Result->Val = delete_node(List, Node);
		List->Index = 1; List->Cache = List->Head;
		return SUCCESS;
	} else if (2 * Index < Cache) {
		_node *Node = List->Head;
		long Steps = Index - 1;
		do Node = Node->Next; while (--Steps);
		Result->Val = delete_node(List, Node);
		List->Index = 1; List->Cache = List->Head;
		return SUCCESS;
	} else if (Index < Cache) {
		_node *Node = List->Cache;
		long Steps = Cache - Index;
		do Node = Node->Prev; while (--Steps);
		Result->Val = delete_node(List, Node);
		List->Index = 1; List->Cache = List->Head;
		return SUCCESS;
	} else if (2 * Index < Cache + Length) {
		_node *Node = List->Cache;
		long Steps = Index - Cache;
		do Node = Node->Next; while (--Steps);
		Result->Val = delete_node(List, Node);
		List->Index = 1; List->Cache = List->Head;
		return SUCCESS;
	} else {
		_node *Node = List->Tail;
		long Steps = Length - Index;
		do Node = Node->Prev; while (--Steps);
		Result->Val = delete_node(List, Node);
		List->Index = 1; List->Cache = List->Head;
		return SUCCESS;
	};
};

static void insert_node(_list *List, _node *Node, Std$Object_t *Value) {
	_node *New = new(_node);
	(New->Prev = Node->Prev)->Next = New;
	(New->Next = Node)->Prev = New;
	New->Value = Value;
	++List->Length;
	List->Array = 0;
	List->Access = 4;
	List->Index = 1; List->Cache = List->Head;
};

METHOD("insert", TYP, T, TYP, Std$Integer$SmallT, SKP) {
	_list *List = (_list *)Args[0].Val;
	long Index = ((Std$Integer_smallt *)Args[1].Val)->Value;
	Std$Object_t *Value = Args[2].Val;
	long Cache = List->Index;
	long Length = List->Length;
	if (Index < 0) Index += Length + 1;
	if ((Index < 1) || (Length + 1 < Index)) return FAILURE;
	if (Index == 1) {
		_node *Node = new(_node);
		Node->Value = Value;
		Node->Next = List->Head;
		if (List->Head) List->Head->Prev = Node; else List->Tail = Node;
		List->Head = Node;
		++List->Length;
		if (List->Array) {++List->Lower; ++List->Upper;};
		List->Index = 1; List->Cache = List->Head;
		List->Access = 4;
		Result->Arg = Args[0];
		return SUCCESS;
	};
	if (Index == Length + 1) {
		_node *Node = new(_node);
		Node->Value = Value;
		Node->Prev = List->Tail;
		if (List->Tail) List->Tail->Next = Node; else List->Head = Node;
		List->Tail = Node;
		++List->Length;
		List->Index = 1; List->Cache = List->Head;
		List->Access = 4;
		Result->Arg = Args[0];
		return SUCCESS;
	};
	if (Index == Length) {
		insert_node(List, List->Tail, Value);
		Result->Arg = Args[0];
		return SUCCESS;
	};
	switch (Index - Cache) {
	case -1: {
		insert_node(List, List->Cache->Prev, Value);
		Result->Arg = Args[0];
		return SUCCESS;
	};
	case 0: {
		insert_node(List, List->Cache, Value);
		Result->Arg = Args[0];
		return SUCCESS;
	};
	case 1: {
		insert_node(List, List->Cache->Next, Value);
		Result->Arg = Args[0];
		return SUCCESS;
	};
	};
	if (List->Array && (List->Lower <= Index) && (Index <= List->Upper)) {
		_node *Node = List->Array[Index - List->Lower];
		insert_node(List, Node, Value);
		Result->Arg = Args[0];
		return SUCCESS;
	} else if (2 * Index < Cache) {
		_node *Node = List->Head;
		long Steps = Index - 1;
		do Node = Node->Next; while (--Steps);
		insert_node(List, Node, Value);
		Result->Arg = Args[0];
		return SUCCESS;
	} else if (Index < Cache) {
		_node *Node = List->Cache;
		long Steps = Cache - Index;
		do Node = Node->Prev; while (--Steps);
		insert_node(List, Node, Value);
		Result->Arg = Args[0];
		return SUCCESS;
	} else if (2 * Index < Cache + Length) {
		_node *Node = List->Cache;
		long Steps = Index - Cache;
		do Node = Node->Next; while (--Steps);
		insert_node(List, Node, Value);
		Result->Arg = Args[0];
		return SUCCESS;
	} else {
		_node *Node = List->Tail;
		long Steps = Length - Index;
		do Node = Node->Prev; while (--Steps);
		insert_node(List, Node, Value);
		Result->Arg = Args[0];
		return SUCCESS;
	};
};

METHOD("length", TYP, T) {
	_list *List = (_list *)Args[0].Val;
	Result->Val = Std$Integer$new_small(List->Length);
	return SUCCESS;
};

METHOD("size", TYP, T) {
	_list *List = (_list *)Args[0].Val;
	Result->Val = Std$Integer$new_small(List->Length);
	return SUCCESS;
};

static Std$Object_t *LeftBracket, *RightBracket, *CommaSpace, *LeftRightBracket, *ValueString;

SYMBOL($AT, "@");

METHOD("@", TYP, T, VAL, Std$String$T) {
	_node *Node = ((_list *)Args[0].Val)->Head;
	if (Node) {
		Std$Object_t *Final;
		Std$Function_result Buffer;
		if (Std$Function$call($AT, 2, &Buffer, Node->Value, 0, Std$String$T, 0) < FAILURE) {
			Std$Function$call(Std$String$Add, 2, &Buffer, LeftBracket, 0, Buffer.Val, 0);
		} else {
			Std$Function$call(Std$String$Add, 2, &Buffer, LeftBracket, 0, ValueString, 0);
		};
		Final = Buffer.Val;
		while (Node = Node->Next) {
			Std$Function$call(Std$String$Add, 2, &Buffer, Final, 0, CommaSpace, 0);
			Final = Buffer.Val;
			if (Std$Function$call($AT, 2, &Buffer, Node->Value, 0, Std$String$T, 0) < FAILURE) {
				Std$Function$call(Std$String$Add, 2, &Buffer, Final, 0, Buffer.Val, 0);
			} else {
				Std$Function$call(Std$String$Add, 2, &Buffer, Final, 0, ValueString, 0);
			};
			Final = Buffer.Val;
		};
		Std$Function$call(Std$String$Add, 2, &Buffer, Final, 0, RightBracket, 0);
		Final = Buffer.Val;
		Result->Val = Final;
		return SUCCESS;
	} else {
		Result->Val = LeftRightBracket;
		return SUCCESS;
	};
};

SYMBOL($EQUAL, "=");

METHOD("in", ANY, TYP, T) {
	for (_node *Node = ((_list *)Args[1].Val)->Head; Node; Node = Node->Next) {
		long Status = Std$Function$call($EQUAL, 2, Result, Args[0].Val, 0, Node->Value, 0);
		if (Status != FAILURE) return Status;
	};
	return FAILURE;
};

typedef struct find_generator {
	Std$Function_cstate State;
	_node *Current;
	long Index;
	Std$Object_t *Value;
} find_generator;

typedef struct find_resume_data {
	find_generator *Generator;
	Std$Function_argument Result;
} find_resume_data;

static long resume_find_list(find_resume_data *Data) {
	find_generator *Generator = Data->Generator;
	_node *Node = Generator->Current;
	int Index = Generator->Index;
	for (_node *Node = Generator->Current; Node; Node = Node->Next) {
		++Index;
		Std$Function_result Result0;
		switch (Std$Function$call($EQUAL, 2, &Result0, Generator->Value, 0, Node->Value, 0)) {
		case SUSPEND: case SUCCESS: {
			Data->Result.Val = Std$Integer$new_small(Index);
			if (Node->Next) {
				Generator->Current = Node->Next;
				Generator->Index = Index;
				return SUSPEND;
			} else {
				return SUCCESS;
			};
		};
		case FAILURE: continue;
		case MESSAGE: {
			Data->Result.Val = Result0.Val;
			return MESSAGE;
		};
		};
	};
	return FAILURE;
};

METHOD("find", TYP, T, ANY) {
	int Index = 0;
	for (_node *Node = ((_list *)Args[0].Val)->Head; Node; Node = Node->Next) {
		++Index;
		Std$Function_result Result0;
		switch (Std$Function$call($EQUAL, 2, &Result0, Args[1].Val, 0, Node->Value, 0)) {
		case SUSPEND: case SUCCESS: {
			Result->Val = Std$Integer$new_small(Index);
			if (Node->Next) {
				find_generator *Generator = new(find_generator);
				Generator->State.Run = Std$Function$resume_c;
				Generator->State.Invoke = resume_find_list;
				Generator->Current = Node->Next;
				Generator->Index = Index;
				Generator->Value = Args[1].Val;
				Result->State = Generator;
				return SUSPEND;
			} else {
				return SUCCESS;
			};
		};
		case FAILURE: continue;
		case MESSAGE: {
			Result->Val = Result0.Val;
			return MESSAGE;
		};
		};
	};
	return FAILURE;
};

METHOD("remove", TYP, T, ANY) {
	for (_node *Node = ((_list *)Args[0].Val)->Head; Node; Node = Node->Next) {
		Std$Function_result Result0;
		switch (Std$Function$call($EQUAL, 2, &Result0, Args[1].Val, 0, Node->Value, 0)) {
		case SUSPEND: case SUCCESS: {
			Result->Val = delete_node(Args[0].Val, Node);
			return SUCCESS;
		};
		case FAILURE: continue;
		case MESSAGE: {
			Result->Val = Result0.Val;
			return MESSAGE;
		};
		};
	};
	return FAILURE;
};

SYMBOL($to, "to");

METHOD("keys", TYP, T) {
	Std$Integer_smallt To = {Std$Integer$SmallT, ((_list *)Args[0].Val)->Length};
	return Std$Function$call(Std$Integer$ToSmallSmall, 2, Result, Std$Integer$new_small(1), 0, &To, 0);
};

typedef struct list_generator {
	Std$Function_cstate State;
	_node *Current;
} list_generator;

typedef struct list_resume_data {
	list_generator *Generator;
	Std$Function_argument Result;
} list_resume_data;

static long resume_values_list(list_resume_data *Data) {
	_node *Node = Data->Generator->Current->Next;
	if (Node != 0) {
		Data->Generator->Current = Node;
		Data->Result.Val = *(Data->Result.Ref = &Node->Value);
		return SUSPEND;
	} else {
		return FAILURE;
	};
};

METHOD("values", TYP, T) {
	_node *Node = ((_list *)Args[0].Val)->Head;
	if (Node != 0) {
		list_generator *Generator = new(list_generator);
		Generator->State.Run = Std$Function$resume_c;
		Generator->State.Invoke = resume_values_list;
		Generator->Current = Node;
		Result->Val = *(Result->Ref = &Node->Value);
		Result->State = Generator;
		return SUSPEND;
	} else {
		return FAILURE;
	};
};

typedef struct list_loop_generator {
	Std$Function_cstate State;
	unsigned long NoOfRefs;
	_node *Current;
	Std$Object_t **Refs[];
} list_loop_generator;

typedef struct list_loop_resume_data {
	list_loop_generator *Generator;
	Std$Function_argument Result;
} list_loop_resume_data;

static long resume_loop_list(list_loop_resume_data *Data) {
	list_loop_generator *Gen = Data->Generator;
	_node *Current = Gen->Current;
	for (unsigned long I = 0; I < Gen->NoOfRefs; ++I) {
		if (Current == 0) return FAILURE;
		Gen->Refs[I][0] = Current->Value;
		Current = Current->Next;
	};
	if (Current == 0) return SUCCESS;
	Gen->Current = Current;
	return SUSPEND;
};

METHOD("loop", TYP, T) {
	_node *Current = ((_list *)Args[0].Val)->Head;
	for (unsigned long I = 0; I < Count - 1; ++I) {
		if (Current == 0) return FAILURE;
		Args[I + 1].Ref[0] = Current->Value;
		Current = Current->Next;
	};
	if (Current == 0) return SUCCESS;
	list_loop_generator *Generator = (list_loop_generator *)Riva$Memory$alloc(sizeof(list_loop_generator) + (Count - 1) * sizeof(Std$Object_t **));
	Generator->State.Run = Std$Function$resume_c;
	Generator->State.Invoke = resume_loop_list;
	Generator->Current = Current;
	Generator->NoOfRefs = Count - 1;
	for (unsigned long I = 0; I < Generator->NoOfRefs; ++I) {
		Generator->Refs[I] = Args[I + 1].Ref;
	};
	Result->Arg = Args[0];
	Result->State = Generator;
	return SUSPEND;
};

METHOD("apply", TYP, T, TYP, Std$Function$T) {
	_list *List = Args[0].Val;
	int Count0 = List->Length;
	Std$Function_argument *Args0 = Riva$Memory$alloc(Count0 * sizeof(Std$Function_argument));
	_node *Node = List->Head;
	Std$Function_argument *Cur = Args0;
	for (;Node; Node = Node->Next, ++Cur) Cur->Val = *(Cur->Ref = &Node->Value);
	return Std$Function$invoke(Args[1].Val, Count0, Result, Args0);
};

METHOD("apply", TYP, Std$Function$T, TYP, T) {
	_list *List = Args[1].Val;
	int Count0 = List->Length;
	Std$Function_argument *Args0 = Riva$Memory$alloc(Count0 * sizeof(Std$Function_argument));
	_node *Node = List->Head;
	Std$Function_argument* Cur = Args0;
	for (;Node; Node = Node->Next, ++Cur) Cur->Val = *(Cur->Ref = &Node->Value);
	return Std$Function$invoke(Args[0].Val, Count0, Result, Args0);
};

METHOD("map", TYP, T, TYP, Std$Function$T) {
	Std$Object_t *Function = Args[1].Val;
	_list *In = Args[0].Val;
	_list *Out = new(_list);
	Out->Type = T;
	_node *Node = 0;
	long Length = 0;
	for (_node *Arg = In->Head; Arg; Arg = Arg->Next) {
		Std$Function_result Result;
		if (Std$Function$invoke(Function, 1, &Result, &Arg->Value) <= SUCCESS) {
			if (Node) {
				_node *Prev = Node;
				Node = new(_node);
				(Node->Prev = Prev)->Next = Node;
			} else {
				Node = new(_node);
				Out->Head = Out->Cache = Node;
				Out->Index = 1;
			};
			++Length;
			Node->Value = Result.Val;
		};
	};
	Out->Tail = Node;
	Out->Length = Length;
	Out->Lower = Out->Upper = 0;
	Out->Access = 4;
	Result->Val = Out;
	return SUCCESS;
};

METHOD("map", TYP, Std$Function$T, TYP, T) {
	Std$Object_t *Function = Args[0].Val;
	_list *Out = new(_list);
	Out->Type = T;
	_node *Node = 0;
	long Length = 0;
	long Count0 = Count - 1;
	Std$Function_argument *Args0 = Riva$Memory$alloc(Count0 * sizeof(Std$Function_argument));
	_node **Nodes = Riva$Memory$alloc(Count0 * sizeof(_node *));
	for (int I = 0; I < Count0; ++I) {
		if ((Nodes[I] = ((_list *)Args[I + 1].Val)->Head) == 0) goto finished;
		Args0[I].Val = *(Args0[I].Ref = &Nodes[I]->Value);
	};
	for (;;) {
		Std$Function_result Result;
		if (Std$Function$invoke(Function, Count0, &Result, Args0) <= SUCCESS) {
			if (Node) {
				_node *Prev = Node;
				Node = new(_node);
				(Node->Prev = Prev)->Next = Node;
			} else {
				Node = new(_node);
				Out->Head = Out->Cache = Node;
				Out->Index = 1;
			};
			++Length;
			Node->Value = Result.Val;
		};
		for (int I = 0; I < Count0; ++I) {
			if ((Nodes[I] = Nodes[I]->Next) == 0) goto finished;
			Args0[I].Val = *(Args0[I].Ref = &Nodes[I]->Value);
		};
	};
finished:
	Out->Tail = Node;
	Out->Length = Length;
	Out->Lower = Out->Upper = 0;
	Out->Access = 4;
	Result->Val = Out;
	return SUCCESS;
};

SYMBOL($QUERY, "?");

static Std$Object_t *sort_list(Std$Object_t **First, Std$Object_t **Last) {
	if (First == Last) return 0;
	Std$Object_t **A = First;
	Std$Object_t **B = Last;
	Std$Object_t *S = *A;
	Std$Object_t *T = *B;

	while (A != B) {
		Std$Function_result Result;
		switch (Std$Function$call($QUERY, 2, &Result, S, 0, T, 0)) {
		case SUSPEND: case SUCCESS: {
			if (((Std$Integer_smallt *)Result.Val)->Value < 0) {
				*B = T; --B; T = *B;
			} else {
				*A = T; ++A; T = *A;
			};
			break;
		};
		case FAILURE: {
			return Std$String$new("Comparison failed in list:sort");
		};
		case MESSAGE: {
			return Result.Val;
		};
		};
	};
	*A = S;
	if (A != First) {
		Std$Object_t *Error = sort_list(First, A - 1);
		if (Error) return Error;
	};
	if (B != Last) {
		Std$Object_t *Error = sort_list(B + 1, Last);
		if (Error) return Error;
	};
	return 0;
};

METHOD("sort", TYP, T) {
	_list *List = Args[0].Val;
	Result->Arg = Args[0];
	if (List->Length == 0) return SUCCESS;
	if (List->Length < 1024) {
		Std$Object_t *First[List->Length];
		Std$Object_t **Last = First - 1;
		for (_node *Node = List->Head; Node; Node = Node->Next) *(++Last) = Node->Value;
		Std$Object_t *Error = sort_list(First, Last);
		if (Error) {
			Result->Val = Error;
			return MESSAGE;
		};
		Last = First - 1;
		for (_node *Node = List->Head; Node; Node = Node->Next) Node->Value = *(++Last);
		return SUCCESS;
	} else {
		Std$Object_t **First = Riva$Memory$alloc(List->Length * sizeof(Std$Object_t *));;
		Std$Object_t **Last = First - 1;
		for (_node *Node = List->Head; Node; Node = Node->Next) *(++Last) = Node->Value;
		Std$Object_t *Error = sort_list(First, Last);
		if (Error) {
			Result->Val = Error;
			return MESSAGE;
		};
		Last = First - 1;
		for (_node *Node = List->Head; Node; Node = Node->Next) Node->Value = *(++Last);
		return SUCCESS;
	};
};

METHOD("collect", TYP, Std$Function$T) {
	Std$Function_result Result0;
	_list *List = new(_list);
	List->Type = T;
	List->Lower = List->Upper = 0;
	List->Access = 4;
	Result->Val = List;
	Std$Object_t *Function = Args[0].Val;
	_node *Node, *Prev;
	unsigned long NoOfElements;
	switch (Std$Function$invoke(Function, Count - 1, &Result0, Args + 1)) {
	case SUSPEND:
		Node = new(_node);
		NoOfElements = 1;
		Node->Value = Result0.Val;
		List->Head = Node;
		List->Cache = Node;
		List->Index = 1;
		for (;;) {
			switch (Std$Function$resume(&Result0)) {
			case SUSPEND:
				++NoOfElements;
				Prev = Node;
				Node = new(_node);
				(Node->Prev = Prev)->Next = Node;
				Node->Value = Result0.Val;
				break;
			case MESSAGE:
				Result->Val = Result0.Val;
				return MESSAGE;
			case SUCCESS:
				++NoOfElements;
				Prev = Node;
				Node = new(_node);
				(Node->Prev = Prev)->Next = Node;
				Node->Value = Result0.Val;
			case FAILURE:
				List->Tail = Node;
				List->Length = NoOfElements;
				return SUCCESS;
			};
		};
	case MESSAGE:
		Result->Val = Result0.Val;
		return MESSAGE;
	case SUCCESS:
		Node = new(_node);
		Node->Value = Result0.Val;
		List->Head = Node;
		List->Cache = Node;
		List->Index = 1;
		List->Tail = Node;
		List->Length = 1;
	case FAILURE:
		return SUCCESS;
	};
};

GLOBAL_FUNCTION(Collect, 1) {
	Std$Function_result Result0;
	_list *List = new(_list);
	List->Type = T;
	List->Lower = List->Upper = 0;
	List->Access = 4;
	Result->Val = List;
	Std$Object_t *Function = Args[0].Val;
	_node *Node, *Prev;
	unsigned long NoOfElements;
	switch (Std$Function$invoke(Function, Count - 1, &Result0, Args + 1)) {
	case SUSPEND:
		Node = new(_node);
		NoOfElements = 1;
		Node->Value = Result0.Val;
		List->Head = Node;
		List->Cache = Node;
		List->Index = 1;
		for (;;) {
			switch (Std$Function$resume(&Result0)) {
			case SUSPEND:
				++NoOfElements;
				Prev = Node;
				Node = new(_node);
				(Node->Prev = Prev)->Next = Node;
				Node->Value = Result0.Val;
				break;
			case MESSAGE:
				Result->Val = Result0.Val;
				return MESSAGE;
			case SUCCESS:
				++NoOfElements;
				Prev = Node;
				Node = new(_node);
				(Node->Prev = Prev)->Next = Node;
				Node->Value = Result0.Val;
			case FAILURE:
				List->Tail = Node;
				List->Length = NoOfElements;
				return SUCCESS;
			};
		};
	case MESSAGE:
		Result->Val = Result0.Val;
		return MESSAGE;
	case SUCCESS:
		Node = new(_node);
		Node->Value = Result0.Val;
		List->Head = Node;
		List->Cache = Node;
		List->Index = 1;
		List->Tail = Node;
		List->Length = 1;
	case FAILURE:
		return SUCCESS;
	};
};

GLOBAL_FUNCTION(CollectN, 2) {
	Std$Function_result Result0;
	unsigned long Max = ((Std$Integer_smallt *)Args[0].Val)->Value;
	_list *List = new(_list);
	List->Type = T;
	List->Lower = List->Upper = 0;
	List->Access = 4;
	Result->Val = List;
	if (Max == 0) return SUCCESS;
	Std$Object_t *Function = Args[1].Val;
	_node *Node, *Prev;
	unsigned long NoOfElements;
	switch (Std$Function$invoke(Function, Count - 2, &Result0, Args + 2)) {
	case SUSPEND:
		Node = new(_node);
		NoOfElements = 1;
		Node->Value = Result0.Val;
		List->Head = Node;
		List->Cache = Node;
		List->Index = 1;
		for (; --Max;) {
			switch (Std$Function$resume(&Result0)) {
			case SUSPEND:
				++NoOfElements;
				Prev = Node;
				Node = new(_node);
				(Node->Prev = Prev)->Next = Node;
				Node->Value = Result0.Val;
				break;
			case MESSAGE:
				Result->Val = Result0.Val;
				return MESSAGE;
			case SUCCESS:
				++NoOfElements;
				Prev = Node;
				Node = new(_node);
				(Node->Prev = Prev)->Next = Node;
				Node->Value = Result0.Val;
			case FAILURE:
				List->Tail = Node;
				List->Length = NoOfElements;
				return SUCCESS;
			};
		};
		List->Tail = Node;
		List->Length = NoOfElements;
		return SUCCESS;
	case MESSAGE:
		Result->Val = Result0.Val;
		return MESSAGE;
	case SUCCESS:
		Node = new(_node);
		Node->Value = Result0.Val;
		List->Head = Node;
		List->Cache = Node;
		List->Index = 1;
		List->Tail = Node;
		List->Length = 1;
	case FAILURE:
		return SUCCESS;
	};
};

void __init (void *Module) {
	LeftBracket = Std$String$new("[");
	RightBracket = Std$String$new("]");
	CommaSpace = Std$String$new(", ");
	LeftRightBracket = Std$String$new("[]");
	ValueString = Std$String$new("<value>");
};
