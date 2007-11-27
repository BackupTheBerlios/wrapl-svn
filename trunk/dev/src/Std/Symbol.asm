%include "Std.inc"

%define KEY_ROTATION 5
%define INCR_ROTATION 2

extern Std$Type$T
extern Std$Function$T
extern Riva$Memory$_alloc
extern Riva$Memory$_alloc_uncollectable

struct __arg__
	.Types:	resd 1
	.Value:	resd 1
endstruct

struct typeentry
	.Type:	resd 1
	.Next:	resd 1
endstruct

struct valueentry
	.Value:	resd 1
	.Next:	resd 1
endstruct

%macro _proceed_ 1
%define _arg(N) __arg__(ebp - 8 * N)
%define _bestscore ebp + 4
%define _bestfunction ebp
align 8
proceed %+ %1:;(index, score, table)
	;mov eax, [esp + 8]
	mov edi, [symbol(eax).ValueSize]
	dec edi
	js %%continue0a
	mov ebx, [_arg(%1).Value]
	mov edx, [symbol(eax).ValueTable]
	ror ebx, KEY_ROTATION
	mov esi, ebx
	ror esi, INCR_ROTATION
	mov eax, ebx
	;ror eax, KEY_ROTATION
%%searchloop0:
	lea eax, [eax + 2 * esi + 1]
	and eax, edi
	cmp [valueentry(edx + sizeof(valueentry) * eax).Value], ebx
	jb %%continue0
	ja %%searchloop0
	mov eax, [valueentry(edx + sizeof(valueentry) * eax).Next]
	mov ebx, [esp + 8]
	add ebx, byte 20
	mov edi, [symbol(eax).Function]
	test edi, edi
	jz %%nofunction0
	cmp ebx, [_bestscore]
	jna %%nofunction0
	mov [_bestscore], ebx
	mov [_bestfunction], edi
%%nofunction0:
%if %1 = 1
	xor eax, eax
	ret 8
%else
	push eax
	push ebx
%assign %%NEXT %1 - 1
	call proceed %+ %%NEXT
	cmp eax, byte 2
	jae %%continue0
	ret 8
%endif
%%continue0:
	mov eax, [esp + 8]
%%continue0a:
	mov edi, [symbol(eax).TypeSize]
	dec edi
	js near %%continue2
	mov ecx, [_arg(%1).Types]
	push ecx
	mov ebx, [ecx]
	mov edx, [symbol(eax).TypeTable]
	ror ebx, KEY_ROTATION
	mov esi, ebx
	ror esi, INCR_ROTATION
	mov eax, ebx
	;ror eax, KEY_ROTATION
%%searchloop1:
	lea eax, [eax + 2 * esi + 1]
	and eax, edi
	cmp [typeentry(edx + sizeof(typeentry) * eax).Type], ebx
	jb %%continue1
	ja %%searchloop1
	mov eax, [typeentry(edx + sizeof(typeentry) * eax).Next]
	mov ebx, [esp + 8]
	add ebx, byte 16
	mov ecx, [symbol(eax).Function]
	jecxz %%nofunction1
	cmp ebx, [_bestscore]
	jna %%nofunction1
	mov [_bestscore], ebx
	mov [_bestfunction], ecx
%%nofunction1:
%if %1 = 1
	xor eax, eax
	add esp, byte 4
	ret 8
%else
	push eax
	push ebx
%assign %%NEXT %1 - 1
	call proceed %+ %%NEXT
	cmp eax, byte 2
	jae %%continue1
	add esp, byte 4
	ret 8
%endif
%%continue1:
	pop edx
	add edx, byte 4
	mov ecx, [edx]
	jecxz %%continue2
	push edx
	mov eax, [esp + 12]
	mov ebx, ecx
	mov edi, [symbol(eax).TypeSize]
	dec edi
	mov edx, [symbol(eax).TypeTable]
	ror ebx, KEY_ROTATION
	mov esi, ebx
	ror esi, INCR_ROTATION
	mov eax, ebx
	;ror eax, KEY_ROTATION
%%searchloop2:
	lea eax, [eax + 2 * esi + 1]
	and eax, edi
	cmp [typeentry(edx + sizeof(typeentry) * eax).Type], ebx
	jb %%continue1
	ja %%searchloop2
	mov eax, [typeentry(edx + sizeof(typeentry) * eax).Next]
	mov ebx, [esp + 8]
	add ebx, byte 8
	mov ecx, [symbol(eax).Function]
	jecxz %%nofunction2
	cmp ebx, [_bestscore]
	jna %%nofunction2
	mov [_bestscore], ebx
	mov [_bestfunction], ecx
%%nofunction2:
%if %1 = 1
	mov eax, 1
	add esp, byte 4
	ret 8
%else
	push eax
	push ebx
%assign %%NEXT %1 - 1
	call proceed %+ %%NEXT
	cmp eax, byte 2
	jae %%continue1
	inc eax
	add esp, byte 4
	ret 8
%endif
%%continue2:
	mov ecx, [esp + 8]
	mov eax, [symbol(ecx).Skip]
	test eax, eax
	jz %%continue3
	mov ebx, [esp + 4]
	add ebx, byte 2
	mov ecx, [symbol(eax).Function]
	jecxz %%nofunction3
	cmp ebx, [_bestscore]
	jna %%nofunction3
	mov [_bestscore], ebx
	mov [_bestfunction], ecx
%%nofunction3:
%if %1 = 1
	mov eax, 2
	ret 8
%else
	push eax
	push ebx
%assign %%NEXT %1 - 1
	call proceed %+ %%NEXT
	inc eax
	ret 8
%endif
%%continue3:
	mov eax, 2
	ret 8
%endmacro

section .text
%assign i 1
%rep 64
	_proceed_ i
	%assign i i + 1
%endrep

section .data
Proceed:
	dd 0
%assign i 1
%rep 64
	dd proceed %+ i
	%assign i i + 1
%endrep

c_type T, Std$Function$T
c_data T.invoke
	push esi
	push edi
	mov ebx, esi
	dec esi
	js .noargs
	push ecx
	push ebp
	push byte 0
	push dword [symbol(ecx).Function]
	mov ebp, esp
.argloop:
	mov eax, [argument(edi + 8 * esi).Val]
	mov edx, [value(eax).Type]
	push eax
	push dword [type(edx).Types]
	dec esi
	jns .argloop
	mov eax, ecx
	push eax
	push byte 0
	call [Proceed + 4 * ebx]
	mov esp, ebp
	pop ecx
	pop eax
	pop ebp
	pop ebx
	pop edi
	pop esi
	mov eax, [value(ecx).Type]
	jmp [type(eax).Invoke]
.noargs:
	mov ecx, [symbol(ecx).Function]
	pop edi
	pop esi
	mov eax, [value(ecx).Type]
	jmp [type(eax).Invoke]

c_data NoMethodMessageT
	dd Std$Type$T
	dd .types
	dd 0
	dd 0
	dd 0
.types:
	dd NoMethodMessageT
	dd 0

extern Std$String$T
extern Std$Integer$SmallT
extern Std$Address$T
unchecked_func nomethod
	push byte sizeof(nomethod_message)
	call Riva$Memory$_alloc
	add esp, byte 4
	mov [value(eax).Type], dword NoMethodMessageT
	mov [nomethod_message(eax).Symbol], ebx
	mov ecx, eax
	xor edx, edx
	mov eax, 2
	ret

extern Std$String$_new

unchecked_func New
	push byte sizeof(symbol)
	call Riva$Memory$_alloc
	pop ecx
	mov [value(eax).Type], dword T
	mov dword [symbol(eax).Name], .anonymous_str
	mov dword [symbol(eax).TypeTable], 0
	mov dword [symbol(eax).TypeSpace], 0
	mov dword [symbol(eax).TypeSize], 0
	mov dword [symbol(eax).ValueTable], 0
	mov dword [symbol(eax).ValueSpace], 0
	mov dword [symbol(eax).ValueSize], 0
	mov dword [symbol(eax).Function], nomethod
	mov ecx, eax
	xor edx, edx
	xor eax, eax
	ret
section .data
.anonymous_str:
	dd Std$String$T
	dd Std$Integer$SmallT
	dd 6, 1
	dd Std$Integer$SmallT, 6
	dd Std$Address$T, .anonymous
	dd 0, 0, 0, 0
.anonymous:
	db "<anon>", 0, 0

c_func _new_string
	push byte sizeof(symbol)
	call Riva$Memory$_alloc
	mov [esp], eax
	mov [value(eax).Type], dword T
	push dword [esp + 8]
	call Std$String$_new
	mov ecx, eax
	pop eax
	pop eax
	mov dword [symbol(eax).Name], ecx
	mov dword [symbol(eax).TypeTable], 0
	mov dword [symbol(eax).TypeSpace], 0
	mov dword [symbol(eax).TypeSize], 0
	mov dword [symbol(eax).ValueTable], 0
	mov dword [symbol(eax).ValueSpace], 0
	mov dword [symbol(eax).ValueSize], 0
	mov dword [symbol(eax).Function], nomethod
	ret

c_func _new
	push byte sizeof(symbol)
	call Riva$Memory$_alloc
	add esp, byte 4
	mov [value(eax).Type], dword T
	mov dword [symbol(eax).TypeTable], 0
	mov dword [symbol(eax).TypeSpace], 0
	mov dword [symbol(eax).TypeSize], 0
	mov dword [symbol(eax).ValueTable], 0
	mov dword [symbol(eax).ValueSpace], 0
	mov dword [symbol(eax).ValueSize], 0
	mov dword [symbol(eax).Function], 0
	ret

extern Std$Object$T

global __In
global __Is
section .data
__In: dd Std$Object$T
__Is: dd Std$Object$T

unchecked_func Set
	push ebp
	shr esi, 1
	push dword [argument(edi + 8).Val]
	dec esi
	mov eax, [argument(edi).Val]
	jz .notypes
	push esi
.next
	add edi, byte 16
	mov ebx, [argument(edi).Val]
	push edi
	push dword [argument(edi + 8).Val]
	push eax
	cmp ebx, __In
	je .type
	cmp ebx, __Is
	je .value
.skip:
	add esp, byte 8
	mov ecx, eax
	mov eax, [symbol(eax).Skip]
	test eax, eax
	jnz .done
	push ecx
	call _new
	pop ecx
	mov [symbol(ecx).Skip], eax
	jmp .done
.value:
	call valuetable_put
	jmp .done
.type:
	call typetable_put
.done:
	pop edi
	dec dword [esp]
	jnz .next
	add esp, byte 4
.notypes:
	pop ecx
	mov [symbol(eax).Function], ecx
	xor edx, edx
	xor eax, eax
	pop ebp
	ret

c_func _add_methods;(methods)
	push ebp
	push esi
	push edi
	push ebx
	mov edi, [esp + 20]
.loop:
	mov eax, [edi]
	add edi, byte 4
	test eax, eax
	jz .loop
	cmp eax, byte -1
	jne .add
	pop ebx
	pop edi
	pop esi
	pop ebp
	ret
.add:
	mov ebx, [edi]
	add edi, byte 4
	jmp [.select + 4 * ebx]
section .data
.select:
	dd .end
	dd .skp
	dd .val
	dd .typ
section .text
.end:
	mov ebx, [edi]
	add edi, byte 4
	mov [symbol(eax).Function], ebx
	jmp .loop
.skp:
	mov ecx, eax
	mov eax, [symbol(eax).Skip]
	test eax, eax
	jnz .add
	push ecx
	call _new
	pop ecx
	mov [symbol(ecx).Skip], eax
	jmp .add
.val:
	add edi, byte 4
	push edi
	push dword [edi - 4]
	push eax
	call valuetable_put
	pop edi
	jmp .add
.typ:
	add edi, byte 4
	push edi
	push dword [edi - 4]
	push eax
	call typetable_put
	pop edi
	jmp .add

c_func _typetable_put;(table, type)
typetable_put:
	mov ebx, [esp + 8]
	ror ebx, KEY_ROTATION
	mov ecx, ebx
	ror ecx, INCR_ROTATION
	mov esi, [esp + 4]
	mov edx, [symbol(esi).TypeSize]
	dec edx
	js .empty_table
	mov ebp, [symbol(esi).TypeTable]
	mov eax, ebx
	; ecx = increment
	; ebx = hash/key
	; edx = mask
	; eax = index
	; ebp = entries
.search_loop:
	lea eax, [eax + 2 * ecx + 1]
	and eax, edx
	cmp [typeentry(ebp + 8 * eax).Type], ebx
	jb .not_present
	ja .search_loop
	mov eax, [typeentry(ebp + 8 * eax).Next]
	ret 8
.empty_table:
	; ebx = hash/key
	; ecx = increment
	push ecx
	push byte 24
	call Riva$Memory$_alloc
	pop edx
	pop ecx
	mov [symbol(esi).TypeSize], dword 2
	mov [symbol(esi).TypeSpace], dword 1
	mov [symbol(esi).TypeTable], eax
	lea edi, [ebx + 2 * ecx + 1]
	mov esi, eax
	call _new
	and edi, byte 1
	mov [typeentry(esi + 8 * edi).Type], ebx
	mov [typeentry(esi + 8 * edi).Next], eax
	ret 8
.not_present:
	dec dword [symbol(esi).TypeSpace]
	jle near .grow_table
	mov edi, eax
	mov esi, edx
	call _new
	push eax
	cmp [typeentry(ebp + 8 * edi).Type], dword 0
	jne .replace_node
.empty_node:
	mov [typeentry(ebp + 8 * edi).Type], ebx
	mov [typeentry(ebp + 8 * edi).Next], eax
	pop eax
	ret 8
.replace_loop:
	lea edi, [edi + 2 * ecx + 1]
	and edi, esi
	cmp [typeentry(ebp + 8 * edi).Type], dword 0
	je .empty_node
	cmp [typeentry(ebp + 8 * edi).Type], ebx
	ja .replace_loop
.replace_node:
	push dword [typeentry(ebp + 8 * edi).Type]
	push dword [typeentry(ebp + 8 * edi).Next]
	mov [typeentry(ebp + 8 * edi).Type], ebx
	mov [typeentry(ebp + 8 * edi).Next], eax
	pop eax
	pop ebx
	mov ecx, ebx
	ror ecx, INCR_ROTATION
	jmp .replace_loop
.grow_table:
	; First sort table entries so that they are decreasing
	call _new
	push eax
	push esi
	mov edx, [symbol(esi).TypeSize]
	shl edx, 3
	push eax
	push ebx
	; node(esp) is our pivot node
	mov edi, ebp
	lea esi, [ebp + edx]
	mov eax, [typeentry(ebp).Type]
	mov ebx, [typeentry(ebp).Next]
	call .sort_section
	pop esi
	mov edx, [symbol(esi).TypeSize]
	add edx, edx
	push edx
	inc edx
	shl edx, 3
	push edx
	call Riva$Memory$_alloc
	pop edx
	pop edx
	mov [symbol(esi).TypeSize], edx
	mov [symbol(esi).TypeTable], eax
	mov [symbol(esi).TypeSpace], edx
	dec edx
	mov ebx, [typeentry(ebp).Type]
.entry_loop:
	dec dword [symbol(esi).TypeSpace]
	mov edi, ebx
	mov ecx, edi
	ror ecx, INCR_ROTATION
.find_slot_loop:
	lea edi, [edi + 2 * ecx + 1]
	and edi, edx
	cmp [typeentry(eax + 8 * edi).Type], dword 0
	jne .find_slot_loop
	mov ecx, [typeentry(ebp).Next]
	mov [typeentry(eax + 8 * edi).Type], ebx
	mov [typeentry(eax + 8 * edi).Next], ecx
	add ebp, byte 8
	mov ebx, [typeentry(ebp).Type]
	test ebx, ebx
	jne .entry_loop
	pop eax
	ret 8
.sort_section:
	; eax-edx = current node
	; node(esp + 4) = pivot node
	; edi = bottom free slot
	; esi = top free slot
	push edi
	push esi
.sort_loop:
	cmp eax, [typeentry(esp + 12).Type]
	ja .add_to_bottom
	mov [typeentry(esi).Type], eax
	mov [typeentry(esi).Next], ebx
	sub esi, byte 8
	cmp esi, edi
	je .finished_section
	mov eax, [typeentry(esi).Type]
	mov ebx, [typeentry(esi).Next]
	jmp .sort_loop
.add_to_bottom:
	mov [typeentry(edi).Type], eax
	mov [typeentry(edi).Next], ebx
	add edi, byte 8
	cmp esi, edi
	je .finished_section
	mov eax, [typeentry(edi).Type]
	mov ebx, [typeentry(edi).Next]
	jmp .sort_loop
.finished_section:
	mov eax, [typeentry(esp + 12).Type]
	mov ebx, [typeentry(esp + 12).Next]
	mov [typeentry(edi).Type], eax
	mov [typeentry(edi).Next], ebx
	pop esi
	push edi
	add edi, byte 8
	cmp esi, edi
	jbe .no_recurse_1
	push dword [typeentry(edi).Next]
	push dword [typeentry(edi).Type]
	mov eax, [typeentry(esi).Type]
	mov ebx, [typeentry(esi).Next]
	call .sort_section
.no_recurse_1:
	pop esi
	pop edi
	sub esi, byte 8
	cmp esi, edi
	jbe .no_recurse_2
	push dword [typeentry(edi).Next]
	push dword [typeentry(edi).Type]
	mov eax, [typeentry(esi).Type]
	mov ebx, [typeentry(esi).Next]
	call .sort_section
.no_recurse_2:
	ret 8

c_func _valuetable_put;(table, value)
valuetable_put:
	mov ebx, [esp + 8]
	ror ebx, KEY_ROTATION
	mov ecx, ebx
	ror ecx, INCR_ROTATION
	mov esi, [esp + 4]
	mov edx, [symbol(esi).ValueSize]
	dec edx
	js .empty_table
	mov ebp, [symbol(esi).ValueTable]
	mov eax, ebx
	; ecx = increment
	; ebx = hash/key
	; edx = mask
	; eax = index
	; ebp = entries
.search_loop:
	lea eax, [eax + 2 * ecx + 1]
	and eax, edx
	cmp [valueentry(ebp + 8 * eax).Value], ebx
	jb .not_present
	ja .search_loop
	mov eax, [valueentry(ebp + 8 * eax).Next]
	ret 8
.empty_table:
	; ebx = hash/key
	; ecx = increment
	push ecx
	push byte 24
	call Riva$Memory$_alloc
	pop edx
	pop ecx
	mov [symbol(esi).ValueSize], dword 2
	mov [symbol(esi).ValueSpace], dword 1
	mov [symbol(esi).ValueTable], eax
	lea edi, [ebx + 2 * ecx + 1]
	mov esi, eax
	call _new
	and edi, byte 1
	mov [typeentry(esi + 8 * edi).Type], ebx
	mov [typeentry(esi + 8 * edi).Next], eax
	ret 8
.not_present:
	dec dword [symbol(esi).ValueSpace]
	jle near .grow_table
	mov edi, eax
	mov esi, edx
	call _new
	push eax
	cmp [valueentry(ebp + 8 * edi).Value], dword 0
	jne .replace_node
.empty_node:
	mov [valueentry(ebp + 8 * edi).Value], ebx
	mov [valueentry(ebp + 8 * edi).Next], eax
	pop eax
	ret 8
.replace_loop:
	lea edi, [edi + 2 * ecx + 1]
	and edi, esi
	cmp [valueentry(ebp + 8 * edi).Value], dword 0
	je .empty_node
	cmp [valueentry(ebp + 8 * edi).Value], ebx
	ja .replace_loop
.replace_node:
	push dword [valueentry(ebp + 8 * edi).Value]
	push dword [valueentry(ebp + 8 * edi).Next]
	mov [valueentry(ebp + 8 * edi).Value], ebx
	mov [valueentry(ebp + 8 * edi).Next], eax
	pop eax
	pop ebx
	mov ecx, ebx
	ror ecx, INCR_ROTATION
	jmp .replace_loop
.grow_table:
	; First sort table entries so that they are decreasing
	call _new
	push eax
	push esi
	mov edx, [symbol(esi).ValueSize]
	shl edx, 3
	push eax
	push ebx
	; node(esp) is our pivot node
	mov edi, ebp
	lea esi, [ebp + edx]
	mov eax, [valueentry(ebp).Value]
	mov ebx, [valueentry(ebp).Next]
	call .sort_section
	pop esi
	mov edx, [symbol(esi).ValueSize]
	add edx, edx
	push edx
	inc edx
	shl edx, 3
	push edx
	call Riva$Memory$_alloc
	pop edx
	pop edx
	mov [symbol(esi).ValueSize], edx
	mov [symbol(esi).ValueTable], eax
	mov [symbol(esi).ValueSpace], edx
	dec edx
.entry_loop:
	dec dword [symbol(esi).ValueSpace]
	mov edi, [valueentry(ebp).Value]
	mov ecx, edi
	ror ecx, INCR_ROTATION
.find_slot_loop:
	lea edi, [edi + 2 * ecx + 1]
	and edi, edx
	cmp [valueentry(eax + 8 * edi).Value], dword 0
	jne .find_slot_loop
	mov ebx, [valueentry(ebp).Value]
	mov ecx, [valueentry(ebp).Next]
	mov [valueentry(eax + 8 * edi).Value], ebx
	mov [valueentry(eax + 8 * edi).Next], ecx
	add ebp, byte 8
	cmp [valueentry(ebp).Value], dword 0
	jne .entry_loop
	pop eax
	ret 8
.sort_section:
	; eax-edx = current node
	; node(esp + 4) = pivot node
	; edi = bottom free slot
	; esi = top free slot
	push edi
	push esi
.sort_loop:
	cmp eax, [valueentry(esp + 12).Value]
	ja .add_to_bottom
	mov [valueentry(esi).Value], eax
	mov [valueentry(esi).Next], ebx
	sub esi, byte 8
	cmp esi, edi
	je .finished_section
	mov eax, [valueentry(esi).Value]
	mov ebx, [valueentry(esi).Next]
	jmp .sort_loop
.add_to_bottom:
	mov [valueentry(edi).Value], eax
	mov [valueentry(edi).Next], ebx
	add edi, byte 8
	cmp esi, edi
	je .finished_section
	mov eax, [valueentry(edi).Value]
	mov ebx, [valueentry(edi).Next]
	jmp .sort_loop
.finished_section:
	mov eax, [valueentry(esp + 12).Value]
	mov ebx, [valueentry(esp + 12).Next]
	mov [valueentry(edi).Value], eax
	mov [valueentry(edi).Next], ebx
	pop esi
	push edi
	add edi, byte 8
	cmp esi, edi
	jbe .no_recurse_1
	push dword [valueentry(edi).Next]
	push dword [valueentry(edi).Value]
	mov eax, [valueentry(esi).Value]
	mov ebx, [valueentry(esi).Next]
	call .sort_section
.no_recurse_1:
	pop esi
	pop edi
	sub esi, byte 8
	cmp esi, edi
	jbe .no_recurse_2
	push dword [valueentry(edi).Next]
	push dword [valueentry(edi).Value]
	mov eax, [valueentry(esi).Value]
	mov ebx, [valueentry(esi).Next]
	call .sort_section
.no_recurse_2:
	ret 8
