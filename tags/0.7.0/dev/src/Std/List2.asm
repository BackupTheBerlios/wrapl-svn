%include "Std.inc"

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
extern Std$Type$T
extern Std$Object$Nil

extern T

section .data

;c_data T
;	dd Std$Type$T
;	dd .types
;	dd 0
;	dd 0
;	dd 0
;.types:
;	dd T
;	dd 0

unchecked_func New2
	push sizeof(_list)
	call Riva$Memory$_alloc_small
	pop ecx
	mov [_list(eax).Type], dword T
	test esi, esi
	jz .empty_list
	mov ecx, [argument(edi).Val]
	mov ecx, [small_int(ecx).Value]
	mov [_list(eax).Length], ecx
	mov edx, Std$Object$Nil
	dec esi
	jz .no_default_value
	mov edx, [argument(edi + 8).Val]
.no_default_value:
    mov ebx, eax
    mov edi, edx
    mov esi, ecx
    push byte sizeof(_node)
    call Riva$Memory$_alloc_small
    mov [esp], ebx
    mov [_list(ebx).Head], eax
    mov [_list(ebx).Cache], eax
    inc dword [_list(ebx).Index]
    mov [_node(eax).Value], edi
    dec esi
    jz .finished
    push edx
.loop:
    mov ebx, eax
    mov [esp], dword sizeof(_node)
    call Riva$Memory$_alloc_small
    mov [_node(eax).Prev], ebx
    mov [_node(ebx).Next], eax
    mov [_node(eax).Value], edi
    dec esi
    jnz .loop
    pop edx
.finished:
    pop ecx
    mov [_list(ecx).Tail], eax
    jmp .common
.empty_list:
	xor esi, esi
	mov [_list(eax).Head], esi
	mov [_list(eax).Tail], esi
	mov [_list(eax).Length], esi
	mov ecx, eax
.common:
	mov [_list(ecx).Upper], edx
	mov [_list(ecx).Lower], edx
	mov [_list(ecx).Access], dword 4
	xor edx, edx
	xor eax, eax
	ret


c_func _new
