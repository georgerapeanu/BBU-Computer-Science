;@author: Rapeanu George - Alexandru(#8 in group list)
;Multiplications, divisions
;a,b,c - byte, d - word
;Exercise 8: (100*a+d+5-75*b)/(c-5) 


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
    a db 1
    b db 2
    c db 3
    d dw 4
    fmt db "%hd",0xd,0xa

; our code starts here
segment code use32 class=code
    start:
        ; ...
    
        xor eax,eax
        mov al, byte[a]
        mov bl,100
        mul bl
        add ax, word[d]
        add ax, 5
        mov cx, ax
        
        
        movsx ax, byte[b]
        mov bx, 75
        mul bx
        sub cx, ax
        
        movsx eax, cx
        movsx bx, byte[c]
        sub bx, 5
;        cwd     ;sign extends ax into dx
;        idiv bx ;division on signed numbers 
        mov edx, 0
        div bx
        
        movsx eax,ax
        push eax
        push fmt
        call [printf]
        add esp,8
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
