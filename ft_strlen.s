global ft_strlen
section .text

ft_strlen:
	mov		rsi, rdi			; copy rdi pointer to rsi
	xor		rax, rax			; length = 0 (xor of 2 equals == 0)
	
	; Check if pointer is 4-byte aligned
	test	rdi, 3				; check if last 2 bits are 0 (4-byte aligned)
	jnz		.unaligned_start 	; if not aligned, handle byte by byte first
	
	; Pointer is aligned, use fast 4-byte processing
	jmp		.aligned_loop

.unaligned_start:
	; Handle unaligned bytes one by one until we reach 4-byte alignment
	cmp		byte [rsi], 0		; check if current byte is zero
	je		.end				; if zero, we're done
	inc		rax					; increment length
	inc		rsi					; move to next byte
	test	rsi, 3				; check if now 4-byte aligned
	jnz		.unaligned_start 	; if still not aligned, continue
	
align 16						; Ensure 16-byte alignment for performance
.aligned_loop:
	; Unrolled loop: process 16 bytes (4 × 4-byte chunks) per iteration
	
	; First 4 bytes
	mov		ecx, [rsi]			; load first 4 bytes
	mov		edx, ecx			; copy ecx to edx
	sub		edx, 0x01010101		; subtract 1 from each byte
	not		ecx					; invert bits in ecx
	and		ecx, 0x80808080		; isolate the highest bit of each byte
	and		ecx, edx			; check if any byte was zero
	jnz		.found_zero_chunk1	; if zero byte found, handle it
	
	; Second 4 bytes
	mov		ecx, [rsi + 4]		; load second 4 bytes
	mov		edx, ecx			; copy ecx to edx
	sub		edx, 0x01010101		; subtract 1 from each byte
	not		ecx					; invert bits in ecx
	and		ecx, 0x80808080		; isolate the highest bit of each byte
	and		ecx, edx			; check if any byte was zero
	jnz		.found_zero_chunk2	; if zero byte found, handle it
	
	; Third 4 bytes
	mov		ecx, [rsi + 8]		; load third 4 bytes
	mov		edx, ecx			; copy ecx to edx
	sub		edx, 0x01010101		; subtract 1 from each byte
	not		ecx					; invert bits in ecx
	and		ecx, 0x80808080		; isolate the highest bit of each byte
	and		ecx, edx			; check if any byte was zero
	jnz		.found_zero_chunk3	; if zero byte found, handle it
	
	; Fourth 4 bytes
	mov		ecx, [rsi + 12]		; load fourth 4 bytes
	mov		edx, ecx			; copy ecx to edx
	sub		edx, 0x01010101		; subtract 1 from each byte
	not		ecx					; invert bits in ecx
	and		ecx, 0x80808080		; isolate the highest bit of each byte
	and		ecx, edx			; check if any byte was zero
	jnz		.found_zero_chunk4	; if zero byte found, handle it
	
	; No zero found in any of the 4 chunks, continue
	add		rsi, 16				; Move to the next 16 bytes
	add		rax, 16				; Increment length by 16
	jmp		.aligned_loop

.found_zero_chunk1:
	; Zero found in first chunk [rsi + 0]
	mov		r8, rsi
	jmp		.byte_check
	
.found_zero_chunk2:
	; Zero found in second chunk [rsi + 4]
	add		rax, 4				; Add 4 for the first complete chunk
	lea		r8, [rsi + 4]		; Point to start of second chunk
	jmp		.byte_check
	
.found_zero_chunk3:
	; Zero found in third chunk [rsi + 8]
	add		rax, 8				; Add 8 for the first two complete chunks
	lea		r8, [rsi + 8]		; Point to start of third chunk
	jmp		.byte_check
	
.found_zero_chunk4:
	; Zero found in fourth chunk [rsi + 12]
	add		rax, 12				; Add 12 for the first three complete chunks
	lea		r8, [rsi + 12]		; Point to start of fourth chunk
	jmp		.byte_check

.byte_check:
	cmp		byte [r8], 0		; check if byte is zero
	je		.end				; if zero, end
	inc		rax					; increment length
	inc		r8					; move to next byte
	jmp		.byte_check

.end:
	ret

; Mark stack as non-executable (fixes linker warning)
section .note.GNU-stack noalloc noexec nowrite progbits
