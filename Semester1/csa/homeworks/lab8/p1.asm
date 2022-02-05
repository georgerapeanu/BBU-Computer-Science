;problem 8: A natural number a (a: dword, defined in the data segment) is given. Read a natural number b from the keyboard and calculate: a + a/b. Display the result of this operation. The values will be displayed in decimal format (base 10) with sign.

bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, printf, scanf               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
import scanf msvcrt.dll 
import printf msvcrt.dll 
import printf msvcrt.dll
                       
                          

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a dd 2300
    b dd 0
    dwordFMT db "%d",0x0
    dwordFMTOutput db "%d",0xa, 0x0

; our code starts here
segment code use32 class=code
    start:
    
        push b
        push dwordFMT
        call [scanf]
        add esp, 8
        
        mov eax, dword[a]
        mov ebx, dword[b]
        cdq
        idiv ebx
        add eax, dword[a]
        
        push eax
        push dwordFMT
        call [printf]
        add esp, 8
        
        
    
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
