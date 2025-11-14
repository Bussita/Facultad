.text
.global main
main:
    movl $0xaa, %ebx
    movl $0xaa, %eax
    rol $24, %eax
    or %ebx, %eax
    ret

