%include "Std.inc"

struct bstate, state
	.Val:		resd 1
	.Ref:		resd 1
	.Code:		resd 1
	.Handler:	resd 1
	.Data:		resd 1
endstruct

struct closure, value
	.Entry:		resd 1
	.Scopes:
endstruct

extern Std$Type$T
extern Std$Function$T
extern Std$String$T
extern Std$Integer$SmallT
extern Std$Address$T
extern Riva$Memory$_alloc

c_data Version
	dd Std$String$T
	dd Std$Integer$SmallT, 5
	dd 1
	dd Std$Integer$SmallT, 5
	dd Std$Address$T, .chars
	dd 0, 0, 0, 0
.chars:
	db "0.6.0", 0

c_data WraplT
	dd Std$Type$T
	dd .types
	dd .invoke
	dd 0
	dd 0
.types:
	dd WraplT
	dd Std$Function$T
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
	;mov eax, 2
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

struct limiter, state
	.Count:	resd 1
endstruct

global invoke_limit
section .text
invoke_limit:
	pop esi
	; edi = offset to current trap
	; ecx = limiting value
	cmp dword [value(ecx).Type], Std$Integer$SmallT
	jne .error
	mov ebx, [small_int(ecx).Value]
	dec ebx
	js backtrack
	jz .return
	push byte sizeof(limiter)
	call Riva$Memory$_alloc
	pop ecx
	mov [limiter(eax).Count], ebx
	mov [state(eax).Run], dword .resume
	mov [state(eax).Resume], esi
	mov ebx, [trap(ebp + edi).State]
	mov [state(eax).Chain], ebx
	mov [trap(ebp + edi).State], eax
.return:
	jmp esi
.error:
	mov ecx, IncorrectTypeMessage
	xor edx, edx
	mov eax, 2
	jmp [bstate(ebp).Handler]
.resume:
	dec dword [limiter(eax).Count]
	js .resume_failure
	jz .resume_return
	mov ebx, eax
	or eax, byte -1
	ret
.resume_failure:
	mov eax, 1
	ret
.resume_return:
	xor eax, eax
	ret

c_data IncorrectTypeMessageT
	dd Std$Type$T
	dd .types
	dd 0
	dd 0
	dd 0
.types:
	dd IncorrectTypeMessageT
	dd 0

method "@", TYP, IncorrectTypeMessageT, VAL, Std$String$T
	mov ecx, .String
	xor edx, edx
	xor eax, eax
	ret
section .data
.String:
	dd Std$String$T
	dd Std$Integer$SmallT, 25
	dd 1
	dd Std$Integer$SmallT, 25
	dd Std$Address$T, .chars
	dd 0, 0, 0, 0
.chars:
	db "Object has incorrect type", 0

global IncorrectTypeMessage
section .data
IncorrectTypeMessage:
	dd IncorrectTypeMessageT

struct select_string_case
	.Length: resd 1
	.String: resd 1
	.Jump: resd 1
endstruct

global select_string
align 8
select_string:
;	int3
	pop edx
	cmp dword [value(ecx).Type], Std$String$T
	je .isstring
	mov ecx, IncorrectTypeMessage
	xor edx, edx
	mov eax, 2
	jmp [bstate(ebp).Handler]
.isstring:
;	add edx, byte 0x03
;	and edx, byte 0xFC
	push ebp
	mov ebp, esp
	cmp [string(ecx).Count], dword 1
	je .simplestring
	mov eax, [small_int(string(ecx).Length).Value]
	sub esp, eax
	and esp, byte -4
	mov edi, esp
	lea ebx, [string(ecx).Blocks]
.copyloop:
	mov ecx, [small_int(string_block(ebx).Length).Value]
	jecxz .copied
	mov esi, [address(string_block(ebx).Chars).Value]
	rep movsb
	add ebx, byte sizeof(string_block)
	jmp .copyloop
.copied:
	mov ebx, esp
	jmp .anystring
.simplestring:
	mov ebx, [address(string_block(string(ecx).Blocks).Chars).Value]
	mov eax, [small_int(string_block(string(ecx).Blocks).Length).Value]
.anystring:
	; ebx = string
	; eax = length
	test eax, eax
	jz .default
.loop:
	add edx, sizeof(select_string_case)
	mov ecx, [select_string_case(edx).Length]
	jecxz .default
	cmp ecx, eax

;	Uncomment this line once strings are sorted
;	ja .default

	jne .loop
	mov esi, [select_string_case(edx).String]
	mov edi, ebx
	repz cmpsb
	jnz .loop
.default:
	mov esp, ebp
	pop ebp
	jmp [select_string_case(edx).Jump]

global CmovSupport
section .data
CmovSupport: dd 0

global detect_cpu_features
section .text
detect_cpu_features:
	push ebx
	mov eax, 0x1
	cpuid
	and edx, 0x8000
	setnz byte [CmovSupport]
	pop ebx
	ret
