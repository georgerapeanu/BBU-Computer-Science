bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit,printf               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
import printf msvcrt 

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    fmt db "%x",0x0
    x dd 0fffdh
; our code starts here
segment code use32 class=code
    start:
        ; ...
        
        mov ax, 054ah
        cmp ax, 54ah
        jne a2
        
        mov eax, 0
        
        push eax
        push fmt
        
        call [printf]
        add esp, 8
        
        a2:
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
 