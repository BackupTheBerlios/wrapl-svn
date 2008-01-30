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
