.data
    a: .long 0x7fffffff
    b: .long 0x1
    str: .asciz "0x%x\n"
    str1: .asciz "Ejecutando foo1...\n"
    str2: .asciz "Ejecutando foo2...\n"
    str4: .asciz "0x%x\n"
    str5: .asciz "0x%x 0x%x\n"

.text

.global main 

main:
    pushq %rsp
    call foo2
    movq %rax, %rbx
    call foo1
    movq $str5, %rdi
    movq %rax, %rsi
    movq %rbx, %rdx
    call printf
    popq %rsp
    ret

foo1:
    # Prologo
    pushq %rbp
    movq %rsp, %rbp
    # ------------------
    xorq %rax, %rax
    movq $str1, %rdi
    call printf
    movl b, %r10d
    roll $31, %r10d
    addl a, %r10d
    movl %r10d, a
    movq $str4, %rdi
    movl a, %esi
    call printf
    movl a, %eax
    # Epilogo
    movq %rbp, %rsp
    popq %rbp
    ret

foo2:
    # Prologo 
    pushq %rbp
    movq %rsp, %rbp
    # -------------------------
    xorq %rax, %rax
    movq $str2, %rdi
    call printf
    movl b, %r10d
    addl a, %r10d
    movl %r10d, a
    xorq %rax, %rax
    movq $str4, %rdi
    movl a, %esi
    call printf
    movl a, %eax
    # Epilogo
    movq %rbp, %rsp
    popq %rbp
    ret

