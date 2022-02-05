%IFNDEF GET_HUNDREDS
%DEFINE GET_HUNDREDS
bits 32
global _get_hundreds
segment data public data use32
segment code public code use32
_get_hundreds:
    push ebp
    mov ebp, esp
    
    mov eax, [ebp + 8]
    mov edx, 0
    mov ecx, 100
    div ecx
    mov ecx, 10
    mov edx, 0
    div ecx
    mov eax, edx
    mov edx, 0
    
    mov esp, ebp
    pop ebp
    ret
%ENDIF