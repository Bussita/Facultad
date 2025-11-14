.text
.global main
main:
    movl $-1, %eax
    movl $1, %ebx
    rol $8, %ebx
    notl %ebx
    and %ebx, %eax
    ret

