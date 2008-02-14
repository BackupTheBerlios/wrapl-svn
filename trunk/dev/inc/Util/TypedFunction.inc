%ifndef UTIL_TYPEDFUNCTION_INC
%define UTIL_TYPEDFUNCTION_INC

%include "Std.inc"

extern Util$TypedFunction$_EmptyTable

%macro typed_func 2
datasect
align 4
global %1
$%1:
	push ebx
	mov eax, [esp + 8]
	mov ebx, [value(eax).Type]
	mov ebx, [type0(ebx).Types]
.type_loop:
	mov ecx, [ebx]
	add ebx, byte 4
	mov edx, ecx
	mov eax, ecx
	ror edx, 3
.search_loop:
	lea eax, [eax + 2 * edx + 1]
	and eax, strict dword 1
	cmp [dword .entries + 8 * eax], ecx
	ja .type_loop
	jb .search_loop
	pop ebx
	jmp [dword .entries + 8 * eax + 4]
align 4
.space: dd 1
.entries:
	dd 0xFFFFFFFF, 0
	dd 0, %2
%endmacro

%endif
