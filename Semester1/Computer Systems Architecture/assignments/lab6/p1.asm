;@author: Rapeanu George - Alexandru(#8 in group list)
;Exercise 8: A list of doublewords is given. Obtain the list made out of the low bytes of the high words of each doubleword from the given list with the property that these bytes are palindromes in base 10.



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
    s dd 12345678h, 1A2C3C4Dh, 98FCDC76h
    lens equ ($ - s) / 4
    fmt db "%hhx ", 0xd, 0xa, 0x0
    current_inverse db 0
    ans times lens db 0

; our code starts here
segment code use32 class=code
    start:
        ; ...
        cld
        mov esi, s
        mov edi, ans
        
        mov ecx, lens
        
        mov bl, 10 ;base
        jecxz doneParseString
        parseString:
            lodsd
            shr eax, 16
            and eax, 0x000000ff
            
            mov byte[current_inverse], 0
            push eax
            invertAL:
                mov ah, 0
                div bl
                mov bh, ah
                
                push eax
                
                mov al, byte[current_inverse]
                mul bl
                add al, bh
                mov byte[current_inverse], al
                
                pop eax
                
                cmp al, 0
            jne invertAL
            pop eax
            cmp al, byte[current_inverse]
            jne notPalindrome
            stosb
            notPalindrome:
            
        loop parseString
        doneParseString:   
          
        mov eax, edi
        sub eax, ans
        
        mov ecx, eax
        mov esi, ans
        cmp ecx, 0
        jz endPrintLoop
        printLoop:
            push ecx
            lodsb
            movzx eax, al
            push eax
            push fmt
            call [printf]
            add esp, 8
            pop ecx
        loop printLoop
        endPrintLoop:
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
