;@author: Rapeanu George - Alexandru(#8 in group list)
;Multiplications, divisions - unsigned interpretation
;Exercise 8:  1/a+200*b-c/(d+1)+x/a-e; a,b-word; c,d-byte; e-doubleword; x-qword


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
    a dw 1
    b dw 2
    c db 3
    d db 4
    e dd 5
    x dq 6
    result dq 0
    fmt db "%llu",0xd,0xa

; our code starts here
segment code use32 class=code
    start:
        ; ...
        
        mov dx, 0
        mov ax, 1
        mov bx, word[a]
        
        div bx
        
        movzx eax,ax
        add dword[result], eax
        adc dword[result + 4], 0
        
        mov ax, word[b]
        mov bx, word 200
        mul bx
        push dx
        push ax
        pop eax
        add dword[result], eax
        adc dword[result + 4], 0
        
        movzx bx, byte[d]
        add bx, 1
        movzx ax, byte[c]
        mov dx, 0
        div bx
        movzx eax, ax
        
        sub dword[result], eax
        sbb dword[result + 4], 0
        
        mov eax, dword[x]
        mov edx, dword[x + 4]
        movzx ebx, word[a]
        div ebx
        
        add dword[result], eax
        adc dword[result + 4], 0
        
        mov eax, dword[e]
        sub dword[result], eax
        sbb dword[result + 4], 0
        
        push dword[result + 4]
        push dword[result]
        push fmt
        call [printf]
        add esp,12
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
