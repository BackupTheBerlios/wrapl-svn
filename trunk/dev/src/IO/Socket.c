#include <IO/Socket.h>
#include <Util/TypedFunction.h>
#include <Riva/Memory.h>
#include <Std.h>

#include <stdarg.h>
#include <stdio.h>

#ifdef LINUX
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/un.h>
#include <netdb.h>
#include <signal.h>
#else
#endif

TYPE(T, NATIVE($TextReaderT), NATIVE($TextWriterT), NATIVE($ReaderT), NATIVE($WriterT), NATIVE($SeekerT), NATIVE($T), IO$Stream$TextReaderT, IO$Stream$TextWriterT, IO$Stream$WriterT, IO$Stream$SeekerT, IO$Stream$T);
TYPE(LocalT, T, NATIVE($TextReaderT), NATIVE($TextWriterT), NATIVE($ReaderT), NATIVE($WriterT), NATIVE($SeekerT), NATIVE($T), IO$Stream$TextReaderT, IO$Stream$TextWriterT, IO$Stream$WriterT, IO$Stream$SeekerT, IO$Stream$T);
TYPE(InetT, T, NATIVE($TextReaderT), NATIVE($TextWriterT), NATIVE($ReaderT), NATIVE($WriterT), NATIVE($SeekerT), NATIVE($T), IO$Stream$TextReaderT, IO$Stream$TextWriterT, IO$Stream$WriterT, IO$Stream$SeekerT, IO$Stream$T);

static IO$Stream_messaget CreateMessage[] = {{IO$Stream$MessageT, "Create Error"}};
static IO$Stream_messaget BindMessage[] = {{IO$Stream$MessageT, "Bind Error"}};
static IO$Stream_messaget ListenMessage[] = {{IO$Stream$MessageT, "Listen Error"}};
static IO$Stream_messaget AcceptMessage[] = {{IO$Stream$MessageT, "Accept Error"}};
static IO$Stream_messaget ConnectMessage[] = {{IO$Stream$MessageT, "Connect Error"}};
static IO$Stream_messaget HostNotFoundMessage[] = {{IO$Stream$MessageT, "Host Not Found"}};
static IO$Stream_messaget ShutdownMessage[] = {{IO$Stream$MessageT, "Shutdown Error"}};

#ifdef LINUX
Std$Integer_smallt STREAM[] = {{Std$Integer$SmallT, IO$Socket$SOCKSTREAM}};
Std$Integer_smallt DGRAM[] = {{Std$Integer$SmallT, IO$Socket$SOCKDGRAM}};
Std$Integer_smallt RAW[] = {{Std$Integer$SmallT, IO$Socket$SOCKRAW}};

Std$Integer_smallt INET[] = {{Std$Integer$SmallT, IO$Socket$PFINET}};
Std$Integer_smallt LOCAL[] = {{Std$Integer$SmallT, IO$Socket$PFLOCAL}};
#else
#endif

GLOBAL_FUNCTION(New, 2) {
#ifdef LINUX
	int Handle, Style;
	Std$Type_t *Type;
	if (Args[1].Val == STREAM) {
		Style = SOCK_STREAM;
	} else if (Args[1].Val == DGRAM) {
		Style = SOCK_DGRAM;
	} else if (Args[1].Val == RAW) {
		Style = SOCK_RAW;
	} else {
		Result->Val = CreateMessage;
		return MESSAGE;
	};
	if (Args[0].Val == INET) {
		Handle = socket(PF_INET, Style, 0);
		Type = InetT;
	} else if (Args[0].Val == LOCAL) {
		Handle = socket(PF_LOCAL, Style, 0);
		Type = LocalT;
	} else {
		Result->Val = CreateMessage;
		return MESSAGE;
	};
	if (Handle < 0) {
		Result->Val = CreateMessage;
		return MESSAGE;
	};
	Result->Val = NATIVE($new)(Type, Handle);
	return SUCCESS;
#else
#endif
};

#ifdef LINUX
METHOD("sendfd", TYP, LocalT, TYP, IO$Posix$T) {
	int Socket = ((IO$Posix_t *)Args[0].Val)->Handle;
	int Handle = ((IO$Posix_t *)Args[1].Val)->Handle;
	char Payload[4];
	union {
		struct cmsghdr a;
		char b[CMSG_SPACE(sizeof(int))];
	} ControlX;
	struct iovec IOVec[1] = {{
		.iov_base = Payload, .iov_len = 4
	}};
	struct msghdr Message = {
		.msg_name = 0, .msg_namelen = 0,
		.msg_iov = IOVec, .msg_iovlen = 1,
		.msg_control = &ControlX, .msg_controllen = sizeof(ControlX)
	};
	struct cmsghdr *CMPtr = CMSG_FIRSTHDR(&Message);
	CMPtr->cmsg_len = CMSG_LEN(sizeof(int));
	CMPtr->cmsg_level = SOL_SOCKET;
	CMPtr->cmsg_type = SCM_RIGHTS;
	*((int*)CMSG_DATA(CMPtr)) = Handle;
	if (sendmsg(Socket, &Message, 0) < 0) {
		Result->Val = Std$String$new("Error sending fd");
		return MESSAGE;
	} else {
		return SUCCESS;
	};
};

METHOD("recvfd", TYP, LocalT) {
	int Socket = ((IO$Posix_t *)Args[0].Val)->Handle;
	char Payload[4];
	union {
		struct cmsghdr a;
		char b[CMSG_SPACE(sizeof(int))];
	} ControlX;
	struct iovec IOVec[1] = {{
		.iov_base = Payload, .iov_len = 4
	}};
	struct msghdr Message = {
		.msg_name = 0, .msg_namelen = 0,
		.msg_iov = IOVec, .msg_iovlen = 1,
		.msg_control = &ControlX, .msg_controllen = sizeof(ControlX)
	};
	struct cmsghdr *CMPtr = CMSG_FIRSTHDR(&Message);
	CMPtr->cmsg_len = CMSG_LEN(sizeof(int));
	CMPtr->cmsg_level = SOL_SOCKET;
	CMPtr->cmsg_type = SCM_RIGHTS;
	*((int*)CMSG_DATA(CMPtr)) = -1;
	if (recvmsg(Socket, &Message, 0) < 0) {
		Result->Val = Std$String$new("Error receiving fd");
		return MESSAGE;
	} else {
		CMPtr = CMSG_FIRSTHDR(&Message);
		if (CMPtr != 0 &&
			CMPtr->cmsg_len == CMSG_LEN(sizeof(int)) &&
			CMPtr->cmsg_level == SOL_SOCKET &&
			CMPtr->cmsg_type == SCM_RIGHTS
		) {
			Result->Val = IO$Posix$new(T, *((int*)CMSG_DATA(CMPtr)));
			return SUCCESS;
		} else {
			Result->Val = Std$String$new("Error receiving fd (2)");
			return MESSAGE;
		};
	};
};

METHOD("bind", TYP, LocalT, TYP, Std$String$T) {
	struct sockaddr_un Name;
	Name.sun_family = AF_LOCAL;
	Std$String$flatten_to(Args[1].Val, Name.sun_path);
	if (bind(((IO$Posix_t *)Args[0].Val)->Handle, &Name, SUN_LEN(&Name)) < 0) {
		Result->Val = BindMessage;
		return MESSAGE;
	};
	return SUCCESS;
};

METHOD("bind", TYP, InetT, TYP, Std$Integer$SmallT) {
	struct sockaddr_in Name;
	Name.sin_family = AF_INET;
	Name.sin_port = htons(((Std$Integer_smallt *)Args[1].Val)->Value);
	Name.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(((IO$Posix_t *)Args[0].Val)->Handle, &Name, sizeof(Name)) < 0) {
		Result->Val = BindMessage;
		return MESSAGE;
	};
	return SUCCESS;
};

METHOD("listen", TYP, T, TYP, Std$Integer$SmallT) {
	int Socket = ((IO$Posix_t *)Args[0].Val)->Handle;
	if (listen(Socket, ((Std$Integer_smallt *)Args[1].Val)->Value) < 0) {
		Result->Val = ListenMessage;
		return MESSAGE;
	};
	return SUCCESS;
};

METHOD("accept", TYP, T) {
	int Socket = ((IO$Posix_t *)Args[0].Val)->Handle;
	struct sockaddr Addr;
	socklen_t Length = sizeof(Addr);
	int Socket0 = accept(Socket, &Addr, &Length);
	if (Socket0 < 0) {
		Result->Val = AcceptMessage;
		return MESSAGE;
	};
	Result->Val = NATIVE($new)(Args[0].Val->Type, Socket0);
	return SUCCESS;
};

SYMBOL($read, "read");
SYMBOL($write, "write");
SYMBOL($both, "both");

static void socket_close(IO$Posix_t *Stream, int Mode) {
	shutdown(Stream->Handle, Mode);
};

METHOD("close", TYP, T, TYP, Std$Symbol$T) {
    int Socket = ((IO$Posix_t *)Args[0].Val)->Handle;
    int Type;
    if (Args[1].Val == $read) {
        Type = 0;
    } else if (Args[1].Val == $write) {
        Type = 1;
    } else if (Args[1].Val == $both) {
        Type = 2;
    } else {
        Result->Val = Std$String$new("Invalid argument to :shutdown(@IO.Socket.T)");
        return MESSAGE;
    };
    if (shutdown(Socket, Type)) {
        Result->Val = ShutdownMessage;
        return MESSAGE;
    };
    return SUCCESS;
};

METHOD("connect", TYP, LocalT, TYP, Std$String$T) {
	int Socket = ((IO$Posix_t *)Args[0].Val)->Handle;
	struct sockaddr_un Name;
	Name.sun_family = AF_LOCAL;
	Std$String$flatten_to(Args[1].Val, Name.sun_path);
	if (connect(((IO$Posix_t *)Args[0].Val)->Handle, &Name, SUN_LEN(&Name)) < 0) {
		Result->Val = ConnectMessage;
		return MESSAGE;
	};
	return SUCCESS;
};

METHOD("connect", TYP, InetT, TYP, Std$String$T, TYP, Std$Integer$SmallT) {
	char HostName[256];
	Std$String$flatten_to(Args[1].Val, HostName);
	struct hostent *HostInfo = gethostbyname(HostName);
	if (HostInfo == 0) {
		Result->Val = HostNotFoundMessage;
		return MESSAGE;
	};
	int Socket = ((IO$Posix_t *)Args[0].Val)->Handle;
	struct sockaddr_in Name;
	Name.sin_family = AF_INET;
	Name.sin_port = htons(((Std$Integer_smallt *)Args[2].Val)->Value);
	Name.sin_addr = *(struct in_addr *)HostInfo->h_addr;
	if (connect(((IO$Posix_t *)Args[0].Val)->Handle, &Name, sizeof(Name)) < 0) {
		Result->Val = ConnectMessage;
		return MESSAGE;
	};
	return SUCCESS;
};

static void pipe_handler(int Signal) {
};

void __init(void) {
	Util$TypedFunction$set(IO$Stream$close, T, socket_close);
	struct sigaction Action;
	Action.sa_handler = (void *)pipe_handler;
	sigemptyset(&Action.sa_mask);
	Action.sa_flags = SA_RESTART;
	sigaction(SIGPIPE, &Action, NULL);
};

#endif
