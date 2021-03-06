#ifndef STD_H
#define STD_H

#include <Std/Address.h>
#include <Std/Function.h>
#include <Std/Integer.h>
#include <Std/Methods.h>
#include <Std/Object.h>
#include <Std/Rational.h>
#include <Std/Real.h>
#include <Std/String.h>
#include <Std/Symbol.h>
#include <Std/List.h>
#include <Std/Table.h>
#include <Std/Type.h>
#include <Std/Array.h>
#include <Std/Coexpr.h>

#ifdef DOCUMENTING

#define MODULE(ARGS...) MODULE(__LINE__, ARGS)

#else

#define MODULE(path...)

#endif 

#endif
