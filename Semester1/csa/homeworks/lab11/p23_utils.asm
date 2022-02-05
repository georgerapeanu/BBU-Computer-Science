%IFNDEF GET_FROM_ALPHABET
%DEFINE GET_FROM_ALPHABET

get_from_alphabet: ;char get_from_alphabet(char* alphabet, char c);
    push ebp
    mov ebp, esp
    
    push ebx
    
    mov ebx, [ebp + 8]
    mov eax, [ebp + 12]
    sub eax, 'a'
    xlat
    
    pop ebx
    
    mov esp, ebp
    pop ebp
    ret
%ENDIF