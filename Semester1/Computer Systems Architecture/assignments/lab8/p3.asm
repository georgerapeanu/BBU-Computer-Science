;problem 8: A text file is given. Read the content of the file, determine the uppercase letter with the highest frequency and display the letter along with its frequency on the screen. The name of text file is defined in the data segment.

bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, fopen, fclose, fscanf, printf               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll
import fscanf msvcrt.dll
import printf msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    filename db "p3.in",0x0
    readmode db "r",0x0
    fd dd 0
    frequency times 'Z' - 'A' + 1 dd 0
    current_char db 0
    readCharFmt db "%c",0x0
    most_frequent_letter_index db 0
    outputFmt db "most frequent letter is %c with frequency %u", 0xa, 0x0
    fileDoesntExistFmt db "Error: specified file doesn't exist", 0xa, 0x0

; our code starts here
segment code use32 class=code
    start:
        
        push readmode
        push filename
        call [fopen]
        add esp, 8
        mov [fd], eax
        cmp eax, 0
        je fileDoesntExist
        
        readLoop:
            push current_char
            push readCharFmt
            push dword[fd]
            call [fscanf]
            add esp, 12
            cmp eax, 1
            jne doneReadLoop
            cmp byte[current_char], 'A'
            jb notUpperCase
            cmp byte[current_char], 'Z'
            ja notUpperCase
            mov al, byte[current_char]
            sub al, 'A'
            movzx eax, al
            inc dword[eax * 4 + frequency]
            notUpperCase:
            jmp readLoop
        doneReadLoop:
        
        mov esi, frequency
        mov ecx, 'Z' - 'A' + 1
        
        mov byte[most_frequent_letter_index], 0
        getMaxLoop:
            lodsd
            movzx ebx, byte[most_frequent_letter_index]
            cmp eax, dword[frequency + ebx * 4]
            jbe notMoreFrequent
            lea eax, [esi - 4]  ;esi points to the next letter address so we need to subtract 4 to get the correct address
            sub eax, frequency
            shr eax, 2
            mov byte[most_frequent_letter_index], al
            notMoreFrequent:
            loop getMaxLoop
        doneGetMaxLoop:
        
        mov al, byte[most_frequent_letter_index]
        add al, 'A'
        
        movzx eax, al
        movzx ebx, byte[most_frequent_letter_index]
        push dword[frequency + 4 * ebx]
        push eax
        push outputFmt
        call [printf]
        add esp, 12
        
        
        push dword[fd]
        call [fclose]
        add esp, 4
        
        jmp doExit
        
        fileDoesntExist:
        push fileDoesntExistFmt
        call [printf]
        add esp, 4
        
        doExit:
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
        
        
        