	.file	"optimizaciones.c"
	.text
	.p2align 4
	.globl	molinete1
	.type	molinete1, @function
molinete1:
.LFB42:
	.cfi_startproc
	endbr64
	addl	$500, contVisitantes(%rip)
	movq	%rdi, %rax
	ret
	.cfi_endproc
.LFE42:
	.size	molinete1, .-molinete1
	.p2align 4
	.globl	molinete2
	.type	molinete2, @function
molinete2:
.LFB46:
	.cfi_startproc
	endbr64
	addl	$500, contVisitantes(%rip)
	movq	%rdi, %rax
	ret
	.cfi_endproc
.LFE46:
	.size	molinete2, .-molinete2
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB44:
	.cfi_startproc
	endbr64
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	xorl	%esi, %esi
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	leaq	molinete1(%rip), %r12
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	movq	%r12, %rdx
	subq	$48, %rsp
	.cfi_def_cfa_offset 80
	movq	%fs:40, %rax
	movq	%rax, 40(%rsp)
	xorl	%eax, %eax
	leaq	12(%rsp), %r13
	leaq	16(%rsp), %rdi
	movl	$3, 12(%rsp)
	movq	%r13, %rcx
	leaq	32(%rsp), %rbp
	call	pthread_create@PLT
	xorl	%esi, %esi
	leaq	24(%rsp), %rdi
	movq	%r13, %rcx
	movq	%r12, %rdx
	call	pthread_create@PLT
	movq	16(%rsp), %rdi
	movq	%rbp, %rsi
	call	pthread_join@PLT
	movq	24(%rsp), %rdi
	movq	%rbp, %rsi
	call	pthread_join@PLT
	movq	40(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L7
	addq	$48, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 32
	xorl	%eax, %eax
	popq	%rbp
	.cfi_def_cfa_offset 24
	popq	%r12
	.cfi_def_cfa_offset 16
	popq	%r13
	.cfi_def_cfa_offset 8
	ret
.L7:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE44:
	.size	main, .-main
	.globl	contVisitantes
	.bss
	.align 4
	.type	contVisitantes, @object
	.size	contVisitantes, 4
contVisitantes:
	.zero	4
	.ident	"GCC: (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
