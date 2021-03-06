#include <Std.h>
#include <IO/Socket.h>
#include <Riva/Memory.h>
#include <Riva/Thread.h>
#include <Riva/System.h>

#ifdef LINUX

#include <sys/socket.h>
#include <sys/un.h>
#include <sys/wait.h>

typedef struct process_t {
	Std$Type_t *Type;
	int Handle;
	pid_t Pid;
} process_t;

TYPE(T, IO$Socket$T, NATIVE($TextReaderT), NATIVE($TextWriterT), NATIVE($ReaderT), NATIVE($WriterT), NATIVE($SeekerT), NATIVE($T), IO$Stream$TextReaderT, IO$Stream$TextWriterT, IO$Stream$WriterT, IO$Stream$SeekerT, IO$Stream$T);

static void finalize_process(process_t *Process, void *Data) {
	close(Process->Handle);
};

GLOBAL_FUNCTION(Open, 2) {
	int Pair[2];
	if (socketpair(AF_LOCAL, SOCK_STREAM, 0, Pair) == -1) {
		Result->Val = Std$String$new("Error: Pipe creation failed.");
		return MESSAGE;
	};
	//fcntl(Pair[0], F_SETFL, fcntl(Pair[0], F_GETFL, 0) | O_NONBLOCK);
	//fcntl(Pair[1], F_SETFL, fcntl(Pair[1], F_GETFL, 0) | O_NONBLOCK);
	pid_t Pid = fork();
	if (Pid == -1) {
		close(Pair[0]);
		close(Pair[1]);
		Result->Val = Std$String$new("Error: Fork failed.");
		return MESSAGE;
	};
	if (Pid == 0) {
		close(Pair[1]);
		dup2(Pair[0], STDIN_FILENO);
		dup2(Pair[0], STDOUT_FILENO);
		dup2(Pair[0], STDERR_FILENO);
		Std$List_t *List = Args[1].Val;
		char *Argv[List->Length + 1];
		int I = 0;
		for (Std$List_node *Node = List->Head; Node; Node = Node->Next) Argv[I++] = Std$String$flatten(Node->Value);
		Argv[I] = 0;
		if (execvp(Std$String$flatten(Args[0].Val), Argv) == -1) {
			close(Pair[0]);
			_exit(-1);
		};
	} else {
		close(Pair[0]);
		process_t *Process = new(process_t);
		Process->Type = T;
		Process->Handle = Pair[1];
		Process->Pid = Pid;
		Riva$Memory$register_finalizer(Process, finalize_process, 0, 0, 0);
		Result->Val = Process;
		return SUCCESS;
	};
};

METHOD("result", TYP, T) {
	process_t *Process = Args[0].Val;
	int Status;
	if (waitpid(Process->Pid, &Status, WNOHANG) == Process->Pid) {
		Result->Val = Std$Integer$new_small(Status);
		return SUCCESS;
	} else {
		return FAILURE;
	};
};

METHOD("wait", TYP, T) {
	process_t *Process = Args[0].Val;
	int Status;
	if (waitpid(Process->Pid, &Status, 0) == Process->Pid) {
		Result->Val = Std$Integer$new_small(Status);
		return SUCCESS;
	} else {
		Result->Val = Std$String$new("Error: Wait failed.");
		return MESSAGE;
	};
};

#else

typedef struct process_t {
	Std$Type_t *Type;
	IO$Windows_t *Stream;
} process_t;

TYPE(T);

GLOBAL_FUNCTION(Execute, 2) {
};

METHOD("result", TYP, T) {
	process_t *Process = Args[0].Val;
};

METHOD("wait", TYP, T) {
	process_t *Process = Args[0].Val;
};

#endif
