%include "Std.inc"

extern Std$Type$T

c_type T
;the base type of all types
.invoke: equ 0

c_data Nil
	dd T

unchecked_func New
;@object : T
;: T
;creates a new object of the same type as <em>object</em>
	mov ecx, [argument(edi).Val]
	add edi, byte sizeof(argument)
	dec esi
	mov eax, [value(ecx).Type]
	jmp [type(eax).Invoke]
