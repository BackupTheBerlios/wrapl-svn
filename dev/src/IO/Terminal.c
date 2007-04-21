#include <Lang.h>
#include <IO/Terminal.h>
#include <Riva/Memory.h>

#include <unistd.h>
#include <stdio.h>

TYPE(T, IO$Posix$T, IO$Stream$T);

TYPE(ReaderT, T, IO$Posix$TextReaderT, IO$Posix$ReaderT, IO$Posix$T, IO$Stream$TextReaderT, IO$Stream$ReaderT, IO$Stream$T);
TYPE(WriterT, T, IO$Posix$TextWriterT, IO$Posix$WriterT, IO$Posix$T, IO$Stream$TextReaderT, IO$Stream$WriterT,
IO$Stream$T);

IO$Posix_t In[] = {{ReaderT, STDIN_FILENO}};
IO$Posix_t Out[] = {{WriterT, STDOUT_FILENO}};
