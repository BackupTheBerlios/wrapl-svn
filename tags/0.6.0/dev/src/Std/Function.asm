%include "Std.inc"

extern Std$Type$T
extern Riva$Memory$_alloc
extern Std$Object$Nil

c_data FewArgsMessageT
	dd Std$Type$T
	dd .types
	dd 0
	dd 0
	dd 0
.types:
	dd FewArgsMessageT
	dd 0

c_data T
	dd Std$Type$T
	dd .types
	dd 0
	dd 0
	dd 0
.types:
	dd T
	dd 0

c_data AsmT
	dd Std$Type$T
	dd .types
	dd .invoke
	dd 0
	dd 0
.types:
	dd AsmT
	dd T
	dd 0
section .text
align 8
.invoke:
	jmp [asm_fun(ecx).Invoke]

c_data CheckedAsmT
	dd Std$Type$T
	dd .types
	dd .invoke
	dd 0
	dd 0
.types:
	dd CheckedAsmT
	dd AsmT
	dd T
	dd 0
section .text
align 8
.invoke:
	cmp esi, [checkedasm_fun(ecx).Count]
	jb .toofewargs
	jmp [asm_fun(checkedasm_fun(ecx).Unchecked).Invoke]
.toofewargs:
	push ecx
	push byte sizeof(fewargs_message)
	call Riva$Memory$_alloc
	add esp, byte 4
	mov [value(eax).Type], dword FewArgsMessageT
	pop dword [fewargs_message(eax).Func]
	mov dword [fewargs_message(eax).Count], esi
	mov ecx, eax
	xor edx, edx
	mov eax, 2
	ret

c_data CT
	dd Std$Type$T
	dd .types
	dd .invoke
	dd 0
	dd 0
.types:
	dd CT
	dd T
	dd 0
section .text
.invoke:
	push byte 0
	push byte 0
	push dword Std$Object$Nil
	push esp
	push edi
	push esi
	push ecx
	call [c_fun(ecx).Invoke]
	add esp, byte 16
	pop ecx
	pop edx
	pop ebx
	ret

c_data CheckedCT
	dd Std$Type$T
	dd .types
	dd .invoke
	dd 0
	dd 0
.types:
	dd CheckedCT
	dd CT
	dd T
	dd 0
section .text
.invoke:
	cmp esi, [checkedc_fun(ecx).Count]
	jb .toofewargs
	push byte 0
	push byte 0
	push dword Std$Object$Nil
	push esp
	push edi
	push esi
	push ecx
	call [checkedc_fun(ecx).Invoke]
	add esp, byte 16
	pop ecx
	pop edx
	pop ebx
	ret
.toofewargs:
	push ecx
	push byte sizeof(fewargs_message)
	call Riva$Memory$_alloc
	add esp, byte 4
	mov [value(eax).Type], dword FewArgsMessageT
	pop dword [fewargs_message(eax).Func]
	mov dword [fewargs_message(eax).Count], esi
	mov ecx, eax
	xor edx, edx
	mov eax, 2
	ret

c_func _new_c
	push byte sizeof(c_fun)
	call Riva$Memory$_alloc
	add esp, byte 4
	mov ecx, [esp + 4]
	mov [value(eax).Type], dword CT
	mov [c_fun(eax).Invoke], ecx
	ret

struct c_state, state
	.Invoke:	resd 1
endstruct

c_func _resume_c
	push byte 0
	push dword Std$Object$Nil
	push eax
	push esp
	call [c_state(eax).Invoke]
	add esp, byte 4
	pop ebx
	pop ecx
	pop edx
	ret

c_func _call
	push ebx
	push esi
	push edi
	lea edi, [esp + 28]
	mov esi, [esp + 20]
	mov ecx, [esp + 16]
	mov eax, [value(ecx).Type]
	call [type(eax).Invoke]
	mov edi, [esp + 24]
	;cmp eax, byte 0
	;jl .state
	;xor ebx, ebx
;.state:
;	faster version of above, assuming eax = -1,0,1 or 2 and valid states have address % 4 = 0
	and ebx, eax
	and bl, 0xFC
	mov [result(edi).State], ebx
	mov [result(edi).Val], ecx
	mov [result(edi).Ref], edx
	pop edi
	pop esi
	pop ebx
	ret

c_func _resume
	push ebx
	push esi
	push edi
	mov edi, [esp + 16]
	mov eax, [result(edi).State]
	call [state(eax).Run]
	mov edi, [esp + 16]
;	cmp eax, byte 0
;	jl .state
;	xor ebx, ebx
;.state:
	and ebx, eax
	and bl, 0xFC
	mov [result(edi).State], ebx
	mov [result(edi).Val], ecx
	mov [result(edi).Ref], edx
	pop edi
	pop esi
	pop ebx
	ret

c_func _invoke
	push ebx
	push esi
	push edi
	mov edi, [esp + 28]
	mov esi, [esp + 20]
	mov ecx, [esp + 16]
	mov eax, [value(ecx).Type]
	call [type(eax).Invoke]
	mov edi, [esp + 24]
;	cmp eax, byte 0
;	jl .state
;	xor ebx, ebx
;.state:
	and ebx, eax
	and bl, 0xFC
	mov [result(edi).State], ebx
	mov [result(edi).Val], ecx
	mov [result(edi).Ref], edx
	pop edi
	pop esi
	pop ebx
	ret
