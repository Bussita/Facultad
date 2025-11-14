.text
.global main
main:
    movl $0, %eax
    jmp L2

L3:
    incl %eax

L2:
    cmpl $4, %eax
    jle L3
    ret

