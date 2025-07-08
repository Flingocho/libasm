global ft_strlen
section .text

ft_strlen:
	mov		rsi, rdi		; copy rdi pointer to rsi
	xor		rax, rax		; length = 0 (xor of 2 equals == 0)

align 16					; Ensure 16-byte alignment for performance
.loop4:
	mov		ecx, [rsi]		; load 4 bytes
	; Check zero bytes in ecx using bit trick:
	mov		edx, ecx		; copy ecx to edx
	sub		edx, 0x01010101	; subtract 1 from each byte
	not		ecx				; invert bits in ecx
	and		ecx, 0x80808080	; isolate the highest bit of each byte
	and		ecx, edx		; check if any byte was zero
	jz		.no_zero4		; if zero byte not found, jump

    ; Zero byte found in these 4 bytes — check byte by byte
	mov		r8, rsi			; copy rsi pointer to r8
.loop1:
	cmp		byte [r8], 0	; check if byte is zero
	je		.end			; if zero, end
	inc		rax				; increment length
	inc		r8				; move to next byte
	jmp		.loop1			

.no_zero4:
	add		rsi, 4			; Move to the next 4 bytes
	add		rax, 4			; Increment length by 4
	jmp		.loop4

.end:
	ret
