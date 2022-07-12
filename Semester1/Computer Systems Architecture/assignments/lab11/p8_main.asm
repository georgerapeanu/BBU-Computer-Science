;Problem 8: Show for each number from 32 to 126 the value of the number (in base 8) and the character with that ASCII code. 
bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, printf               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import printf msvcrt.dll
%include "p8_utils.asm"
                          
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    fmtBase8 db "Base 8 of %d is %s", 0xa, 0x0
    fmtChar db "Char with ASCII %d is %c",0xa, 0x0
    base8_representation resb 4

; our code starts here
segment code use32 class=code
    start:
        
        mov esi, 32
        loop_over_values:
            cmp esi, 126
            ja done_loop_values
            
            push base8_representation
            push esi
            call byte_to_base_8
            add esp, 8
            
            push base8_representation
            push esi
            push fmtBase8
            call [printf]
            add esp, 12
            
            push esi
            push esi
            push fmtChar
            call [printf]
            add esp, 12
            
            inc esi
            jmp loop_over_values
        done_loop_values:
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
