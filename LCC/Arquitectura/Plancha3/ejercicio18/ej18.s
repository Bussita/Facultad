calculo:
    # Prologo
    pushq %rbp
    movq %rsp, %rbp
    # ------------------------
    xorq %r10, %r10
    movq %rdi, %r10
    addq %rdx, %r10
    addq %rcx, %r10
    xorq %r11, %r11
    movq 16(%rbp), %r11
    addq 24(%rbp), %r11
    movq $1, %rax
    imul %r11
    imul %r10
    # Epilogo
    movq %rbp, %rsp
    popq %rbp
    ret

