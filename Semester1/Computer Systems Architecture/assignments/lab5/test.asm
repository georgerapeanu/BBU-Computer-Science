;@author: Rapeanu George - Alexandru(#8 in group list)
;Exercise 8: A character string S is given. Obtain the string D that contains all capital letters of the string S.


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
    s db 'a', 'A', 'b', 'B', '2', '%', 'x', 'M'
    lenS equ $ - s
    d times lenS db 0
    fmtChar db "%c",0x0
    fmtDword db "%d",0xd,0xa

; our code starts here
segment code use32 class=code
    start:
        ; ...
        
        mov ecx, 10
        testLoop:
            times 0x100 db 0x90
            push ecx
            push fmtDword
            call [printf]
            add esp, 4
            pop ecx
            dec ecx
            cmp ecx, 0
            jz doneTestLoop
            jmp testLoop
        doneTestLoop:
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
