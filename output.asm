.586
.model flat, c
.stack 4096

extern printf:near
extern exit:near

.data
	_printIntFormat BYTE "%d", 0
	_printFloatFormat BYTE "%f", 0
	_printStrFormat BYTE "%s", 0


.code
main PROC
	; Assignment
	mov eax, 1
	mov [a], eax
	; Assignment
	mov eax, 1
	mov [b], eax
	; Assignment
	mov eax, 5.89
	mov [c], eax
	; Comparison
	mov eax, [t0]
	cmp eax, b
	sete al
	movzx eax, al
	mov [t0], eax
	; Conditional jump
	mov eax, [t0]
	test eax, eax
	jz t1
	; Unhandled instruction: print abc
	jmp t2
t1:
	; Unhandled instruction: print ABC
t2:
	; Comparison
	mov eax, [t3]
	cmp eax, b
	sete al
	movzx eax, al
	mov [t3], eax
t4:
	; Conditional jump
	mov eax, [t3]
	test eax, eax
	jz t5
	; Unhandled instruction: print abc
	jmp t4
t5:
	; Assignment
	mov eax, 2
	mov [t6], eax
	; Conditional jump
	mov eax, [t6]
	test eax, eax
	jz t7
	; Assignment
	mov eax, 1
	mov [d], eax
	jmp t8
t7:
t8:

	; Program exit
	push 0
	call exit
main ENDP
END main
