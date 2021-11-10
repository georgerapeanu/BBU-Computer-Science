;@author: Rapeanu George - Alexandru(#8 in group list)
;Exercise 22: Two byte strings S1 and S2 of the same length are given. Obtain the string D where each element contains the minimum of the corresponding elements from S1 and S2. 


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
    
    s1 db 1, 3, 6, 2, 3, 7
    s2 db 6, 3, 8, 1, 2, 5
    len equ $ - s2
    d times len db 0
    
    fmtByte db "%hhx ",0x0
    fmtDword db "%d",0xd,0xa,0x0

; our code starts here
segment code use32 class=code
    start:
        ; ...
        
        mov ecx, 0
        
        cmp ecx, len
        jae doneReadLoop
        readLoop:
            mov al, byte[s1 + ecx]
            cmp al, byte[s2 + ecx]
            jbe doneMinimum
            mov al, byte[s2 + ecx]
            doneMinimum:
            mov byte[d + ecx], al
            inc ecx
            cmp ecx, len
            jb readLoop
        doneReadLoop:
        
        push len
        push fmtDword
        call [printf]
        add esp, 8
        
        mov ecx, len
        
        mov esi, d
        jecxz donePrintLoop
        printLoop:
            push ecx
            lodsb
            push eax
            push fmtByte
            call [printf]
            add esp, 8
            pop ecx
            loop printLoop
        donePrintLoop:
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
