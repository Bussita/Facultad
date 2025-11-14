.data
list: .long 10, 20, 30, 40, 50, 60, 70, 80, 90, 100
length: .byte 10

.text
.global main

main:
    xorq %rax, %rax
    xorq %rcx, %rcx
    movb length, %cl
    decb %cl
    leaq list, %rbx
sumar:
    addl (%rbx, %rcx, 4), %eax
    loop sumar
    addl (%rbx, %rcx, 4), %eax
    ret
