#include <Std.h>
#include <IO/Socket.h>
#include <Riva/Memory.h>

#ifdef LINUX

#include <sys/socket.h>
#include <sys/un.h>
#include <sys/wait.h>

typedef struct process_t {
	Std$Type_t *Type;
	pid_t Pid;
	IO$Posix_t *Stream;
	int Child;
} process_t;

TYPE(T);

GLOBAL_FUNCTION(Execute, 2) {
	int Pair[2];
	pid_t Pid;
	if (socketpair(AF_LOCAL, SOCK_STREAM, 0, Pair) == -1) {
		Result->Val = Std$String$new("Error: Pipe creation failed.");
		return MESSAGE;
	};
	Pid = fork();
	if (Pid == -1) {
		close(Pair[0]);
		close(Pair[1]);
		Result->Val = Std$String$new("Error: Fork failed.");
		return MESSAGE;
	};
	if (Pid == 0) {
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
		IO$Posix_t *Stream = new(IO$Posix_t);
		Stream->Type = IO$Socket$T;
		Stream->Handle = Pair[1];
		process_t *Process = new(process_t);
		Process->Type = T;
		Process->Pid = Pid;
		Process->Stream = Stream;
		Process->Child = Pair[0];
		Result->Val = Process;
		return SUCCESS;
	};
};

METHOD("stream", TYP, T) {
	process_t *Process = Args[0].Val;
	Result->Val = Process->Stream;
	return SUCCESS;
};

METHOD("result", TYP, T) {
	process_t *Process = Args[0].Val;
	int Status;
	if (waitpid(Process->Pid, &Status, WNOHANG) == Process->Pid) {
		close(Process->Child);
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
		close(Process->Child);
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

METHOD("stream", TYP, T) {
	process_t *Process = Args[0].Val;
	Result->Val = Process->Stream;
	return SUCCESS;
};

METHOD("result", TYP, T) {
	process_t *Process = Args[0].Val;
};

METHOD("wait", TYP, T) {
	process_t *Process = Args[0].Val;
};

#endif