.text
.global main
main:
    movl $0x80000000, %eax
    addl %eax, %eax
    ret

