.data
    format: .asciz "%ld\n"
    format2: .asciz "0x%x\n"
    i: .quad 0xDEADBEEF

.text
.global main

main:
    pushq $0x11223344
    movq $format, %rdi # El primer argumento es el formato.
    movq $1234, %rsi # El valor a imprimir.
    xorq %rax, %rax # Cantidad de valores de punto flotante.
    call printf
    
    movq $format2, %rdi
    movq %rsp, %rsi
    call printf
    
    movq $format2, %rdi
    movq $format, %rsi
    call printf

    movq $format2, %rdi
    movq (%rsp), %rsi
    call printf

    movq $format, %rdi
    pushq $0x2
    pushq $0x1
    movq 8(%rsp), %rsi
    call printf

    movq $format, %rdi
    movq i, %rsi
    call printf

    movq $format2, %rdi
    movq $i, %rsi
    call printf
    
    addq $24, %rsp
    ret

