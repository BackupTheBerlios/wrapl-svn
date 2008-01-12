%include "Std.inc"

extern Std$Type$T
extern Riva$Memory$_alloc
extern Std$Object$Nil

c_type FewArgsMessageT
.invoke: equ 0

c_type T
.invoke: equ 0

c_data Nil
	dd T

c_type AsmT, T
.invoke:
	jmp [asm_fun(ecx).Invoke]

c_type CheckedAsmT, AsmT, T
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

c_type CT, T
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

c_type CheckedCT, CT, T
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
	call [type0(eax).Invoke]
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
	call [type0(eax).Invoke]
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

struct constant, value
    .Value: resd 1
endstruct

c_type ConstantT, T
.invoke:
    lea edx, [constant(ecx).Value]
    mov ecx, [constant(ecx).Value]
    xor eax, eax
    ret

func Constant, 1
    push byte sizeof(constant)
    call Riva$Memory$_alloc
    add esp, byte 4
    mov ecx, [argument(edi).Val]
    mov [value(eax).Type], dword ConstantT
    mov [constant(eax).Value], ecx
    mov ecx, eax
    xor edx, edx
    xor eax, eax
    ret

struct variable, value
    .Address: resd 1
endstruct

c_type VariableT, T
.invoke:
    mov edx, [variable(ecx).Address]
    mov ecx, [edx]
    xor eax, eax
    ret

func Variable, 1
    push byte sizeof(constant)
    call Riva$Memory$_alloc
    add esp, byte 4
    mov edx, [argument(edi).Ref]
    mov [value(eax).Type], dword VariableT
    mov [variable(eax).Address], edx
    mov ecx, eax
    xor edx, edx
    xor eax, eax
    ret
