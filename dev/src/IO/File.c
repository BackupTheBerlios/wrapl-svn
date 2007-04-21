#include <IO/File.h>
#include <Riva/Memory.h>
#include <Lang.h>

#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

TYPE(T, IO$Posix$SeekerT, IO$Posix$T, IO$Stream$SeekerT, IO$Stream$T);

TYPE(ReaderT, T, IO$Posix$ReaderT, IO$Posix$SeekerT, IO$Posix$T, IO$Stream$ReaderT, IO$Stream$SeekerT, IO$Stream$T);
TYPE(WriterT, T, IO$Posix$WriterT, IO$Posix$SeekerT, IO$Posix$T, IO$Stream$WriterT, IO$Stream$SeekerT, IO$Stream$T);
TYPE(ReaderWriterT, ReaderT, WriterT, T, IO$Posix$ReaderT, IO$Posix$WriterT, IO$Posix$SeekerT, IO$Posix$T, IO$Stream$WriterT, IO$Stream$SeekerT, IO$Stream$T);

TYPE(TextReaderT, ReaderT, T, IO$Posix$TextReaderT, IO$Posix$ReaderT, IO$Posix$SeekerT, IO$Posix$T, IO$Stream$TextReaderT, IO$Stream$ReaderT, IO$Stream$SeekerT, IO$Stream$T);
TYPE(TextWriterT, WriterT, T, IO$Posix$TextWriterT, IO$Posix$WriterT, IO$Posix$SeekerT, IO$Posix$T, IO$Stream$TextReaderT, IO$Stream$WriterT, IO$Stream$SeekerT, IO$Stream$T);
TYPE(TextReaderWriterT, ReaderT, WriterT, T, IO$Posix$TextReaderT, IO$Posix$TextWriterT, IO$Posix$ReaderT, IO$Posix$WriterT, IO$Posix$SeekerT, IO$Posix$T, IO$Stream$TextReaderT, IO$Stream$TextWriterT, IO$Stream$WriterT, IO$Stream$SeekerT, IO$Stream$T);

static IO$Stream_messaget OpenMessage[] = {{IO$Stream$MessageT, "Open Error"}};

Lang$Integer_smallt READ[] = {{Lang$Integer$SmallT, IO$File$OPENREAD}};
Lang$Integer_smallt WRITE[] = {{Lang$Integer$SmallT, IO$File$OPENWRITE}};
Lang$Integer_smallt APPEND[] = {{Lang$Integer$SmallT, IO$File$OPENAPPEND}};
Lang$Integer_smallt TEXT[] = {{Lang$Integer$SmallT, IO$File$OPENTEXT}};

typedef struct {Lang$Type_t *Type; int Mode;} openmode_t;

static openmode_t OpenModes[] = {
	{T, 0}, {ReaderT, O_RDONLY}, {WriterT, O_WRONLY | O_CREAT}, {ReaderWriterT, O_RDWR | O_CREAT},
	{T, 0}, {TextReaderT, O_RDONLY}, {TextWriterT, O_WRONLY | O_CREAT}, {TextReaderWriterT, O_RDWR | O_CREAT}
};

GLOBAL_FUNCTION(Open, 2) {
	Lang$String_t *Arg0 = Args[0].Val;
	char FileName[Arg0->Length.Value + 1];
	Lang$String$flatten_to(Args[0].Val, FileName);
	int Mode;
	Lang$Type_t *Type;
	int Flags = ((Lang$Integer_smallt *)Args[1].Val)->Value;
	openmode_t OpenMode = OpenModes[Flags % 8];
	if ((Flags & IO$File$OPENWRITE) && !(Flags & IO$File$OPENAPPEND)) OpenMode.Mode |= O_TRUNC;
	int Handle = open(FileName, OpenMode.Mode, 0644);
	if (Handle < 0) {
		Result->Val = OpenMessage;
		return MESSAGE;
	};
	IO$Posix_t *Stream = new(IO$Posix_t);
	Stream->Type = OpenMode.Type;
	Stream->Handle = Handle;
	Result->Val = Stream;
	return SUCCESS;
};

IO$Posix_t *_open(const char *FileName, int Flags) {
	int Mode;
	Lang$Type_t *Type;
	openmode_t OpenMode = OpenModes[Flags % 8];
	if ((Flags & IO$File$OPENWRITE) && !(Flags & IO$File$OPENAPPEND)) OpenMode.Mode |= O_TRUNC;
	int Handle = open(FileName, OpenMode.Mode, 0644);
	if (Handle < 0) return 0;
	IO$Posix_t *Stream = new(IO$Posix_t);
	Stream->Type = OpenMode.Type;
	Stream->Handle = Handle;
	return Stream;
};
