#ifndef PARSER_H
#define PARSER_H

#include <Sys/Module.h>

#include "scanner.h"
#include "compiler.h"

extern expr_t *accept_expr(scanner_t *Scanner);
extern module_expr_t *accept_module(scanner_t *Scanner, Sys$Module_t *Module);
extern module_expr_t *parse_module(scanner_t *Scanner, Sys$Module_t *Module);

#endif
