#ifndef IO_SOCKET_H
#define IO_SOCKET_H

#include <IO/Posix.h>

#define RIVA_MODULE IO$Socket
#include <Riva-Header.h>

extern Lang$Type_t IO$Socket$T[];

//RIVA_CFUN(IO$Posix_t *, new, const char *, int);

#define IO$Socket$SOCKSTREAM	1
#define IO$Socket$SOCKDGRAM		2
#define IO$Socket$SOCKRAW		4

#define IO$Socket$PFINET		8
#define IO$Socket$PFLOCAL		16

#undef RIVA_MODULE

#endif
