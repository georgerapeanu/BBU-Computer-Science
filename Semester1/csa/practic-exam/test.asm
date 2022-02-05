bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
extern printf
extern fread
extern fopen
extern fclose
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import printf msvcrt.dll
import fread msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    MAX_CODE_LENGTH_INCLUDING_0_TERMINATING_CHARACTER equ 1024
    BUFFER_LENGTH equ 1024
    access_mode db "r", 0x0
    fisier db "input.txt", 0x0
    buffer resb BUFFER_LENGTH
    fd dd 0
    error_opening_file_message db "An error occured while opening the file", 0x0
    string_fmt db "%s", 0xd, 0xa, 0x0
    code_with_separator_fmt db "#%s",0x0
    code_without_separator_fmt db "%s", 0x0
    current_code resb MAX_CODE_LENGTH_INCLUDING_0_TERMINATING_CHARACTER
    read_bytes dd 0
    has_previous_print db 0

; our code starts here
segment code use32 class=code

    flush_code: ;void flush_code(char* code) // flushes the given code if it respects the given propery
        push ebp
        mov ebp, esp
        sub esp, 4 ; [ebp - 4] holds the length of the given string
        push esi
        
        mov esi, dword[ebp + 8]
        mov dword[ebp - 4], 0
        
        get_length_loop:
            lodsb
            cmp al, 0
            je done_get_length_loop
            inc dword[ebp - 4]
            jmp get_length_loop
        done_get_length_loop:
        
        cmp dword[ebp - 4], 0
        je dont_print
        
        mov ecx, dword[ebp - 4]
        mov eax, dword[ebp + 8]
        mov dl, byte[eax]
        cmp dl, byte[eax + ecx - 1]
        jne dont_print
        
        push current_code
        
        cmp byte[has_previous_print], 1
        je print_with_separator
        push code_without_separator_fmt
        jmp done_separator_if
        print_with_separator:
        push code_with_separator_fmt
        jmp done_separator_if
        done_separator_if:
        
        call [printf]
        add esp, 8
        
        mov byte[has_previous_print], 1
        
        dont_print:
        
        pop esi
        mov esp, ebp
        pop ebp
        
        ret
    start:
        
        push access_mode
        push fisier
        call [fopen]
        add esp, 8
        cmp eax, 0
        je error_opening_file
        mov dword[fd], eax
        
        
        mov edi, current_code
        read_file_loop:
            push dword [fd]
            push dword BUFFER_LENGTH
            push dword 1
            push buffer
            call [fread]
            add esp, 16
            mov dword[read_bytes], eax
            
            mov ecx, dword[read_bytes]
            mov esi, buffer
            jecxz done
            process_read_bytes_loop:
                push ecx
                lodsb
                cmp al, '#'
                jne dont_flush
                mov al, 0
                stosb
                push current_code
                call flush_code
                add esp, 4
                mov edi, current_code
                jmp done_if
                dont_flush:
                stosb
                done_if:
                pop ecx
            loop process_read_bytes_loop
            
            cmp dword[read_bytes], BUFFER_LENGTH
            jb done
            jmp read_file_loop
        
    
        jmp just_exit
    
        error_opening_file:
        push error_opening_file_message
        push string_fmt
        call [printf]
        add esp, 8
        jmp just_exit
    
        done:
        
        mov al, 0
        stosb
        push current_code
        call flush_code
        add esp, 4
        mov edi, current_code
       
        push dword[fd]
        call [fclose]
        add esp, 4
       
        
        just_exit:
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
