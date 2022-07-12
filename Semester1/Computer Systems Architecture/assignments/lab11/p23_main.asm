; Problem 23: Read a string s1 (which contains only lowercase letters). Using an alphabet (defined in the data segment), determine and display the string s2 obtained by substitution of each letter of the string s1 with the corresponding letter in the given alphabet.
; Example:
; The alphabet:  OPQRSTUVWXYZABCDEFGHIJKLMN
; The string s1: anaaremere
; The string s2: OBOOFSASFS
bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, getchar, printf               
import exit msvcrt.dll
import getchar msvcrt.dll
import printf msvcrt.dll    
                          
                          
%include "p23_utils.asm"

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    alphabet db "OPQRSTUVWXYZABCDEFGHIJKLMN"
    fmt_char db "%c", 0x0

; our code starts here
segment code use32 class=code
    start:

        read_loop:
            call [getchar]
            cmp eax, -1
            je done_read_loop
            
            push eax
            push alphabet
            call get_from_alphabet
            add esp, 8
            
            movzx eax, al
            push eax
            push fmt_char
            call [printf]
            add esp, 8
        jmp read_loop    
        done_read_loop:
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
