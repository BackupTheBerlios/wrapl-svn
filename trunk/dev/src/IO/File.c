#include <IO/File.h>
#include <Riva/Memory.h>
#include <Std.h>

#include <stdarg.h>
#include <stdio.h>

TYPE(T, NATIVE($SeekerT), NATIVE($T), IO$Stream$SeekerT, IO$Stream$T);

TYPE(ReaderT, T, NATIVE($ReaderT), NATIVE($SeekerT), NATIVE($T), IO$Stream$ReaderT, IO$Stream$SeekerT, IO$Stream$T);
TYPE(WriterT, T, NATIVE($WriterT), NATIVE($SeekerT), NATIVE($T), IO$Stream$WriterT, IO$Stream$SeekerT, IO$Stream$T);
TYPE(ReaderWriterT, ReaderT, WriterT, T, NATIVE($ReaderT), NATIVE($WriterT), NATIVE($SeekerT), NATIVE($T), IO$Stream$WriterT, IO$Stream$SeekerT, IO$Stream$T);

TYPE(TextReaderT, ReaderT, T, NATIVE($TextReaderT), NATIVE($ReaderT), NATIVE($SeekerT), NATIVE($T), IO$Stream$TextReaderT, IO$Stream$ReaderT, IO$Stream$SeekerT, IO$Stream$T);
TYPE(TextWriterT, WriterT, T, NATIVE($TextWriterT), NATIVE($WriterT), NATIVE($SeekerT), NATIVE($T), IO$Stream$TextWriterT, IO$Stream$WriterT, IO$Stream$SeekerT, IO$Stream$T);
TYPE(TextReaderWriterT, ReaderT, WriterT, T, NATIVE($TextReaderT), NATIVE($TextWriterT), NATIVE($ReaderT), NATIVE($WriterT), NATIVE($SeekerT), NATIVE($T), IO$Stream$TextReaderT, IO$Stream$TextWriterT, IO$Stream$WriterT, IO$Stream$SeekerT, IO$Stream$T);

static IO$Stream_messaget OpenMessage[] = {{IO$Stream$MessageT, "Open Error"}};

Std$Integer_smallt READ[] = {{Std$Integer$SmallT, IO$File$OPENREAD}};
Std$Integer_smallt WRITE[] = {{Std$Integer$SmallT, IO$File$OPENWRITE}};
Std$Integer_smallt APPEND[] = {{Std$Integer$SmallT, IO$File$OPENAPPEND}};
Std$Integer_smallt TEXT[] = {{Std$Integer$SmallT, IO$File$OPENTEXT}};

#ifdef WINDOWS

typedef struct {Std$Type_t *Type; int Access, Create;} openmode_t;

static openmode_t OpenModes[] = {
	{T, 0}, {ReaderT, GENERIC_READ, OPEN_EXISTING},
	{WriterT, GENERIC_WRITE}, {ReaderWriterT, GENERIC_READ | GENERIC_WRITE},
	{T, 0}, {TextReaderT, GENERIC_READ, OPEN_EXISTING},
	{TextWriterT, GENERIC_WRITE}, {TextReaderWriterT, GENERIC_READ | GENERIC_WRITE}
};

#else

typedef struct {Std$Type_t *Type; int Mode;} openmode_t;

static openmode_t OpenModes[] = {
	{T, 0}, {ReaderT, O_RDONLY}, {WriterT, O_WRONLY | O_CREAT}, {ReaderWriterT, O_RDWR | O_CREAT},
	{T, 0}, {TextReaderT, O_RDONLY}, {TextWriterT, O_WRONLY | O_CREAT}, {TextReaderWriterT, O_RDWR | O_CREAT}
};

#endif

GLOBAL_FUNCTION(Open, 2) {
//@filename : Std$String$T
//@mode : Std$Integer$T
//:T
//Opens filename with the correct mode and returns a file object
	Std$String_t *Arg0 = Args[0].Val;
	int Flags = ((Std$Integer_smallt *)Args[1].Val)->Value;
#ifdef WINDOWS
    char *FileName = Std$String$flatten(Args[0].Val);
    openmode_t OpenMode = OpenModes[Flags % 8];
    if (Flags & IO$File$OPENWRITE) {
    	OpenMode.Create = (Flags & IO$File$OPENAPPEND) ? OPEN_ALWAYS : CREATE_ALWAYS;
	};
    HANDLE Handle = CreateFile(FileName, OpenMode.Access, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OpenMode.Create, 0, 0);
    if (Handle == INVALID_HANDLE_VALUE) {
        Result->Val = OpenMessage;
		return MESSAGE;
	};
	if (Flags & IO$File$OPENAPPEND) {
		SetFilePointer(Handle, 0, 0, FILE_END);
	};
	Result->Val = NATIVE($new)(OpenMode.Type, Handle);
	return SUCCESS;
#else
	char FileName[Arg0->Length.Value + 1];
	Std$String$flatten_to(Args[0].Val, FileName);
	openmode_t OpenMode = OpenModes[Flags % 8];
	int Handle = open(FileName, OpenMode.Mode, 0644);
	if (Handle < 0) {
		Result->Val = OpenMessage;
		return MESSAGE;
	};
	if (Flags & IO$File$OPENAPPEND) {
		lseek(Handle, 0, SEEK_END);
	} else if (Flags & IO$File$OPENWRITE) {
		ftruncate(Handle, 0);
	};
	Result->Val = NATIVE($new)(OpenMode.Type, Handle);
	return SUCCESS;
#endif
};

#ifdef WINDOWS
NATIVE(_t) *__file_open(const char *FileName, int Flags) {
    openmode_t OpenMode = OpenModes[Flags % 8];
    HANDLE Handle = CreateFile(FileName, OpenMode.Access, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OpenMode.Create, 0, 0);
    if (Handle == INVALID_HANDLE_VALUE) return 0;
	if (Flags & IO$File$OPENAPPEND) SetFilePointer(Handle, 0, 0, FILE_END);
	return NATIVE($new)(OpenMode.Type, Handle);
};

GLOBAL_FUNCTION(Temp, 0) {
};

#else

NATIVE(_t) *__file_open(const char *FileName, int Flags) {
	int Mode;
	openmode_t OpenMode = OpenModes[Flags % 8];
	int Handle = open(FileName, OpenMode.Mode, 0644);
	if (Handle < 0) return 0;
	if (Flags & IO$File$OPENAPPEND) lseek(Handle, 0, SEEK_END);
	return NATIVE($new)(OpenMode.Type, Handle);
};

GLOBAL_FUNCTION(Temp, 0) {
	int Handle = tmpfile();
	if (Handle) {
		Result->Val = NATIVE($new)(TextReaderWriterT, Handle);;
		return SUCCESS;
	} else {
		Result->Val = OpenMessage;
		return MESSAGE;
	};
};

#endif
