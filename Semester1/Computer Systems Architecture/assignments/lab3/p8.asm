;@author: Rapeanu George - Alexandru(#8 in group list)
;imuliplications, idivisions - signed interpretation

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
    b db 2
    c db 3
    e dd 4
    x dq -5
    result dq 0
    fmt db "%lld",0xd,0xa

; our code starts here
segment code use32 class=code
    start:
        ; ...
;Exercise 22: a/2+b*b-a*b*c+e+x; a,b,c-byte; e-doubleword; x-qword
        
        mov ah, 0
        mov al, byte[a]
        mov bl, byte 2
        idiv bl
        movsx eax, al
        cdq
        add dword[result],eax
        adc dword[result + 4],edx
        
        mov al, byte[b]
        mov bl, byte[b]
        mul bl
        movsx eax,ax
        cdq
        add dword[result],eax
        adc dword[result + 4],edx
        
        mov al, byte[a]
        mov bl, byte[b]
        mul bl
        movsx bx, byte[c]
        mul bx
        push dx
        push ax
        pop eax
        cdq
        sub dword[result],eax
        sbb dword[result + 4],edx
        mov eax, dword[e]
        cdq
        add dword[result],eax
        adc dword[result + 4],edx
        
        mov eax, dword[x]
        mov edx, dword[x + 4]
        add dword[result],eax
        adc dword[result + 4],edx
    
        push dword[result + 4]
        push dword[result]
        push fmt
        call [printf]
        add esp,12
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
