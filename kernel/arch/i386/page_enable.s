.text
.global _enablePaging
.type _enablePaging, @function
_enablePaging:
	push %ebp
	mov %esp, %ebp

	mov 8(%esp), %eax
	mov %eax, %cr3

	mov %cr0, %eax
	or $0x80000000, %eax
	mov %eax, %cr0

	mov %ebp, %esp
	pop %ebp
	ret
