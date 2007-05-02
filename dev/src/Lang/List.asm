%include "Lang.inc"

struct _node
	.Next:	resd 1
	.Prev:	resd 1
	.Value:	resd 1
endstruct

struct _list
	.Type:		resd 1
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
s
extern Riva$Memory$_alloc
extern Riva$Memory$_alloc_atomic
extern Riva$Memory$_alloc_small
extern Lang$Type$T

section .data

c_data T
	dd Lang$Type$T
	dd .types
	dd 0
	dd 0
	dd 0
.types:
	dd T
	dd 0

unchecked_func New
	push sizeof(_list)
	call Riva$Memory$_alloc_small
	pop ecx
	mov [_list(eax).Type], dword T
	test esi, esi
	jz .empty_list
	mov ecx, [argument(edi).Val]
	mov ecx, [small_int(ecx).Value]
	mov [_list(eax).Length], ecx
	mov edx, Lang$Object$Nil
	cmp esi, byte 1
	jb .no_default_value
	mov edx, [argument(edi).Val]
.no_default_value:


.empty_list:
	xor edx, edx
	mov [_list(eax).Head], edx
	mov [_list(eax).Tail], edx
	mov [_list(eax).Length], edx
.common:
	mov [_list(eax).Upper], edx
	mov [_list(eax).Lower], edx
	mov [_list(eax).Access], dword 4
	mov ecx, eax
	xor eax, eax
	ret
