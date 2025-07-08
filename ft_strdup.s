global ft_strdup
extern malloc
extern ft_strlen
extern ft_strcpy
section .text

ft_strdup:
    ; Save original string pointer
    push    rdi
    
    ; Calculate string length using optimized ft_strlen
    call    ft_strlen
    
    ; Allocate memory for length + 1 (null terminator)
    inc     rax                 ; length + 1
    mov     rdi, rax            ; pass size to malloc
    call    malloc wrt ..plt    ; call malloc
    
    ; Check if malloc failed
    test    rax, rax
    jz      .malloc_failed
    
    ; Copy string using optimized ft_strcpy
    mov     rdi, rax            ; destination = allocated memory
    pop     rsi                 ; source = original string (from stack)
    push    rax                 ; save allocated memory pointer
    call    ft_strcpy           ; copy string
    pop     rax                 ; restore allocated memory pointer
    
    ret                         ; return pointer to duplicated string

.malloc_failed:
    pop     rdi                 ; clean up original pointer from stack
    xor     rax, rax            ; return NULL
    ret


section .note.GNU-stack noalloc noexec nowrite progbits