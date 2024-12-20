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
	; Assignment
	mov eax, 5.9
	mov [d], eax
	; Unhandled complex assignment: str = "str"
	; Unhandled complex assignment: bol = true
	; Unhandled complex assignment: ch = 'a'
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
	mov eax, 0
	mov [i], eax
	; Comparison
	mov eax, [t6]
	cmp eax, 5
	setl al
	movzx eax, al
	mov [t6], eax
t7:
	; Conditional jump
	mov eax, [t6]
	test eax, eax
	jz t8
	; Unhandled instruction: print abc
	; Unhandled instruction: i++
	jmp t7
t8:
	; Assignment
	mov eax, 2
	mov [t9], eax
	; Conditional jump
	mov eax, [t9]
	test eax, eax
	jz t10
	; Assignment
	mov eax, 1
	mov [e], eax
	; Comparison
	mov eax, [t12]
	cmp eax, 1
	sete al
	movzx eax, al
	mov [t12], eax
	; Conditional jump
	mov eax, [t12]
	test eax, eax
	jz t13
	; Unhandled instruction: print 1
	jmp t14
t13:
t14:
	jmp t11
t10:
t11:
	; Assignment
	mov eax, 2
	mov [day], eax
	; Unhandled instruction: if (day != 1) goto t16
	jmp t15
t16:
	; Unhandled instruction: print Monday\n
	jmp t15
	jmp t15
	; Unhandled instruction: if (day != 2) goto t17
	jmp t15
t17:
	; Unhandled instruction: print Tuesday\n
	jmp t15
	jmp t15
	; Unhandled instruction: if (day != 3) goto t18
	jmp t15
t18:
	; Unhandled instruction: print Wednesday\n
	jmp t15
	jmp t15
	; Unhandled instruction: if (day != 4) goto t19
	jmp t15
t19:
	; Unhandled instruction: print Thursday\n
	jmp t15
	jmp t15
	; Unhandled instruction: if (day != 5) goto t20
	jmp t15
t20:
	; Unhandled instruction: print Friday\n
	jmp t15
	jmp t15
	; Unhandled instruction: if (day != 6) goto t21
	jmp t15
t21:
	; Unhandled instruction: print Saturday\n
	jmp t15
	jmp t15
	; Unhandled instruction: if (day != 7) goto t22
	jmp t15
t22:
	; Unhandled instruction: print Sunday\n
	jmp t15
	jmp t15
t15:
	; Assignment
	mov eax, 2
	mov [t23], eax
	; Conditional jump
	mov eax, [t23]
	test eax, eax
	jz t24
	; Assignment
	mov eax, 4
	mov [f], eax
	jmp t25
t24:
t25:

	; Program exit
	push 0
	call exit
main ENDP
END main
