%include "Std.inc"

extern Std$Type$T
extern Riva$Memory$_alloc
extern Riva$Memory$_alloc_small

c_type T
.invoke: equ 0

c_data Nil
	dd T
	dd 0

c_func _alloc
	push byte sizeof(address)
	call Riva$Memory$_alloc_small
	pop ecx
	mov [value(eax).Type], dword T
	ret

c_func _new ;(long  Value)
	push byte sizeof(address)
	call Riva$Memory$_alloc_small
	pop ecx
	mov [value(eax).Type], dword T
	mov ecx, [esp + 4]
	mov [address(eax).Value], ecx
	ret

func New, 1
	mov eax, [argument(edi).Val]
	push dword [small_int(eax).Value]
	call Riva$Memory$_alloc
	mov [esp], eax
	push byte sizeof(address)
	call Riva$Memory$_alloc_small
	pop ecx
	mov [value(eax).Type], dword T
	pop dword [address(eax).Value]
	mov ecx, eax
	xor eax, eax
	xor edx, edx
	ret

func FromVal, 1
	push byte sizeof(address)
	call Riva$Memory$_alloc_small
	pop ecx
	mov [value(eax).Type], dword T
	mov ecx, eax
	mov eax, [argument(edi).Val]
	mov [address(ecx).Value], eax
	xor edx, edx
	xor eax, eax
	ret

func FromRef, 1
	push byte sizeof(address)
	call Riva$Memory$_alloc_small
	pop ecx
	mov [value(eax).Type], dword T
	mov ecx, eax
	mov eax, [argument(edi).Ref]
	mov [address(ecx).Value], eax
	xor edx, edx
	xor eax, eax
	ret

func ToVal, 1
    mov eax, [argument(edi).Val]
    mov ecx, [address(eax).Value]
    xor edx, edx
    xor eax, eax
    ret

func ToRef, 1
    mov eax, [argument(edi).Val]
    mov edx, [address(eax).Value]
    mov ecx, [edx]
    xor eax, eax
    ret
