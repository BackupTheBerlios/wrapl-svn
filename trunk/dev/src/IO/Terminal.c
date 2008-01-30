#include <Std.h>
#include <IO/Terminal.h>
#include <Riva/Memory.h>

TYPE(T, NATIVE($T), IO$Stream$T);

TYPE(ReaderT, T, NATIVE($TextReaderT), NATIVE($ReaderT), NATIVE($T), IO$Stream$TextReaderT, IO$Stream$ReaderT, IO$Stream$T);
TYPE(WriterT, T, NATIVE($TextWriterT), NATIVE($WriterT), NATIVE($T), IO$Stream$TextWriterT, IO$Stream$WriterT, IO$Stream$T);

#ifdef WINDOWS

NATIVE(_t) In[] = {{ReaderT, 0}};
NATIVE(_t) Out[] = {{WriterT, 0}};

void __init(void) {
    In->Handle = GetStdHandle(STD_INPUT_HANDLE);
    Out->Handle = GetStdHandle(STD_OUTPUT_HANDLE);
};

#else

#include <unistd.h>

NATIVE(_t) In[] = {{ReaderT, STDIN_FILENO}};
NATIVE(_t) Out[] = {{WriterT, STDOUT_FILENO}};

#endif
