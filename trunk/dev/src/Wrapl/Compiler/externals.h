#ifndef EXTERNALS_H
#define EXTERNALS_H

#include "assembler.h"

extern operand_t *external_load(const char *Path, const char *Name);
extern operand_t *external_import(const operand_t *Module, const char *Name);

#endif
