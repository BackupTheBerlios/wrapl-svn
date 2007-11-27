%include "Std.inc"

extern Riva$Memory$_alloc
extern Riva$Memory$_alloc_atomic
extern Riva$Memory$_alloc_small
extern Std$Type$T

section .data

c_type T
.invoke: equ 0

c_func _alloc
	push byte sizeof(real)
	call Riva$Memory$_alloc_small
	pop ecx
	mov [value(eax).Type], dword T
	ret

extern atof
c_func _new_string ;(char *Digits)
	push byte sizeof(real)
	call Riva$Memory$_alloc_small
	pop ecx
	mov [value(eax).Type], dword T
	push eax
	push dword [esp + 8]
	call atof
	add esp, byte 4
	pop eax
	fstp qword [real(eax).Value]
	ret

c_func _new ;(double  Value)
	push byte sizeof(real)
	call Riva$Memory$_alloc_small
	pop ecx
	mov [value(eax).Type], dword T
	fld qword [esp + 4]
	fstp qword [real(eax).Value]
	ret
