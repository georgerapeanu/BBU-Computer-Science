;problem 23: Read a hexadecimal number with 2 digits from the keyboard. Display the number in base 10, in both interpretations: as an unsigned number and as an signed number (on 8 bits).

bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, scanf, printf               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import printf msvcrt.dll
import scanf msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a db 0
    byteHexaFmt db "%x", 0x0
    outputFmt db "signed: %d, unsigned: %u", 0xa, 0x0

; our code starts here
segment code use32 class=code
    start:
        
        push a
        push byteHexaFmt
        call [scanf]
        add esp, 8
        
        movzx eax, byte[a]
        push eax
        movsx eax, byte[a]
        push eax
        push outputFmt
        call [printf]
        add esp, 12
    
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
