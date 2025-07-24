; assembly part using x86-64

section .data
msg db "Hello World", 13,10,0

section .text
bits 64
default rel

global asmhello
extern printf

asmhello:
	SUB RSP, 8*5	; caller
	LEA rcx, [msg] 
	call printf
	add RSP, 8*5
	ret