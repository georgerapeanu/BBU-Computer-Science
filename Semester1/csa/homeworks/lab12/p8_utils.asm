bits 32
global _byte_to_base_8
segment data public data use32
segment code public code use32

%IFNDEF BYTE_TO_BASE_8
%DEFINE BYTE_TO_BASE_8

_byte_to_base_8: ;void byte_to_base_8(BYTE value, char* answer);
    push ebp
    mov ebp, esp
    sub esp, 4
    push esi
    push edi

    
    mov edx, [ebp + 8]
    lea edi, [ebp - 1]
    std
    
    mov ecx, 3
    .get_octal_digits_loop:
        mov eax, edx
        shr edx, 3
        and eax, 7
        add eax, '0'
        stosb
    loop .get_octal_digits_loop
    
    lea esi, [edi + 1]
    mov edi, [ebp + 12]
    
    cld
    mov ecx, 3
    .get_most_significant_digit:
    
        cmp ecx, 1
        je .done_get_most_significant_digit
        cmp byte[esi], '0'
        jne .done_get_most_significant_digit
        inc esi
    
    loop .get_most_significant_digit
    .done_get_most_significant_digit:
    
    .tmp_loop:
        movsb
    loop .tmp_loop
    
    mov eax, 0 ;store 0x0 at the end of the string
    stosb
    
    pop edi
    pop esi
    mov esp, ebp
    pop ebp
    ret

%ENDIF