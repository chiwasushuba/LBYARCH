; assembly part using x86-64

section .data
; RCX - width, RDX - height, R8 - float*, R9 - int*
scale dd: 255.0

section .text
bits 64
default rel

global imgCvtGrayFloatToInt

imgCvtGrayFloatToInt:
	
	MOV RAX, RCX	; First parameter
	IMUL RAX, RDX	; First Parameter * Second Parameter = Size
	MOV R10, RAX	; Store size at R10 for counter limit
	XOR R11, R11	; Loop counter reset

	MOVSS XMM1, dword [scale]		; Scale

.LOOP:
	CMP R11, R10
	JGE .END
    MOVSS XMM0, [R8 + R11*4]
    MULSS XMM0, XMM1
	CVTSS2SI EAX, XMM0
	MOV [R9 + R11*4], EAX
	INC R11
	JMP .LOOP

.END:
	leave
	ret


	