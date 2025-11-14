.text
.global main
main:
    movl $1, %eax
    movl $1, %ebx
    rol $31, %eax
    rol $15, %ebx
    or %ebx, %eax
    ret

