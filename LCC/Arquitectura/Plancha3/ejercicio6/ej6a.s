.text
.global main
main:
    # Supongamos la operacion 0x1 << 31
    movl $1, %eax
    rol $31, %eax
    ret

