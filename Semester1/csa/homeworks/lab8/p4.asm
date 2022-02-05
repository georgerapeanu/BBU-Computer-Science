;Problem 23: A file name and a hexadecimal number (on 16 bits) are given. Create a file with the given name and write each nibble composing the hexadecimal number on a different line to file.
bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, fopen, fclose, scanf, fprintf               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    
import fopen msvcrt.dll
import fclose msvcrt.dll
import scanf msvcrt.dll
import fprintf msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    fd dd 0
    fileName resb 100
    number dw 0
    readInputFmt db "%s %hx", 0x0
    printHexaNibbleFmt db "%c", 0xa, 0x0
    lookupTable db "0123456789abcdef",0x0
    writeMode db "w",0x0

; our code starts here
segment code use32 class=code
    start:
        
        push number
        push fileName
        push readInputFmt
        call [scanf]
        add esp, 12
        
        push writeMode
        push fileName
        call [fopen]
        add esp, 8
        mov dword[fd], eax
        
        mov ecx, 4
        printNibblesLoop:
            push ecx
            mov ax, word[number]
            and ax, 0xf000
            shr ax, 12
            movzx eax, ax
            movzx eax, byte[lookupTable + eax]
            push eax
            push printHexaNibbleFmt
            push dword[fd]
            call [fprintf]
            add esp, 12
            shl word[number], 4
            pop ecx
            loop printNibblesLoop
        donePrintNibbleLoop:
        
        push dword[fd]
        call [fclose]
        add esp, 4
        
    
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
