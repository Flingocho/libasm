global ft_write
extern __errno_location
section .text

ft_write:
    ; System call number for write is 1
    mov     rax, 1                     ; syscall number for sys_write
    ; rdi already contains fd (first parameter)
    ; rsi already contains buf (second parameter)  
    ; rdx already contains count (third parameter)
    syscall                            ; invoke system call
    
    ; Check for error (negative return value)
    cmp     rax, 0
    jl      .error                     ; if negative, handle error
    ret                                ; return number of bytes written

.error:
    ; Save the negative error code
    neg     rax                         ; make error code positive
    mov     r8, rax                     ; save error code in r8
    
    ; Call __errno_location() to get errno address
    push    r8                          ; save error code
    call    __errno_location wrt ..plt  ; get errno location
    pop     r8                          ; restore error code
    
    ; Set errno to the error code
    mov     [rax], r8d                  ; store error code in errno (32-bit)
    
    ; Return -1
    mov     rax, -1
    ret


section .note.GNU-stack noalloc noexec nowrite progbits