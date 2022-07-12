;@author: Rapeanu George - Alexandru(#8 in group list)
;Exercise 22:
;Given the doubleword A and the word B, compute the word C as follows:
;
;    the bits 0-4 of C are the invert of the bits 20-24 of A
;    the bits 5-8 of C have the value 1
;    the bits 9-12 of C are the same as the bits 12-15 of B
;    the bits 13-15 of C are the same as the bits 7-9 of A


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
    
    a dd 0111_1000_0101_0100_0000_1101_0101_1010b
    b dw 0101_0110_0111_1101b
    c dw 0                                          ;should be 0100_1011_1111_1010b = 0x4bfa
    fmt db "%x",0xd,0xa

; our code starts here
segment code use32 class=code
    start:
        ; ...
    
    
        mov eax, dword[a]
        shr eax, 20
        not eax
        and eax, 0x1f
        or word[c], ax
        
        or word[c], 0x000001e0

        mov ax, word[b]
        shr ax, 12
        and ax, 0xf
        shl ax, 9
        or word[c], ax
        
        mov eax, dword[a]
        shr eax, 7
        and eax, 0x7
        shl eax, 13
        
        or word[c], ax
    
        movsx eax, word[c]
        push eax
        push fmt
        call [printf]
        add esp,8
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
