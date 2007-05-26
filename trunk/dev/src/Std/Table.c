#include <Std.h>
#include <Riva/Memory.h>
//#include <stdlib.h>


SYMBOL($AT, "@");
SYMBOL($COMP, "?");
SYMBOL($HASH, "#");

TYPE(T);
TYPE(NodeType);

/* Maximum AVL height. */
#ifndef AVL_MAX_HEIGHT
#define AVL_MAX_HEIGHT 32
#endif

/* Tree data structure. */
struct avl_table {
	Std$Type_t *avl_type;
	struct avl_node *avl_root;          /* Tree's root. */
	unsigned long avl_count;                   /* Number of items in tree. */
	unsigned long avl_generation;       /* Generation number. */
	Std$Object_t *avl_compare;
	Std$Object_t *avl_hash;
};

/* An AVL tree node. */
struct avl_node {
	Std$Type_t *avl_node_type;
	struct avl_node *avl_link[2];  /* Subtrees. */
	Std$Object_t *avl_key, *avl_value;      /* Key/Value of node. */
	unsigned long avl_hash;            /* Hash value for value. */
	signed char avl_balance;       /* Balance factor. */
};

/* AVL traverser structure. */
struct avl_traverser {
	Std$Function_cstate avl_state;
	struct avl_table *avl_table;        /* Tree being traversed. */
	struct avl_node *avl_node;          /* Current node in tree. */
	struct avl_node *avl_stack[AVL_MAX_HEIGHT];
	                                    /* All the nodes above |avl_node|. */
	unsigned long avl_height;                  /* Number of nodes in |avl_parent|. */
	unsigned long avl_generation;       /* Generation number. */
};

/* Creates and returns a new table
   with comparison function |compare| using parameter |param|
   and memory allocator |allocator|.
   Returns |0| if memory allocation failed. */
struct avl_table *avl_create (Std$Object_t *avl_compare, Std$Object_t *avl_hash) {
	struct avl_table *tree = (struct avl_table *)Riva$Memory$alloc(sizeof *tree);
	tree->avl_type = T;
	tree->avl_root = 0;
	tree->avl_count = 0;
	tree->avl_generation = 0;
	tree->avl_compare = avl_compare;
	tree->avl_hash = avl_hash;
	return tree;
}

static int avl_compare(const struct avl_table *t, Std$Object_t *a, Std$Object_t *b) {
	Std$Function_result Result;
	Std$Function$call(t->avl_compare, 2, &Result, a, 0, b, 0);
	return ((Std$Integer_smallt *)Result.Val)->Value;
};

/* Search |tree| for an item matching |item|, and return it if found.
   Otherwise return |0|. */
static Std$Object_t *avl_find (const struct avl_table *tree, Std$Object_t *key, unsigned long hash) {
	struct avl_node *p;
	for (p = tree->avl_root; p != 0;) {
		int cmp = hash - p->avl_hash;
		if (cmp == 0) cmp = avl_compare(tree, key, p->avl_key);
		if (cmp < 0) p = p->avl_link[0];
		else if (cmp > 0) p = p->avl_link[1];
		else return &p->avl_value;
	}
	return 0;
}

/* Inserts |item| into |tree| and returns a pointer to |item|'s address.
   If a duplicate item is found in the tree,
   returns a pointer to the duplicate without inserting |item|.
   Returns |0| in case of memory allocation failure. */
static Std$Object_t **avl_probe (struct avl_table *tree, Std$Object_t *key, unsigned long hash) {
	struct avl_node *y, *z; /* Top node to update balance factor, and parent. */
	struct avl_node *p, *q; /* Iterator, and parent. */
	struct avl_node *n;     /* Newly inserted node. */
	struct avl_node *w;     /* New root of rebalanced subtree. */
	int dir;                /* Direction to descend. */

	unsigned char da[AVL_MAX_HEIGHT]; /* Cached comparison results. */
	int k = 0;              /* Number of cached results. */

	z = (struct avl_node *) tree;
	y = tree->avl_root;
	dir = 0;
	for (q = z, p = y; p != 0; q = p, p = p->avl_link[dir]) {
		int cmp = hash - p->avl_hash;
		if (cmp == 0) cmp = avl_compare(tree, key, p->avl_key);
		if (cmp == 0) return &p->avl_value;
		if (p->avl_balance != 0) z = q, y = p, k = 0;
		da[k++] = dir = cmp > 0;
	}

	n = q->avl_link[dir] = (struct avl_node *)Riva$Memory$alloc(sizeof *n);
	n->avl_node_type = NodeType;

	tree->avl_count++;
	n->avl_key = key;
	n->avl_hash = hash;
	n->avl_value = 0;
	n->avl_link[0] = n->avl_link[1] = 0;
	n->avl_balance = 0;
	if (y == 0) return &n->avl_value;

	for (p = y, k = 0; p != n; p = p->avl_link[da[k]], k++)
		if (da[k] == 0) p->avl_balance--;
		else p->avl_balance++;

	if (y->avl_balance == -2) {
		struct avl_node *x = y->avl_link[0];
		if (x->avl_balance == -1) {
			w = x;
			y->avl_link[0] = x->avl_link[1];
			x->avl_link[1] = y;
			x->avl_balance = y->avl_balance = 0;
		} else {
			w = x->avl_link[1];
			x->avl_link[1] = w->avl_link[0];
			w->avl_link[0] = x;
			y->avl_link[0] = w->avl_link[1];
			w->avl_link[1] = y;
			if (w->avl_balance == -1) x->avl_balance = 0, y->avl_balance = +1;
			else if (w->avl_balance == 0) x->avl_balance = y->avl_balance = 0;
			else x->avl_balance = -1, y->avl_balance = 0;
			w->avl_balance = 0;
		}
	} else if (y->avl_balance == +2) {
		struct avl_node *x = y->avl_link[1];
		if (x->avl_balance == +1) {
			w = x;
			y->avl_link[1] = x->avl_link[0];
			x->avl_link[0] = y;
			x->avl_balance = y->avl_balance = 0;
		} else {
			w = x->avl_link[0];
			x->avl_link[0] = w->avl_link[1];
			w->avl_link[1] = x;
			y->avl_link[1] = w->avl_link[0];
			w->avl_link[0] = y;
			if (w->avl_balance == +1) x->avl_balance = 0, y->avl_balance = -1;
			else if (w->avl_balance == 0) x->avl_balance = y->avl_balance = 0;
			else x->avl_balance = +1, y->avl_balance = 0;
			w->avl_balance = 0;
		}
	} else return &n->avl_value;
	z->avl_link[y != z->avl_link[0]] = w;

	tree->avl_generation++;
	return &n->avl_value;
}

/* Deletes from |tree| and returns an item matching |item|.
   Returns a null pointer if no matching item found. */
static Std$Object_t *avl_delete (struct avl_table *tree, Std$Object_t *key, long hash) {
	/* Stack of nodes. */
	struct avl_node *pa[AVL_MAX_HEIGHT]; /* Nodes. */
	unsigned char da[AVL_MAX_HEIGHT];    /* |avl_link[]| indexes. */
	int k;                               /* Stack pointer. */

	struct avl_node *p;   /* Traverses tree to find node to delete. */
	int cmp;              /* Result of comparison between |item| and |p|. */
	Std$Object_t *data;

	k = 0;
	p = (struct avl_node *) tree;
	for (cmp = -1; cmp != 0;) {
		int dir = cmp > 0;
		pa[k] = p;
		da[k++] = dir;
		p = p->avl_link[dir];
		if (p == 0) return 0;
		cmp = hash - p->avl_hash;
		if (cmp == 0) cmp = avl_compare(tree, key, p->avl_key);
	}
	data = p->avl_value;

	if (p->avl_link[1] == 0) {
		pa[k - 1]->avl_link[da[k - 1]] = p->avl_link[0];
	} else {
		struct avl_node *r = p->avl_link[1];
		if (r->avl_link[0] == 0) {
			r->avl_link[0] = p->avl_link[0];
			r->avl_balance = p->avl_balance;
			pa[k - 1]->avl_link[da[k - 1]] = r;
			da[k] = 1;
			pa[k++] = r;
		} else {
			struct avl_node *s;
			int j = k++;
			for (;;) {
				da[k] = 0;
				pa[k++] = r;
				s = r->avl_link[0];
				if (s->avl_link[0] == 0) break;
				r = s;
			}

			s->avl_link[0] = p->avl_link[0];
			r->avl_link[0] = s->avl_link[1];
			s->avl_link[1] = p->avl_link[1];
			s->avl_balance = p->avl_balance;

			pa[j - 1]->avl_link[da[j - 1]] = s;
			da[j] = 1;
			pa[j] = s;
		}
	}

	while (--k > 0) {
		struct avl_node *y = pa[k];
		if (da[k] == 0) {
			y->avl_balance++;
			if (y->avl_balance == +1) {
				break;
			} else if (y->avl_balance == +2) {
				struct avl_node *x = y->avl_link[1];
				if (x->avl_balance == -1) {
					struct avl_node *w;
					w = x->avl_link[0];
					x->avl_link[0] = w->avl_link[1];
					w->avl_link[1] = x;
					y->avl_link[1] = w->avl_link[0];
					w->avl_link[0] = y;
					if (w->avl_balance == +1)
						x->avl_balance = 0, y->avl_balance = -1;
					else if (w->avl_balance == 0)
						x->avl_balance = y->avl_balance = 0;
					else /* |w->avl_balance == -1| */
						x->avl_balance = +1, y->avl_balance = 0;
					w->avl_balance = 0;
					pa[k - 1]->avl_link[da[k - 1]] = w;
				} else {
					y->avl_link[1] = x->avl_link[0];
					x->avl_link[0] = y;
					pa[k - 1]->avl_link[da[k - 1]] = x;
					if (x->avl_balance == 0) {
						x->avl_balance = -1;
						y->avl_balance = +1;
						break;
					} else x->avl_balance = y->avl_balance = 0;
				}
			}
		} else {
			y->avl_balance--;
			if (y->avl_balance == -1) {
				break;
			} else if (y->avl_balance == -2) {
				struct avl_node *x = y->avl_link[0];
				if (x->avl_balance == +1) {
					struct avl_node *w;
					w = x->avl_link[1];
					x->avl_link[1] = w->avl_link[0];
					w->avl_link[0] = x;
					y->avl_link[0] = w->avl_link[1];
					w->avl_link[1] = y;
					if (w->avl_balance == -1)
						x->avl_balance = 0, y->avl_balance = +1;
					else if (w->avl_balance == 0)
						x->avl_balance = y->avl_balance = 0;
					else /* |w->avl_balance == +1| */
						x->avl_balance = -1, y->avl_balance = 0;
					w->avl_balance = 0;
					pa[k - 1]->avl_link[da[k - 1]] = w;
				} else {
					y->avl_link[0] = x->avl_link[1];
					x->avl_link[1] = y;
					pa[k - 1]->avl_link[da[k - 1]] = x;
					if (x->avl_balance == 0) {
						x->avl_balance = +1;
						y->avl_balance = -1;
						break;
					} else x->avl_balance = y->avl_balance = 0;
				}
			}
		}
	}

	tree->avl_count--;
	tree->avl_generation++;
	return data;
}

static void trav_refresh (struct avl_traverser *trav) {
	trav->avl_generation = trav->avl_table->avl_generation;
	if (trav->avl_node != 0) {
		struct avl_node *node = trav->avl_node;
		struct avl_node *i;
		trav->avl_height = 0;
		for (i = trav->avl_table->avl_root; i != node; ) {
			int cmp = node->avl_hash - i->avl_hash;
			if (cmp == 0) cmp = avl_compare(trav->avl_table, node->avl_key, i->avl_key);
			trav->avl_stack[trav->avl_height++] = i;
			i = i->avl_link[cmp > 0];
		}
	}
}

/* Initializes |trav| for |tree|
   and selects and returns a pointer to its least-valued item.
   Returns |0| if |tree| contains no nodes. */
static Std$Object_t *avl_t_first (struct avl_traverser *trav, struct avl_table *tree) {
	struct avl_node *x;
	trav->avl_table = tree;
	trav->avl_height = 0;
	trav->avl_generation = tree->avl_generation;
	x = tree->avl_root;
	if (x != 0) while (x->avl_link[0] != 0) {
		trav->avl_stack[trav->avl_height++] = x;
		x = x->avl_link[0];
	}
	trav->avl_node = x;
	return x != 0 ? x : 0;
}

/* Returns the next data item in inorder
   within the tree being traversed with |trav|,
   or if there are no more data items returns |0|. */
static Std$Object_t *avl_t_next (struct avl_traverser *trav) {
	struct avl_node *x;
	if (trav->avl_generation != trav->avl_table->avl_generation) trav_refresh (trav);
	x = trav->avl_node;
	if (x == 0) {
		return avl_t_first (trav, trav->avl_table);
	} else if (x->avl_link[1] != 0) {
		trav->avl_stack[trav->avl_height++] = x;
		x = x->avl_link[1];
		while (x->avl_link[0] != 0) {
			trav->avl_stack[trav->avl_height++] = x;
			x = x->avl_link[0];
		}
	} else {
		struct avl_node *y;
		do {
			if (trav->avl_height == 0) {
				trav->avl_node = 0;
				return 0;
			}
			y = x;
			x = trav->avl_stack[--trav->avl_height];
		} while (y == x->avl_link[1]);
	}
	trav->avl_node = x;
	return x;
}

GLOBAL_FUNCTION(New, 0) {
	if (Count == 0) {
		Result->Val = avl_create($COMP, $HASH);
	} else if (Count == 1) {
		Result->Val = avl_create(Args[0].Val, $HASH);
	} else if (Count == 2) {
		Result->Val = avl_create(Args[0].Val, Args[1].Val);
	};
	return SUCCESS;
};

GLOBAL_FUNCTION(Make, 0) {
	struct avl_table *Table = avl_create($COMP, $HASH);
	int I;
	for (I = 0; I < Count; I+=2) {
		Std$Function_result Result1;
		Std$Object_t **Slot;
		Std$Function$call($HASH, 1, &Result1, Args[I].Val, 0);
		Slot = avl_probe(Table, Args[I].Val, ((Std$Integer_smallt *)Result1.Val)->Value);
		*Slot = Args[I + 1].Val;
	};
	Result->Val = Table;
	return SUCCESS;
};

GLOBAL_FUNCTION(Collect, 1) {
	Std$Function_result Result0;
	Std$Object_t *Function = Args[0].Val;
	struct avl_table *Table = avl_create($COMP, $HASH);
	long Return = Std$Function$invoke(Function, Count - 1, &Result0, Args + 1);
	if (Return == SUCCESS) {
		Std$Function_result Result1;
		Std$Object_t **Slot;
		Std$Function$call($HASH, 1, &Result1, Result0.Val, 0);
		Slot = avl_probe(Table, Result0.Val, ((Std$Integer_smallt *)Result1.Val)->Value);
		*Slot = Std$Object$Nil;
	} else if (Return == SUSPEND) {
		Std$Function_result Result1;
		Std$Object_t **Slot;
		Std$Function$call($HASH, 1, &Result1, Result0.Val, 0);
		Slot = avl_probe(Table, Result0.Val, ((Std$Integer_smallt *)Result1.Val)->Value);
		*Slot = Std$Object$Nil;
		Return = Std$Function$resume(&Result0);
		while (Return == SUSPEND) {
			Std$Function$call($HASH, 1, &Result1, Result0.Val, 0);
			Slot = avl_probe(Table, Result0.Val, ((Std$Integer_smallt *)Result1.Val)->Value);
			*Slot = Std$Object$Nil;
			Return = Std$Function$resume(&Result0);
		};
		if (Return == SUCCESS) {
			Std$Function$call($HASH, 1, &Result1, Result0.Val, 0);
			Slot = avl_probe(Table, Result0.Val, ((Std$Integer_smallt *)Result1.Val)->Value);
			*Slot = Std$Object$Nil;
		} else if (Return == MESSAGE) {
			*Result = Result0;
			return MESSAGE;
		};
	} else if (Return == MESSAGE) {
		*Result = Result0;
		return MESSAGE;
	};
	Result->Val = Table;
	return SUCCESS;
};

METHOD("copy", TYP, T) {
	struct avl_table *Table = avl_create($COMP, $HASH);
	struct avl_traverser Traverser;
	for (struct avl_node *Node = avl_t_first(&Traverser, Args[0].Val); Node; Node = avl_t_next(&Traverser)) {
		avl_probe(Table, Node->avl_key, Node->avl_hash)[0] = Node->avl_value;
	};
	Result->Val = Table;
	return SUCCESS;
};

METHOD("+", TYP, T, TYP, T) {
	struct avl_table *Table = avl_create($COMP, $HASH);
	struct avl_traverser Traverser;
	for (struct avl_node *Node = avl_t_first(&Traverser, Args[0].Val); Node; Node = avl_t_next(&Traverser)) {
		avl_probe(Table, Node->avl_key, Node->avl_hash)[0] = Node->avl_value;
	};
	for (struct avl_node *Node = avl_t_first(&Traverser, Args[1].Val); Node; Node = avl_t_next(&Traverser)) {
		avl_probe(Table, Node->avl_key, Node->avl_hash)[0] = Node->avl_value;
	};
	Result->Val = Table;
	return SUCCESS;
};

METHOD("-", TYP, T, TYP, T) {
	struct avl_table *Table = avl_create($COMP, $HASH);
	struct avl_traverser Traverser;
	for (struct avl_node *Node = avl_t_first(&Traverser, Args[0].Val); Node; Node = avl_t_next(&Traverser)) {
		if (avl_find(Args[1].Val, Node->avl_key, Node->avl_hash) == 0) {
			avl_probe(Table, Node->avl_key, Node->avl_hash)[0] = Node->avl_value;
		};
	};
	Result->Val = Table;
	return SUCCESS;
};

METHOD("*", TYP, T, TYP, T) {
	struct avl_table *Table = avl_create($COMP, $HASH);
	struct avl_traverser Traverser;
	for (struct avl_node *Node = avl_t_first(&Traverser, Args[0].Val); Node; Node = avl_t_next(&Traverser)) {
		if (avl_find(Args[1].Val, Node->avl_key, Node->avl_hash)) {
			avl_probe(Table, Node->avl_key, Node->avl_hash)[0] = Node->avl_value;
		};
	};
	Result->Val = Table;
	return SUCCESS;
};

METHOD("insert", TYP, T, SKP) {
	struct avl_table *Table = (struct avl_table *)Args[0].Val;
	Std$Function_result Result1;
	Std$Object_t **Slot;
	Std$Function$call(Table->avl_hash, 1, &Result1, Args[1].Val, 0);
	Slot = avl_probe(Table, Args[1].Val, ((Std$Integer_smallt *)Result1.Val)->Value);
	*Slot = Count > 2 ? Args[2].Val : Std$Object$Nil;
	Result->Arg = Args[0];
	return SUCCESS;
};

METHOD("delete", TYP, T, SKP) {
	struct avl_table *Table = (struct avl_table *)Args[0].Val;
	Std$Function_result Result1;
	Std$Function$call(Table->avl_hash, 1, &Result1, Args[1].Val, 0);
	if (avl_delete(Table, Args[1].Val, ((Std$Integer_smallt *)Result1.Val)->Value)) {
		Result->Arg = Args[0];
		return SUCCESS;
	} else {
		return FAILURE;
	};
};

METHOD("[]",TYP, T, SKP ) {
	struct avl_table *Table = (struct avl_table *)Args[0].Val;
	Std$Function_result Result1;
	Std$Object_t **Slot;
	Std$Function$call(Table->avl_hash, 1, &Result1, Args[1].Val, 0);
	Slot = avl_find(Table, Args[1].Val, ((Std$Integer_smallt *)Result1.Val)->Value);
	if (Slot != 0) {
		Result->Val = *(Result->Ref = Slot);
		return SUCCESS;
	} else {
		return FAILURE;
	};
};

static Std$Object_t *LeftBrace, *RightBrace, *SpaceIsSpace, *CommaSpace;

METHOD("@", TYP, T, VAL, Std$String$T) {
	Std$Function_result Buffer;
	Std$Object_t *Final = LeftBrace;
	struct avl_traverser Traverser;
	struct avl_node *Node = avl_t_first(&Traverser, Args[0].Val);
	if (Node != 0) {
		Std$Function$call($AT, 2, &Buffer, Node->avl_key, 0, Std$String$T, 0);
		Std$Function$call(Std$Methods$add_string_string, 2, &Buffer, Final, 0, Buffer.Val, 0);
		Final = Buffer.Val;
		if (Node->avl_value != Std$Object$Nil) {
			Std$Function$call(Std$Methods$add_string_string, 2, &Buffer, Final, 0, SpaceIsSpace, 0);
			Final = Buffer.Val;
			Std$Function$call($AT, 2, &Buffer, Node->avl_value, 0, Std$String$T, 0);
			Std$Function$call(Std$Methods$add_string_string, 2, &Buffer, Final, 0, Buffer.Val, 0);
			Final = Buffer.Val;
		};
	};
	for (Node = avl_t_next(&Traverser); Node; Node = avl_t_next(&Traverser)) {
		Std$Function$call(Std$Methods$add_string_string, 2, &Buffer, Final, 0, CommaSpace, 0);
		Final = Buffer.Val;
		Std$Function$call($AT, 2, &Buffer, Node->avl_key, 0, Std$String$T, 0);
		Std$Function$call(Std$Methods$add_string_string, 2, &Buffer, Final, 0, Buffer.Val, 0);
		Final = Buffer.Val;
		if (Node->avl_value != Std$Object$Nil) {
			Std$Function$call(Std$Methods$add_string_string, 2, &Buffer, Final, 0, SpaceIsSpace, 0);
			Final = Buffer.Val;
			Std$Function$call($AT, 2, &Buffer, Node->avl_value, 0, Std$String$T, 0);
			Std$Function$call(Std$Methods$add_string_string, 2, &Buffer, Final, 0, Buffer.Val, 0);
			Final = Buffer.Val;
		};
	};
	Std$Function$call(Std$Methods$add_string_string, 2, &Buffer, Final, 0, RightBrace, 0);
	Final = Buffer.Val;
	Result->Val = Final;
	return SUCCESS;
};

METHOD("key", TYP, NodeType) {
	Result->Val = ((struct avl_node *)Args[0].Val)->avl_key;
	return SUCCESS;
};

METHOD("value", TYP, NodeType) {
	Result->Val = *(Result->Ref = &((struct avl_node *)Args[0].Val)->avl_value);
	return SUCCESS;
};

typedef struct avl_resume_data {
	struct avl_traverser *Traverser;
	Std$Function_argument Result;
} avl_resume_data;

static long resume_items_table(avl_resume_data *Data) {
	Std$Object_t *Node = avl_t_next(Data->Traverser);
	if (Node != 0) {
		Data->Result.Val = Node;
		Data->Result.Ref = 0;
		return SUSPEND;
	} else {
		return FAILURE;
	};
};

METHOD("items", TYP, T) {
	struct avl_traverser *Traverser = (struct avl_traverser *)Riva$Memory$alloc(sizeof(*Traverser));
	Std$Object_t *Node = avl_t_first(Traverser, Args[0].Val);
	Traverser->avl_state.Run = Std$Function$resume_c;
	Traverser->avl_state.Invoke = resume_items_table;
	if (Node != 0) {
		Result->Val = Node;
		Result->State = Traverser;
		return SUSPEND;
	} else {
		return FAILURE;
	};
};

struct avl_traverser2 {
	Std$Function_cstate avl_state;
	struct avl_table *avl_table;        /* Tree being traversed. */
	struct avl_node *avl_node;          /* Current node in tree. */
	struct avl_node *avl_stack[AVL_MAX_HEIGHT];
	                                    /* All the nodes above |avl_node|. */
	unsigned long avl_height;                  /* Number of nodes in |avl_parent|. */
	unsigned long avl_generation;       /* Generation number. */
	Std$Object_t **Key, **Value;
};

typedef struct avl_resume_data2 {
	struct avl_traverser2 *Traverser;
	Std$Function_argument Result;
} avl_resume_data2;

static long resume_loop_table(avl_resume_data2 *Data) {
	struct avl_node *Node = avl_t_next(Data->Traverser);
	if (Node != 0) {
		*(Data->Traverser->Key) = Node->avl_key;
		*(Data->Traverser->Value) = Node->avl_value;
		return SUSPEND;
	} else {
		return FAILURE;
	};
};

METHOD("loop", TYP, T) {
	struct avl_traverser2 *Traverser = (struct avl_traverser2 *)Riva$Memory$alloc(sizeof(*Traverser));
	struct avl_node *Node = avl_t_first(Traverser, Args[0].Val);
	Traverser->avl_state.Run = Std$Function$resume_c;
	Traverser->avl_state.Invoke = resume_loop_table;
	Traverser->Key = Args[1].Ref;
	Traverser->Value = Args[2].Ref;
	if (Node != 0) {
		*(Traverser->Key) = Node->avl_key;
		*(Traverser->Value) = Node->avl_value;
		Result->State = Traverser;
		return SUSPEND;
	} else {
		return FAILURE;
	};
};

static long resume_keys_table(avl_resume_data *Data) {
	struct avl_node *Node = avl_t_next(Data->Traverser);
	if (Node != 0) {
		Data->Result.Val = Node->avl_key;
		Data->Result.Ref = 0;
		return SUSPEND;
	} else {
		return FAILURE;
	};
};

METHOD("keys", TYP, T) {
	struct avl_traverser *Traverser = (struct avl_traverser *)Riva$Memory$alloc(sizeof(*Traverser));
	struct avl_node *Node = avl_t_first(Traverser, Args[0].Val);
	Traverser->avl_state.Run = Std$Function$resume_c;
	Traverser->avl_state.Invoke = resume_keys_table;
	if (Node != 0) {
		Result->Val = Node->avl_key;
		Result->State = Traverser;
		return SUSPEND;
	} else {
		return FAILURE;
	};
};

static long resume_values_table(avl_resume_data *Data) {
	struct avl_node *Node = avl_t_next(Data->Traverser);
	if (Node != 0) {
		Data->Result.Val = *(Data->Result.Ref = &Node->avl_value);
		return SUSPEND;
	} else {
		return FAILURE;
	};
};

METHOD("values", TYP, T) {
	struct avl_traverser *Traverser = (struct avl_traverser *)Riva$Memory$alloc(sizeof(*Traverser));
	struct avl_node *Node = avl_t_first(Traverser, Args[0].Val);
	Traverser->avl_state.Run = Std$Function$resume_c;
	Traverser->avl_state.Invoke = resume_values_table;
	if (Node != 0) {
		Result->Val = *(Result->Ref = &Node->avl_value);
		Result->State = Traverser;
		return SUSPEND;
	} else {
		return FAILURE;
	};
};

METHOD("size", TYP, T) {
	Result->Val = Std$Integer$new_small(((struct avl_table *)Args[0].Val)->avl_count);
	return SUCCESS;
};

METHOD("hash", TYP, T) {
	Result->Val = ((struct avl_table *)Args[0].Val)->avl_hash;
	return SUCCESS;
};

METHOD("compare", TYP, T) {
	Result->Val = ((struct avl_table *)Args[0].Val)->avl_compare;
	return SUCCESS;
};

void __init(void *Module) {
	LeftBrace = Std$String$new("{");
	RightBrace = Std$String$new("}");
	CommaSpace = Std$String$new(", ");
	SpaceIsSpace = Std$String$new(" is ");
};
