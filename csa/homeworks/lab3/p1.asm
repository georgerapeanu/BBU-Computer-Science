;@author: Rapeanu George - Alexandru(#8 in group list)
;Additions, subtactions - unsigned representation
;Exercise 8: (a+b-d)+(a-b-d) 


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
    
        mov eax, 0
        mov edx, 0
        
        movzx ebx, byte[a]
        add eax, ebx
        adc edx,0
        
        movzx ebx, word[b]
        add eax, ebx
        adc edx,0
        
        mov ebx, dword[d]
        mov ecx, dword[d + 4]
        
        sub eax,ebx
        sbb edx,ecx
        
        movzx ebx, byte[a]
        add eax, ebx
        adc edx,0
        
        movzx ebx, word[b]
        sub eax, ebx
        sbb edx,0
        
        mov ebx, dword[d]
        mov ecx, dword[d + 4]
        
        sub eax,ebx
        sbb edx,ecx
        
        push edx
        push eax
        push fmt
        call [printf]
        add esp,12
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
