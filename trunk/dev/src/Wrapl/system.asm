%define WRAPL2
%include "Lang.inc"

struct bstate, state
	.Val:		resd 1
	.Ref:		resd 1
	.Code:		resd 1
	.Handler:	resd 1
endstruct

struct closure, value
	.Entry:		resd 1
	.Scopes:
endstruct

extern Lang$Type$T
extern Lang$Function$T

global WraplT
section .data
WraplT:
	dd Lang$Type$T
	dd .types
	dd .invoke
	dd 0
	dd 0
.types:
	dd WraplT
	dd Lang$Function$T
	dd 0
section .text
.invoke:
	;int3
	jmp [closure(ecx).Entry]

global run_state
align 8
run_state:
	push ebp
	mov ebp, eax
	mov ecx, [bstate(eax).Val]
	mov edx, [bstate(eax).Ref]
	jmp [bstate(eax).Code]

struct trap
	.Run:		resd 1
	.State:		resd 1
	.Chain:		resd 1
endstruct

%macro deref_arg 1.nolist
	mov eax, [argument(edi + (8 * %1)).Ref]
	test eax, eax
	jz %%notref
	mov eax, [argument(eax).Val]
	mov [argument(edi + (8 * %1)).Val], eax
%%notref:
%endmacro

global send_message
align 8
send_message:
	jmp dword [bstate(ebp).Handler]

global resend_message
align 8
resend_message:
	mov eax, 2
	pop ebp
	ret

global invoke_function
global backtrack
section .text
invoke_function:
	mov eax, [value(ecx).Type]
	call [type(eax).Invoke]
.loop:
	pop esi
	pop edi
	jmp [.returntable + 4 * eax]
section .data
	dd .suspend
.returntable:
	dd .return
	dd backtrack
	dd .message
section .text
.suspend:
	mov [state(ebx).Resume], esi
	mov eax, [trap(ebp + edi).State]
	mov [state(ebx).Chain], eax
	mov [trap(ebp + edi).State], ebx
.return:
	jmp esi
.message:
	jmp [bstate(ebp).Handler]
backtrack:
	mov eax, [trap(ebp + edi).State]
	mov esi, [state(eax).Chain]
	mov [trap(ebp + edi).State], esi
	push edi
	push dword [state(eax).Resume]
	call [state(eax).Run]
	pop esi
	pop edi
	jmp [invoke_function.returntable + 4 * eax]
