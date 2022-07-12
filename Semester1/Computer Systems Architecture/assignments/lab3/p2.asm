;@author: Rapeanu George - Alexandru(#8 in group list)
;Additions, subtactions - unsigned representation
;Exercise 22: (d+c) - (c+b) - (b+a) 


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
    a db 1
    b dw 2
    c dd 3
    d dq 4
    fmt db "%llx",0xd,0xa

; our code starts here
segment code use32 class=code
    start:
        ; ...
    
        xor eax,eax

        mov eax, dword[d]
        mov edx, dword[d + 4]
        
        add eax, dword[c]
        adc edx, 0
        
        sub eax, dword[c]
        sbb edx, 0
        
        movzx ebx, word[b]
        sub eax, ebx
        sbb edx, 0
        
        movzx ebx, word[b]
        sub eax, ebx
        sbb edx, 0

        movzx ebx, byte[a]
        sub eax, ebx
        sbb edx, 0
        
        push edx
        push eax
        push fmt
        call [printf]
        add esp,12
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
