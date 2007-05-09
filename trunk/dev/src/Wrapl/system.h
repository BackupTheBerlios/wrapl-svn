#ifndef SYSTEM_H
#define SYSTEM_H

#include <stdint.h>

#include <Riva/Memory.h>

extern "C" {

extern void run_state();
extern void invoke_function();
extern void backtrack();
extern void send_message();
extern void resend_message();

};

#endif
