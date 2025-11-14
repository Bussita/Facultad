	.file	"test.c"
	.text
	.type	copiar_puntero_entero, @function
copiar_puntero_entero:
.LFB6:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movl	$4, %edi
	call	malloc@PLT
	movq	%rax, -8(%rbp)
	movq	-24(%rbp), %rax
	movl	(%rax), %edx
	movq	-8(%rbp), %rax
	movl	%edx, (%rax)
	movq	-8(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	copiar_puntero_entero, .-copiar_puntero_entero
	.type	comparar_puntero_entero, @function
comparar_puntero_entero:
.LFB7:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rax
	movl	(%rax), %edx
	movq	-16(%rbp), %rax
	movl	(%rax), %ecx
	movl	%edx, %eax
	subl	%ecx, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	comparar_puntero_entero, .-comparar_puntero_entero
	.type	destruir_puntero_entero, @function
destruir_puntero_entero:
.LFB8:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	free@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	destruir_puntero_entero, .-destruir_puntero_entero
	.section	.rodata
.LC0:
	.string	"%d "
	.text
	.type	imprimir_puntero_entero, @function
imprimir_puntero_entero:
.LFB9:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rax
	movl	(%rax), %eax
	movl	%eax, %esi
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE9:
	.size	imprimir_puntero_entero, .-imprimir_puntero_entero
	.section	.rodata
.LC1:
	.string	"test.c"
.LC2:
	.string	"avl_validar(arbol) == 1"
	.align 8
.LC3:
	.string	"Se inserto %d. Recorrido preorden: "
.LC4:
	.string	""
	.align 8
.LC5:
	.string	"avl_buscar(arbol2, numeros + i) == 1"
	.align 8
.LC6:
	.string	"avl_buscar(arbol2, otrosNumeros + i) == 0"
.LC7:
	.string	"Ok"
	.text
	.globl	main
	.type	main, @function
main:
.LFB10:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	addq	$-128, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	leaq	destruir_puntero_entero(%rip), %rax
	movq	%rax, %rdx
	leaq	comparar_puntero_entero(%rip), %rax
	movq	%rax, %rsi
	leaq	copiar_puntero_entero(%rip), %rax
	movq	%rax, %rdi
	call	avl_crear@PLT
	movq	%rax, -104(%rbp)
	movl	$0, -120(%rbp)
	jmp	.L8
.L10:
	call	rand@PLT
	movslq	%eax, %rdx
	imulq	$274877907, %rdx, %rdx
	shrq	$32, %rdx
	sarl	$6, %edx
	movl	%eax, %ecx
	sarl	$31, %ecx
	subl	%ecx, %edx
	imull	$1000, %edx, %ecx
	subl	%ecx, %eax
	movl	%eax, %edx
	movl	%edx, -124(%rbp)
	leaq	-124(%rbp), %rdx
	movq	-104(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	avl_insertar@PLT
	movq	-104(%rbp), %rax
	movq	%rax, %rdi
	call	avl_validar@PLT
	cmpl	$1, %eax
	je	.L9
	leaq	__PRETTY_FUNCTION__.0(%rip), %rax
	movq	%rax, %rcx
	movl	$37, %edx
	leaq	.LC1(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC2(%rip), %rax
	movq	%rax, %rdi
	call	__assert_fail@PLT
.L9:
	addl	$1, -120(%rbp)
.L8:
	cmpl	$499, -120(%rbp)
	jle	.L10
	movq	-104(%rbp), %rax
	movq	%rax, %rdi
	call	avl_destruir@PLT
	leaq	destruir_puntero_entero(%rip), %rax
	movq	%rax, %rdx
	leaq	comparar_puntero_entero(%rip), %rax
	movq	%rax, %rsi
	leaq	copiar_puntero_entero(%rip), %rax
	movq	%rax, %rdi
	call	avl_crear@PLT
	movq	%rax, -96(%rbp)
	movl	$10, -48(%rbp)
	movl	$20, -44(%rbp)
	movl	$15, -40(%rbp)
	movl	$25, -36(%rbp)
	movl	$30, -32(%rbp)
	movl	$16, -28(%rbp)
	movl	$18, -24(%rbp)
	movl	$19, -20(%rbp)
	movl	$0, -116(%rbp)
	jmp	.L11
.L12:
	movl	-116(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	leaq	-48(%rbp), %rax
	addq	%rax, %rdx
	movq	-96(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	avl_insertar@PLT
	movl	-116(%rbp), %eax
	cltq
	movl	-48(%rbp,%rax,4), %eax
	movl	%eax, %esi
	leaq	.LC3(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	-96(%rbp), %rax
	movl	$0, %ecx
	leaq	imprimir_puntero_entero(%rip), %rdx
	movl	$1, %esi
	movq	%rax, %rdi
	call	avl_recorrer@PLT
	leaq	.LC4(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	addl	$1, -116(%rbp)
.L11:
	cmpl	$7, -116(%rbp)
	jle	.L12
	movl	$-50, -80(%rbp)
	movl	$-4, -76(%rbp)
	movl	$5, -72(%rbp)
	movl	$14, -68(%rbp)
	movl	$27, -64(%rbp)
	movl	$56, -60(%rbp)
	movl	$0, -112(%rbp)
	jmp	.L13
.L15:
	movl	-112(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	leaq	-48(%rbp), %rax
	addq	%rax, %rdx
	movq	-96(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	avl_buscar@PLT
	cmpl	$1, %eax
	je	.L14
	leaq	__PRETTY_FUNCTION__.0(%rip), %rax
	movq	%rax, %rcx
	movl	$58, %edx
	leaq	.LC1(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC5(%rip), %rax
	movq	%rax, %rdi
	call	__assert_fail@PLT
.L14:
	addl	$1, -112(%rbp)
.L13:
	cmpl	$7, -112(%rbp)
	jle	.L15
	movl	$0, -108(%rbp)
	jmp	.L16
.L18:
	movl	-108(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	leaq	-80(%rbp), %rax
	addq	%rax, %rdx
	movq	-96(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	avl_buscar@PLT
	testl	%eax, %eax
	je	.L17
	leaq	__PRETTY_FUNCTION__.0(%rip), %rax
	movq	%rax, %rcx
	movl	$60, %edx
	leaq	.LC1(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC6(%rip), %rax
	movq	%rax, %rdi
	call	__assert_fail@PLT
.L17:
	addl	$1, -108(%rbp)
.L16:
	cmpl	$5, -108(%rbp)
	jle	.L18
	movl	$8, %edi
	call	malloc@PLT
	movq	%rax, -88(%rbp)
	movq	-88(%rbp), %rax
	movl	$20, (%rax)
	movq	-88(%rbp), %rdx
	movq	-96(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	avl_eliminar@PLT
	movq	%rax, -96(%rbp)
	movq	-96(%rbp), %rax
	movq	%rax, %rdi
	call	avl_destruir@PLT
	leaq	.LC7(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L20
	call	__stack_chk_fail@PLT
.L20:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE10:
	.size	main, .-main
	.section	.rodata
	.type	__PRETTY_FUNCTION__.0, @object
	.size	__PRETTY_FUNCTION__.0, 5
__PRETTY_FUNCTION__.0:
	.string	"main"
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
