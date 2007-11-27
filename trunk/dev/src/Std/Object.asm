%include "Std.inc"

extern Std$Type$T

c_type T
.invoke: equ 0

c_data Nil
	dd T

unchecked_func New
	mov ecx, [argument(edi).Val]
	add edi, byte sizeof(argument)
	dec esi
	mov eax, [value(ecx).Type]
	jmp [type(eax).Invoke]
