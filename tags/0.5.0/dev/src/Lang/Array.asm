%include "Lang.inc"

extern Lang$Type$T
extern Lang$Integer$SmallT
extern Lang$Object$Nil
extern Riva$Memory$_alloc

c_data T
	dd Lang$Type$T
	dd .types
	dd 0
	dd 0
	dd 0
.types:
	dd T
	dd 0

func New, 1
	mov eax, [argument(edi).Val]
	mov eax, [small_int(eax).Value]
	push eax
	lea eax, [4 * eax + 4]
	push eax
	call Riva$Memory$_alloc
	mov [esp], eax
	push byte sizeof(array)
	call Riva$Memory$_alloc
	add esp, byte 4
	pop dword [array(eax).Values]
	pop ecx
	mov [value(eax).Type], dword T
	mov [value(array(eax).Length).Type], dword Lang$Integer$SmallT
	mov [small_int(array(eax).Length).Value], ecx
	push eax
	mov edi, [array(eax).Values]
	mov eax, Lang$Object$Nil
	rep stosd
.empty:
	pop ecx
	xor edx, edx
	xor eax, eax
	ret

c_func _new
	mov eax, [esp + 4]
	push eax
	lea eax, [4 * eax + 4]
	push eax
	call Riva$Memory$_alloc
	mov [esp], eax
	push byte sizeof(array)
	call Riva$Memory$_alloc
	add esp, byte 4
	mov [value(eax).Type], dword T
	mov [value(array(eax).Length).Type], dword Lang$Integer$SmallT
	pop dword [array(eax).Values]
	pop dword [small_int(array(eax).Length).Value]
	ret
