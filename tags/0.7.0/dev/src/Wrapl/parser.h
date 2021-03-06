#ifndef PARSER_H
#define PARSER_H

#include <Sys/Module.h>

#include "scanner.h"
#include "compiler.h"

extern module_expr_t *accept_module(scanner_t *Scanner, Sys$Module_t *Module);
extern command_expr_t *accept_command(scanner_t *Scanner);

#endif
