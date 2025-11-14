.data
    b: .float 2.3
    str: .asciz "El valor escalado es %f\n"
.text
.global main
main:
    pushq %rbp
    pushq %rdi
    pushq %rsi
    movq 8(%rsi), %rdi
    call atoi
    pushq %rax
    movq (%rsp), %rdi
    movss b, %xmm0
    call scale
    popq %rax
    ret

scale:
    # Prologo
    pushq %rbp
    movq %rsp, %rbp
    # -----------------------
    pushq $8
    movq %rdi, %rax
    xorq %rdx, %rdx
    cvtsi2sd %rax, %xmm7
    cvtss2sd %xmm0, %xmm0
    mulsd %xmm7, %xmm0
    cvtsi2sd (%rsp), %xmm6
    addsd %xmm6, %xmm0
    cvttsd2siq %xmm0, %r10
    pushq %r10
    call imprime
    popq %r10
    cvtsi2sdq %r10, %xmm0
    popq %r10
    # Epilogo
    movq %rbp, %rsp
    popq %rbp
    ret

imprime:
    # Prologo
    pushq %rbp
    movq %rsp, %rbp
    # -------------
    pushq %r10
    movq $str, %rdi
    movb $1, %al
    call printf
    xorq %rax, %rax
    # Epilogo
    movq %rbp, %rsp
    popq %rbp
    ret

