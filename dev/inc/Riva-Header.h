#ifndef RIVA_HEADER_H
#define RIVA_HEADER_H

#ifdef	__cplusplus
	#define __EXTERN	extern "C"
#else
	#define __EXTERN	extern
#endif

#define __stringify2(A) #A
#define __stringify(A) __stringify2(A)
#define __concat2(A, B) A ## B
#define __concat(A, B) __concat2(A, B)

#ifdef WINDOWS

#define RIVA_CFUN(TYPE, FUNC, ARGS ...)\
	__EXTERN TYPE __concat(RIVA_MODULE, $ ## FUNC) ( ARGS ) asm(__stringify(__concat(__concat(_, RIVA_MODULE), __concat($_, FUNC))))

#else

#define RIVA_CFUN(TYPE, FUNC, ARGS ...)\
	__EXTERN TYPE __concat(RIVA_MODULE, $ ## FUNC) ( ARGS ) asm(__stringify(__concat(RIVA_MODULE, __concat($_, FUNC))))

#endif

#endif
