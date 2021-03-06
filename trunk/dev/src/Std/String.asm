%include "Std.inc"

extern Std$Type$T
extern Riva$Memory$_alloc
extern Riva$Memory$_alloc_atomic
extern Std$Object$Nil
extern Std$Integer$_alloc_small

c_type T
.invoke: equ 0

extern strlen
extern Std$Integer$SmallT
extern Std$Address$T
c_func _new
	mov eax, [esp + 4]
	test eax, eax
	jnz .notnull
	mov eax, Nil
	ret
.notnull:
	push eax
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

c_func _copy
	mov eax, [esp + 4]
	test eax, eax
	jnz .notnull
	mov eax, Nil
	ret
.notnull:
	push eax
	call strlen
	mov [esp], eax
	push eax
	inc eax
	push eax
	call Riva$Memory$_alloc_atomic
	pop ecx
	mov [eax + ecx], byte 0
	pop ecx
	push edi
	push esi
	mov esi, [esp + 16]
	mov edi, eax
	mov [esp + 16], eax
	rep movsb
	pop esi
	pop edi
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

c_func _copy_length
	mov eax, [esp + 8]
	push eax
	inc eax
	push eax
	call Riva$Memory$_alloc_atomic
	pop ecx
	mov [eax + ecx], byte 0
	pop ecx
	push edi
	push esi
	mov esi, [esp + 12]
	mov edi, eax
	mov [esp + 12], eax
	rep movsb
	pop esi
	pop edi
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

func Ord, 1
	mov eax, [argument(edi).Val]
	cmp [small_int(string(eax).Length).Value], dword 0
	jne .nonempty
	xor eax, eax
	inc eax
	ret
.nonempty:
	xor edx, edx
	mov eax, [address(string_block(string(eax).Blocks).Chars).Value]
	mov dl, [eax]
	push edx
	call Std$Integer$_alloc_small
	pop dword [small_int(eax).Value]
	mov ecx, eax
	xor edx, edx
	xor eax, eax
	ret

func Chr, 1
	push byte 2
	call Riva$Memory$_alloc_atomic
	add esp, byte 4
	mov ecx, [argument(edi).Val]
	mov ecx, [small_int(ecx).Value]
	mov [eax], cl
	mov [eax + 1], byte 0
	mov ebx, eax
	push byte sizeof(string) + 2 * sizeof(string_block)
	call Riva$Memory$_alloc
	add esp, byte 4
	mov edx, 1
	mov [value(eax).Type], dword T
	mov [value(string(eax).Length).Type], dword Std$Integer$SmallT
	mov [small_int(string(eax).Length).Value], edx
	mov [string(eax).Count], edx
	mov [value(string_block(string(eax).Blocks).Length).Type], dword Std$Integer$SmallT
	mov [small_int(string_block(string(eax).Blocks).Length).Value], edx
	mov [value(string_block(string(eax).Blocks).Chars).Type], dword Std$Address$T
	mov [address(string_block(string(eax).Blocks).Chars).Value], ebx
	mov ecx, eax
	xor edx, edx
	xor eax, eax
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

func $Add, 2
	mov ebx, [argument(edi + 8).Val]
	mov esi, [small_int(string(ebx).Length).Value]
	test esi, esi
	jnz .first_not_empty
	mov ecx, [argument(edi).Val]
	xor edx, edx
	xor eax, eax
	ret
.first_not_empty:
	mov eax, [argument(edi).Val]
	mov ecx, [small_int(string(eax).Length).Value]
	test ecx, ecx
	jnz .second_not_empty
	mov ecx, [argument(edi + 8).Val]
	xor edx, edx
	xor eax, eax
	ret
.second_not_empty:
	mov edx, [string(eax).Count]
	add esi, ecx
	mov ecx, [string(ebx).Count]
	add ecx, edx
	mov edx, [small_int(string_block(string(eax).Blocks + (edx - 2) * (sizeof(string_block) / 2)).Length).Value]
	add edx, [small_int(string_block(string(ebx).Blocks).Length).Value]
	push esi
	cmp edx, byte 32
	jb .compress
	push ecx
	lea ecx, [2 * ecx + 2]
	lea eax, [sizeof(string) + ecx * (sizeof(string_block) / 2)]
	push eax
	call Riva$Memory$_alloc
	add esp, byte 4
	mov [value(eax).Type], dword T
	pop dword [string(eax).Count]
	mov [value(string(eax).Length).Type], dword Std$Integer$SmallT
	pop dword [small_int(string(eax).Length).Value]
	mov edx, edi
	lea edi, [string(eax).Blocks]
	mov ebx, [argument(edx).Val]
	lea esi, [string(ebx).Blocks]
	mov ecx, [string(ebx).Count]
	shl ecx, 2
	rep movsd
	mov ebx, [argument(edx + 8).Val]
	lea esi, [string(ebx).Blocks]
	mov ecx, [string(ebx).Count]
	shl ecx, 2
	rep movsd
	mov ecx, eax
	xor edx, edx
	xor eax, eax
	ret
.compress:
	dec ecx
	push ecx
	lea ecx, [2 * ecx + 2]
	lea eax, [sizeof(string) + ecx * (sizeof(string_block) / 2)]
	push eax
	call Riva$Memory$_alloc
	add esp, byte 4
	mov [value(eax).Type], dword T
	pop dword [string(eax).Count]
	mov [value(string(eax).Length).Type], dword Std$Integer$SmallT
	pop dword [small_int(string(eax).Length).Value]
	mov edx, edi
	lea edi, [string(eax).Blocks]
	mov ebx, [argument(edx).Val]
	lea esi, [string(ebx).Blocks]
	mov ecx, [string(ebx).Count]
	lea ecx, [4 * ecx - 4]
	rep movsd
	mov ebx, [argument(edx + 8).Val]
	push eax
	push esi
	push edi
	push ebx
	mov eax, [small_int(string_block(esi).Length).Value]
	add eax, [small_int(string_block(string(ebx).Blocks).Length).Value]
	mov [value(string_block(edi).Length).Type], dword Std$Integer$SmallT
	mov [small_int(string_block(edi).Length).Value], eax
	mov [value(string_block(edi).Chars).Type], dword Std$Address$T
	inc eax
	push eax
	call Riva$Memory$_alloc_atomic
	add esp, byte 4
	mov edi, [esp + 4]
	mov [address(string_block(edi).Chars).Value], eax
	mov edi, eax
	mov esi, [esp + 8]
	mov ecx, [small_int(string_block(esi).Length).Value]
	mov esi, [address(string_block(esi).Chars).Value]
	rep movsb
	pop ebx
	mov esi, [address(string_block(string(ebx).Blocks).Chars).Value]
	mov ecx, [small_int(string_block(string(ebx).Blocks).Length).Value]
	rep movsb
	pop edi
	pop esi
	add edi, byte sizeof(string_block)
	lea esi, [string(ebx).Blocks + sizeof(string_block)]
	mov ecx, [string(ebx).Count]
	lea ecx, [4 * ecx - 4]
	rep movsd
	pop ecx
	xor edx, edx
	xor eax, eax
	ret

c_data Nil
	dd T
	dd Std$Integer$SmallT
	dd 0, 0
	dd 0, 0, 0, 0

c_data Lower
	dd T
	dd Std$Integer$SmallT
	dd 26, 1
	dd Std$Integer$SmallT, 26
	dd Std$Address$T, .chars
	dd 0, 0, 0, 0
.chars:
	db "abcdefghijklmnopqrstuvwxyz"

c_data Upper
	dd T
	dd Std$Integer$SmallT
	dd 26, 1
	dd Std$Integer$SmallT, 26
	dd Std$Address$T, .chars
	dd 0, 0, 0, 0
.chars:
	db "ABCDEFGHIJKLMNOPQRSTUVWXYZ"

c_func _add
	push ebx
	push esi
	push edi
	mov ebx, [esp + 20]
	mov esi, [small_int(string(ebx).Length).Value]
	test esi, esi
	jnz .first_not_empty
	mov eax, [esp + 16]
	pop edi
	pop esi
	pop ebx
	ret
.first_not_empty:
	mov eax, [esp + 16]
	mov ecx, [small_int(string(eax).Length).Value]
	test ecx, ecx
	jnz .second_not_empty
	mov eax, [esp + 20]
	pop edi
	pop esi
	pop ebx
	ret
.second_not_empty:
	mov edx, [string(eax).Count]
	add esi, ecx
	mov ecx, [string(ebx).Count]
	add ecx, edx
	mov edx, [small_int(string_block(string(eax).Blocks + (edx - 2) * (sizeof(string_block) / 2)).Length).Value]
	add edx, [small_int(string_block(string(ebx).Blocks).Length).Value]
	push esi
	cmp edx, byte 32
	jb .compress
	push ecx
	lea ecx, [2 * ecx + 2]
	lea eax, [sizeof(string) + ecx * (sizeof(string_block) / 2)]
	push eax
	call Riva$Memory$_alloc
	add esp, byte 4
	mov [value(eax).Type], dword T
	pop dword [string(eax).Count]
	mov [value(string(eax).Length).Type], dword Std$Integer$SmallT
	pop dword [small_int(string(eax).Length).Value]
	mov edx, edi
	lea edi, [string(eax).Blocks]
	mov ebx, [esp + 16]
	lea esi, [string(ebx).Blocks]
	mov ecx, [string(ebx).Count]
	shl ecx, 2
	rep movsd
	mov ebx, [esp + 20]
	lea esi, [string(ebx).Blocks]
	mov ecx, [string(ebx).Count]
	shl ecx, 2
	rep movsd
	pop edi
	pop esi
	pop ebx
	ret
.compress:
	dec ecx
	push ecx
	lea ecx, [2 * ecx + 2]
	lea eax, [sizeof(string) + ecx * (sizeof(string_block) / 2)]
	push eax
	call Riva$Memory$_alloc
	add esp, byte 4
	mov [value(eax).Type], dword T
	pop dword [string(eax).Count]
	mov [value(string(eax).Length).Type], dword Std$Integer$SmallT
	pop dword [small_int(string(eax).Length).Value]
	mov edx, edi
	lea edi, [string(eax).Blocks]
	mov ebx, [esp + 16]
	lea esi, [string(ebx).Blocks]
	mov ecx, [string(ebx).Count]
	lea ecx, [4 * ecx - 4]
	rep movsd
	mov ebx, [esp + 20]
	push eax
	push esi
	push edi
	push ebx
	mov eax, [small_int(string_block(esi).Length).Value]
	add eax, [small_int(string_block(string(ebx).Blocks).Length).Value]
	mov [value(string_block(edi).Length).Type], dword Std$Integer$SmallT
	mov [small_int(string_block(edi).Length).Value], eax
	mov [value(string_block(edi).Chars).Type], dword Std$Address$T
	inc eax
	push eax
	call Riva$Memory$_alloc_atomic
	add esp, byte 4
	mov edi, [esp + 4]
	mov [address(string_block(edi).Chars).Value], eax
	mov edi, eax
	mov esi, [esp + 8]
	mov ecx, [small_int(string_block(esi).Length).Value]
	mov esi, [address(string_block(esi).Chars).Value]
	rep movsb
	pop ebx
	mov esi, [address(string_block(string(ebx).Blocks).Chars).Value]
	mov ecx, [small_int(string_block(string(ebx).Blocks).Length).Value]
	rep movsb
	pop edi
	pop esi
	add edi, byte sizeof(string_block)
	lea esi, [string(ebx).Blocks + sizeof(string_block)]
	mov ecx, [string(ebx).Count]
	lea ecx, [4 * ecx - 4]
	rep movsd
	pop eax
	pop edi
	pop esi
	pop ebx
	ret

func Hash, 1
	mov eax, [argument(edi).Val]
	lea edi, [string(eax).Blocks]
	xor ebx, ebx
	xor eax, eax
	mov ecx, [small_int(string_block(edi).Length).Value]
	jecxz .done
.outer_loop:
	mov esi, [address(string_block(edi).Chars).Value]
.inner_loop:
	lodsb
	ror ebx, 4
	add ebx, eax
	dec ecx
	jnz .inner_loop
	add edi, byte sizeof(string_block)
	mov ecx, [small_int(string_block(edi).Length).Value]
	test ecx, ecx
	jnz .outer_loop
.done:
	call Std$Integer$_alloc_small
	mov [small_int(eax).Value], ebx
	mov ecx, eax
	xor edx, edx
	xor eax, eax
	ret

section .data
LESS: dd Std$Integer$SmallT, -1
ZERO:
EQUAL: dd Std$Integer$SmallT, 0
ONE:
GREATER: dd Std$Integer$SmallT, 1

func Compare, 2
    	mov eax, [argument(edi).Val]
	mov ebx, [argument(edi + 8).Val]
	lea eax, [string(eax).Blocks]
	lea ebx, [string(ebx).Blocks]
	mov ecx, [small_int(string_block(eax).Length).Value]
	mov esi, [address(string_block(eax).Chars).Value]
	mov edx, [small_int(string_block(ebx).Length).Value]
	mov edi, [address(string_block(ebx).Chars).Value]
	test ecx, ecx
	jnz .first_not_empty0
	test edx, edx
	jz .equal
	jmp .less
.first_not_empty0:
	test edx, edx
	jz .greater
.compare_loop:
	cmpsb
	jb .less
	ja .greater
	dec ecx
	jz .reload_first
.first_not_empty:
	dec edx
	jnz .compare_loop
	add ebx, byte sizeof(string_block)
	mov edx, [small_int(string_block(ebx).Length).Value]
	test edx, edx
	mov edi, [address(string_block(ebx).Chars).Value]
	jnz .compare_loop
.greater:
	mov ecx, GREATER
	xor edx, edx
	xor eax, eax
	ret
.reload_first:
	add eax, byte sizeof(string_block)
	mov ecx, [small_int(string_block(eax + 8).Length).Value]
	test ecx, ecx
	mov esi, [address(string_block(eax).Chars).Value]
	jnz .first_not_empty
	dec edx
	jnz .less
	cmp [small_int(string_block(ebx + sizeof(string_block)).Length).Value], dword 0
	jne .less
.equal:
	mov ecx, EQUAL
	xor edx, edx
	xor eax, eax
	ret
.less:
	mov ecx, LESS
	xor edx, edx
	xor eax, eax
	ret
