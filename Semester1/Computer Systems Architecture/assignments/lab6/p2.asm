;@author: Rapeanu George - Alexandru(#8 in group list)
;Exercise 23: Being given a string of bytes, build a string of words which contains in the low bytes of the words the set of distinct characters from the given string and in the high byte of a word it contains the number of occurrences of the low byte of the word in the given byte string. 



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
    sir db 2, 4, 2, 5, 2, 2, 4, 4 
    len equ $ - sir
    fmt db "%hx", 0xd, 0xa, 0x0
    ans times 2 * len dw 0

; our code starts here
segment code use32 class=code
    start:
        ; ...
    
        cld
        mov edx, 0
        
        mov edi, ans
        loopOverAllBytes:
            mov ecx, len
            mov esi, sir
            mov bl, dl
            mov bh, 0
            
            cmp ecx, 0
            jz doneParseString
            parseString:
                lodsb
                cmp al, bl
                jne notEqual
                inc bh
                notEqual:
            loop parseString
            doneParseString:
            cmp bh, 0
            je notFound
            mov ax, bx
            stosw
            notFound:
        inc edx
        cmp edx, 256
        je doneLoopOverAllBytes
        jmp loopOverAllBytes
        doneLoopOverAllBytes:
    
        mov ecx, edi
        sub ecx, ans
        mov eax, ecx
        mov edx, 0
        mov ebx, 2
        div ebx
        mov ecx, eax
        
        cmp ecx, 0
        je donePrintLoop
        mov esi, ans
        printLoop:
            push ecx
            lodsw
            movzx eax, ax
            push eax
            push fmt
            call [printf]
            add esp, 8
            pop ecx
        loop printLoop
        donePrintLoop:
    
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
