%include "Std.inc"

extern Riva$Memory$_alloc
extern Std$String$T
extern Std$Integer$SmallT
extern Std$Address$T

global index_string_small_small

textsect
index_string_small_small:
	push ebx
	push edi
	push esi
	mov eax, [esp + 16]
	mov ebx, [esp + 20]
	mov ecx, [esp + 24]
	cmp ebx, ecx
	jl .notempty
	mov eax, .empty_string
	pop esi
	pop edi
	pop ebx
	ret
.notempty:
	xor edx, edx
	lea esi, [string(eax).Blocks - sizeof(string_block)]
.findfirstloop:
	add esi, byte sizeof(string_block)
	add edx, [small_int(string_block(esi).Length).Value]
	cmp edx, ebx
	jbe .findfirstloop
	push esi
	sub edx, [small_int(string_block(esi).Length).Value]
	mov eax, ebx
	sub eax, edx
	push eax
	sub esi, byte sizeof(string_block)
.findsecondloop:
	add esi, byte sizeof(string_block)
	add edx, [small_int(string_block(esi).Length).Value]
	cmp edx, ecx
	jb .findsecondloop
	sub edx, ecx
	push edx
	sub esi, [esp + 8]
	lea eax, [sizeof(string) + esi + 2 * sizeof(string_block)]
	shr esi, 4
	push ecx
	inc esi
	sub [esp], ebx
	push esi
	push eax
	call Riva$Memory$_alloc
	add esp, byte 4
	mov [value(eax).Type], dword Std$String$T
	pop ecx
	mov [value(string(eax).Length).Type], dword Std$Integer$SmallT
	pop dword [small_int(string(eax).Length).Value]
	mov [string(eax).Count], ecx
	mov esi, [esp + 8]
	shl ecx, 2
	lea edi, [string(eax).Blocks]
	rep movsd
	pop edx
	sub [small_int(string_block(edi - sizeof(string_block)).Length).Value], edx
	pop edx
	add [address(string_block(string(eax).Blocks).Chars).Value], edx
	sub [small_int(string_block(string(eax).Blocks).Length).Value], edx
	add esp, byte 4
	pop esi
	pop edi
	pop ebx
	ret
datasect
.empty_string:
	dd Std$String$T
	dd Std$Integer$SmallT
	dd 0
	dd 0
	dd 0, 0, 0, 0
