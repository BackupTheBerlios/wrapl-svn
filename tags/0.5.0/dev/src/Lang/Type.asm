%include "Lang.inc"

extern Riva$Memory$_alloc
extern Riva$Memory$_alloc_atomic
extern Lang$Object$Nil

struct fields
	.Length:	resd 1
	.Fields:
endstruct

struct levels
	.Length:	resd 1
	.Levels:
endstruct

c_data T
	dd T
	dd .types
	dd .invoke
	dd 0
	dd 0
.types:
	dd T
	dd 0
section .text
c_func T.invoke
	push ecx
	mov eax, [type(ecx).Fields]
	mov eax, [small_int(array(eax).Length).Value]
	push eax
	lea eax, [4 * eax + 4]
	push eax
	call Riva$Memory$_alloc
	mov [esp], eax

	push edi
	lea edi, [eax + 4 + 4 * esi]
	mov ecx, [esp + 8]
	sub ecx, esi
	mov eax, Lang$Object$Nil
	rep stosd
	pop edi

	dec esi
	js .nofields
	mov ecx, [esp]
.copyfields:
	add ecx, byte 4
	mov edx, [argument(edi).Val]
	add edi, byte sizeof(argument)
	dec esi
	mov [ecx], edx
	jns .copyfields
.nofields:

	pop ecx
	add esp, byte 4
	pop dword [value(ecx).Type]
	xor edx, edx
	xor eax, eax
	ret

func Of, 1
	mov eax, [argument(edi).Val]
	mov ecx, [value(eax).Type]
	xor edx, edx
	xor eax, eax
	ret

c_func _new
	push byte sizeof(fields)
	call Riva$Memory$_alloc
	mov [esp], eax
	push byte sizeof(levels)
	call Riva$Memory$_alloc
	mov [esp], eax
	push byte 8
	call Riva$Memory$_alloc
	mov [esp], eax
	push byte sizeof(type)
	call Riva$Memory$_alloc
	add esp, byte 4
	mov [value(eax).Type], dword T
	pop ecx
	pop dword [type(eax).Levels]
	pop dword [type(eax).Fields]
	mov [ecx], eax
	mov [type(eax).Types], ecx
	ret

extern Lang$Symbol$_typetable_put
extern Lang$Array$_new

unchecked_func New
	push edi
	push esi
	push byte sizeof(type)
	call Riva$Memory$_alloc
	mov [esp], eax
	mov [value(eax).Type], dword T
	mov eax, [argument(edi).Val]
	push byte 1
	push dword [small_int(array(eax).Length).Value]
	dec esi
	jz near .noparents
.sizeloop:
	mov eax, [argument(edi + 8 * esi).Val]
	mov ebx, [type(eax).Fields]
	mov ebx, [small_int(array(ebx).Length).Value]
	add [esp], ebx
	mov ebx, [type(eax).Levels]
	mov ebx, [levels(ebx).Length]
	add [esp + 4], ebx
	dec esi
	jnz .sizeloop
	mov eax, [esp]
	push eax
	call Lang$Array$_new
	mov [esp], eax
	mov eax, [esp + 8]
	lea eax, [4 * eax + 4]
	push eax
	call Riva$Memory$_alloc
	mov ebx, [esp + 16]
	mov [esp], eax
	mov [eax], ebx
	mov eax, [esp + 12]
	lea eax, [4 * eax + 4]
	push eax
	call Riva$Memory$_alloc_atomic
	mov ebx, [esp + 16]
	mov [esp], eax
	mov [levels(eax).Length], ebx
	; [esp] = Levels
	; [esp + 4] = Types
	; [esp + 8] = Fields
	; [esp + 12] = NoOfFields
	; [esp + 16] = NoOfTypes
	; [esp + 20] = Type
	; [esp + 24] = NoOfArgs
	; [esp + 28] = Args
	mov edx, [esp + 28]
	mov esi, [argument(edx).Val]
	mov ecx, [small_int(array(esi).Length).Value]
	mov esi, [array(esi).Values]
	mov edi, [esp + 8]
	mov edi, [array(edi).Values]
	rep movsd
	mov ebx, [esp + 24]
	dec ebx
.fieldcopyloop:
	mov esi, [argument(edx + 8 * ebx).Val]
	mov esi, [type(esi).Fields]
	mov ecx, [small_int(array(esi).Length).Value]
	mov esi, [array(esi).Values]
	rep movsd
	dec ebx
	jnz .fieldcopyloop
	mov [edi], ebx
	mov ebx, [esp + 24]
	dec ebx
	mov edi, [esp + 4]
	add edi, byte 4
.typecopyloop:
	mov esi, [argument(edx + 8 * ebx).Val]
	mov ecx, [type(esi).Levels]
	mov esi, [type(esi).Types]
	mov ecx, [levels(ecx).Length]
	rep movsd
	dec ebx
	jnz .typecopyloop
	mov edi, [esp]
	add edi, byte 4
	mov [edi], ebx
	mov ebx, [esp + 24]
	add edi, byte 4
	dec ebx
.levelcopyloop:
	mov esi, [argument(edx + 8 * ebx).Val]
	mov esi, [type(esi).Levels]
	mov ecx, [levels(esi).Length]
.levelcopyloop0:
	add esi, byte 4
	mov eax, [esi]
	inc eax
	mov [edi], eax
	add edi, byte 4
	dec ecx
	jnz .levelcopyloop0
	dec ebx
	jnz .levelcopyloop
	; [esp] = Levels
	; [esp + 4] = Types
	; [esp + 8] = Fields
	; [esp + 12] = NoOfFields
	; [esp + 16] = NoOfTypes
	; [esp + 20] = Type
	; [esp + 24] = NoOfArgs
	; [esp + 28] = Args
	mov edi, [esp + 4]
	mov esi, [esp]
	mov ebx, [esp + 16]
	xor eax, eax
	dec ebx
	call .sort
.evenifnoparents:
	mov esi, [esp + 8]
	mov esi, [array(esi).Values]
	mov edi, FieldGetter
	push esi
	push edi
	mov esi, [esi]
	test esi, esi
	jz .nofields
.fieldaccessloop:
	push edi
	push dword [esp + 32]
	push esi
	call Lang$Symbol$_typetable_put
	pop dword [symbol(eax).Function]
	add [esp + 4], dword 4
	add [esp], dword 8
	mov esi, [esp + 4]
	mov edi, [esp]
	mov esi, [esi]
	test esi, esi
	jnz .fieldaccessloop
.nofields:
	add esp, byte 8
	mov ecx, [esp + 20]
	pop dword [type(ecx).Levels]
	pop dword [type(ecx).Types]
	pop dword [type(ecx).Fields]
	xor edx, edx
	add esp, byte 20
	xor eax, eax
	ret
.noparents:
	push eax
	push byte 8
	call Riva$Memory$_alloc_atomic
	mov ebx, [esp + 16]
	mov [esp], eax
	mov [eax], ebx
	mov [eax + 4], dword 0
	push byte 8
	call Riva$Memory$_alloc_atomic
	mov [esp], eax
	mov [levels(eax).Length], dword 1
	mov [levels(eax).Levels], dword 0
	jmp .evenifnoparents

.sort:;(edi = Types, esi = Levels, eax = Low, ebx = High)
	cmp eax, ebx
	jl .nontrivial
	ret
.nontrivial:
	push eax
	push ebx
	mov ecx, [esi + 4 * eax + 4]
	push dword [edi + 4 * eax]
	mov edx, [esi + 4 * ebx + 4]
	push dword [edi + 4 * ebx]
.sortloop:
	cmp edx, ecx
	jae .above
.below:
	pop dword [edi + 4 * eax]
	mov [esi + 4 * eax + 4], edx
	inc eax
	cmp eax, ebx
	je .finish
	push dword [edi + 4 * eax]
	mov edx, [esi + 4 * eax + 4]
	jmp .sortloop
.above:
	pop dword [edi + 4 * ebx]
	mov [esi + 4 * ebx + 4], edx
	dec ebx
	cmp eax, ebx
	je .finish
	push dword [edi + 4 * ebx]
	mov edx, [esi + 4 * ebx + 4]
	jmp .sortloop
.finish
	pop dword [edi + 4 * ebx]
	mov [esi + 4 * ebx + 4], ecx
	pop ebx
	push eax
	inc eax
	call .sort
	pop ebx
	sub ebx, byte 2
	pop eax
	jmp .sort

%macro field_getter 1
section .dfields class=data, use32
get_field_%1:
	dd Lang$Function$AsmT
	dd %%here
section .cfields class=text, use32
%%here:
	mov edx, [argument(edi).Val]
	add edx, 4 + (4 * %1)
	mov ecx, [edx]
	xor eax, eax
	ret
%endmacro

section .dfields class=data,use32
align 8
FieldGetter:
%assign i 0
%rep 1024
	field_getter i
	%assign i i + 1
%endrep
