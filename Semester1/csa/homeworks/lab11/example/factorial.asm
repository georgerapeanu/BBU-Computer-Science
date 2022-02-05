
; we need to avoid multiple inclusion of this file
%ifndef _FACTORIAL_ASM_ ; if _FACTORIAL_ASM_ is not defined
%define _FACTORIAL_ASM_ ; then we define it

; procedure definition
factorial:                  ; int _stdcall factorial(int n)
	mov eax, 1
	mov ecx, [esp + 4]  ; read the parameter from the stack

	repeat: 
		mul ecx
	loop repeat         ; the case ecx = 0 is not considered

	ret 4
%endif