%include "Std.inc"

extern Std$Type$T
extern Riva$Memory$_alloc
extern Riva$Memory$_alloc_atomic
extern Std$Object$Nil

c_data T
	dd Std$Type$T
	dd .types
	dd 0
	dd 0
	dd 0
.types:
	dd T
	dd 0

extern strlen
extern Std$Integer$SmallT
extern Std$Address$T
c_func _new
	push dword [esp + 4]
	call strlen
	mov [esp], eax
	push byte sizeof(string) + 2 * sizeof(string_block)
	call Riva$Memory$_alloc
	add esp, byte 4
	pop edx
	mov ecx, [esp + 4]
	mov [value(eax).Type], dword T
	mov [value(string(eax).Length).Type], dword Std$Integer$SmallT
	mov [small_int(string(eax).Length).Value], edx
	mov [string(eax).Count], dword 1
	mov [value(string_block(string(eax).Blocks).Length).Type], dword Std$Integer$SmallT
	mov [small_int(string_block(string(eax).Blocks).Length).Value], edx
	mov [value(string_block(string(eax).Blocks).Chars).Type], dword Std$Address$T
	mov [address(string_block(string(eax).Blocks).Chars).Value], ecx
	ret

c_func _new_length
	push byte sizeof(string) + 2 * sizeof(string_block)
	call Riva$Memory$_alloc
	add esp, byte 4
	mov edx, [esp + 8]
	mov ecx, [esp + 4]
	mov [value(eax).Type], dword T
	mov [value(string(eax).Length).Type], dword Std$Integer$SmallT
	mov [small_int(string(eax).Length).Value], edx
	mov [string(eax).Count], dword 1
	mov [value(string_block(string(eax).Blocks).Length).Type], dword Std$Integer$SmallT
	mov [small_int(string_block(string(eax).Blocks).Length).Value], edx
	mov [value(string_block(string(eax).Blocks).Chars).Type], dword Std$Address$T
	mov [address(string_block(string(eax).Blocks).Chars).Value], ecx
	ret

c_func _new_char
	push byte 2
	call Riva$Memory$_alloc_atomic
	add esp, byte 4
	mov ecx, [esp + 4]
	mov [eax], cl
	mov [eax + 1], byte 0
	mov [esp + 4], eax
	push byte sizeof(string) + 2 * sizeof(string_block)
	call Riva$Memory$_alloc
	add esp, byte 4
	mov ecx, [esp + 4]
	mov edx, 1
	mov [value(eax).Type], dword T
	mov [value(string(eax).Length).Type], dword Std$Integer$SmallT
	mov [small_int(string(eax).Length).Value], edx
	mov [string(eax).Count], edx
	mov [value(string_block(string(eax).Blocks).Length).Type], dword Std$Integer$SmallT
	mov [small_int(string_block(string(eax).Blocks).Length).Value], edx
	mov [value(string_block(string(eax).Blocks).Chars).Type], dword Std$Address$T
	mov [address(string_block(string(eax).Blocks).Chars).Value], ecx
	ret

func FromAddress, 2
	push byte sizeof(string) + 2 * sizeof(string_block)
	call Riva$Memory$_alloc
	add esp, byte 4
	mov ecx, [argument(edi).Val]
	mov edx, [argument(edi + 8).Val]
	mov [value(eax).Type], dword T
	mov ecx, [address(ecx).Value]
	mov edx, [small_int(edx).Value]
	mov [value(string(eax).Length).Type], dword Std$Integer$SmallT
	mov [small_int(string(eax).Length).Value], edx
	mov [string(eax).Count], dword 1
	mov [value(string_block(string(eax).Blocks).Chars).Type], dword Std$Address$T
	mov [address(string_block(string(eax).Blocks).Chars).Value], ecx
	mov [value(string_block(string(eax).Blocks).Length).Type], dword Std$Integer$SmallT
	mov [small_int(string_block(string(eax).Blocks).Length).Value], edx
	mov ecx, eax
	xor edx, edx
	xor eax, eax
	ret

func GetBlockAddress, 2
	mov eax, [argument(edi).Val]
	mov ecx, [argument(edi + 8).Val]
	mov ecx, [small_int(ecx).Value]
	shl ecx, 4
	lea ecx, [string_block(string(eax).Blocks + ecx).Chars]
	cmp [value(ecx).Type], dword 0
	je .failure
	xor edx, edx
	xor eax, eax
	ret
.failure:
	xor eax, eax
	inc eax
	ret

func GetBlockLength, 2
	mov eax, [argument(edi).Val]
	mov ecx, [argument(edi + 8).Val]
	mov ecx, [small_int(ecx).Value]
	shl ecx, 4
	lea ecx, [string_block(string(eax).Blocks + ecx).Length]
	cmp [value(ecx).Type], dword 0
	je .failure
	xor edx, edx
	xor eax, eax
	ret
.failure:
	xor eax, eax
	inc eax
	ret

struct get_blocks_state, state
	.Block:		resd 1
	.Address:	resd 1
	.Length:	resd 1
endstruct

func GetBlocks, 3
	mov eax, [argument(edi).Val]
	add eax, byte string.Blocks
	cmp [eax], dword 0
	je .failure
	mov ecx, [argument(edi + 8).Ref]
	mov edx, [argument(edi + 16).Ref]
	mov [ecx], eax
	add eax, byte 8
	mov [edx], eax
	add eax, byte 8
	cmp [eax], dword 0
	jne .suspend
	mov ecx, Std$Object$Nil
	xor edx, edx
	xor eax, eax
	ret
.suspend:
	push edx
	push ecx
	push eax
	push byte sizeof(get_blocks_state)
	call Riva$Memory$_alloc
	pop edx
	mov dword [state(eax).Run], .resume
	pop dword [get_blocks_state(eax).Block]
	pop dword [get_blocks_state(eax).Address]
	pop dword [get_blocks_state(eax).Length]
	mov ecx, Std$Object$Nil
	xor edx, edx
	mov ebx, eax
	or eax, byte -1
	ret
.failure:
	xor eax, eax
	inc eax
	ret
.resume:
	mov ecx, [get_blocks_state(eax).Address]
	mov edx, [get_blocks_state(eax).Length]
	mov ebx, [get_blocks_state(eax).Block]
	mov [ecx], ebx
	add ebx, byte 8
	mov [edx], ebx
	add ebx, byte 8
	mov ecx, Std$Object$Nil
	xor edx, edx
	cmp [ebx], dword 0
	jne .resuspend
	xor eax, eax
	ret
.resuspend:
	mov [get_blocks_state(eax).Block], ebx
	mov ebx, eax
	or eax, byte -1
	ret
