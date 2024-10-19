GLOBAL cpuVendor, getSecs, getMins, getHours, getKeyPressed

section .text
	
cpuVendor:
	push rbp
	mov rbp, rsp

	push rbx

	mov rax, 0
	cpuid


	mov [rdi], ebx
	mov [rdi + 4], edx
	mov [rdi + 8], ecx

	mov byte [rdi+13], 0

	mov rax, rdi

	pop rbx

	mov rsp, rbp
	pop rbp
	ret


getSecs:
	push rbp
	mov rbp, rsp

	mov al, 0x00
	out 70h, al
	in al, 71h

	mov rsp, rbp
	pop rbp
	ret


getMins:
	push rbp
	mov rbp, rsp

	mov al, 0x02
	out 70h, al
	in al, 71h

	mov rsp, rbp
	pop rbp
	ret

getHours:
	push rbp
	mov rbp, rsp

	mov al, 0x04
	out 70h, al
	in al, 71h

	mov rsp, rbp
	pop rbp
	ret


getKeyPressed:
    mov rax, 0
    in al, 60h

    ret
