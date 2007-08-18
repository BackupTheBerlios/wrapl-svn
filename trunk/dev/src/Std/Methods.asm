%include "Std.inc"

extern Riva$Memory$_alloc
extern Riva$Memory$_alloc_atomic

extern Std$Type$T
extern Std$Function$T
extern Std$Function$FewArgsMessageT
extern Std$Address$T
extern Std$Symbol$T
extern Std$Symbol$NoMethodMessageT
extern Std$Integer$T
extern Std$Integer$BigT
extern Std$Integer$SmallT
extern Std$String$T
extern Std$Real$T
extern Std$Array$T
extern Std$Object$Nil
extern Std$Object$T

extern Std$Address$_alloc

%define ADDRESS TYP, Std$Address$T
%define SMALLINT TYP, Std$Integer$SmallT
%define BIGINT TYP, Std$Integer$BigT
%define REAL TYP, Std$Real$T
%define STRING TYP, Std$String$T
%define OBJECT TYP, Std$Object$T
%define SYMBOL TYP, Std$Symbol$T
%define ANY SKP

method "put", ADDRESS, ADDRESS, SMALLINT
	mov eax, [argument(edi).Val]
	mov ebx, [argument(edi + 8).Val]
	mov ecx, [argument(edi + 16).Val]
	mov edi, [address(eax).Value]
	mov esi, [address(ebx).Value]
	mov ecx, [small_int(ecx).Value]
	rep movsb
	mov ecx, Std$Object$Nil
	xor edx, edx
	xor eax, eax
	ret

method "put", ADDRESS, ADDRESS, SMALLINT, SMALLINT
	mov eax, [argument(edi).Val]
	mov ebx, [argument(edi + 8).Val]
	mov ecx, [argument(edi + 16).Val]
	mov edx, [argument(edi + 24).Val]
	mov edi, [address(eax).Value]
	add edi, [small_int(edx).Value]
	mov esi, [address(ebx).Value]
	mov ecx, [small_int(ecx).Value]
	rep movsb
	mov ecx, Std$Object$Nil
	xor edx, edx
	xor eax, eax
	ret

method "put8", ADDRESS, SMALLINT
	mov esi, [argument(edi).Val]
	mov eax, [argument(edi + 8).Val]
	mov esi, [address(esi).Value]
	mov al, [small_int(eax).Value]
	mov [esi], al
	mov ecx, Std$Object$Nil
	xor edx, edx
	xor eax, eax
	ret

method "put", ADDRESS, OBJECT
	mov esi, [argument(edi).Val]
	mov eax, [argument(edi + 8).Val]
	mov esi, [address(esi).Value]
	mov [esi], eax
	mov ecx, Std$Object$Nil
	xor edx, edx
	xor eax, eax
	ret

method "put", ADDRESS, OBJECT, SMALLINT
	mov esi, [argument(edi).Val]
	mov eax, [argument(edi + 8).Val]
	mov ebx, [argument(edi + 16).Val]
	mov esi, [address(esi).Value]
	add esi, [small_int(ebx).Value]
	mov [esi], eax
	mov ecx, Std$Object$Nil
	xor edx, edx
	xor eax, eax
	ret

method "put32", ADDRESS, SMALLINT
	mov esi, [argument(edi).Val]
	mov eax, [argument(edi + 8).Val]
	mov esi, [address(esi).Value]
	mov eax, [small_int(eax).Value]
	mov [esi], eax
	mov ecx, Std$Object$Nil
	xor edx, edx
	xor eax, eax
	ret

method "put8", ADDRESS, SMALLINT, SMALLINT
	mov esi, [argument(edi).Val]
	mov eax, [argument(edi + 8).Val]
	mov ebx, [argument(edi + 16).Val]
	mov esi, [address(esi).Value]
	add esi, [small_int(ebx).Value]
	mov al, [small_int(eax).Value]
	mov [esi], al
	mov ecx, Std$Object$Nil
	xor edx, edx
	xor eax, eax
	ret

method "put32", ADDRESS, SMALLINT, SMALLINT
	mov esi, [argument(edi).Val]
	mov eax, [argument(edi + 8).Val]
	mov ebx, [argument(edi + 16).Val]
	mov esi, [address(esi).Value]
	add esi, [small_int(ebx).Value]
	mov eax, [small_int(eax).Value]
	mov [esi], eax
	mov ecx, Std$Object$Nil
	xor edx, edx
	xor eax, eax
	ret

method "put", ADDRESS, STRING
	mov eax, [argument(edi + 8).Val]
	lea eax, [string(eax).Blocks]
	mov edi, [argument(edi).Val]
	mov edi, [address(edi).Value]
.loop:
	mov ecx, [small_int(string_block(eax).Length).Value]
	jecxz .finished
	mov esi, [small_int(string_block(eax).Chars).Value]
	rep movsb
	add eax, byte sizeof(string_block)
	jmp .loop
.finished:
	mov ecx, Std$Object$Nil
	xor edx, edx
	xor eax, eax
	ret

method "puts", ADDRESS, STRING, SMALLINT
	mov eax, [argument(edi + 8).Val]
	mov ebx, [argument(edi + 16).Val]
	lea eax, [string(eax).Blocks]
	mov edi, [argument(edi).Val]
	mov edi, [address(edi).Value]
	add edi, [small_int(ebx).Value]
.loop:
	mov ecx, [small_int(string_block(eax).Length).Value]
	jecxz .finished
	mov esi, [small_int(string_block(eax).Chars).Value]
	rep movsb
	add eax, byte sizeof(string_block)
	jmp .loop
.finished:
	mov ecx, Std$Object$Nil
	xor edx, edx
	xor eax, eax
	ret

method "get", ADDRESS
	mov eax, [argument(edi).Val]
	mov edx, [address(eax).Value]
	mov ecx, [edx]
	xor eax, eax
	ret

method "get", ADDRESS, SMALLINT
	mov eax, [argument(edi).Val]
	mov ebx, [argument(edi + 8).Val]
	mov edx, [address(eax).Value]
	add edx, [small_int(ebx).Value]
	mov ecx, [edx]
	xor eax, eax
	ret

method "get8", ADDRESS
	mov eax, [argument(edi).Val]
	mov eax, [address(eax).Value]
	movzx eax, byte [eax]
	push eax
	call Std$Integer$_alloc_small
	pop dword [small_int(eax).Value]
	mov ecx, eax
	xor eax, eax
	xor edx, edx
	ret

method "get32", ADDRESS
	mov eax, [argument(edi).Val]
	mov eax, [address(eax).Value]
	push dword [eax]
	call Std$Integer$_alloc_small
	pop dword [small_int(eax).Value]
	mov ecx, eax
	xor eax, eax
	xor edx, edx
	ret

method "get8", ADDRESS, SMALLINT
	mov eax, [argument(edi).Val]
	mov ebx, [argument(edi + 8).Val]
	mov eax, [address(eax).Value]
	add eax, [small_int(ebx).Value]
	movzx eax, byte [eax]
	push eax
	call Std$Integer$_alloc_small
	pop dword [small_int(eax).Value]
	mov ecx, eax
	xor eax, eax
	xor edx, edx
	ret

method "get32", ADDRESS, SMALLINT
	mov eax, [argument(edi).Val]
	mov ebx, [argument(edi + 8).Val]
	mov eax, [address(eax).Value]
	add eax, [small_int(ebx).Value]
	push dword [eax]
	call Std$Integer$_alloc_small
	pop dword [small_int(eax).Value]
	mov ecx, eax
	xor eax, eax
	xor edx, edx
	ret

method "gets", ADDRESS, SMALLINT
	mov eax, [argument(edi + 8).Val]
	mov eax, [small_int(eax).Value]
	push eax
	push eax
	call Riva$Memory$_alloc_atomic
	mov [esp], eax
	mov esi, [argument(edi).Val]
	mov esi, [address(esi).Value]
	mov edi, eax
	mov ecx, [esp + 4]
	rep movsb
	push byte sizeof(string) + 2 * sizeof(string_block)
	call Riva$Memory$_alloc
	add esp, byte 4
	mov ecx, eax
	mov [value(ecx).Type], dword Std$String$T
	mov [value(string(ecx).Length).Type], dword Std$Integer$SmallT
	pop dword [address(string_block(string(ecx).Blocks).Chars).Value]
	pop eax
	mov [small_int(string(ecx).Length).Value], eax
	mov [small_int(string_block(string(ecx).Blocks).Length).Value], eax
	mov [string(ecx).Count], dword 1
	mov [value(string_block(string(ecx).Blocks).Length).Type], dword Std$Integer$SmallT
	mov [value(string_block(string(ecx).Blocks).Chars).Type], dword Std$Address$T
	xor edx, edx
	xor eax, eax
	ret

method "gets", ADDRESS, SMALLINT, SMALLINT
	mov eax, [argument(edi + 16).Val]
	mov eax, [small_int(eax).Value]
	push eax
	push eax
	call Riva$Memory$_alloc_atomic
	mov [esp], eax
	mov esi, [argument(edi).Val]
	mov ebx, [argument(edi + 8).Val]
	mov esi, [address(esi).Value]
	add esi, [small_int(ebx).Value]
	mov edi, eax
	mov ecx, [esp + 4]
	rep movsb
	push byte sizeof(string) + 2 * sizeof(string_block)
	call Riva$Memory$_alloc
	add esp, byte 4
	mov ecx, eax
	mov [value(ecx).Type], dword Std$String$T
	mov [value(string(ecx).Length).Type], dword Std$Integer$SmallT
	pop dword [address(string_block(string(ecx).Blocks).Chars).Value]
	pop eax
	mov [small_int(string(ecx).Length).Value], eax
	mov [small_int(string_block(string(ecx).Blocks).Length).Value], eax
	mov [string(ecx).Count], dword 1
	mov [value(string_block(string(ecx).Blocks).Length).Type], dword Std$Integer$SmallT
	mov [value(string_block(string(ecx).Blocks).Chars).Type], dword Std$Address$T
	xor edx, edx
	xor eax, eax
	ret

method "+", SMALLINT, ADDRESS
method "+", ADDRESS, SMALLINT
	mov eax, [argument(edi).Val]
	mov ebx, [argument(edi + 8).Val]
	mov eax, [eax + 4]
	add eax, [ebx + 4]
	push eax
	call Std$Address$_alloc
	mov ecx, eax
	pop dword [eax + 4]
	xor edx, edx
	xor eax, eax
	ret

method "-", ADDRESS, SMALLINT
	mov eax, [argument(edi).Val]
	mov ebx, [argument(edi + 8).Val]
	mov eax, [eax + 4]
	sub eax, [ebx + 4]
	push eax
	call Std$Address$_alloc
	mov ecx, eax
	pop dword [eax + 4]
	xor edx, edx
	xor eax, eax
	ret

method "-", ADDRESS, ADDRESS
	mov eax, [argument(edi).Val]
	mov ebx, [argument(edi + 8).Val]
	mov eax, [eax + 4]
	sub eax, [ebx + 4]
	push eax
	call Std$Integer$_alloc_small
	mov ecx, eax
	pop dword [eax + 4]
	xor edx, edx
	xor eax, eax
	ret

extern Std$String$_new
extern sprintf

method "@", ADDRESS, VAL, Std$String$T
	push byte 12
	call Riva$Memory$_alloc_atomic
	mov [esp], eax
	mov [eax], byte '#'
	inc eax
	mov ebx, [argument(edi).Val]
	push dword [address(ebx).Value]
	push .format
	push eax
	call sprintf
	add esp, byte 12
	call Std$String$_new
	add esp, byte 4
	mov ecx, eax
	xor edx, edx
	xor eax, eax
	ret
section .data
.format:
	db "%x", 0, 0

method "@", ANY, TYP, Std$Type$T
	mov ecx, [argument(edi).Val]
	mov edx, [argument(edi + 8).Val]
	mov eax, [value(ecx).Type]
	mov eax, [type(eax).Types]
.loop:
	cmp [eax], edx
	je .matched
	add eax, byte 4
	cmp [eax], dword 0
	jne .loop
	push byte sizeof(nomethod_message)
	call Riva$Memory$_alloc
	add esp, byte 4
	mov [value(eax).Type], dword Std$Symbol$NoMethodMessageT
	mov [nomethod_message(eax).Symbol], ebx
	mov ecx, eax
	xor edx, edx
	mov eax, 2
	ret
.matched:
	mov edx, [argument(edi).Ref]
	xor eax, eax
	ret

section .data
LESS: dd Std$Integer$SmallT, -1
ZERO:
EQUAL: dd Std$Integer$SmallT, 0
ONE:
GREATER: dd Std$Integer$SmallT, 1

method "?", ANY, ANY
	mov eax, [argument(edi).Val]
	mov ecx, [argument(edi + 8).Val]
	cmp eax, ecx
	je .equal
	mov eax, [value(eax).Type]
	cmp eax, [value(ecx).Type]
	jl .less
	jg .greater
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
.greater:
	mov ecx, GREATER
	xor edx, edx
	xor eax, eax
	ret

method "@", VAL, Std$Object$Nil, VAL, Std$String$T
	mov ecx, .nilstr
	xor edx, edx
	xor eax, eax
	ret
section .data
.nilstr:
	dd Std$String$T
	dd Std$Integer$SmallT
	dd 3, 1
	dd Std$Integer$SmallT, 3
	dd Std$Address$T, .nil
	dd 0, 0, 0, 0
.nil:
	db "NIL", 0

method "@", SYMBOL, VAL, Std$String$T
	mov edx, [argument(edi).Val]
	lea edx, [symbol(edx).Name]
	mov ecx, [edx]
	xor eax, eax
	ret

extern Std$String$Add
extern Std$String$Add.invoke
extern asprintf
method "@", TYP, Std$Symbol$NoMethodMessageT, VAL, Std$String$T
	mov edx, [argument(edi).Val]
	mov edx, [nomethod_message(edx).Symbol]
	push byte 0
	push dword [symbol(edx).Name]
	push byte 0
	push dword .messagestr
	mov edi, esp
	mov esi, 2
	mov ecx, Std$String$Add
	call Std$String$Add.invoke
	add esp, byte 16
	ret
section .data
.messagestr:
	dd Std$String$T
	dd Std$Integer$SmallT
	dd 3, 1
	dd Std$Integer$SmallT, 11
	dd Std$Address$T, .str
	dd 0, 0, 0, 0
.str:
	db "no method: ", 0

method "@", TYP, Std$Function$FewArgsMessageT, VAL, Std$String$T
	sub esp, byte 4
	mov edx, [argument(edi).Val]
	mov eax, esp
	push dword [fewargs_message(edx).Count]
	mov edx, [fewargs_message(edx).Func]
	push dword [checkedc_fun(edx).Count]
	push dword [checkedc_fun(edx).Line]
	push dword [checkedc_fun(edx).File]
	push dword .format
	push eax
	call asprintf
	add esp, byte 24
	call Std$String$_new
	add esp, byte 4
	mov ecx, eax
	xor edx, edx
	xor eax, eax
	ret
section .data
.format: db "%s:%d: expected %d args, received %d", 0

method "@", SMALLINT, VAL, Std$String$T
	push byte 10
	call Riva$Memory$_alloc_atomic
	mov [esp], eax
	mov ebx, [argument(edi).Val]
	push dword [small_int(ebx).Value]
	push dword .format
	push eax
	call sprintf
	add esp, byte 12
	call Std$String$_new
	add esp, byte 4
	mov ecx, eax
	xor edx, edx
	xor eax, eax
	ret
section .data
.format:
	db "%d", 0, 0

method "hex", SMALLINT
	push byte 10
	call Riva$Memory$_alloc_atomic
	mov [esp], eax
	mov ebx, [argument(edi).Val]
	push dword [small_int(ebx).Value]
	push dword .format
	push eax
	call sprintf
	add esp, byte 12
	call Std$String$_new
	add esp, byte 4
	mov ecx, eax
	xor edx, edx
	xor eax, eax
	ret
section .data
.format:
	db "%x", 0, 0

extern __gmpz_get_str

method "@", BIGINT, VAL, Std$String$T
	mov ebx, [argument(edi).Val]
	lea ebx, [big_int(ebx).Value]
	push ebx
	push 10
	push 0
	call __gmpz_get_str
	add esp, byte 12
	push eax
	call Std$String$_new
	add esp, byte 4
	mov ecx, eax
	xor edx, edx
	xor eax, eax
	ret

extern __gmpz_init_set_str
method "@", STRING, VAL, Std$Integer$T
	sub esp, byte 12
	mov ebx, esp
	mov eax, [argument(edi).Val]
	push byte 0
	sub esp, [small_int(string(eax).Length).Value]
	mov edi, esp
	lea eax, [string(eax).Blocks]
.copy:
	mov ecx, [small_int(string_block(eax).Length).Value]
	jecxz .done
	mov esi, [address(string_block(eax).Chars).Value]
	rep movsb
	add eax, byte sizeof(string_block)
	jmp .copy
.done:
	mov edx, esp
	push byte 10
	push edx
	push ebx
	call __gmpz_init_set_str
	test eax, eax
	js .failure
	mov esp, ebx
	jmp finish_integer
.failure:
	xor eax, eax
	lea esp, [ebx + 12]
	inc eax
	ret

extern atof
method "@", STRING, VAL, Std$Real$T
	mov ebx, esp
	mov eax, [argument(edi).Val]
	push byte 0
	sub esp, [small_int(string(eax).Length).Value]
	mov edi, esp
	lea eax, [string(eax).Blocks]
.copy:
	mov ecx, [small_int(string_block(eax).Length).Value]
	jecxz .done
	mov esi, [address(string_block(eax).Chars).Value]
	rep movsb
	add eax, byte sizeof(string_block)
	jmp .copy
.done:
	push esp
	call atof
	mov esp, ebx
	call Std$Real$_alloc
	fstp qword [real(eax).Value]
	mov ecx, eax
	xor eax, eax
	xor edx, edx
	ret

method "[]", TYP, Std$Array$T, SMALLINT
	mov eax, [argument(edi + 8).Val]
	mov eax, [small_int(eax).Value]
	mov ecx, [argument(edi).Val]
	mov edx, [array(ecx).Values]
	lea edx, [edx + 8 * eax]
	mov ecx, [edx]
	xor eax, eax
	ret

method "apply", TYP, Std$Array$T, TYP, Std$Function$T
	mov eax, [argument(edi).Val]
	mov ecx, [argument(edi + 8).Val]
	mov esi, [small_int(array(eax).Length).Value]
	mov edi, [array(eax).Values]
	mov eax, [value(ecx).Type]
	jmp [type(eax).Invoke]

method "apply", TYP, Std$Function$T, TYP, Std$Array$T
	mov eax, [argument(edi + 8).Val]
	mov ecx, [argument(edi).Val]
	mov esi, [small_int(array(eax).Length).Value]
	mov edi, [array(eax).Values]
	mov eax, [value(ecx).Type]
	jmp [type(eax).Invoke]

extern __gmpz_init_set_si
extern __gmpz_add_ui
extern __gmpz_sub_ui
extern __gmpz_mul_si

extern Std$Integer$_alloc_small
extern Std$Integer$_alloc_big

method "-", SMALLINT
	call Std$Integer$_alloc_small
	mov ecx, eax
	mov eax, [argument(edi).Val]
	mov eax, [small_int(eax).Value]
	neg eax
	mov [small_int(ecx).Value], eax
	xor edx, edx
	xor eax, eax
	ret

method "abs", SMALLINT
	call Std$Integer$_alloc_small
	mov ecx, eax
	mov eax, [argument(edi).Val]
	mov eax, [small_int(eax).Value]
	neg eax
	jns .done
	neg eax
.done:
	mov [small_int(ecx).Value], eax
	xor edx, edx
	xor eax, eax
	ret

method "+", SMALLINT, SMALLINT
add_small_small:
	mov eax, [argument(edi).Val]
	mov ebx, [argument(edi + 8).Val]
	mov eax, [small_int(eax).Value]
	add eax, [small_int(ebx).Value]
	jo .overflow
	push eax
	call Std$Integer$_alloc_small
	mov ecx, eax
	pop dword [small_int(ecx).Value]
	xor edx, edx
	xor eax, eax
	ret
.overflow:
	call Std$Integer$_alloc_big
	push eax
	lea esi, [big_int(eax).Value]
	mov eax, [argument(edi).Val]
	push dword [small_int(eax).Value]
	push esi
	call __gmpz_init_set_si
	mov eax, [argument(edi + 8).Val]
	mov eax, [small_int(eax).Value]
	neg eax
	jns sub_small_small.finish
	neg eax
.finish:
	push eax
	push esi
	push esi
	call __gmpz_add_ui
	add esp, byte 20
	pop ecx
	xor edx, edx
	xor eax, eax
	ret

method "-", SMALLINT, SMALLINT
sub_small_small:
	mov eax, [argument(edi).Val]
	mov ebx, [argument(edi + 8).Val]
	mov eax, [small_int(eax).Value]
	sub eax, [small_int(ebx).Value]
	jo .overflow
	push eax
	call Std$Integer$_alloc_small
	mov ecx, eax
	pop dword [small_int(ecx).Value]
	xor edx, edx
	xor eax, eax
	ret
.overflow:
	call Std$Integer$_alloc_big
	push eax
	lea esi, [big_int(eax).Value]
	mov eax, [argument(edi).Val]
	push dword [small_int(eax).Value]
	push esi
	call __gmpz_init_set_si
	mov eax, [argument(edi + 8).Val]
	mov eax, [small_int(eax).Value]
	neg eax
	jns add_small_small.finish
	neg eax
.finish:
	push eax
	push esi
	push esi
	call __gmpz_sub_ui
	add esp, byte 20
	pop ecx
	xor edx, edx
	xor eax, eax
	ret

method "*", SMALLINT, SMALLINT
	mov eax, [argument(edi).Val]
	mov ebx, [argument(edi + 8).Val]
	mov eax, [small_int(eax).Value]
	imul eax, [small_int(ebx).Value]
	jo .overflow
	push eax
	call Std$Integer$_alloc_small
	mov ecx, eax
	pop dword [small_int(ecx).Value]
	xor edx, edx
	xor eax, eax
	ret
.overflow:
	call Std$Integer$_alloc_big
	push eax
	lea esi, [big_int(eax).Value]
	mov eax, [argument(edi).Val]
	push dword [small_int(eax).Value]
	push esi
	call __gmpz_init_set_si
	mov eax, [argument(edi + 8).Val]
	mov eax, [small_int(eax).Value]
	push eax
	push esi
	push esi
	call __gmpz_mul_si
	add esp, byte 20
	pop ecx
	xor edx, edx
	xor eax, eax
	ret

method "/", SMALLINT, SMALLINT
	call Std$Integer$_alloc_small
	mov ecx, eax
	mov eax, [argument(edi).Val]
	mov ebx, [argument(edi + 8).Val]
	mov eax, [small_int(eax).Value]
	cdq
	idiv dword [small_int(ebx).Value]
	mov [small_int(ecx).Value], eax
	xor edx, edx
	xor eax, eax
	ret

method "%", SMALLINT, SMALLINT
	call Std$Integer$_alloc_small
	mov ecx, eax
	mov eax, [argument(edi).Val]
	mov ebx, [argument(edi + 8).Val]
	mov eax, [small_int(eax).Value]
	cdq
	idiv dword [small_int(ebx).Value]
	mov [small_int(ecx).Value], edx
	xor edx, edx
	xor eax, eax
	ret

method "~", SMALLINT
	call Std$Integer$_alloc_small
	mov ecx, eax
	mov eax, [argument(edi).Val]
	mov eax, [small_int(eax).Value]
	not eax
	mov [small_int(ecx).Value], eax
	xor edx, edx
	xor eax, eax
	ret

method "and", SMALLINT, SMALLINT
	call Std$Integer$_alloc_small
	mov ecx, eax
	mov eax, [argument(edi).Val]
	mov ebx, [argument(edi + 8).Val]
	mov eax, [small_int(eax).Value]
	and eax, [small_int(ebx).Value]
	mov [small_int(ecx).Value], eax
	xor edx, edx
	xor eax, eax
	ret

method "or", SMALLINT, SMALLINT
	call Std$Integer$_alloc_small
	mov ecx, eax
	mov eax, [argument(edi).Val]
	mov ebx, [argument(edi + 8).Val]
	mov eax, [small_int(eax).Value]
	or eax, [small_int(ebx).Value]
	mov [small_int(ecx).Value], eax
	xor edx, edx
	xor eax, eax
	ret

method "xor", SMALLINT, SMALLINT
	call Std$Integer$_alloc_small
	mov ecx, eax
	mov eax, [argument(edi).Val]
	mov ebx, [argument(edi + 8).Val]
	mov eax, [small_int(eax).Value]
	xor eax, [small_int(ebx).Value]
	mov [small_int(ecx).Value], eax
	xor edx, edx
	xor eax, eax
	ret

method "sar", SMALLINT, SMALLINT
sar_small_small:
	mov eax, [argument(edi).Val]
	mov ebx, [argument(edi + 8).Val]
	mov eax, [small_int(eax).Value]
	mov ecx, [small_int(ebx).Value]
	neg ecx
	jz .noshift
	jns sal_small_small.run
	neg ecx
.run:
	sar eax, cl
	jz .zero
	push eax
	call Std$Integer$_alloc_small
	mov ecx, eax
	pop dword [small_int(eax).Value]
	xor edx, edx
	xor eax, eax
	ret
.noshift:
	mov ecx, [argument(edi).Val]
	xor edx, edx
	xor eax, eax
	ret
.zero:
	mov ecx, ZERO
	xor edx, edx
	xor eax, eax
	ret

extern __gmpz_mul_2exp
method "sal", SMALLINT, SMALLINT
sal_small_small:
	mov eax, [argument(edi).Val]
	mov ebx, [argument(edi + 8).Val]
	mov eax, [small_int(eax).Value]
	test eax, eax
	jz sar_small_small.zero
	mov ecx, [small_int(ebx).Value]
	neg ecx
	jz .noshift
	jns sar_small_small.run
	neg ecx
.run:
	cmp ecx, 32
	jae .overflow
.loop:
	add eax, eax
	jo .overflow
	dec ecx
	jnz .loop
	push eax
	call Std$Integer$_alloc_small
	mov ecx, eax
	pop dword [small_int(ecx).Value]
	xor edx, edx
	xor eax, eax
	ret
.noshift:
	mov ecx, [argument(edi).Val]
	xor edx, edx
	xor eax, eax
	ret
.overflow:
	call Std$Integer$_alloc_big
	push eax
	lea esi, [big_int(eax).Value]
	mov eax, [argument(edi).Val]
	push dword [small_int(eax).Value]
	push esi
	call __gmpz_init_set_si
	mov eax, [argument(edi + 8).Val]
	mov eax, [small_int(eax).Value]
	push eax
	push esi
	push esi
	call __gmpz_mul_2exp
	add esp, byte 20
	pop ecx
	xor edx, edx
	xor eax, eax
	ret

method "shl", SMALLINT, SMALLINT
	call Std$Integer$_alloc_small
	push eax
	mov eax, [argument(edi).Val]
	mov ebx, [argument(edi + 8).Val]
	mov eax, [small_int(eax).Value]
	mov ecx, [small_int(ebx).Value]
	shl eax, cl
	pop ecx
	mov [small_int(ecx).Value], eax
	xor edx, edx
	xor eax, eax
	ret

method "shr", SMALLINT, SMALLINT
	call Std$Integer$_alloc_small
	push eax
	mov eax, [argument(edi).Val]
	mov ebx, [argument(edi + 8).Val]
	mov eax, [small_int(eax).Value]
	mov ecx, [small_int(ebx).Value]
	shr eax, cl
	pop ecx
	mov [small_int(ecx).Value], eax
	xor edx, edx
	xor eax, eax
	ret

method "rol", SMALLINT, SMALLINT
	call Std$Integer$_alloc_small
	push eax
	mov eax, [argument(edi).Val]
	mov ebx, [argument(edi + 8).Val]
	mov eax, [small_int(eax).Value]
	mov ecx, [small_int(ebx).Value]
	rol eax, cl
	pop ecx
	mov [small_int(ecx).Value], eax
	xor edx, edx
	xor eax, eax
	ret

method "ror", SMALLINT, SMALLINT
	call Std$Integer$_alloc_small
	push eax
	mov eax, [argument(edi).Val]
	mov ebx, [argument(edi + 8).Val]
	mov eax, [small_int(eax).Value]
	mov ecx, [small_int(ebx).Value]
	ror eax, cl
	pop ecx
	mov [small_int(ecx).Value], eax
	xor edx, edx
	xor eax, eax
	ret

extern __gmpz_pow_ui
method "^", SMALLINT, SMALLINT
	sub esp, byte 12
	mov ebx, esp
	mov eax, [argument(edi).Val]
	push dword [small_int(eax).Value]
	push ebx
	call __gmpz_init_set_si
	add esp, byte 8
	mov eax, [argument(edi + 8).Val]
	push dword [small_int(eax).Value]
	push ebx
	push ebx
	call __gmpz_pow_ui
	add esp, byte 12
	jmp finish_integer

method "<", ADDRESS, ADDRESS
method "<", SMALLINT, SMALLINT
	mov eax, [argument(edi).Val]
	mov ecx, [argument(edi + 8).Val]
	mov eax, [small_int(eax).Value]
	cmp eax, [small_int(ecx).Value]
	jge .fail
	mov edx, [argument(edi + 8).Ref]
	xor eax, eax
	ret
.fail:
	xor eax, eax
	inc eax
	ret

method ">", ADDRESS, ADDRESS
method ">", SMALLINT, SMALLINT
	mov eax, [argument(edi).Val]
	mov ecx, [argument(edi + 8).Val]
	mov eax, [small_int(eax).Value]
	cmp eax, [small_int(ecx).Value]
	jle .fail
	mov edx, [argument(edi + 8).Ref]
	xor eax, eax
	ret
.fail:
	xor eax, eax
	inc eax
	ret

method "=", ADDRESS, ADDRESS
method "=", SMALLINT, SMALLINT
	mov eax, [argument(edi).Val]
	mov ecx, [argument(edi + 8).Val]
	mov eax, [small_int(eax).Value]
	cmp eax, [small_int(ecx).Value]
	jne .fail
	mov edx, [argument(edi + 8).Ref]
	xor eax, eax
	ret
.fail:
	xor eax, eax
	inc eax
	ret

method "~=", ADDRESS, ADDRESS
method "~=", SMALLINT, SMALLINT
	mov eax, [argument(edi).Val]
	mov ecx, [argument(edi + 8).Val]
	mov eax, [small_int(eax).Value]
	cmp eax, [small_int(ecx).Value]
	je .fail
	mov edx, [argument(edi + 8).Ref]
	xor eax, eax
	ret
.fail:
	xor eax, eax
	inc eax
	ret

method "<=", ADDRESS, ADDRESS
method "<=", SMALLINT, SMALLINT
	mov eax, [argument(edi).Val]
	mov ecx, [argument(edi + 8).Val]
	mov eax, [small_int(eax).Value]
	cmp eax, [small_int(ecx).Value]
	jg .fail
	mov edx, [argument(edi + 8).Ref]
	xor eax, eax
	ret
.fail:
	xor eax, eax
	inc eax
	ret

method ">=", ADDRESS, ADDRESS
method ">=", SMALLINT, SMALLINT
	mov eax, [argument(edi).Val]
	mov ecx, [argument(edi + 8).Val]
	mov eax, [small_int(eax).Value]
	cmp eax, [small_int(ecx).Value]
	jl .fail
	mov edx, [argument(edi + 8).Ref]
	xor eax, eax
	ret
.fail:
	xor eax, eax
	inc eax
	ret

method "?", ADDRESS, ADDRESS
method "?", SMALLINT, SMALLINT
	mov eax, [argument(edi).Val]
	mov ecx, [argument(edi + 8).Val]
	mov eax, [small_int(eax).Value]
	cmp eax, [small_int(ecx).Value]
	jl .less
	jg .greater
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
.greater:
	mov ecx, GREATER
	xor edx, edx
	xor eax, eax
	ret

method "in", SMALLINT, SMALLINT
	mov ecx, [argument(edi).Val]
	mov eax, [argument(edi + 8).Val]
	mov ecx, [small_int(ecx).Value]
	mov eax, [small_int(eax).Value]
	cmp ecx, byte 32
	jae .failure
	xor edx, edx
	inc edx
	shl edx, cl
	and edx, eax
	jz .failure
	mov ecx, [argument(edi).Val]
	mov edx, [argument(edi).Ref]
	xor eax, eax
	ret
.failure:
	mov eax, 1
	ret

extern __gmpz_init

extern __gmpz_neg
method "-", BIGINT
	sub esp, byte 12
	push esp
	call __gmpz_init
	add esp, byte 4
	mov ebx, esp
	mov eax, [argument(edi).Val]
	lea eax, [big_int(eax).Value]
	push eax
	push ebx
	call __gmpz_neg
	add esp, byte 8
	jmp finish_integer

extern __gmpz_abs
method "abs", BIGINT
	sub esp, byte 12
	push esp
	call __gmpz_init
	add esp, byte 4
	mov ebx, esp
	mov eax, [argument(edi).Val]
	lea eax, [big_int(eax).Value]
	push eax
	push ebx
	call __gmpz_abs
	add esp, byte 8
	jmp finish_integer

extern __gmpz_com
method "~", BIGINT
	sub esp, byte 12
	push esp
	call __gmpz_init
	add esp, byte 4
	mov ebx, esp
	mov eax, [argument(edi).Val]
	lea eax, [big_int(eax).Value]
	push eax
	push ebx
	call __gmpz_com
	add esp, byte 8
	jmp finish_integer

extern __gmpz_add
method "+", BIGINT, BIGINT
	sub esp, byte 12
	push esp
	call __gmpz_init
	add esp, byte 4
	mov ebx, esp
	mov eax, [argument(edi + 8).Val]
	lea eax, [big_int(eax).Value]
	push eax
	mov eax, [argument(edi).Val]
	lea eax, [big_int(eax).Value]
	push eax
	push ebx
	call __gmpz_add
	add esp, byte 12
	jmp finish_integer

extern __gmpz_sub
method "-", BIGINT, BIGINT
	sub esp, byte 12
	push esp
	call __gmpz_init
	add esp, byte 4
	mov ebx, esp
	mov eax, [argument(edi + 8).Val]
	lea eax, [big_int(eax).Value]
	push eax
	mov eax, [argument(edi).Val]
	lea eax, [big_int(eax).Value]
	push eax
	push ebx
	call __gmpz_sub
	add esp, byte 12
	jmp finish_integer

extern __gmpz_mul
method "*", BIGINT, BIGINT
	sub esp, byte 12
	push esp
	call __gmpz_init
	add esp, byte 4
	mov ebx, esp
	mov eax, [argument(edi + 8).Val]
	lea eax, [big_int(eax).Value]
	push eax
	mov eax, [argument(edi).Val]
	lea eax, [big_int(eax).Value]
	push eax
	push ebx
	call __gmpz_mul
	add esp, byte 12
	jmp finish_integer

extern __gmpz_tdiv_q
method "/", BIGINT, BIGINT
	sub esp, byte 12
	push esp
	call __gmpz_init
	add esp, byte 4
	mov ebx, esp
	mov eax, [argument(edi + 8).Val]
	lea eax, [big_int(eax).Value]
	push eax
	mov eax, [argument(edi).Val]
	lea eax, [big_int(eax).Value]
	push eax
	push ebx
	call __gmpz_tdiv_q
	add esp, byte 12
	jmp finish_integer

extern __gmpz_mod
method "%", BIGINT, BIGINT
	sub esp, byte 12
	push esp
	call __gmpz_init
	add esp, byte 4
	mov ebx, esp
	mov eax, [argument(edi + 8).Val]
	lea eax, [big_int(eax).Value]
	push eax
	mov eax, [argument(edi).Val]
	lea eax, [big_int(eax).Value]
	push eax
	push ebx
	call __gmpz_mod
	add esp, byte 12
	call Std$Integer$_alloc_big
	pop dword [eax + 4]
	pop dword [eax + 8]
	pop dword [eax + 12]
	mov ecx, eax
	xor edx, edx
	xor eax, eax
	ret

extern __gmpz_cmp
method "<", BIGINT, BIGINT
	mov eax, [argument(edi + 8).Val]
	lea eax, [big_int(eax).Value]
	push eax
	mov eax, [argument(edi).Val]
	lea eax, [big_int(eax).Value]
	push eax
	call __gmpz_cmp
	add esp, byte 8
	cmp eax, byte 0
	jge .fail
	mov ecx, [argument(edi + 8).Val]
	mov edx, [argument(edi + 8).Ref]
	xor eax, eax
	ret
.fail:
	xor eax, eax
	inc eax
	ret

method ">", BIGINT, BIGINT
	mov eax, [argument(edi + 8).Val]
	lea eax, [big_int(eax).Value]
	push eax
	mov eax, [argument(edi).Val]
	lea eax, [big_int(eax).Value]
	push eax
	call __gmpz_cmp
	add esp, byte 8
	cmp eax, byte 0
	jle .fail
	mov ecx, [argument(edi + 8).Val]
	mov edx, [argument(edi + 8).Ref]
	xor eax, eax
	ret
.fail:
	xor eax, eax
	inc eax
	ret

method ">=", BIGINT, BIGINT
	mov eax, [argument(edi + 8).Val]
	lea eax, [big_int(eax).Value]
	push eax
	mov eax, [argument(edi).Val]
	lea eax, [big_int(eax).Value]
	push eax
	call __gmpz_cmp
	add esp, byte 8
	cmp eax, byte 0
	jl .fail
	mov ecx, [argument(edi + 8).Val]
	mov edx, [argument(edi + 8).Ref]
	xor eax, eax
	ret
.fail:
	xor eax, eax
	inc eax
	ret

method "<=", BIGINT, BIGINT
	mov eax, [argument(edi + 8).Val]
	lea eax, [big_int(eax).Value]
	push eax
	mov eax, [argument(edi).Val]
	lea eax, [big_int(eax).Value]
	push eax
	call __gmpz_cmp
	add esp, byte 8
	cmp eax, byte 0
	jg .fail
	mov ecx, [argument(edi + 8).Val]
	mov edx, [argument(edi + 8).Ref]
	xor eax, eax
	ret
.fail:
	xor eax, eax
	inc eax
	ret

method "=", BIGINT, BIGINT
	mov eax, [argument(edi + 8).Val]
	lea eax, [big_int(eax).Value]
	push eax
	mov eax, [argument(edi).Val]
	lea eax, [big_int(eax).Value]
	push eax
	call __gmpz_cmp
	add esp, byte 8
	cmp eax, byte 0
	jne .fail
	mov ecx, [argument(edi + 8).Val]
	mov edx, [argument(edi + 8).Ref]
	xor eax, eax
	ret
.fail:
	xor eax, eax
	inc eax
	ret

method "~=", BIGINT, BIGINT
	mov eax, [argument(edi + 8).Val]
	lea eax, [big_int(eax).Value]
	push eax
	mov eax, [argument(edi).Val]
	lea eax, [big_int(eax).Value]
	push eax
	call __gmpz_cmp
	add esp, byte 8
	cmp eax, byte 0
	je .fail
	mov ecx, [argument(edi + 8).Val]
	mov edx, [argument(edi + 8).Ref]
	xor eax, eax
	ret
.fail:
	xor eax, eax
	inc eax
	ret

method "?", BIGINT, BIGINT
	mov eax, [argument(edi + 8).Val]
	lea eax, [big_int(eax).Value]
	push eax
	mov eax, [argument(edi).Val]
	lea eax, [big_int(eax).Value]
	push eax
	call __gmpz_cmp
	add esp, byte 8
	cmp eax, byte 0
	jl .less
	jg .greater
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
.greater:
	mov ecx, GREATER
	xor edx, edx
	xor eax, eax
	ret

extern __gmpz_add_ui
method "+", BIGINT, SMALLINT
add_big_small:
	sub esp, byte 12
	push esp
	call __gmpz_init
	add esp, byte 4
	mov ebx, esp
	mov eax, [argument(edi + 8).Val]
	mov eax, [small_int(eax).Value]
	neg eax
	jns sub_big_small.finish
	neg eax
.finish:
	push eax
	mov eax, [argument(edi).Val]
	lea eax, [big_int(eax).Value]
	push eax
	push ebx
	call __gmpz_add_ui
	add esp, byte 12
	jmp finish_integer

extern __gmpz_sub_ui
method "-", BIGINT, SMALLINT
sub_big_small:
	sub esp, byte 12
	push esp
	call __gmpz_init
	add esp, byte 4
	mov ebx, esp
	mov eax, [argument(edi + 8).Val]
	mov eax, [small_int(eax).Value]
	neg eax
	jns add_big_small.finish
	neg eax
.finish:
	push eax
	mov eax, [argument(edi).Val]
	lea eax, [big_int(eax).Value]
	push eax
	push ebx
	call __gmpz_sub_ui
	add esp, byte 12
	jmp finish_integer

extern __gmpz_mul_si
method "*", BIGINT, SMALLINT
	sub esp, byte 12
	push esp
	call __gmpz_init
	add esp, byte 4
	mov ebx, esp
	mov eax, [argument(edi + 8).Val]
	push dword [small_int(eax).Value]
	mov eax, [argument(edi).Val]
	lea eax, [big_int(eax).Value]
	push eax
	push ebx
	call __gmpz_mul_si
	add esp, byte 12
	jmp finish_integer

extern __gmpz_tdiv_q_ui
extern __gmpz_neg
method "/", BIGINT, SMALLINT
	sub esp, byte 12
	push esp
	call __gmpz_init
	add esp, byte 4
	mov ebx, esp
	mov eax, [argument(edi + 8).Val]
	mov eax, [small_int(eax).Value]
	neg eax
	jns .negative
	neg eax
	push eax
	mov eax, [argument(edi).Val]
	lea eax, [big_int(eax).Value]
	push eax
	push ebx
	call __gmpz_tdiv_q_ui
	add esp, byte 12
	jmp finish_integer
.negative:
	push eax
	mov eax, [argument(edi).Val]
	lea eax, [big_int(eax).Value]
	push eax
	push ebx
	call __gmpz_tdiv_q_ui
	add esp, byte 12
	mov eax, esp
	push eax
	push eax
	call __gmpz_neg
	add esp, byte 12
	jmp finish_integer

extern __gmpz_fdiv_ui
method "%", BIGINT, SMALLINT
	mov ebx, esp
	mov eax, [argument(edi + 8).Val]
	push dword [small_int(eax).Value]
	mov eax, [argument(edi).Val]
	lea eax, [big_int(eax).Value]
	push eax
	call __gmpz_fdiv_ui
	add esp, byte 8
	push eax
	call Std$Integer$_alloc_small
	pop dword [small_int(eax).Value]
	mov ecx, eax
	xor edx, edx
	xor eax, eax
	ret

extern __gmpz_mul_2exp
method "sal", BIGINT, SMALLINT
sal_big_small:
	sub esp, byte 12
	push esp
	call __gmpz_init
	add esp, byte 4
	mov ebx, esp
	mov eax, [argument(edi + 8).Val]
	mov ecx, [small_int(eax).Value]
	neg ecx
	jns sar_big_small.finish
	neg ecx
.finish:
	push ecx
	mov eax, [argument(edi).Val]
	lea eax, [big_int(eax).Value]
	push eax
	push ebx
	call __gmpz_mul_2exp
	add esp, byte 12
	jmp finish_integer

extern __gmpz_tdiv_q_2exp
method "sar", BIGINT, SMALLINT
sar_big_small:
	sub esp, byte 12
	push esp
	call __gmpz_init
	add esp, byte 4
	mov ebx, esp
	mov eax, [argument(edi + 8).Val]
	mov ecx, [small_int(eax).Value]
	neg ecx
	jns sal_big_small.finish
	neg ecx
.finish:
	push ecx
	mov eax, [argument(edi).Val]
	lea eax, [big_int(eax).Value]
	push eax
	push ebx
	call __gmpz_tdiv_q_2exp
	add esp, byte 12
	jmp finish_integer

extern __gmpz_mul_2exp
method "shl", BIGINT, SMALLINT
shl_big_small:
	sub esp, byte 12
	push esp
	call __gmpz_init
	add esp, byte 4
	mov ebx, esp
	mov eax, [argument(edi + 8).Val]
	mov ecx, [small_int(eax).Value]
	neg ecx
	js shr_big_small.finish
	neg ecx
.finish:
	push ecx
	mov eax, [argument(edi).Val]
	lea eax, [big_int(eax).Value]
	push eax
	push ebx
	call __gmpz_mul_2exp
	add esp, byte 12
	jmp finish_integer

extern __gmpz_fdiv_q_2exp
method "shr", BIGINT, SMALLINT
shr_big_small:
	sub esp, byte 12
	push esp
	call __gmpz_init
	add esp, byte 4
	mov ebx, esp
	mov eax, [argument(edi + 8).Val]
	mov ecx, [small_int(eax).Value]
	neg ecx
	js shl_big_small.finish
	neg ecx
.finish:
	push ecx
	mov eax, [argument(edi).Val]
	lea eax, [big_int(eax).Value]
	push eax
	push ebx
	call __gmpz_fdiv_q_2exp
	add esp, byte 12
	jmp finish_integer

extern __gmpz_pow_ui
method "^", BIGINT, SMALLINT
	sub esp, byte 12
	push esp
	call __gmpz_init
	add esp, byte 4
	mov ebx, esp
	mov eax, [argument(edi + 8).Val]
	push dword [small_int(eax).Value]
	mov eax, [argument(edi).Val]
	lea eax, [big_int(eax).Value]
	push eax
	push ebx
	call __gmpz_pow_ui
	add esp, byte 12
	jmp finish_integer

extern __gmpz_cmp_si
method "<", BIGINT, SMALLINT
	mov eax, [argument(edi + 8).Val]
	push dword [small_int(eax).Value]
	mov eax, [argument(edi).Val]
	lea eax, [big_int(eax).Value]
	push eax
	call __gmpz_cmp_si
	add esp, byte 8
	cmp eax, byte 0
	jge .fail
	mov ecx, [argument(edi + 8).Val]
	mov edx, [argument(edi + 8).Ref]
	xor eax, eax
	ret
.fail:
	xor eax, eax
	inc eax
	ret

method ">", BIGINT, SMALLINT
	mov eax, [argument(edi + 8).Val]
	push dword [small_int(eax).Value]
	mov eax, [argument(edi).Val]
	lea eax, [big_int(eax).Value]
	push eax
	call __gmpz_cmp_si
	add esp, byte 8
	cmp eax, byte 0
	jle .fail
	mov ecx, [argument(edi + 8).Val]
	mov edx, [argument(edi + 8).Ref]
	xor eax, eax
	ret
.fail:
	xor eax, eax
	inc eax
	ret

method ">=", BIGINT, SMALLINT
	mov eax, [argument(edi + 8).Val]
	push dword [small_int(eax).Value]
	mov eax, [argument(edi).Val]
	lea eax, [big_int(eax).Value]
	push eax
	call __gmpz_cmp_si
	add esp, byte 8
	cmp eax, byte 0
	jl .fail
	mov ecx, [argument(edi + 8).Val]
	mov edx, [argument(edi + 8).Ref]
	xor eax, eax
	ret
.fail:
	xor eax, eax
	inc eax
	ret

method "<=", BIGINT, SMALLINT
	mov eax, [argument(edi + 8).Val]
	push dword [small_int(eax).Value]
	mov eax, [argument(edi).Val]
	lea eax, [big_int(eax).Value]
	push eax
	call __gmpz_cmp_si
	add esp, byte 8
	cmp eax, byte 0
	jg .fail
	mov ecx, [argument(edi + 8).Val]
	mov edx, [argument(edi + 8).Ref]
	xor eax, eax
	ret
.fail:
	xor eax, eax
	inc eax
	ret

method "=", BIGINT, SMALLINT
	mov eax, [argument(edi + 8).Val]
	push dword [small_int(eax).Value]
	mov eax, [argument(edi).Val]
	lea eax, [big_int(eax).Value]
	push eax
	call __gmpz_cmp_si
	add esp, byte 8
	cmp eax, byte 0
	jne .fail
	mov ecx, [argument(edi + 8).Val]
	mov edx, [argument(edi + 8).Ref]
	xor eax, eax
	ret
.fail:
	xor eax, eax
	inc eax
	ret

method "~=", BIGINT, SMALLINT
	mov eax, [argument(edi + 8).Val]
	push dword [small_int(eax).Value]
	mov eax, [argument(edi).Val]
	lea eax, [big_int(eax).Value]
	push eax
	call __gmpz_cmp_si
	add esp, byte 8
	cmp eax, byte 0
	je .fail
	mov ecx, [argument(edi + 8).Val]
	mov edx, [argument(edi + 8).Ref]
	xor eax, eax
	ret
.fail:
	xor eax, eax
	inc eax
	ret

method "?", BIGINT, SMALLINT
	mov eax, [argument(edi + 8).Val]
	push dword [small_int(eax).Value]
	mov eax, [argument(edi).Val]
	lea eax, [big_int(eax).Value]
	push eax
	call __gmpz_cmp_si
	add esp, byte 8
	cmp eax, byte 0
	jl .less
	jg .greater
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
.greater:
	mov ecx, GREATER
	xor edx, edx
	xor eax, eax
	ret

method "+", SMALLINT, BIGINT
add_small_big:
	sub esp, byte 12
	push esp
	call __gmpz_init
	add esp, byte 4
	mov ebx, esp
	mov eax, [argument(edi).Val]
	mov eax, [small_int(eax).Value]
	neg eax
	jns .negative
	neg eax
	push eax
	mov eax, [argument(edi + 8).Val]
	lea eax, [big_int(eax).Value]
	push eax
	push ebx
	call __gmpz_add_ui
	add esp, byte 12
	jmp finish_integer
.negative:
	push eax
	mov eax, [argument(edi + 8).Val]
	lea eax, [big_int(eax).Value]
	push eax
	push ebx
	call __gmpz_sub_ui
	add esp, byte 12
	jmp finish_integer

method "-", SMALLINT, BIGINT
	sub esp, byte 12
	push esp
	call __gmpz_init
	add esp, byte 4
	mov ebx, esp
	mov eax, [argument(edi).Val]
	mov eax, [small_int(eax).Value]
	neg eax
	jns .negative
	neg eax
	push eax
	mov eax, [argument(edi + 8).Val]
	lea eax, [big_int(eax).Value]
	push eax
	push ebx
	call __gmpz_sub_ui
	add esp, byte 12
	mov eax, esp
	push eax
	push eax
	call __gmpz_neg
	add esp, byte 8
	jmp finish_integer
.negative:
	push eax
	mov eax, [argument(edi + 8).Val]
	lea eax, [big_int(eax).Value]
	push eax
	push ebx
	call __gmpz_add_ui
	add esp, byte 12
	mov eax, esp
	push eax
	push eax
	call __gmpz_neg
	add esp, byte 8
	jmp finish_integer

extern __gmpz_mul_si
method "*", SMALLINT, BIGINT
	sub esp, byte 12
	push esp
	call __gmpz_init
	add esp, byte 4
	mov ebx, esp
	mov eax, [argument(edi).Val]
	push dword [small_int(eax).Value]
	mov eax, [argument(edi + 8).Val]
	lea eax, [big_int(eax).Value]
	push eax
	push ebx
	call __gmpz_mul_si
	add esp, byte 12
	jmp finish_integer

method "/", SMALLINT, BIGINT
section .data
	mov ecx, .zero
	xor edx, edx
	xor eax, eax
	ret
.zero:
	dd Std$Integer$SmallT
	dd 0

method "%", SMALLINT, BIGINT
	mov ecx, [argument(edi).Val]
	mov eax, [small_int(ecx).Value]
	test eax, eax
	js add_small_big
	xor edx, edx
	xor eax, eax
	ret

method "<", SMALLINT, BIGINT
	mov eax, [argument(edi).Val]
	push dword [small_int(eax).Value]
	mov eax, [argument(edi + 8).Val]
	lea eax, [big_int(eax).Value]
	push eax
	call __gmpz_cmp_si
	add esp, byte 8
	cmp eax, byte 0
	jl .fail
	mov ecx, [argument(edi + 8).Val]
	mov edx, [argument(edi + 8).Ref]
	xor eax, eax
	ret
.fail:
	xor eax, eax
	inc eax
	ret

method ">", SMALLINT, BIGINT
	mov eax, [argument(edi).Val]
	push dword [small_int(eax).Value]
	mov eax, [argument(edi + 8).Val]
	lea eax, [big_int(eax).Value]
	push eax
	call __gmpz_cmp_si
	add esp, byte 8
	cmp eax, byte 0
	jg .fail
	mov ecx, [argument(edi + 8).Val]
	mov edx, [argument(edi + 8).Ref]
	xor eax, eax
	ret
.fail:
	xor eax, eax
	inc eax
	ret

method ">=", SMALLINT, BIGINT
	mov eax, [argument(edi).Val]
	push dword [small_int(eax).Value]
	mov eax, [argument(edi + 8).Val]
	lea eax, [big_int(eax).Value]
	push eax
	call __gmpz_cmp_si
	add esp, byte 8
	cmp eax, byte 0
	jge .fail
	mov ecx, [argument(edi + 8).Val]
	mov edx, [argument(edi + 8).Ref]
	xor eax, eax
	ret
.fail:
	xor eax, eax
	inc eax
	ret

method "<=", SMALLINT, BIGINT
	mov eax, [argument(edi).Val]
	push dword [small_int(eax).Value]
	mov eax, [argument(edi + 8).Val]
	lea eax, [big_int(eax).Value]
	push eax
	call __gmpz_cmp_si
	add esp, byte 8
	cmp eax, byte 0
	jle .fail
	mov ecx, [argument(edi + 8).Val]
	mov edx, [argument(edi + 8).Ref]
	xor eax, eax
	ret
.fail:
	xor eax, eax
	inc eax
	ret

method "=", SMALLINT, BIGINT
	mov eax, [argument(edi).Val]
	push dword [small_int(eax).Value]
	mov eax, [argument(edi + 8).Val]
	lea eax, [big_int(eax).Value]
	push eax
	call __gmpz_cmp_si
	add esp, byte 8
	cmp eax, byte 0
	jne .fail
	mov ecx, [argument(edi + 8).Val]
	mov edx, [argument(edi + 8).Ref]
	xor eax, eax
	ret
.fail:
	xor eax, eax
	inc eax
	ret

method "~=", SMALLINT, BIGINT
	mov eax, [argument(edi).Val]
	push dword [small_int(eax).Value]
	mov eax, [argument(edi + 8).Val]
	lea eax, [big_int(eax).Value]
	push eax
	call __gmpz_cmp_si
	add esp, byte 8
	cmp eax, byte 0
	je .fail
	mov ecx, [argument(edi + 8).Val]
	mov edx, [argument(edi + 8).Ref]
	xor eax, eax
	ret
.fail:
	xor eax, eax
	inc eax
	ret

method "?", SMALLINT, BIGINT
	mov eax, [argument(edi).Val]
	push dword [small_int(eax).Value]
	mov eax, [argument(edi + 8).Val]
	lea eax, [big_int(eax).Value]
	push eax
	call __gmpz_cmp_si
	add esp, byte 8
	cmp eax, byte 0
	jg .less
	jl .greater
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
.greater:
	mov ecx, GREATER
	xor edx, edx
	xor eax, eax
	ret

extern __gmpz_tstbit
method "in", SMALLINT, BIGINT
	mov eax, [argument(edi).Val]
	push dword [small_int(eax).Value]
	mov eax, [argument(edi + 8).Val]
	lea eax, [big_int(eax).Value]
	push eax
	call __gmpz_tstbit
	add esp, byte 8
	cmp eax, byte 0
	je .fail
	mov ecx, [argument(edi).Val]
	mov edx, [argument(edi).Ref]
	xor eax, eax
	ret
.fail:
	xor eax, eax
	inc eax
	ret

extern __gmpz_fits_slong_p
extern __gmpz_get_si
finish_integer:
	push esp
	call __gmpz_fits_slong_p
	add esp, byte 4
	test eax, eax
	jnz .convert_to_small
	call Std$Integer$_alloc_big
	pop dword [eax + 4]
	pop dword [eax + 8]
	pop dword [eax + 12]
	mov ecx, eax
	xor edx, edx
	xor eax, eax
	ret
.convert_to_small
	push esp
	call __gmpz_get_si
	add esp, byte 16
	push eax
	call Std$Integer$_alloc_small
	pop dword [small_int(eax).Value]
	mov ecx, eax
	xor edx, edx
	xor eax, eax
	ret

struct repeat_value_state, state
	.Value:	resd 1
endstruct

c_func resume_repeat_value
	mov ecx, [repeat_value_state(eax).Value]
	mov ebx, eax
	or eax, byte -1
	xor edx, edx
	ret

extern Std$Integer$ToSmallSmall
_method "to", Std$Integer$ToSmallSmall, SMALLINT, SMALLINT

struct to_small_small_small_state, state
	.Current:	resd 1
	.Limit:		resd 1
	.Increment:	resd 1
endstruct

method "to", SMALLINT, SMALLINT, SMALLINT
	mov ebx, [argument(edi + 16).Val]
	mov ebx, [small_int(ebx).Value]
	test ebx, ebx
	js near downto_small_small_small
	jz near repeat_small
	mov eax, [argument(edi + 8).Val]
	mov ecx, [argument(edi).Val]
	mov eax, [small_int(eax).Value]
	cmp eax, [small_int(ecx).Value]
	jl .fail
	je .return
.suspend:
	push ecx
	push ebx
	push eax
	push dword [small_int(ecx).Value]
	push byte sizeof(to_small_small_small_state)
	call Riva$Memory$_alloc
	add esp, byte 4
	pop dword [to_small_small_small_state(eax).Current]
	pop dword [to_small_small_small_state(eax).Limit]
	pop dword [to_small_small_small_state(eax).Increment]
	mov dword [state(eax).Run], .resume
	pop ecx
	mov ebx, eax
	or eax, byte -1
	xor edx, edx
	ret
.return:
	xor edx, edx
	xor eax, eax
	ret
.fail:
	xor eax, eax
	inc eax
	ret
.resume:
	mov ecx, [to_small_small_small_state(eax).Current]
	add ecx, [to_small_small_small_state(eax).Increment]
	cmp ecx, [to_small_small_small_state(eax).Limit]
	jg .fail
	je .return2
	mov [to_small_small_small_state(eax).Current], ecx
	push eax
	push ecx
	call Std$Integer$_alloc_small
	mov ecx, eax
	pop dword [small_int(ecx).Value]
	xor edx, edx
	or eax, byte -1
	pop ebx
	ret
.return2:
	push ecx
	call Std$Integer$_alloc_small
	pop dword [small_int(eax).Value]
	mov ecx, eax
	xor edx, edx
	xor eax, eax
	ret
downto_small_small_small:
	mov eax, [argument(edi + 8).Val]
	mov ecx, [argument(edi).Val]
	mov eax, [small_int(eax).Value]
	cmp eax, [small_int(ecx).Value]
	jg .fail
	je .return
.suspend:
	push ecx
	push ebx
	push eax
	push dword [small_int(ecx).Value]
	push byte sizeof(to_small_small_small_state)
	call Riva$Memory$_alloc
	add esp, byte 4
	pop dword [to_small_small_small_state(eax).Current]
	pop dword [to_small_small_small_state(eax).Limit]
	pop dword [to_small_small_small_state(eax).Increment]
	mov dword [state(eax).Run], .resume
	pop ecx
	mov ebx, eax
	or eax, byte -1
	xor edx, edx
	ret
.return:
	xor edx, edx
	xor eax, eax
	ret
.fail:
	xor eax, eax
	inc eax
	ret
.resume:
	mov ecx, [to_small_small_small_state(eax).Current]
	add ecx, [to_small_small_small_state(eax).Increment]
	cmp ecx, [to_small_small_small_state(eax).Limit]
	jl .fail
	je .return2
	mov [to_small_small_small_state(eax).Current], ecx
	push eax
	push ecx
	call Std$Integer$_alloc_small
	mov ecx, eax
	pop dword [small_int(ecx).Value]
	xor edx, edx
	or eax, byte -1
	pop ebx
	ret
.return2:
	push ecx
	call Std$Integer$_alloc_small
	pop dword [small_int(eax).Value]
	mov ecx, eax
	xor edx, edx
	xor eax, eax
	ret
repeat_small:
	push byte sizeof(repeat_value_state)
	call Riva$Memory$_alloc
	add esp, byte 4
	mov ecx, [argument(edi).Val]
	mov [repeat_value_state(eax).Value], ecx
	mov dword [state(eax).Run], resume_repeat_value
	mov ebx, eax
	or eax, byte -1
	xor edx, edx
	ret

struct up_small_state, state
	.Current:	resd 1
endstruct

method "up", SMALLINT
	mov ecx, [argument(edi).Val]
.suspend:
	push ecx
	push dword [small_int(ecx).Value]
	push byte sizeof(up_small_state)
	call Riva$Memory$_alloc
	add esp, byte 4
	pop dword [up_small_state(eax).Current]
	mov dword [state(eax).Run], .resume
	pop ecx
	mov ebx, eax
	or eax, byte -1
	xor edx, edx
	ret
.return:
	xor edx, edx
	xor eax, eax
	ret
.fail:
	xor eax, eax
	inc eax
	ret
.resume:
	mov ecx, [up_small_state(eax).Current]
	inc ecx
	mov [up_small_state(eax).Current], ecx
	push eax
	push ecx
	call Std$Integer$_alloc_small
	mov ecx, eax
	pop dword [small_int(ecx).Value]
	xor edx, edx
	or eax, byte -1
	pop ebx
	ret

struct down_small_state, state
	.Current:	resd 1
endstruct

method "down", SMALLINT
	mov ecx, [argument(edi).Val]
.suspend:
	push ecx
	push dword [small_int(ecx).Value]
	push byte sizeof(up_small_state)
	call Riva$Memory$_alloc
	add esp, byte 4
	pop dword [down_small_state(eax).Current]
	mov dword [state(eax).Run], .resume
	pop ecx
	mov ebx, eax
	or eax, byte -1
	xor edx, edx
	ret
.return:
	xor edx, edx
	xor eax, eax
	ret
.fail:
	xor eax, eax
	inc eax
	ret
.resume:
	mov ecx, [down_small_state(eax).Current]
	dec ecx
	mov [down_small_state(eax).Current], ecx
	push eax
	push ecx
	call Std$Integer$_alloc_small
	mov ecx, eax
	pop dword [small_int(ecx).Value]
	xor edx, edx
	or eax, byte -1
	pop ebx
	ret

extern sprintf
method "@", REAL, VAL, Std$String$T
	push byte 12
	call Riva$Memory$_alloc_atomic
	mov [esp], eax
	mov ebx, [argument(edi).Val]
	fld qword [real(ebx).Value]
	sub esp, byte 8
	fstp qword [esp]
	push .format
	push eax
	call sprintf
	add esp, byte 16
	call Std$String$_new
	add esp, byte 4
	mov ecx, eax
	xor edx, edx
	xor eax, eax
	ret
.format:
	db "%f", 0

extern __gmpz_init_set_d
method "@", REAL, VAL, Std$Integer$SmallT
	sub esp, byte 12
	mov ebx, esp
	mov eax, [argument(edi).Val]
	fld qword [real(eax).Value]
	sub esp, byte 8
	fstp qword [esp]
	push ebx
	call __gmpz_init_set_d
	add esp, byte 12
	jmp finish_integer

extern Std$Real$_alloc
method "@", SMALLINT, VAL, Std$Real$T
	call Std$Real$_alloc
	mov ecx, eax
	mov eax, [argument(edi).Val]
	fild dword [small_int(eax).Value]
	fstp qword [real(ecx).Value]
	xor eax, eax
	xor edx, edx
	ret

extern __gmpz_get_d
method "@", BIGINT, VAL, Std$Real$T
	mov eax, [argument(edi).Val]
	lea eax, [big_int(eax).Value]
	push eax
	call __gmpz_get_d
	add esp, byte 4
	call Std$Real$_alloc
	fstp qword [real(eax).Value]
	mov ecx, eax
	xor eax, eax
	xor edx, edx
	ret

method "+", REAL, REAL
	mov eax, [argument(edi).Val]
	fld qword [real(eax).Value]
	mov eax, [argument(edi + 8).Val]
	fadd qword [real(eax).Value]
	call Std$Real$_alloc
	fstp qword [real(eax).Value]
	mov ecx, eax
	xor edx, edx
	xor eax, eax
	ret

method "-", REAL, REAL
	mov eax, [argument(edi).Val]
	fld qword [real(eax).Value]
	mov eax, [argument(edi + 8).Val]
	fsub qword [real(eax).Value]
	call Std$Real$_alloc
	fstp qword [real(eax).Value]
	mov ecx, eax
	xor edx, edx
	xor eax, eax
	ret

method "*", REAL, REAL
	mov eax, [argument(edi).Val]
	fld qword [real(eax).Value]
	mov eax, [argument(edi + 8).Val]
	fmul qword [real(eax).Value]
	call Std$Real$_alloc
	fstp qword [real(eax).Value]
	mov ecx, eax
	xor edx, edx
	xor eax, eax
	ret

method "/", REAL, REAL
	mov eax, [argument(edi).Val]
	fld qword [real(eax).Value]
	mov eax, [argument(edi + 8).Val]
	fdiv qword [real(eax).Value]
	call Std$Real$_alloc
	fstp qword [real(eax).Value]
	mov ecx, eax
	xor edx, edx
	xor eax, eax
	ret

method "abs", REAL
	mov eax, [argument(edi).Val]
	fld qword [real(eax).Value]
	fabs
	call Std$Real$_alloc
	fstp qword [real(eax).Value]
	mov ecx, eax
	xor edx, edx
	xor eax, eax
	ret

method "-", REAL
	mov eax, [argument(edi).Val]
	fld qword [real(eax).Value]
	fchs
	call Std$Real$_alloc
	fstp qword [real(eax).Value]
	mov ecx, eax
	xor edx, edx
	xor eax, eax
	ret

extern floor
method "floor", REAL
	mov eax, [argument(edi).Val]
	fld qword [real(eax).Value]
	sub esp, byte 8
	fstp qword [esp]
	call floor
	add esp, byte 8
	call Std$Integer$_alloc_small
	fistp dword [small_int(eax).Value]
	mov ecx, eax
	xor edx, edx
	xor eax, eax
	ret

extern ceil
method "ceil", REAL
	mov eax, [argument(edi).Val]
	fld qword [real(eax).Value]
	sub esp, byte 8
	fstp qword [esp]
	call ceil
	add esp, byte 8
	call Std$Integer$_alloc_small
	fistp dword [small_int(eax).Value]
	mov ecx, eax
	xor edx, edx
	xor eax, eax
	ret

extern round
method "round", REAL
	mov eax, [argument(edi).Val]
	fld qword [real(eax).Value]
	call Std$Integer$_alloc_small
	fistp dword [small_int(eax).Value]
	mov ecx, eax
	xor edx, edx
	xor eax, eax
	ret

method "sin", REAL
	mov eax, [argument(edi).Val]
	fld qword [real(eax).Value]
	fsin
	call Std$Real$_alloc
	fstp qword [real(eax).Value]
	mov ecx, eax
	xor edx, edx
	xor eax, eax
	ret

method "cos", REAL
	mov eax, [argument(edi).Val]
	fld qword [real(eax).Value]
	fcos
	call Std$Real$_alloc
	fstp qword [real(eax).Value]
	mov ecx, eax
	xor edx, edx
	xor eax, eax
	ret

method "tan", REAL
	mov eax, [argument(edi).Val]
	fld qword [real(eax).Value]
	fsincos
	fdivp st1, st0
	call Std$Real$_alloc
	fstp qword [real(eax).Value]
	mov ecx, eax
	xor edx, edx
	xor eax, eax
	ret

extern asin
method "asin", REAL
	sub esp, byte 8
	mov eax, [argument(edi).Val]
	fld qword [real(eax).Value]
	fstp qword [esp]
	call asin
	add esp, byte 8
	call Std$Real$_alloc
	fstp qword [real(eax).Value]
	mov ecx, eax
	xor edx, edx
	xor eax, eax
	ret

extern acos
method "acos", REAL
	sub esp, byte 8
	mov eax, [argument(edi).Val]
	fld qword [real(eax).Value]
	fstp qword [esp]
	call acos
	add esp, byte 8
	call Std$Real$_alloc
	fstp qword [real(eax).Value]
	mov ecx, eax
	xor edx, edx
	xor eax, eax
	ret

method "atan", REAL
	mov eax, [argument(edi).Val]
	fld1
	fld qword [real(eax).Value]
	fatan
	call Std$Real$_alloc
	fstp qword [real(eax).Value]
	mov ecx, eax
	xor edx, edx
	xor eax, eax
	ret

method "atan", REAL, REAL
	mov eax, [argument(edi).Val]
	mov ebx, [argument(edi + 8).Val]
	fld qword [real(eax).Value]
	fld qword [real(ebx).Value]
	fpatan
	call Std$Real$_alloc
	fstp qword [real(eax).Value]
	mov ecx, eax
	xor edx, edx
	xor eax, eax
	ret

method "sqrt", REAL
	mov eax, [argument(edi).Val]
	fld qword [real(eax).Value]
	fsqrt
	call Std$Real$_alloc
	fstp qword [real(eax).Value]
	mov ecx, eax
	xor edx, edx
	xor eax, eax
	ret

extern exp
method "exp", REAL
	sub esp, byte 8
	mov eax, [argument(edi).Val]
	fld qword [real(eax).Value]
	fstp qword [esp]
	call exp
	add esp, byte 8
	call Std$Real$_alloc
	fstp qword [real(eax).Value]
	mov ecx, eax
	xor edx, edx
	xor eax, eax
	ret

extern log
method "ln", REAL
	sub esp, byte 8
	mov eax, [argument(edi).Val]
	fld qword [real(eax).Value]
	fstp qword [esp]
	call log
	add esp, byte 8
	call Std$Real$_alloc
	fstp qword [real(eax).Value]
	mov ecx, eax
	xor edx, edx
	xor eax, eax
	ret

extern pow
method "^", REAL, REAL
	sub esp, byte 16
	mov eax, [argument(edi).Val]
	fld qword [real(eax).Value]
	mov eax, [argument(edi + 8).Val]
	fld qword [real(eax).Value]
	fstp qword [esp + 8]
	fstp qword [esp]
	call pow
	add esp, byte 16
	call Std$Real$_alloc
	fstp qword [real(eax).Value]
	mov ecx, eax
	xor edx, edx
	xor eax, eax
	ret

;0x01 = less
;0x40 = equal
;0x00 = greater

%macro real_compare_finish 1
%ifidn %1, S
	mov ecx, [argument(edi + 8).Val]
	mov edx, [argument(edi + 8).Ref]
	xor eax, eax
	ret
%elifidn %1, F
	mov eax, 1
	ret
%else
	%error "Invalid use of real comparision macros"
%endif
%endmacro

%macro real_compare 3
	mov eax, [argument(edi).Val]
	fld qword [real(eax).Value]
	mov eax, [argument(edi + 8).Val]
	fcomp qword [real(eax).Value]
	xor eax, eax
	fnstsw ax
	shr ah, 1
	jc .less
	and ah, 0x20
	jnz .equal
.greater:
	real_compare_finish %1
.equal:
	real_compare_finish %2
.less:
	real_compare_finish %3
%endmacro

method "<", REAL, REAL
	real_compare F, F, S

method "<=", REAL, REAL
	real_compare F, S, S

method ">", REAL, REAL
	real_compare S, F, F

method ">=", REAL, REAL
	real_compare S, S, F

method "=", REAL, REAL
	real_compare F, S, F

method "~=", REAL, REAL
	real_compare S, F, S

method "?", REAL, REAL
	mov eax, [argument(edi).Val]
	fld qword [real(eax).Value]
	mov eax, [argument(edi + 8).Val]
	fcomp qword [real(eax).Value]
	xor eax, eax
	fnstsw ax
	shr ah, 1
	jc .less
	and ah, 0x20
	jnz .equal
.greater:
	mov ecx, GREATER
	xor edx, edx
	xor eax, eax
	ret
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

method "#", REAL
	call Std$Integer$_alloc_small
	mov ecx, [argument(edi).Val]
	fld qword [real(ecx).Value]
	fstp dword [small_int(eax).Value]
	mov ecx, eax
	xor edx, edx
	xor eax, eax
	ret

method "+", REAL, SMALLINT
	mov eax, [argument(edi).Val]
	fld qword [real(eax).Value]
	mov eax, [argument(edi + 8).Val]
	fiadd dword [small_int(eax).Value]
	call Std$Real$_alloc
	fstp qword [real(eax).Value]
	mov ecx, eax
	xor edx, edx
	xor eax, eax
	ret

method "-", REAL, SMALLINT
	mov eax, [argument(edi).Val]
	fld qword [real(eax).Value]
	mov eax, [argument(edi + 8).Val]
	fisub dword [small_int(eax).Value]
	call Std$Real$_alloc
	fstp qword [real(eax).Value]
	mov ecx, eax
	xor edx, edx
	xor eax, eax
	ret

method "*", REAL, SMALLINT
	mov eax, [argument(edi).Val]
	fld qword [real(eax).Value]
	mov eax, [argument(edi + 8).Val]
	fimul dword [small_int(eax).Value]
	call Std$Real$_alloc
	fstp qword [real(eax).Value]
	mov ecx, eax
	xor edx, edx
	xor eax, eax
	ret

method "/", REAL, SMALLINT
	mov eax, [argument(edi).Val]
	fld qword [real(eax).Value]
	mov eax, [argument(edi + 8).Val]
	fidiv dword [small_int(eax).Value]
	call Std$Real$_alloc
	fstp qword [real(eax).Value]
	mov ecx, eax
	xor edx, edx
	xor eax, eax
	ret

method "+", SMALLINT, REAL
	mov eax, [argument(edi + 8).Val]
	fld qword [real(eax).Value]
	mov eax, [argument(edi).Val]
	fiadd dword [small_int(eax).Value]
	call Std$Real$_alloc
	fstp qword [real(eax).Value]
	mov ecx, eax
	xor edx, edx
	xor eax, eax
	ret

method "-", SMALLINT, REAL
	mov eax, [argument(edi + 8).Val]
	fld qword [real(eax).Value]
	mov eax, [argument(edi).Val]
	fisubr dword [small_int(eax).Value]
	call Std$Real$_alloc
	fstp qword [real(eax).Value]
	mov ecx, eax
	xor edx, edx
	xor eax, eax
	ret

method "*", SMALLINT, REAL
	mov eax, [argument(edi + 8).Val]
	fld qword [real(eax).Value]
	mov eax, [argument(edi).Val]
	fimul dword [small_int(eax).Value]
	call Std$Real$_alloc
	fstp qword [real(eax).Value]
	mov ecx, eax
	xor edx, edx
	xor eax, eax
	ret

method "/", SMALLINT, REAL
	mov eax, [argument(edi + 8).Val]
	fld qword [real(eax).Value]
	mov eax, [argument(edi).Val]
	fidivr dword [small_int(eax).Value]
	call Std$Real$_alloc
	fstp qword [real(eax).Value]
	mov ecx, eax
	xor edx, edx
	xor eax, eax
	ret

method "left", STRING, SMALLINT
	mov eax, [argument(edi + 8).Val]
	mov eax, [small_int(eax).Value]
	mov ebx, [argument(edi).Val]
	cmp eax, [small_int(string(ebx).Length).Value]
	jbe .nopad
	push eax
	sub eax, [small_int(string(ebx).Length).Value]
	push eax
	call Riva$Memory$_alloc_atomic
	push eax
	mov eax, [string(ebx).Count]
	inc eax
	push eax
	shl eax, 4
	add eax, byte sizeof(string) + sizeof(string_block)
	push eax
	call Riva$Memory$_alloc
	pop edx
	pop ecx
	mov [string(eax).Count], ecx
	lea edi, [string(eax).Blocks]
	lea esi, [string(ebx).Blocks]
	lea ecx, [4 * ecx - 4]
	rep movsd
	pop edx
	pop ecx
	mov [value(string_block(edi).Chars).Type], dword Std$Address$T
	mov [address(string_block(edi).Chars).Value], edx
	mov [value(string_block(edi).Length).Type], dword Std$Integer$SmallT
	mov [small_int(string_block(edi).Length).Value], ecx
	mov dword [value(string(eax).Length).Type], Std$Integer$SmallT
	pop dword [small_int(string(eax).Length).Value]
	mov dword [value(eax).Type], Std$String$T
	mov ebx, eax
	mov edi, edx
	mov al, ' '
	rep stosb
.nopad:
	mov ecx, ebx
	xor edx, edx
	xor eax, eax
	ret

method "right", STRING, SMALLINT
	mov eax, [argument(edi + 8).Val]
	mov eax, [small_int(eax).Value]
	mov ebx, [argument(edi).Val]
	cmp eax, [small_int(string(ebx).Length).Value]
	jbe .nopad
	push eax
	sub eax, [small_int(string(ebx).Length).Value]
	push eax
	call Riva$Memory$_alloc_atomic
	push eax
	mov eax, [string(ebx).Count]
	inc eax
	push eax
	shl eax, 4
	add eax, byte sizeof(string) + sizeof(string_block)
	push eax
	call Riva$Memory$_alloc
	pop edx
	pop ecx
	mov [string(eax).Count], ecx
	lea edi, [string(eax).Blocks + sizeof(string_block)]
	lea esi, [string(ebx).Blocks]
	lea ecx, [4 * ecx - 4]
	rep movsd
	pop edx
	pop ecx
	mov [value(string_block(string(eax).Blocks).Chars).Type], dword Std$Address$T
	mov [address(string_block(string(eax).Blocks).Chars).Value], edx
	mov [value(string_block(string(eax).Blocks).Length).Type], dword Std$Integer$SmallT
	mov [small_int(string_block(string(eax).Blocks).Length).Value], ecx
	mov dword [value(string(eax).Length).Type], Std$Integer$SmallT
	pop dword [small_int(string(eax).Length).Value]
	mov dword [value(eax).Type], Std$String$T
	mov ebx, eax
	mov edi, edx
	mov al, ' '
	rep stosb
.nopad:
	mov ecx, ebx
	xor edx, edx
	xor eax, eax
	ret

method "left", STRING, SMALLINT, STRING
	mov eax, [argument(edi + 8).Val]
	mov eax, [small_int(eax).Value]
	mov ebx, [argument(edi).Val]
	cmp eax, [small_int(string(ebx).Length).Value]
	jbe .nopad
	push byte ' '
	mov edx, [argument(edi + 16).Val]
	cmp [small_int(string(edx).Length).Value], dword 0
	je .default
	mov edx, [address(string_block(string(edx).Blocks).Chars).Value]
	mov edx, [edx]
	mov [esp], edx
.default:
	push eax
	sub eax, [small_int(string(ebx).Length).Value]
	push eax
	call Riva$Memory$_alloc_atomic
	push eax
	mov eax, [string(ebx).Count]
	inc eax
	push eax
	shl eax, 4
	add eax, byte sizeof(string) + sizeof(string_block)
	push eax
	call Riva$Memory$_alloc
	pop edx
	pop ecx
	mov [string(eax).Count], ecx
	lea edi, [string(eax).Blocks]
	lea esi, [string(ebx).Blocks]
	lea ecx, [4 * ecx - 4]
	rep movsd
	pop edx
	pop ecx
	mov [value(string_block(edi).Chars).Type], dword Std$Address$T
	mov [address(string_block(edi).Chars).Value], edx
	mov [value(string_block(edi).Length).Type], dword Std$Integer$SmallT
	mov [small_int(string_block(edi).Length).Value], ecx
	mov dword [value(string(eax).Length).Type], Std$Integer$SmallT
	pop dword [small_int(string(eax).Length).Value]
	mov dword [value(eax).Type], Std$String$T
	mov ebx, eax
	mov edi, edx
	pop eax
	rep stosb
.nopad:
	mov ecx, ebx
	xor edx, edx
	xor eax, eax
	ret

method "right", STRING, SMALLINT, STRING
	mov eax, [argument(edi + 8).Val]
	mov eax, [small_int(eax).Value]
	mov ebx, [argument(edi).Val]
	cmp eax, [small_int(string(ebx).Length).Value]
	jbe .nopad
	push byte ' '
	mov edx, [argument(edi + 16).Val]
	cmp [small_int(string(edx).Length).Value], dword 0
	je .default
	mov edx, [address(string_block(string(edx).Blocks).Chars).Value]
	mov edx, [edx]
	mov [esp], edx
.default:
	push eax
	sub eax, [small_int(string(ebx).Length).Value]
	push eax
	call Riva$Memory$_alloc_atomic
	push eax
	mov eax, [string(ebx).Count]
	inc eax
	push eax
	shl eax, 4
	add eax, byte sizeof(string) + sizeof(string_block)
	push eax
	call Riva$Memory$_alloc
	pop edx
	pop ecx
	mov [string(eax).Count], ecx
	lea edi, [string(eax).Blocks + sizeof(string_block)]
	lea esi, [string(ebx).Blocks]
	lea ecx, [4 * ecx - 4]
	rep movsd
	pop edx
	pop ecx
	mov [value(string_block(string(eax).Blocks).Chars).Type], dword Std$Address$T
	mov [address(string_block(string(eax).Blocks).Chars).Value], edx
	mov [value(string_block(string(eax).Blocks).Length).Type], dword Std$Integer$SmallT
	mov [small_int(string_block(string(eax).Blocks).Length).Value], ecx
	mov dword [value(string(eax).Length).Type], Std$Integer$SmallT
	pop dword [small_int(string(eax).Length).Value]
	mov dword [value(eax).Type], Std$String$T
	mov ebx, eax
	mov edi, edx
	pop eax
	rep stosb
.nopad:
	mov ecx, ebx
	xor edx, edx
	xor eax, eax
	ret

method "ord", STRING
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

method "chr", SMALLINT
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
	mov [value(eax).Type], dword Std$String$T
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

_method "+", Std$String$Add, STRING, STRING

method "[]", STRING, SMALLINT
	mov eax, [argument(edi).Val]
	mov ebx, [argument(edi + 8).Val]
	mov ebx, [small_int(ebx).Value]
	mov edx, [small_int(string(eax).Length).Value]
	dec ebx
	jns .firstpositive
	add ebx, edx
	inc ebx
	js near .outofbounds
.firstpositive:
	cmp ebx, edx
	jge near .outofbounds
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
	push byte sizeof(string) + 2 * sizeof(string_block)
	call Riva$Memory$_alloc
	add esp, byte 4
	mov [value(eax).Type], dword Std$String$T
	mov [value(string(eax).Length).Type], dword Std$Integer$SmallT
	mov [small_int(string(eax).Length).Value], byte 1
	mov [string(eax).Count], byte 1
	mov esi, [esp + 4]
	mov ecx, 4
	lea edi, [string(eax).Blocks]
	rep movsd
	pop edx
	add [address(string_block(string(eax).Blocks).Chars).Value], edx
	mov [small_int(string_block(string(eax).Blocks).Length).Value], dword 1
	add esp, byte 4
	mov ecx, eax
	xor edx, edx
	xor eax, eax
	ret
.outofbounds:
	mov eax, 1
	ret

method "[]", STRING, SMALLINT, SMALLINT
	mov eax, [argument(edi).Val]
	mov ebx, [argument(edi + 8).Val]
	mov ecx, [argument(edi + 16).Val]
	mov ebx, [small_int(ebx).Value]
	mov ecx, [small_int(ecx).Value]
	mov edx, [small_int(string(eax).Length).Value]
	dec ebx
	jns .firstpositive
	add ebx, edx
	inc ebx
	js near .outofbounds
.firstpositive:
	cmp ebx, edx
	jge near .outofbounds
	dec ecx
	jns .secondpositive
	add ecx, edx
	inc ecx
	js near .outofbounds
.secondpositive:
	cmp ecx, edx
	jg near .outofbounds
	cmp ebx, ecx
	jl .notempty
	mov ecx, .empty_string
	xor edx, edx
	xor eax, eax
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
	mov ecx, eax
	xor edx, edx
	xor eax, eax
	ret
.outofbounds:
	mov eax, 1
	ret
section .data
.empty_string:
	dd Std$String$T
	dd Std$Integer$SmallT
	dd 0
	dd 0
	dd 0, 0, 0, 0

symbol ?init, "init"

extern Std$Type$T.invoke
extern Std$Symbol$T.invoke

method "new", TYP, Std$Type$T
	push esi
	push edi
	xor esi, esi
	mov ecx, [argument(edi).Val]
	call Std$Type$T.invoke
	pop edi
	pop esi
	push ecx
	mov [argument(edi).Val], ecx
	mov [argument(edi).Ref], dword 0
	mov ecx, ?init
	call Std$Symbol$T.invoke
	pop ecx
	xor edx, edx
	xor eax, eax
	ret

%macro string_compare_finish 1
%ifidn %1, S
	mov ecx, [argument(edi + 8).Val]
	mov edx, [argument(edi + 8).Ref]
	xor eax, eax
	ret
%elifidn %1, F
	mov eax, 1
	ret
%else
	%error "Invalid use of string comparision macros"
%endif
%endmacro

%macro string_compare 3
	mov eax, [argument(edi).Val]
	mov ebx, [argument(edi + 8).Val]
	lea eax, [string(eax).Blocks]
	lea ebx, [string(ebx).Blocks]
	push edi
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
	pop edi
	string_compare_finish %1
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
	pop edi
	string_compare_finish %2
.less:
	pop edi
	string_compare_finish %3
%endmacro

method "<", STRING, STRING
	string_compare F, F, S

method "<=", STRING, STRING
	string_compare F, S, S

method ">", STRING, STRING
	string_compare S, F, F

method ">=", STRING, STRING
	string_compare S, S, F

method "=", STRING, STRING
	string_compare F, S, F

method "~=", STRING, STRING
	string_compare S, F, S

method "?", STRING, STRING
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

method "#", ANY
	call Std$Integer$_alloc_small
	mov ecx, [argument(edi).Val]
	mov [small_int(eax).Value], ecx
	mov ecx, eax
	xor edx, edx
	xor eax, eax
	ret

method "#", ADDRESS
	call Std$Integer$_alloc_small
	mov ecx, [argument(edi).Val]
	mov ecx, [address(ecx).Value]
	mov [small_int(eax).Value], ecx
	mov ecx, eax
	xor edx, edx
	xor eax, eax
	ret

method "#", SMALLINT
	mov ecx, [argument(edi).Val]
	xor edx, edx
	xor eax, eax
	ret

method "#", BIGINT
	mov ecx, [argument(edi).Val]
	lea ecx, [big_int(ecx).Value]
	push ecx
	call __gmpz_get_si
	mov [esp], eax
	call Std$Integer$_alloc_small
	pop dword [small_int(eax).Value]
	mov ecx, eax
	xor edx, edx
	xor eax, eax
	ret

method "bits", SMALLINT
bits_small:
	mov eax, [argument(edi).Val]
	mov eax, [small_int(eax).Value]
.run:
	mov edx, eax
	and edx, 0x55555555
	sub eax, edx
	shr eax, 1
	add eax, edx
	mov edx, eax
	and edx, 0x33333333
	sub eax, edx
	shr eax, 2
	add eax, edx
	mov edx, eax
	and edx, 0x0F0F0F0F
	sub eax, edx
	shr eax, 4
	add eax, edx
	mov edx, eax
	and edx, 0x00FF00FF
	sub eax, edx
	shr eax, 8
	add eax, edx
	mov edx, eax
	and edx, 0x0000FFFF
	sub eax, edx
	shr eax, 16
	add eax, edx
	push eax
	call Std$Integer$_alloc_small
	pop dword [small_int(eax).Value]
	mov ecx, eax
	xor edx, edx
	xor eax, eax
	ret

method "scan0", SMALLINT
	mov eax, [argument(edi).Val]
	mov eax, [small_int(eax).Value]
	not eax
	lea edx, [eax - 1]
	xor eax, edx
	jmp bits_small.run

method "scan1", SMALLINT
	mov eax, [argument(edi).Val]
	mov eax, [small_int(eax).Value]
	lea edx, [eax - 1]
	xor eax, edx
	jmp bits_small.run

struct bits_small_state, state
	.Source:	resd 1
	.Last:		resd 1
	.Limit:		resd 1
endstruct

section .text
resume_ones_small:
	mov ebx, eax
	mov eax, [bits_small_state(ebx).Source]
	mov ecx, [bits_small_state(ebx).Last]
.loop:
	inc ecx
	sar eax, 1
	jc .suspend
	jnz .loop
	inc eax
	ret
.suspend:
	cmp ecx, [bits_small_state(ebx).Limit]
	ja .failure
	mov [bits_small_state(ebx).Source], eax
	mov [bits_small_state(ebx).Last], ecx
	push ecx
	call Std$Integer$_alloc_small
	pop dword [small_int(eax).Value]
	mov ecx, eax
	or eax, byte -1
	xor edx, edx
	ret
.failure:
	xor eax, eax
	inc eax
	ret

method "ones", SMALLINT
ones_small:
	mov eax, [argument(edi).Val]
	mov eax, [small_int(eax).Value]
.run:
	xor ecx, ecx
.loop:
	sar eax, 1
	jc .suspend
	lea ecx, [ecx + 1]
	jnz .loop
	inc eax
	ret
.suspend:
	push ecx
	push eax
	push byte sizeof(bits_small_state)
	call Riva$Memory$_alloc
	add esp, byte 4
	pop dword [bits_small_state(eax).Source]
	mov dword [bits_small_state(eax).Limit], 0xFFFFFFFF
	mov ecx, [esp]
	mov [bits_small_state(eax).Last], ecx
	mov ebx, eax
	mov dword [state(ebx).Run], resume_ones_small
	call Std$Integer$_alloc_small
	pop dword [small_int(eax).Value]
	mov ecx, eax
	or eax, byte -1
	xor edx, edx
	ret

method "ones", SMALLINT, SMALLINT
ones_small_small:
	mov eax, [argument(edi).Val]
	mov ecx, [argument(edi + 8).Val]
	mov eax, [small_int(eax).Value]
	mov ecx, [small_int(ecx).Value]
.run:
	cmp ecx, 32
	jae .failure
	sar eax, cl
.loop:
	sar eax, 1
	jc .suspend
	lea ecx, [ecx + 1]
	jnz .loop
	inc eax
	ret
.suspend:
	push ecx
	push eax
	push byte sizeof(bits_small_state)
	call Riva$Memory$_alloc
	add esp, byte 4
	pop dword [bits_small_state(eax).Source]
	mov dword [bits_small_state(eax).Limit], 0xFFFFFFFF
	mov ecx, [esp]
	mov [bits_small_state(eax).Last], ecx
	mov ebx, eax
	mov dword [state(ebx).Run], resume_ones_small
	call Std$Integer$_alloc_small
	pop dword [small_int(eax).Value]
	mov ecx, eax
	or eax, byte -1
	xor edx, edx
	ret
.failure:
	xor eax, eax
	inc eax
	ret

method "ones", SMALLINT, SMALLINT, SMALLINT
ones_small_small_small:
	mov eax, [argument(edi).Val]
	mov ecx, [argument(edi + 8).Val]
	mov ebx, [argument(edi + 16).Val]
	mov eax, [small_int(eax).Value]
	mov ecx, [small_int(ecx).Value]
	mov ebx, [small_int(ebx).Value]
.run:
	cmp ecx, 32
	jae .failure
	sar eax, cl
.loop:
	sar eax, 1
	jc .suspend
	lea ecx, [ecx + 1]
	jnz .loop
	inc eax
	ret
.suspend:
	cmp ecx, ebx
	ja .failure
	push ecx
	push eax
	push byte sizeof(bits_small_state)
	call Riva$Memory$_alloc
	add esp, byte 4
	pop dword [bits_small_state(eax).Source]
	mov [bits_small_state(eax).Limit], ebx
	mov ecx, [esp]
	mov [bits_small_state(eax).Last], ecx
	mov ebx, eax
	mov dword [state(ebx).Run], resume_ones_small
	call Std$Integer$_alloc_small
	pop dword [small_int(eax).Value]
	mov ecx, eax
	or eax, byte -1
	xor edx, edx
	ret
.failure:
	xor eax, eax
	inc eax
	ret

method "zeros", SMALLINT
	mov eax, [argument(edi).Val]
	mov eax, [small_int(eax).Value]
	not eax
	jmp ones_small.run

method "zeros", SMALLINT, SMALLINT
	mov eax, [argument(edi).Val]
	mov ecx, [argument(edi + 8).Val]
	mov eax, [small_int(eax).Value]
	mov ecx, [small_int(ecx).Value]
	not eax
	jmp ones_small_small.run

method "zeros", SMALLINT, SMALLINT, SMALLINT
	mov eax, [argument(edi).Val]
	mov ecx, [argument(edi + 8).Val]
	mov ebx, [argument(edi + 16).Val]
	mov eax, [small_int(eax).Value]
	mov ecx, [small_int(ecx).Value]
	mov ebx, [small_int(ebx).Value]
	not eax
	jmp ones_small_small_small.run

method "bit", SMALLINT, SMALLINT
	mov eax, [argument(edi).Val]
	mov ecx, [argument(edi + 8).Val]
	mov eax, [small_int(eax).Value]
	mov ecx, [small_int(ecx).Value]
	cmp ecx, 31
	jbe .noclip
	mov ecx, 31
.noclip:
	shr eax, cl
	and eax, 1
	lea ecx, [ZERO + 8 * eax]
	xor edx, edx
	xor eax, eax
	ret

extern __gmpz_popcount
method "bits", BIGINT
	mov ecx, [argument(edi).Val]
	lea ecx, [big_int(ecx).Value]
	push ecx
	call __gmpz_popcount
	mov [esp], eax
	call Std$Integer$_alloc_small
	pop dword [small_int(eax).Value]
	mov ecx, eax
	xor edx, edx
	xor eax, eax
	ret

extern __gmpz_scan0
method "scan0", BIGINT
	mov ecx, [argument(edi).Val]
	lea ecx, [big_int(ecx).Value]
	push byte 0
	push ecx
	call __gmpz_scan0
	mov [esp], eax
	call Std$Integer$_alloc_small
	pop dword [small_int(eax).Value]
	pop ecx
	mov ecx, eax
	xor edx, edx
	xor eax, eax
	ret

extern __gmpz_scan1
method "scan1", BIGINT
	mov ecx, [argument(edi).Val]
	lea ecx, [big_int(ecx).Value]
	push byte 0
	push ecx
	call __gmpz_scan1
	mov [esp], eax
	call Std$Integer$_alloc_small
	pop dword [small_int(eax).Value]
	pop ecx
	mov ecx, eax
	xor edx, edx
	xor eax, eax
	ret

struct bits_big_state, state
	.Source:	resd 1
	.Last:		resd 1
	.Limit:		resd 1
endstruct

section .text
resume_ones_big:
	mov ebx, eax
	push dword [bits_big_state(ebx).Last]
	push dword [bits_big_state(ebx).Source]
	call __gmpz_scan1
	add esp, byte 8
	cmp eax, [bits_big_state(ebx).Limit]
	ja .failure
.suspend:
	push eax
	inc eax
	mov [bits_big_state(ebx).Last], eax
	call Std$Integer$_alloc_small
	pop dword [small_int(eax).Value]
	mov ecx, eax
	or eax, byte -1
	xor edx, edx
	ret
.failure:
	xor eax, eax
	inc eax
	ret

method "ones", BIGINT
	mov eax, [argument(edi).Val]
	lea eax, [big_int(eax).Value]
	push eax
	push byte 0
	push eax
	call __gmpz_scan1
	add esp, byte 8
	cmp eax, byte -1
	je .failure
	push eax
	push byte sizeof(bits_big_state)
	call Riva$Memory$_alloc
	add esp, byte 4
	mov ebx, eax
	call Std$Integer$_alloc_small
	pop edx
	mov [small_int(eax).Value], edx
	inc edx
	mov [bits_big_state(ebx).Last], edx
	pop dword [bits_big_state(ebx).Source]
	mov dword [bits_big_state(ebx).Limit], 0xFFFFFFFE
	mov dword [state(ebx).Run], resume_ones_big
	mov ecx, eax
	or eax, byte -1
	xor edx, edx
	ret
.failure:
	add esp, byte 4
	xor eax, eax
	inc eax
	ret

method "ones", BIGINT, SMALLINT
	mov eax, [argument(edi).Val]
	mov ebx, [argument(edi + 8).Val]
	lea eax, [big_int(eax).Value]
	push eax
	push dword [small_int(ebx).Value]
	push eax
	call __gmpz_scan1
	add esp, byte 8
	cmp eax, byte -1
	je .failure
	push eax
	push byte sizeof(bits_big_state)
	call Riva$Memory$_alloc
	add esp, byte 4
	mov ebx, eax
	call Std$Integer$_alloc_small
	pop edx
	mov [small_int(eax).Value], edx
	inc edx
	mov [bits_big_state(ebx).Last], edx
	pop dword [bits_big_state(ebx).Source]
	mov dword [bits_big_state(ebx).Limit], 0xFFFFFFFE
	mov dword [state(ebx).Run], resume_ones_big
	mov ecx, eax
	or eax, byte -1
	xor edx, edx
	ret
.failure:
	add esp, byte 4
	xor eax, eax
	inc eax
	ret

method "ones", BIGINT, SMALLINT, SMALLINT
	mov eax, [argument(edi).Val]
	mov ebx, [argument(edi + 8).Val]
	mov ecx, [argument(edi + 16).Val]
	lea eax, [big_int(eax).Value]
	push dword [small_int(ecx).Value]
	push eax
	push dword [small_int(ebx).Value]
	push eax
	call __gmpz_scan1
	add esp, byte 8
	cmp eax, [esp + 4]
	ja .failure
	push eax
	push byte sizeof(bits_big_state)
	call Riva$Memory$_alloc
	add esp, byte 4
	mov ebx, eax
	call Std$Integer$_alloc_small
	pop edx
	mov [small_int(eax).Value], edx
	inc edx
	mov [bits_big_state(ebx).Last], edx
	pop dword [bits_big_state(ebx).Source]
	pop dword [bits_big_state(ebx).Limit]
	mov dword [state(ebx).Run], resume_ones_big
	mov ecx, eax
	or eax, byte -1
	xor edx, edx
	ret
.failure:
	add esp, byte 8
	xor eax, eax
	inc eax
	ret

section .text
resume_zeros_big:
	mov ebx, eax
	push dword [bits_big_state(ebx).Last]
	push dword [bits_big_state(ebx).Source]
	call __gmpz_scan0
	add esp, byte 8
	cmp eax, [bits_big_state(ebx).Limit]
	ja .failure
.suspend:
	push eax
	inc eax
	mov [bits_big_state(ebx).Last], eax
	call Std$Integer$_alloc_small
	pop dword [small_int(eax).Value]
	mov ecx, eax
	or eax, byte -1
	xor edx, edx
	ret
.failure:
	xor eax, eax
	inc eax
	ret

method "zeros", BIGINT
	mov eax, [argument(edi).Val]
	lea eax, [big_int(eax).Value]
	push eax
	push byte 0
	push eax
	call __gmpz_scan0
	add esp, byte 8
	cmp eax, byte -1
	je .failure
	push eax
	push byte sizeof(bits_big_state)
	call Riva$Memory$_alloc
	add esp, byte 4
	mov ebx, eax
	call Std$Integer$_alloc_small
	pop edx
	mov [small_int(eax).Value], edx
	inc edx
	mov [bits_big_state(ebx).Last], edx
	pop dword [bits_big_state(ebx).Source]
	mov dword [bits_big_state(ebx).Limit], 0xFFFFFFFE
	mov dword [state(ebx).Run], resume_zeros_big
	mov ecx, eax
	or eax, byte -1
	xor edx, edx
	ret
.failure:
	add esp, byte 4
	xor eax, eax
	inc eax
	ret

method "zeros", BIGINT, SMALLINT
	mov eax, [argument(edi).Val]
	mov ebx, [argument(edi + 8).Val]
	lea eax, [big_int(eax).Value]
	push eax
	push dword [small_int(ebx).Value]
	push eax
	call __gmpz_scan0
	add esp, byte 8
	cmp eax, byte -1
	je .failure
	push eax
	push byte sizeof(bits_big_state)
	call Riva$Memory$_alloc
	add esp, byte 4
	mov ebx, eax
	call Std$Integer$_alloc_small
	pop edx
	mov [small_int(eax).Value], edx
	inc edx
	mov [bits_big_state(ebx).Last], edx
	pop dword [bits_big_state(ebx).Source]
	mov dword [bits_big_state(ebx).Limit], 0xFFFFFFFE
	mov dword [state(ebx).Run], resume_zeros_big
	mov ecx, eax
	or eax, byte -1
	xor edx, edx
	ret
.failure:
	add esp, byte 4
	xor eax, eax
	inc eax
	ret

method "zeros", BIGINT, SMALLINT, SMALLINT
	mov eax, [argument(edi).Val]
	mov ebx, [argument(edi + 8).Val]
	mov ecx, [argument(edi + 16).Val]
	lea eax, [big_int(eax).Value]
	push dword [small_int(ecx).Value]
	push eax
	push dword [small_int(ebx).Value]
	push eax
	call __gmpz_scan0
	add esp, byte 8
	cmp eax, byte -1
	je .failure
	push eax
	push byte sizeof(bits_big_state)
	call Riva$Memory$_alloc
	add esp, byte 4
	mov ebx, eax
	call Std$Integer$_alloc_small
	pop edx
	mov [small_int(eax).Value], edx
	inc edx
	mov [bits_big_state(ebx).Last], edx
	pop dword [bits_big_state(ebx).Source]
	pop dword [bits_big_state(ebx).Limit]
	mov dword [state(ebx).Run], resume_zeros_big
	mov ecx, eax
	or eax, byte -1
	xor edx, edx
	ret
.failure:
	add esp, byte 8
	xor eax, eax
	inc eax
	ret

extern __gmpz_bit_small
method "bit", BIGINT, SMALLINT
	mov ecx, [argument(edi).Val]
	mov eax, [argument(edi + 8).Val]
	lea ecx, [big_int(ecx).Value]
	push dword [small_int(eax).Value]
	push ecx
	call __gmpz_tstbit
	mov [esp], eax
	call Std$Integer$_alloc_small
	pop dword [small_int(eax).Value]
	pop edx
	mov ecx, eax
	xor edx, edx
	xor eax, eax
	ret

method "#", STRING
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

method "in", ANY, TYP, Std$Type$T
	mov ecx, [argument(edi).Val]
	mov eax, [argument(edi + 8).Val]
	mov edx, [value(ecx).Type]
	mov edx, [type(edx).Types]
	sub edx, byte 4
.loop:
	add edx, byte 4
	mov ebx, [edx]
	test ebx, ebx
	jz .fail
	cmp ebx, eax
	jne .loop
	xor edx, edx
	xor eax, eax
	ret
.fail:
	xor eax, eax
	inc eax
	ret

method "<", TYP, Std$Type$T, TYP, Std$Type$T
	mov eax, [argument(edi).Val]
	mov ecx, [argument(edi + 8).Val]
	mov eax, [type(eax).Types]
.loop:
	add eax, byte 4
	mov ebx, [eax]
	test ebx, ebx
	jz .fail
	cmp ebx, ecx
	jne .loop
	xor edx, edx
	xor eax, eax
	ret
.fail:
	xor eax, eax
	inc eax
	ret

method ">", TYP, Std$Type$T, TYP, Std$Type$T
	mov ecx, [argument(edi + 8).Val]
	mov edx, [argument(edi).Val]
	mov eax, [type(ecx).Types]
.loop:
	add eax, byte 4
	mov ebx, [eax]
	test ebx, ebx
	jz .fail
	cmp ebx, edx
	jne .loop
	xor edx, edx
	xor eax, eax
	ret
.fail:
	xor eax, eax
	inc eax
	ret

method "<=", TYP, Std$Type$T, TYP, Std$Type$T
	mov eax, [argument(edi).Val]
	mov ecx, [argument(edi + 8).Val]
	mov eax, [type(eax).Types]
	sub eax, byte 4
.loop:
	add eax, byte 4
	mov ebx, [eax]
	test ebx, ebx
	jz .fail
	cmp ebx, ecx
	jne .loop
	xor edx, edx
	xor eax, eax
	ret
.fail:
	xor eax, eax
	inc eax
	ret

method ">=", TYP, Std$Type$T, TYP, Std$Type$T
	mov ecx, [argument(edi + 8).Val]
	mov edx, [argument(edi).Val]
	mov eax, [type(ecx).Types]
	sub eax, byte 4
.loop:
	add eax, byte 4
	mov ebx, [eax]
	test ebx, ebx
	jz .fail
	cmp ebx, edx
	jne .loop
	xor edx, edx
	xor eax, eax
	ret
.fail:
	xor eax, eax
	inc eax
	ret

method "=", ANY, ANY
	mov ecx, [argument(edi + 8).Val]
	cmp ecx, [argument(edi).Val]
	jne .fail
	mov edx, [argument(edi + 8).Ref]
	xor eax, eax
	ret
.fail:
	xor eax, eax
	inc eax
	ret

method "~=", ANY, ANY
	mov ecx, [argument(edi + 8).Val]
	cmp ecx, [argument(edi).Val]
	je .fail
	mov edx, [argument(edi + 8).Ref]
	xor eax, eax
	ret
.fail:
	xor eax, eax
	inc eax
	ret

method "length", STRING
	mov ecx, [argument(edi).Val]
	lea ecx, [string(ecx).Length]
	xor edx, edx
	xor eax, eax
	ret
