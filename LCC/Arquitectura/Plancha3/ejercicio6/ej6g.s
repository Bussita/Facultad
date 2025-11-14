.text
.global main
main:
    movl $0, %eax
    movl $-1, %ebx
    or %ebx, %eax
    ret

