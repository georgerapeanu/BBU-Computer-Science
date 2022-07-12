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
    
        mov ecx, lenS
        mov esi, s
        mov edi, d
        
        jecxz doneReadLoop
        
        cld
        readLoop:
            lodsb
            
            cmp al, 'A'
            jb notUppercase
            cmp al, 'Z'
            ja notUppercase
            
            stosb
            notUppercase:
            loop readLoop
        doneReadLoop:
        
        mov eax, edi
        sub eax, d
        
        push eax
        push fmtDword
        call [printf]
        add esp, 8
        
        mov ecx, eax
        mov eax, 0
        
        mov esi, d
        jecxz donePrintLoop
        printLoop:
            push ecx
            lodsb
            push eax
            push fmtChar
            call [printf]
            add esp, 8
            pop ecx
            loop printLoop
        donePrintLoop:
        
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
