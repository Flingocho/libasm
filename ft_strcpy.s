global ft_strcpy
section .text

ft_strcpy:
    mov     rax, rdi        ; Save destination pointer for return value
    
    ; Check if both source and dest are 4-byte aligned
    mov     rcx, rsi        ; Copy source pointer
    or      rcx, rdi        ; OR both pointers
    test    rcx, 3          ; Check if either is unaligned
    jnz     .unaligned_copy ; If unaligned, use byte-by-byte
    
    ; Both pointers are aligned, use fast 4-byte copying
    jmp     .aligned_copy

.unaligned_copy:
    ; Handle unaligned case or align to 4-byte boundary
    mov     dl, [rsi]       ; Load byte from source
    mov     [rdi], dl       ; Store byte to destination
    test    dl, dl          ; Check if null terminator
    jz      .end            ; If null, we're done
    inc     rsi             ; Move to next source byte
    inc     rdi             ; Move to next destination byte
    
    ; Check if now both are aligned
    mov     rcx, rsi
    or      rcx, rdi
    test    rcx, 3
    jnz     .unaligned_copy ; Still unaligned, continue byte-by-byte
    
align 16                    ; Align the fast loop for performance
.aligned_copy:
    ; Copy 4 bytes at a time with zero detection
    mov     ecx, [rsi]      ; Load 4 bytes from source
    
    ; Check for null byte using the same trick as strlen
    mov     edx, ecx        ; Copy the 4 bytes
    sub     edx, 0x01010101 ; Subtract 1 from each byte
    not     ecx             ; Invert bits
    and     ecx, 0x80808080 ; Isolate high bits
    and     ecx, edx        ; Check if any byte was zero
    jnz     .has_null       ; If zero found, handle carefully
    
    ; No null byte, safe to copy all 4 bytes
    mov     ecx, [rsi]      ; Reload original 4 bytes
    mov     [rdi], ecx      ; Store 4 bytes to destination
    add     rsi, 4          ; Move source pointer by 4
    add     rdi, 4          ; Move dest pointer by 4
    jmp     .aligned_copy   ; Continue with next 4 bytes

.has_null:
    ; Null byte detected in these 4 bytes, copy byte by byte
    mov     dl, [rsi]       ; Load byte from source
    mov     [rdi], dl       ; Store byte to destination
    test    dl, dl          ; Check if null terminator
    jz      .end            ; If null, we're done
    inc     rsi             ; Move to next source byte
    inc     rdi             ; Move to next destination byte
    jmp     .has_null       ; Continue until null found

.end:
    ret                     ; Return original destination pointer





section .note.GNU-stack noalloc noexec nowrite progbits