;@author: Rapeanu George - Alexandru(#8 in group list)
;Exercise 8:
;Given the words A and B, compute the byte C as follows:
;
;    the bits 0-5 are the same as the bits 5-10 of A
;    the bits 6-7 are the same as the bits 1-2 of B.
;
;Compute the doubleword D as follows:
;
;    the bits 8-15 are the same as the bits of C
;    the bits 0-7 are the same as the bits 8-15 of B
;    the bits 24-31 are the same as the bits 0-7 of A
;    the bits 16-23 are the same as the bits 8-15 of A.



bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

extern printf
import printf msvcrt.dll
                          
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a dw 1010_0010_0011_1111b
    b dw 0100_0011_0110_1011b
    c db 0                          ;should be 0101_0001b = 0x51
    d dd 0                          ;should be 0011_1111_1010_0010_0101_0001_0100_0011 = 0x3fa25143
    fmtByte db "%hhx",0xd,0xa,0x0
    fmtDword db "%x",0xd,0xa,0x0

; our code starts here
segment code use32 class=code
    start:
        ; ...
        
        mov ax, word[a]
        shr ax, 5
        and ax, word 0000_0000_0011_1111b
        or byte[c], al
        
        mov ax, word[b]
        shr ax, 1
        and ax, word 0000_0000_0000_0011b
        shl ax, 6
        or byte[c], al
        
        movzx eax, byte[c]
        
        push eax
        push fmtByte
        call [printf]
        add esp,8
        
        movzx eax, byte[c]
        shl eax, 8
        or dword[d], eax
        
        movzx eax, byte[b + 1]
        or dword[d], eax
        
        movzx eax, byte[a]
        shl eax, 24
        or dword[d], eax
        
        movzx eax, byte[a + 1]
        shl eax, 16
        or dword[d], eax        
        
        mov eax, dword[d]
        
        push eax
        push fmtDword
        call [printf]
        add esp,8
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
