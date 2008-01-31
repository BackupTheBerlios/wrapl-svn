bits 32
section .symbols noexec
section .methods noexec
section .text

%macro __newsect 3
%ifdef WINDOWS
	section %1%2 class=%3 use32
%else
	[section %1%2 %3]
%endif
%endmacro

%macro textsect 0
%ifdef WINDOWS
	__newsect .t, __LINE__, text
%else
	__newsect .t, __LINE__, exec
%endif
%endmacro

%macro datasect 0
%ifdef WINDOWS
	__newsect .d, __LINE__, data
%else
	__newsect .d, __LINE__, noexec
%endif
%endmacro

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

struct value
	.Type:		resd 1
endstruct

;struct type, value
;	.Types:			resd 1
;	.Invoke:		resd 1; invoke(value, args, count)
;	.Fields:		resd 1
;	.Levels:		resd 1
;endstruct

struct type0, value
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
	.Chain:		resd 1
	.Resume:	resd 1
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

struct rational, value
	.Value: resd 6
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

textsect

struct bstate, state
	.Val:		resd 1
	.Ref:		resd 1
	.Code:		resd 1
	.Handler:	resd 1
	.Data:		resd 1
endstruct

struct closure, value
	.Entry:		resd 1
	.Scopes:
endstruct

struct listnode
	.Value:		resd 1
	.Next:		resd 1
	.Prev:		resd 1
endstruct

struct list, value
	.Head:		resd 1
	.Tail:		resd 1
	.Cache:		resd 1
	.Array:		resd 1
	.Length:	resd 1
	.Index:		resd 1
	.Lower:		resd 1
	.Upper:		resd 1
	.Access:	resd 1
endstruct

extern Std$Type$T
extern Std$Function$T
extern Std$String$T
extern Std$Address$T
extern Riva$Memory$_alloc
extern Std$Integer$SmallT
extern Std$String$T
extern Wrapl$Runtime$_invoke_function
extern Wrapl$Runtime$_run_state
extern Wrapl$Runtime$_resend_message
extern Wrapl$Runtime$_backtrack
extern Wrapl$Runtime$WraplT
extern Std$Object$Nil
extern Wrapl$Runtime$CreateStringBlock
extern Std$List$T
extern Wrapl$Runtime$_incorrect_type
extern Wrapl$Runtime$_select_string
extern Std$Symbol$Is
extern Std$Symbol$In
extern Std$Symbol$Set

