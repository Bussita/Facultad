.data
    a: .long 4
    b: .quad 0x1122334455667788

.text
.global main
main:
    movq b, %rax
    movw $-1, %ax
    movb $0xdd, %ah
    addb $8, %al
    shrb $1, %al
    movl $-1, %eax
    imull a
    ret

