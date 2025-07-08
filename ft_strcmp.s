global ft_strcmp
section .text

ft_strcmp:
    ; Check if both strings are 4-byte aligned
    mov     rcx, rdi        ; Copy first string pointer
    or      rcx, rsi        ; OR both pointers
    test    rcx, 3          ; Check if either is unaligned
    jnz     .unaligned_cmp  ; If unaligned, use byte-by-byte
    
    ; Both pointers are aligned, use fast 4-byte comparison
    jmp     .aligned_cmp

.unaligned_cmp:
    ; Handle unaligned case or align to 4-byte boundary
    mov     al, [rdi]       ; Load byte from first string
    mov     dl, [rsi]       ; Load byte from second string
    
    cmp     al, dl          ; Compare the two bytes
    jne     .not_equal      ; If different, handle the difference
    
    test    al, al          ; Check if we reached null terminator
    jz      .equal          ; If null, strings are equal
    
    inc     rdi             ; Move to next byte in first string
    inc     rsi             ; Move to next byte in second string
    
    ; Check if now both are aligned
    mov     rcx, rdi
    or      rcx, rsi
    test    rcx, 3
    jnz     .unaligned_cmp  ; Still unaligned, continue byte-by-byte
    
align 16                    ; Align the fast loop for performance
.aligned_cmp:
    ; Compare 4 bytes at a time
    mov     ecx, [rdi]      ; Load 4 bytes from first string
    mov     edx, [rsi]      ; Load 4 bytes from second string
    
    cmp     ecx, edx        ; Compare the 4-byte chunks
    jne     .chunks_differ  ; If different, need byte-by-byte comparison
    
    ; Check for null byte in the 4-byte chunk using same trick as strlen
    mov     r8d, ecx        ; Copy the 4 bytes
    sub     r8d, 0x01010101 ; Subtract 1 from each byte
    not     ecx             ; Invert bits
    and     ecx, 0x80808080 ; Isolate high bits
    and     ecx, r8d        ; Check if any byte was zero
    jnz     .equal          ; If zero found, strings are equal
    
    ; No null byte and chunks are equal, continue
    add     rdi, 4          ; Move to next 4 bytes
    add     rsi, 4          ; Move to next 4 bytes
    jmp     .aligned_cmp    ; Continue with next 4 bytes

.chunks_differ:
    ; 4-byte chunks differ, find the exact differing byte
    mov     al, [rdi]       ; Load first byte of chunk
    mov     dl, [rsi]       ; Load first byte of chunk
    cmp     al, dl          ; Compare first bytes
    jne     .not_equal      ; If different, we found the difference
    
    ; First bytes are equal, check second byte
    mov     al, [rdi + 1]   ; Load second byte
    mov     dl, [rsi + 1]   ; Load second byte
    cmp     al, dl          ; Compare second bytes
    jne     .not_equal      ; If different, we found the difference
    
    ; Second bytes are equal, check third byte
    mov     al, [rdi + 2]   ; Load third byte
    mov     dl, [rsi + 2]   ; Load third byte
    cmp     al, dl          ; Compare third bytes
    jne     .not_equal      ; If different, we found the difference
    
    ; Must be the fourth byte that differs
    mov     al, [rdi + 3]   ; Load fourth byte
    mov     dl, [rsi + 3]   ; Load fourth byte
    ; Fall through to .not_equal

.not_equal:
    ; Calculate difference: *s1 - *s2
    movzx   rax, al         ; Zero-extend first byte to RAX
    movzx   rdx, dl         ; Zero-extend second byte to RDX
    sub     rax, rdx        ; Subtract to get difference
    ret

.equal:
    xor     rax, rax        ; Return 0 (strings are equal)
    ret


section .note.GNU-stack noalloc noexec nowrite progbits
