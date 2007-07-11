%ifndef WRAPL_INC
%define WRAPL_INC

%macro struct 1.nolist
	%define %1(X) X + %1
	struc %1
%endmacro

%macro struct 2.nolist
	%define %1(X) X + %1
	struc %1
		resb sizeof(%2)
%endmacro

%macro endstruct 0.nolist
	.__size__:
	endstruc
%endmacro

%define sizeof(T) T %+ .__size__

extern Std$Function$AsmT
extern Std$Function$CheckedAsmT

%macro unchecked_func 1
	global %1
section .d %+ %s, class=data,use32
align 8
%1:
	dd Std$Function$AsmT
	dd %%here
section .t %+ %s, class=text,use32
align 8
%%here:
%endmacro

%macro func 2
	global %1
	global %1.invoke
section .d %+ %s, class=data,use32
align 8
%1:
	dd Std$Function$CheckedAsmT
.unchecked:
	dd Std$Function$AsmT
	dd .invoke
	dd %2
	dd %%file
	dd __LINE__
%%file:
	db __FILE__, 0
section .t %+ %s, class=text,use32
align 8
.invoke:
%endmacro

%macro c_func 1
	section .u %+ %s, class=text,use32
	align 8
	global %1
	%1:
%endmacro

%macro c_data 1
	section .e %+ %s, class=data,use32
	align 8
	global %1
	%1:
%endmacro

struct value
	.Type:		resd 1
endstruct

struct type, value
	.Types:			resd 1
	.Invoke:		resd 1; invoke(value, args, count)
	.Fields:		resd 1
	.Levels:		resd 1
endstruct

struct argument
	.Val:	resd 1
	.Ref:	resd 1
endstruct

struct result
	.Val:	resd 1
	.Ref:	resd 1
	.State:	resd 1
endstruct

struct state
	.Run:		resd 1
	.Resume:	resd 1
	.Chain:		resd 1
endstruct

struct asm_fun, value
	.Invoke:	resd 1;(fun, count, args)
endstruct

struct checkedasm_fun, value
	.Unchecked:		resb sizeof(asm_fun)
	.Count:			resd 1
	.File:			resd 1
	.Line:			resd 1
endstruct

struct c_fun, value
	.Invoke:	resd 1;(native, count, args, result)
endstruct

struct checkedc_fun, value
	.Invoke:	resd 1
	.Count:		resd 1
	.File:		resd 1
	.Line:		resd 1
endstruct

struct fewargs_message, value
	.Func:		resd 1
	.Count:		resd 1
endstruct

struct address, value
	.Value:	resd 1
endstruct

struct small_int, value
	.Value: resd 1
endstruct

struct big_int, value
	.Value: resd 3
endstruct

struct real, value
	.Value:	resq 1
endstruct

struct array, value
	.Length: resb sizeof(small_int)
	.Values: resd 1
endstruct

struct string, value
	.Length:	resb sizeof(small_int)
	.Count:		resd 1
	.Blocks:
endstruct

struct string_block
	.Length:	resb sizeof(small_int)
	.Chars:		resb sizeof(address)
endstruct

struct symbol, value
	.ValueSize:		resd 1
	.ValueSpace:	resd 1
	.ValueTable:	resd 1
	.TypeSize:		resd 1
	.TypeSpace:		resd 1
	.TypeTable:		resd 1
	.Skip:			resd 1
	.Function:		resd 1
	.Name:			resd 1
endstruct

struct nomethod_message, value
	.Symbol: resd 1
endstruct

struct coexpr, value
	.Fired:		resd 1
	.Resume:	resd 1
	.Function:	resd 1
	.Scope:		resd 1
endstruct

%define ANY 1
%define SKP 1
%define VAL 2
%define TYP 3

%macro symbol 2
section .symbols
%1: db %2, 0
%endmacro

%macro method 2+
section .symbols
%%SYMBOL:
	db %1, 0
section .methods
	dd %%SYMBOL
	dd %2, 0
	dd unchecked_func %+ __LINE__
section .data
align 8
unchecked_func %+ __LINE__: dd Std$Function$AsmT, %%entry
section .methodtext
align 8
%%entry:
%endmacro

%macro _method 3+
section .symbols
%%SYMBOL:
	db %1, 0
section .methods
	dd %%SYMBOL
	dd %3, 0
	dd %2
%endmacro

%endif
