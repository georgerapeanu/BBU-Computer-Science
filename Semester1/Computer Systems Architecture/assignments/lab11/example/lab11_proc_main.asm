;  the program calculates and displays the factorial of a number
;  the procedure factorial is defined in the file factorial.asm
bits 32
global start

import printf msvcrt.dll
import exit msvcrt.dll
extern printf, exit

; the code from factorial.asm will be inserted here
%include "factorial.asm"

segment data use32 class=data
	format_string db "factorial=%d", 10, 13, 0

segment code use32 class=code
start:
	push dword 6
	call factorial

	push eax
	push format_string
	call [printf]
	add esp, 4*2

	push 0
	call [exit]