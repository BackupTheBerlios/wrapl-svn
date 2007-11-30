%include "Std.inc"

extern Riva$Memory$_alloc
extern Riva$Memory$_alloc_atomic
extern Riva$Memory$_alloc_small
extern Std$Type$T

section .data

c_type T
;  base type of all integer types
.invoke: equ 0

c_type SmallT, T
;  integers that fit into a signed machine word.
.invoke:
	mov eax, [small_int(ecx).Value]
	dec eax
	jns .nonnegative
	add eax, esi
	inc eax
	js .failure
.nonnegative:
	cmp eax, esi
	jae .failure
	mov ecx, [argument(edi + 8 * eax).Val]
	mov edx, [argument(edi + 8 * eax).Ref]
	xor eax, eax
	ret
.failure:
	xor eax, eax
	inc eax
	ret

c_type BigT, T
;  arbritrary precision integers.<br/>
;  note: instances of type <em>BigT</em> should never contain values which can fit into a signed machine word.
.invoke:
	; simply fail (we can't have this many arguments anyway)
	xor eax, eax
	inc eax
	ret

c_func _alloc_small
	push byte sizeof(small_int)
	call Riva$Memory$_alloc_small
	pop ecx
	mov [value(eax).Type], dword SmallT
	ret

c_func _alloc_big
	push byte sizeof(big_int)
	call Riva$Memory$_alloc_small
	pop ecx
	mov [value(eax).Type], dword BigT
	ret

extern __gmpz_init_set_str
extern __gmpz_fits_slong_p
extern __gmpz_get_si

c_func _new_string ;(char *Digits)
	sub esp, byte 12
	mov eax, esp
	push byte 10
	push dword [esp + 20]
	push eax
	call __gmpz_init_set_str
	add esp, byte 12
	push esp
	call __gmpz_fits_slong_p
	add esp, byte 4
	test eax, eax
	jnz .convert_to_small
	call _alloc_big
	pop dword [eax + 4]
	pop dword [eax + 8]
	pop dword [eax + 12]
	ret
.convert_to_small
	push esp
	call __gmpz_get_si
	add esp, byte 16
	push eax
	push byte sizeof(small_int)
	call Riva$Memory$_alloc_small
	pop ecx
	mov [value(eax).Type], dword SmallT
	pop dword [small_int(eax).Value]
	ret

c_func _new_small ;(long  Value)
	push byte sizeof(small_int)
	call Riva$Memory$_alloc_small
	pop ecx
	mov [value(eax).Type], dword SmallT
	mov ecx, [esp + 4]
	mov [small_int(eax).Value], ecx
	ret

extern __gmpz_init_set
c_func _new_big ;(mpz_t Value)
	push byte sizeof(big_int)
	call Riva$Memory$_alloc_small
	pop ecx
	mov [value(eax).Type], dword BigT
	push eax
	lea eax, [big_int(eax).Value]
	push dword [esp + 8]
	push eax
	call __gmpz_init_set
	add esp, byte 8
	pop eax
	ret

extern Riva$Memory$_realloc
extern __gmp_set_memory_functions

section .text
_realloc:
	push dword [esp + 12]
	push dword [esp + 8]
	call Riva$Memory$_realloc
	add esp, byte 8
_free:
	ret	

c_func __init
	push dword _free
	push dword _realloc
	push dword Riva$Memory$_alloc
	call __gmp_set_memory_functions
	add esp, byte 12
	ret

struct to_small_small_state, state
	.Current:	resd 1
	.Limit:		resd 1
endstruct

unchecked_func ToSmallSmall
;  generates the values from <em>from</em> to <em>to</em> inclusive
;@from : SmallT
;@to : SmallT
;:SmallT
	mov eax, [argument(edi + 8).Val]
	mov ecx, [argument(edi).Val]
	mov eax, [small_int(eax).Value]
	cmp eax, [small_int(ecx).Value]
	jl .fail
	je .return
.suspend:
	push ecx
	push eax
	push dword [small_int(ecx).Value]
	push byte sizeof(to_small_small_state)
	call Riva$Memory$_alloc
	add esp, byte 4
	pop dword [to_small_small_state(eax).Current]
	pop dword [to_small_small_state(eax).Limit]
	mov dword [state(eax).Run], .resume
	pop ecx
	mov ebx, eax
	or eax, byte -1
	xor edx, edx
	ret
.return:
	xor edx, edx
	xor eax, eax
	ret
.fail:
	xor eax, eax
	inc eax
	ret
.resume:
	mov ecx, [to_small_small_state(eax).Current]
	inc ecx
	cmp ecx, [to_small_small_state(eax).Limit]
	jg .fail
	je .return2
	mov [to_small_small_state(eax).Current], ecx
	push eax
	push ecx
	call _alloc_small
	mov ecx, eax
	pop dword [small_int(ecx).Value]
	xor edx, edx
	or eax, byte -1
	pop ebx
	ret
.return2:
	push ecx
	call _alloc_small
	pop dword [small_int(eax).Value]
	mov ecx, eax
	xor edx, edx
	xor eax, eax
	ret
