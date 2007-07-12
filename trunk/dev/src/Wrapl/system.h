#ifndef SYSTEM_H
#define SYSTEM_H

#include <stdint.h>

#include <Riva/Memory.h>

extern "C" {

extern Std$Type_t WraplT[];

extern void run_state();
extern void invoke_function();
extern void invoke_limit();
extern void backtrack();
extern void send_message();
extern void resend_message();
extern void select_string();
extern void incorrect_type();

extern void detect_cpu_features();

extern bool CmovSupport;

extern Std$Type_t IncorrectTypeMessageT[];
extern Std$Object_t IncorrectTypeMessage[];

};

#endif
