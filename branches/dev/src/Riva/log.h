#ifndef LOG_H
#define LOG_H

extern void log_writes(const char *);
extern void log_writen(const char *, unsigned long);
extern int log_writef(const char *, ...);

extern void log_errors(const char *);
extern void log_errorn(const char *, unsigned long);
extern int log_errorf(const char *, ...);

extern void log_init(void);
extern void log_enable(void);

#endif
