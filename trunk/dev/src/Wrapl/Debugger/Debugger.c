#include <Std.h>
#include <Riva.h>
#include <Wrapl/Loader.h>
#include <glib.h>
#include <gtk/gtk.h>
#include <pthread.h>

typedef struct variable_t {
	struct variable_t *Next;
	const char *Name;
	int Index;
} variable_t;

typedef struct module_t {
	const char *Name;
	int NoOfLines;
	GtkSourceBuffer *Source;
	GtkTreePath *Globals;
	int MaxBreakpoint;
	int *Breakpoints;
} module_t;

typedef struct function_t {
	module_t *Module;
	const char *Name;
	int NoOfScopes;
	int LineNo;
	int *Breakpoints;
	struct scope_t *Main;
} function_t;

typedef struct scope_t {
	function_t *Function;
	int Index;
	variable_t *Head, *Tail;
} scope_t;

typedef struct scope_instance_t {
	scope_t *Scope;
	Std$Object_t **Values;
	int Mapped;
} scope_instance_t;

typedef struct instance_t {
	struct instance_t *Up;
	struct thread_t *Thread;
	function_t *Function;
	int Mapped;
	scope_instance_t Scopes[];
} instance_t;

typedef struct thread_t {
	instance_t *Instance;
	pthread_cond_t Paused;
	pthread_mutex_t Lock;
	GtkTreeStore *Locals;
	int LineNo;
	struct {
		enum {RUNNING, STEP_IN, STEP_OVER, STEP_OUT, RUN_TO, PAUSED} Mode;
		union {
			instance_t *Instance;
			module_t *Module;
		};
		int LineNo;
	} Step;
} thread_t;

typedef struct bstate_t {
	void *Run;
	void *Chain;
	void *Resume;
	Std$Object_t *Val;
	Std$Object_t **Ref;
	void *Code;
	void *Handler;
	function_t *Debug;
	Std$Object_t **Scopes[];
} bstate_t;

static pthread_key_t ThreadKey;

static void thread_exit(thread_t *Thread) {
};

static GtkSourceView *SourceView;
static GtkTreeStore *Globals;
static GtkTreeView *LocalsView;
static GtkListStore *Modules, *Threads;
static GtkTextTagTable *SourceTags;
static GtkTextTag *SourceTag, *PausedTag;
static thread_t *DisplayedThread = 0;
static module_t *DisplayedModule = 0;

enum {COL_LINENO, COL_BREAK, COL_TEXT};

static GdkPixbuf *BreakpointPixbuf;
static GdkPixbuf *NoBreakpointPixbuf;

static inline int is_breakpoint(module_t *Module, int LineNo) {
	if (Module->Breakpoints == 0) return 0;
	if (Module->MaxBreakpoint <= LineNo) return 0;
	return Module->Breakpoints[LineNo - 1];
};

static inline void set_breakpoint(module_t *Module, int LineNo) {
	if (Module->Breakpoints == 0) {
		Module->Breakpoints = Riva$Memory$alloc_atomic(Module->NoOfLines);
		memset(Module->Breakpoints, 0, Module->NoOfLines);
		Module->MaxBreakpoint = Module->NoOfLines;
	} else if (Module->MaxBreakpoint <= LineNo) {
		int *Breakpoints = Riva$Memory$alloc_atomic(Module->NoOfLines);
		memset(Breakpoints, 0, Module->NoOfLines);
		memcpy(Breakpoints, Module->Breakpoints, Module->MaxBreakpoint);
		Module->Breakpoints = Breakpoints;
		Module->MaxBreakpoint = Module->NoOfLines;
	};
	Module->Breakpoints[LineNo - 1] = 1;
	GtkTextIter StartIter, EndIter;
	gtk_text_buffer_get_iter_at_line(Module->Source, &StartIter, LineNo - 1);
	gtk_text_buffer_get_iter_at_line(Module->Source, &EndIter, LineNo - 1);
	gtk_text_iter_forward_char(&EndIter);
	gtk_text_buffer_delete(Module->Source, &StartIter, &EndIter);
	gtk_text_buffer_insert_pixbuf(Module->Source, &StartIter, BreakpointPixbuf);
};

static inline void clear_breakpoint(module_t *Module, int LineNo) {
	Module->Breakpoints[LineNo - 1] = 0;
	GtkTextIter StartIter, EndIter;
	gtk_text_buffer_get_iter_at_line(Module->Source, &StartIter, LineNo - 1);
	gtk_text_buffer_get_iter_at_line(Module->Source, &EndIter, LineNo - 1);
	gtk_text_iter_forward_char(&EndIter);
	gtk_text_buffer_delete(Module->Source, &StartIter, &EndIter);
	gtk_text_buffer_insert_pixbuf(Module->Source, &StartIter, NoBreakpointPixbuf);
};

static void *add_module(const char *Name) {
	//printf("Adding module: %s\n", Name);
	module_t *Module = Riva$Memory$alloc_uncollectable(sizeof(module_t));
	Module->Name = Name;
	Module->Source = gtk_source_buffer_new(SourceTags);
	GtkTreeIter Iter;
	gtk_list_store_append(Modules, &Iter);
	gtk_list_store_set(Modules, &Iter, 0, Name, 1, Module, -1);
	gtk_text_view_set_buffer(SourceView, Module->Source);
	DisplayedModule = Module;
	gtk_tree_store_append(Globals, &Iter, 0);
	gtk_tree_store_set(Globals, &Iter, 0, Module->Name, 1, 0, 2, 0, 3, 0, -1);
	Module->Globals = gtk_tree_model_get_path(Globals, &Iter);
	return Module;
};

static void add_line(module_t *Module, const char *Line) {
	//printf("Adding line to %s: %s\n", Module->Name, Line);
	GtkTextIter Iter;
	gtk_text_buffer_get_end_iter(Module->Source, &Iter);
	gtk_text_buffer_insert_pixbuf(Module->Source, &Iter, NoBreakpointPixbuf);
	gtk_text_buffer_insert_with_tags(Module->Source, &Iter, Line, strlen(Line), SourceTag, 0);
	gtk_text_buffer_insert_with_tags(Module->Source, &Iter, "\n", 1, SourceTag, 0);
	Module->NoOfLines++;
};

static void add_global(module_t *Module, const char *Name, Std$Object_t **Address) {
	//printf("Adding global variable to %s: %s @ %x\n", Module->Name, Name, Address);
	GtkTreeIter Parent, Iter;
	gtk_tree_model_get_iter(Globals, &Parent, Module->Globals);
	gtk_tree_store_append(Globals, &Iter, &Parent);
	gtk_tree_store_set(Globals, &Iter, 0, Name, 1, "NIL", 2, Address, 3, Std$Object$Nil, -1);
};

static void *add_function(module_t *Module, int LineNo) {
	//printf("Adding function to %s @ %d\n", Module->Name, LineNo);
	function_t *Function = Riva$Memory$alloc_uncollectable(sizeof(function_t));
	Function->Module = Module;
	Function->LineNo = LineNo;
	asprintf(&Function->Name, "%s:%d", Module->Name, LineNo);
	return Function;
};

static void add_breakpoints(function_t *Function, int MaxLineNo) {
	//printf("Adding breakpoints to %x: %d\n", Function, MaxLineNo);
	int Count = MaxLineNo - Function->LineNo + 1;
	int *Breakpoints = Riva$Memory$alloc_atomic(Count);
	memset(Breakpoints, 0, Count);
	Function->Breakpoints = Breakpoints;
};

static void *add_scope(function_t *Function, int Index) {
	//printf("Adding scope to %s.%x: %d\n", Function->Module->Name, Function, Index);
	scope_t *Scope = new(scope_t);
	Scope->Function = Function;
	Scope->Index = Index;
	if (Function->NoOfScopes < Index + 1) Function->NoOfScopes = Index + 1;
	if (Index == 0) Function->Main = Scope;
	return Scope;
};

static void add_local(scope_t *Scope, const char *Name, int Index) {
	//printf("Adding local variable to %s.%x.%x: %s @ %d\n", Scope->Function->Module->Name, Scope->Function, Scope, Name, Index);
	variable_t *Variable = new(variable_t);
	Variable->Name = Name;
	Variable->Index = Index;
	if (Scope->Tail) {
		Scope->Tail->Next = Variable;
	} else {
		Scope->Head = Variable;
	};
	Scope->Tail = Variable;
};

static GAsyncQueue *PauseQueue;

static void unpause_thread(thread_t *Thread) {
	pthread_cond_signal(&Thread->Paused);
	pthread_mutex_unlock(&Thread->Lock);
};

static void map_instance(instance_t *Instance, GtkTreeStore *Locals) {
	//printf("Checking Instance %x\n", Instance);
	if (Instance == 0) return;
	if (Instance->Mapped) return;
	map_instance(Instance->Up, Locals);
	GtkTreeIter Iter;
	gtk_tree_store_prepend(Locals, &Iter, 0);
	gtk_tree_store_set(Locals, &Iter, 0, Instance->Function->Name, 4, -1, -1);
	Instance->Mapped = 1;
};

SYMBOL($AS, "@");

static gboolean update_variable(GtkTreeModel *Variables, GtkTreePath *Path, GtkTreeIter *Iter, void *Data) {
	Std$Object_t **Address, *Value;
	const char *Name;
	gtk_tree_model_get(Variables, Iter, 0, &Name, 2, &Address, 3, &Value, -1);
	//printf("Name, Address, Value = %s, %x, %x\n", Name, Address, Address ? Address[0] : 0);
	if (Address) {		
		if (Address[0] != Value) {
			Std$Function_result Result;
			if (Std$Function$call($AS, 2, &Result, Address[0], 0, Std$String$T, 0) < FAILURE) {
				gtk_tree_store_set(Variables, Iter, 1, Std$String$flatten(Result.Val), 3, Address[0], -1);
			} else {
				gtk_tree_store_set(Variables, Iter, 1, "<value>", 3, Address[0], -1);
			};
		};
	};
	return FALSE;
};

static void update_display(void) {
	//printf("Updating display...\n");
	map_instance(DisplayedThread->Instance, DisplayedThread->Locals);
	GtkTreeIter FuncIter, VarIter;
	gtk_tree_model_get_iter_first(DisplayedThread->Locals, &FuncIter);
	for (instance_t *Instance = DisplayedThread->Instance; Instance; Instance = Instance->Up) {
		function_t *Function = Instance->Function;
		for (int I = 0; I < Function->NoOfScopes; ++I) {
			if (Instance->Scopes[I].Mapped == 0) {
				scope_t *Scope = Instance->Scopes[I].Scope;
				if (Scope) {
					Std$Object_t **Values = Instance->Scopes[I].Values;
					for (variable_t *Var = Scope->Head; Var; Var = Var->Next) {
						gtk_tree_store_append(DisplayedThread->Locals, &VarIter, &FuncIter);
						//printf("Index = %d\n", Var->Index);
						gtk_tree_store_set(DisplayedThread->Locals, &VarIter, 0, Var->Name, 1, "NIL", 2, Values + (2 * Var->Index), 3, Std$Object$Nil, 4, Scope->Index, -1);
					};
					Instance->Scopes[I].Mapped = 1;
				};
			};
		};
		gtk_tree_model_iter_next(DisplayedThread->Locals, &FuncIter);
	};
	instance_t *Instance = DisplayedThread->Instance;
	function_t *Function = Instance->Function;
	module_t *Module = Function->Module;
	GtkTextIter LineBeg, LineEnd;
	//printf("Applying tag to line %d\n", DisplayedThread->LineNo);
	//printf("Instance = %x\n", Instance);
	//printf("Function = %x\n", Function);
	gtk_text_buffer_get_iter_at_line(Module->Source, &LineBeg, DisplayedThread->LineNo - 1);
	gtk_text_buffer_get_iter_at_line(Module->Source, &LineEnd, DisplayedThread->LineNo);
	gtk_text_buffer_apply_tag(Module->Source, PausedTag, &LineBeg, &LineEnd);
	gtk_text_view_set_buffer(SourceView, Module->Source);
	DisplayedModule = Module;
	gtk_text_view_scroll_to_iter(SourceView, &LineBeg, 0.0, TRUE, 0.0, 0.5);
	gtk_tree_model_foreach(Globals, update_variable, 0);
	gtk_tree_model_foreach(DisplayedThread->Locals, update_variable, 0);
};

static void display_thread(thread_t *Thread) {	
	//printf("Thread, Thread->Locals = %x, %x\n", Thread, Thread->Locals);
	gtk_tree_view_set_model(LocalsView, Thread->Locals);
	DisplayedThread = Thread;
};

static void break_thread(thread_t *Thread) {
	Thread->Step.Mode = PAUSED;
	pthread_mutex_lock(&Thread->Lock);
	//printf("Hello world!\n\n\n\n");
	//printf("PauseQueue = %x\n", PauseQueue);
	g_async_queue_push(PauseQueue, Thread);
	g_main_context_wakeup(0);
	pthread_cond_wait(&Thread->Paused, &Thread->Lock);
	pthread_mutex_unlock(&Thread->Lock);
	//printf("Thread resumed.\n");
};

static void thread_selection_changed(GtkTreeSelection *Selection, void *User) {
	GtkTreeIter Iter;
	if (gtk_tree_selection_get_selected(Selection, 0, &Iter)) {
		thread_t *Thread;
		gtk_tree_model_get(Threads, &Iter, 2, &Thread, -1);
		if (DisplayedThread != Thread) {
			display_thread(Thread);
			if (Thread->Step.Mode == PAUSED) update_display();
		};
	};
};

static void *enter_function(function_t *Function, bstate_t *BState, Std$Object_t **Values) {
	//printf("Entering function: %s.%x @ %x\n", Function->Module->Name, Function, BState);
	thread_t *Thread = pthread_getspecific(ThreadKey);
	if ((Thread == 0) && (Thread != (thread_t *)0xFFFFFFFF)) {
		//printf("Discovered new thread\n");
		Thread = new(thread_t);
		Thread->Locals = gtk_tree_store_new(5, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_POINTER, G_TYPE_POINTER, G_TYPE_INT);
		Thread->LineNo = Function->LineNo;
		pthread_setspecific(ThreadKey, Thread);
		pthread_cond_init(&Thread->Paused, 0);
		GtkTreeIter Iter;
		gtk_list_store_append(Threads, &Iter);
		char *ID;
		asprintf(&ID, "0x%8x", Thread);
		gtk_list_store_set(Threads, &Iter, 0, GTK_STOCK_MEDIA_PLAY, 1, ID, 2, Thread, -1);
	};
	instance_t *Instance = Riva$Memory$alloc(sizeof(instance_t) + Function->NoOfScopes * sizeof(scope_instance_t));
	Instance->Function = Function;
	Instance->Thread = Thread;
	Instance->Up = Thread->Instance;
	Instance->Scopes[0].Mapped = 0;
	Instance->Scopes[0].Scope = Function->Main;
	Instance->Scopes[0].Values = Values;
	Thread->Instance = Instance;
	//printf("Returning instance %x\n", Instance);
	if (DisplayedThread == 0) break_thread(Thread);
	return Instance;
};

static void exit_function(instance_t *Instance) {
	//printf("Leaving function %x\n", Instance);
	thread_t *Thread = Instance->Thread;
	if (Instance->Mapped) {
		GtkTreeIter Iter;
		gtk_tree_model_get_iter_first(Thread->Locals, &Iter);
		gtk_tree_store_remove(Thread->Locals, &Iter);
	};
	Thread->Instance = Instance->Up;
};

static void enter_scope(instance_t *Instance, scope_t *Scope, Std$Object_t **Values) {
	//printf("Entering scope: %s.%x.%x @ %x\n", Scope->Function->Module->Name, Scope->Function, Scope, Values);
	if (Instance->Scopes[Scope->Index].Mapped) {
		GtkTreeIter FuncIter, VarIter;
		GtkTreeStore *Locals = Instance->Thread->Locals;
		gtk_tree_model_get_iter_first(Locals, &FuncIter);
		if (gtk_tree_model_iter_children(Locals, &VarIter, &FuncIter)) for (;;) {
			int Index;
			gtk_tree_model_get(Locals, &VarIter, 4, &Index, -1);
			//printf("Index = %d\n", Index);
			if (Index == Scope->Index) {
				if (!gtk_tree_store_remove(Locals, &VarIter)) break;
			} else {
				if (!gtk_tree_model_iter_next(Locals, &VarIter)) break;
			};
		};
		Instance->Scopes[Scope->Index].Mapped = 0;
	};
	Instance->Scopes[Scope->Index].Scope = Scope;
	Instance->Scopes[Scope->Index].Values = Values;
};

static void exit_scope(instance_t *Instance) {
	//printf("Exiting scope\n");
};

static void break_line(instance_t *Instance, int LineNo) {
	//printf("Break line: %d in %x\n", LineNo, Instance);
	thread_t *Thread = Instance->Thread;
	//printf("Thread = %x\n", Thread);
	if (Thread == (thread_t *)0xFFFFFFFF) return;
	//printf("Checking for STEP_IN\n");
	if (Thread->Step.Mode == STEP_IN) goto breakpoint;
	//printf("Checking for breakpoint\n");
	function_t *Function = Instance->Function;
	module_t *Module = Function->Module;
	if (is_breakpoint(Module, LineNo)) goto breakpoint;
	//printf("Checking for STEP_OVER\n");
	if ((Thread->Step.Mode == STEP_OVER) && (Instance == Thread->Step.Instance) && (LineNo != Thread->Step.LineNo)) goto breakpoint;
	//printf("Checking for RUN_TO\n");
	if ((Thread->Step.Mode == RUN_TO) && (Module == Thread->Step.Module) && (LineNo == Thread->Step.LineNo)) goto breakpoint;
	//printf("No breakpoint found, returning.\n");
	return;
breakpoint:
	Thread->LineNo = LineNo;
	break_thread(Thread);
	//printf("returning from line breakpoint.\n");
};

GLOBAL_FUNCTION(Enable, 0) {
	static Wrapl$Loader_debugger Debugger[1] = {{
		add_module,
		add_line,
		add_global,
		add_function,
		add_breakpoints,
		add_scope,
		add_local,
		enter_function,
		exit_function,
		enter_scope,
		exit_scope,
		break_line
	}};
	Wrapl$Loader$enable_debug(Debugger);
	return SUCCESS;
};

GLOBAL_FUNCTION(Disable, 0) {
	Wrapl$Loader$disable_debug();
	return SUCCESS;
};

extern char UI_Start[];
extern char UI_End[];

static void module_selection_changed(GtkTreeSelection *Selection, void *User) {
	GtkTreeIter Iter;
	if (gtk_tree_selection_get_selected(Selection, 0, &Iter)) {
		module_t *Module;
		gtk_tree_model_get(Modules, &Iter, 1, &Module, -1);
		gtk_text_view_set_buffer(SourceView, Module->Source);
		DisplayedModule = Module;
	};
};

extern guint8 BreakpointData[];
extern guint8 NoBreakpointData[];

static gboolean pause_queue_prepare(GSource *Source, gint *Timeout) {
	Timeout[0] = -1;
	return g_async_queue_length(PauseQueue) > 0;
};

static gboolean pause_queue_check(GSource *Source) {
	return g_async_queue_length(PauseQueue) > 0;
};

static gboolean pause_queue_dispatch(GSource *Source, GSourceFunc Callback, void *Data) {
	thread_t *Thread = g_async_queue_pop(PauseQueue);
	//printf("Dispatch thread lock signal... %x\n", Thread);
	pthread_mutex_lock(&Thread->Lock);
	GtkTreeIter Iter;
	gtk_tree_model_get_iter_first(Threads, &Iter);
	for (;;) {
		thread_t *Test;
		gtk_tree_model_get(Threads, &Iter, 2, &Test, -1);
		if (Test == Thread) break;
		gtk_tree_model_iter_next(Threads, &Iter);
	};
	gtk_list_store_set(Threads, &Iter, 0, GTK_STOCK_MEDIA_PAUSE, -1);
	if (DisplayedThread == 0) display_thread(Thread);
	if (DisplayedThread == Thread) update_display();
	return TRUE;
};

static void run_clicked(GtkButton *Button, void *User) {
	if (DisplayedThread == 0) return;
	if (DisplayedThread->Step.Mode != PAUSED) return;
	instance_t *Instance = DisplayedThread->Instance;
	function_t *Function = Instance->Function;
	module_t *Module = Function->Module;
	GtkTextIter LineBeg, LineEnd;
	//printf("Removing tag from line %d\n", DisplayedThread->LineNo);
	//printf("Instance = %x\n", Instance);
	gtk_text_buffer_get_iter_at_line(Module->Source, &LineBeg, DisplayedThread->LineNo - 1);
	gtk_text_buffer_get_iter_at_line(Module->Source, &LineEnd, DisplayedThread->LineNo);
	gtk_text_buffer_remove_tag(Module->Source, PausedTag, &LineBeg, &LineEnd);
	DisplayedThread->Step.Mode = RUNNING;
	pthread_cond_signal(&DisplayedThread->Paused);
	//printf("Resuming thread...\n");
	pthread_mutex_unlock(&DisplayedThread->Lock);
};

static void step_into_clicked(GtkButton *Button, void *User) {
	if (DisplayedThread == 0) return;
	if (DisplayedThread->Step.Mode != PAUSED) return;
	instance_t *Instance = DisplayedThread->Instance;
	function_t *Function = Instance->Function;
	module_t *Module = Function->Module;
	GtkTextIter LineBeg, LineEnd;
	//printf("Removing tag from line %d\n", DisplayedThread->LineNo);
	//printf("Instance = %x\n", Instance);
	gtk_text_buffer_get_iter_at_line(Module->Source, &LineBeg, DisplayedThread->LineNo - 1);
	gtk_text_buffer_get_iter_at_line(Module->Source, &LineEnd, DisplayedThread->LineNo);
	gtk_text_buffer_remove_tag(Module->Source, PausedTag, &LineBeg, &LineEnd);
	DisplayedThread->Step.Mode = STEP_IN;
	pthread_cond_signal(&DisplayedThread->Paused);
	//printf("Resuming thread...\n");
	pthread_mutex_unlock(&DisplayedThread->Lock);
};

static void step_over_clicked(GtkButton *Button, void *User) {
	if (DisplayedThread == 0) return;
	if (DisplayedThread->Step.Mode != PAUSED) return;
	instance_t *Instance = DisplayedThread->Instance;
	function_t *Function = Instance->Function;
	module_t *Module = Function->Module;
	GtkTextIter LineBeg, LineEnd;
	//printf("Removing tag from line %d\n", DisplayedThread->LineNo);
	//printf("Instance = %x\n", Instance);
	gtk_text_buffer_get_iter_at_line(Module->Source, &LineBeg, DisplayedThread->LineNo - 1);
	gtk_text_buffer_get_iter_at_line(Module->Source, &LineEnd, DisplayedThread->LineNo);
	gtk_text_buffer_remove_tag(Module->Source, PausedTag, &LineBeg, &LineEnd);
	DisplayedThread->Step.Mode = STEP_OVER;
	DisplayedThread->Step.Instance = Instance;
	DisplayedThread->Step.LineNo = DisplayedThread->LineNo;
	pthread_cond_signal(&DisplayedThread->Paused);
	//printf("Resuming thread...\n");
	pthread_mutex_unlock(&DisplayedThread->Lock);
};

static void pause_clicked(GtkButton *Button, void *User) {
	if (DisplayedThread == 0) return;
	if (DisplayedThread->Step.Mode == PAUSED) return;
	//printf("Pausing thread %x\n", DisplayedThread);
	DisplayedThread->Step.Mode = STEP_IN;
};

static void breakpoint_clicked(GtkButton *Button, void *User) {
	if (DisplayedModule == 0) return;
	GtkTextIter Iter;
	gtk_text_buffer_get_iter_at_mark(
		DisplayedModule->Source, &Iter,
		gtk_text_buffer_get_insert(DisplayedModule->Source)
	);
	int LineNo = gtk_text_iter_get_line(&Iter) + 1;
	if (is_breakpoint(DisplayedModule, LineNo)) {
		clear_breakpoint(DisplayedModule, LineNo);
	} else {
		set_breakpoint(DisplayedModule, LineNo);
	};
};

static void initialize(void) {
	static GSourceFuncs pause_queue_functions = {
		pause_queue_prepare,
		pause_queue_check,
		pause_queue_dispatch,
		0,
	};
	PauseQueue = g_async_queue_new();
	g_source_attach(g_source_new(&pause_queue_functions, sizeof(GSource)), 0);
	GladeXML *Xml = glade_xml_new_from_buffer(UI_Start, UI_End - UI_Start, 0, 0);
	
	SourceTags = gtk_text_tag_table_new();
	SourceTag = gtk_text_tag_new(0);
	g_object_set(SourceTag, "family", "Monospace", 0);
	gtk_text_tag_table_add(SourceTags, SourceTag);
	PausedTag = gtk_text_tag_new(0);
	g_object_set(PausedTag, "background", "yellow", 0);
	gtk_text_tag_table_add(SourceTags, PausedTag);
	SourceView = gtk_source_view_new();
	gtk_container_add(glade_xml_get_widget(Xml, "SourceScrolledWindow"), SourceView);
	gtk_text_view_set_editable(SourceView, FALSE);
	gtk_source_view_set_show_line_numbers(SourceView, TRUE);
	
	BreakpointPixbuf = gdk_pixbuf_new_from_inline(-1, BreakpointData, FALSE, 0);
	NoBreakpointPixbuf = gdk_pixbuf_new_from_inline(-1, NoBreakpointData, FALSE, 0);

	GtkCellRenderer *Renderer;
	GtkTreeViewColumn *Column;
	Modules = gtk_list_store_new(2, G_TYPE_STRING, G_TYPE_POINTER);
	GtkWidget *ModulesView = glade_xml_get_widget(Xml, "ModulesView");
	Renderer = gtk_cell_renderer_text_new();
	Column = gtk_tree_view_column_new_with_attributes("File", Renderer, "text", 0, 0);
	gtk_tree_view_append_column(ModulesView, Column);
	gtk_tree_view_set_model(ModulesView, Modules);
	GtkTreeSelection *Selection = gtk_tree_view_get_selection(ModulesView);
	g_signal_connect(Selection, "changed", module_selection_changed, 0);

	GtkWidget *ThreadsView = glade_xml_get_widget(Xml, "ThreadsView");
	Threads = gtk_list_store_new(3, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_POINTER);
	Renderer = gtk_cell_renderer_pixbuf_new();
	Column = gtk_tree_view_column_new_with_attributes("State", Renderer, "stock-id", 0, 0);
	gtk_tree_view_append_column(ThreadsView, Column);
	Renderer = gtk_cell_renderer_text_new();
	Column = gtk_tree_view_column_new_with_attributes("Thread", Renderer, "text", 1, 0);
	gtk_tree_view_append_column(ThreadsView, Column);
	gtk_tree_view_set_model(ThreadsView, Threads);
	Selection = gtk_tree_view_get_selection(ThreadsView);
	g_signal_connect(Selection, "changed", thread_selection_changed, 0);

	GtkWidget *GlobalsView = glade_xml_get_widget(Xml, "GlobalsView");
	Globals = gtk_tree_store_new(4, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_POINTER, G_TYPE_POINTER);
	Renderer = gtk_cell_renderer_text_new();
	Column = gtk_tree_view_column_new_with_attributes("Name", Renderer, "text", 0, 0);
	gtk_tree_view_append_column(GlobalsView, Column);
	Renderer = gtk_cell_renderer_text_new();
	Column = gtk_tree_view_column_new_with_attributes("Value", Renderer, "text", 1, 0);
	gtk_tree_view_append_column(GlobalsView, Column);
	gtk_tree_view_set_model(GlobalsView, Globals);

	LocalsView = glade_xml_get_widget(Xml, "LocalsView");
	Renderer = gtk_cell_renderer_text_new();
	Column = gtk_tree_view_column_new_with_attributes("Name", Renderer, "text", 0, 0);
	gtk_tree_view_append_column(LocalsView, Column);
	Renderer = gtk_cell_renderer_text_new();
	Column = gtk_tree_view_column_new_with_attributes("Value", Renderer, "text", 1, 0);
	gtk_tree_view_append_column(LocalsView, Column);

	g_signal_connect(glade_xml_get_widget(Xml, "StepIntoButton"), "clicked", step_into_clicked, 0);
	g_signal_connect(glade_xml_get_widget(Xml, "StepOverButton"), "clicked", step_over_clicked, 0);
	g_signal_connect(glade_xml_get_widget(Xml, "RunButton"), "clicked", run_clicked, 0);
	g_signal_connect(glade_xml_get_widget(Xml, "PauseButton"), "clicked", pause_clicked, 0);
	g_signal_connect(glade_xml_get_widget(Xml, "BreakpointButton"), "clicked", breakpoint_clicked, 0);

	gtk_widget_show_all(glade_xml_get_widget(Xml, "MainWindow"));
};

static void debugger_thread(void) {
	pthread_setspecific(&ThreadKey, (void *)0xFFFFFFFF);
	gtk_main();
};

void __init(void) {
	static Wrapl$Loader_debugger Debugger[1] = {{
		add_module,
		add_line,
		add_global,
		add_function,
		add_breakpoints,
		add_scope,
		add_local,
		enter_function,
		exit_function,
		enter_scope,
		exit_scope,
		break_line
	}};

	int Argc = 0;
	char **Argv = 0;
	if (!g_thread_supported()) g_thread_init(0);
	gtk_init(&Argc, &Argv);
	pthread_key_create(&ThreadKey, thread_exit);
	pthread_t Handle;
	initialize();
	pthread_create(&Handle, 0, debugger_thread, 0);	
	Wrapl$Loader$enable_debug(Debugger);
};
