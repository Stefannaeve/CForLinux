	.file	"1out.c"
	.text
	.section	.rodata
.LC0:
	.string	"Entering main"
	.text
	.globl	main
	.type	main, @function
main:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	%edi, -20(%rbp)
	movq	%rsi, -32(%rbp)
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$40, %edi
	call	malloc@PLT
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	addq	$8, %rax
	movl	(%rax), %edx
	movq	-8(%rbp), %rax
	addq	$20, %rax
	addl	$10, %edx
	movl	%edx, (%rax)
	movl	$30, -12(%rbp)
	movl	-12(%rbp), %eax
	addl	$40, %eax
	movl	%eax, -16(%rbp)
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	main, .-main
	.ident	"GCC: (Debian 12.2.0-14) 12.2.0"
	.section	.note.GNU-stack,"",@progbits
