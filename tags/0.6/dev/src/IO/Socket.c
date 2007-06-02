#include <Std.h>
#include <IO/Socket.h>
#include <Riva/Memory.h>

#include <stdarg.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/un.h>
#include <netdb.h>

TYPE(T, IO$Posix$ReaderT, IO$Posix$WriterT, IO$Posix$T, IO$Stream$ReaderT, IO$Stream$WriterT, IO$Stream$T);
TYPE(LocalT, T, IO$Posix$ReaderT, IO$Posix$WriterT, IO$Posix$T, IO$Stream$ReaderT, IO$Stream$WriterT, IO$Stream$T);
TYPE(InetT, T, IO$Posix$ReaderT, IO$Posix$WriterT, IO$Posix$T, IO$Stream$ReaderT, IO$Stream$WriterT, IO$Stream$T);

static IO$Stream_messaget CreateMessage[] = {{IO$Stream$MessageT, "Create Error"}};
static IO$Stream_messaget BindMessage[] = {{IO$Stream$MessageT, "Bind Error"}};
static IO$Stream_messaget ListenMessage[] = {{IO$Stream$MessageT, "Listen Error"}};
static IO$Stream_messaget AcceptMessage[] = {{IO$Stream$MessageT, "Accept Error"}};
static IO$Stream_messaget ConnectMessage[] = {{IO$Stream$MessageT, "Connect Error"}};
static IO$Stream_messaget HostNotFoundMessage[] = {{IO$Stream$MessageT, "Host Not Found"}};

Std$Integer_smallt STREAM[] = {{Std$Integer$SmallT, IO$Socket$SOCKSTREAM}};
Std$Integer_smallt DGRAM[] = {{Std$Integer$SmallT, IO$Socket$SOCKDGRAM}};
Std$Integer_smallt RAW[] = {{Std$Integer$SmallT, IO$Socket$SOCKRAW}};

Std$Integer_smallt INET[] = {{Std$Integer$SmallT, IO$Socket$PFINET}};
Std$Integer_smallt LOCAL[] = {{Std$Integer$SmallT, IO$Socket$PFLOCAL}};

GLOBAL_FUNCTION(New, 2) {
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
	IO$Posix_t *Stream = new(IO$Posix_t);
	Stream->Type = Type;
	Stream->Handle = Handle;
	Result->Val = Stream;
	return SUCCESS;
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
	IO$Posix_t *Socket1 = new(IO$Posix_t);
	Socket1->Type = Args[0].Val->Type;
	Socket1->Handle = Socket0;
	Result->Val = Socket1;
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
