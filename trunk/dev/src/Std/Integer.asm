%include "Std.inc"

extern Riva$Memory$_alloc
extern Riva$Memory$_alloc_atomic
extern Riva$Memory$_alloc_small
extern Std$Type$T

section .data

c_data T
	dd Std$Type$T
	dd .types
	dd 0
	dd 0
	dd 0
.types:
	dd T
	dd 0

c_data SmallT
	dd Std$Type$T
	dd .types
	dd .invoke
	dd 0
	dd 0
.types:
	dd SmallT
	dd T
	dd 0
section .text
align 8
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

c_data BigT
	dd Std$Type$T
	dd .types
	dd .invoke
	dd 0
	dd 0
.types:
	dd BigT
	dd T
	dd 0
section .text
align 8
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

c_func _new_big ;(mpz_t Value)

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
