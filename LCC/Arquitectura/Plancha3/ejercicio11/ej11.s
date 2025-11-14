.data
    arr: .byte 1, 2, 3, 4
    longitud: .long 4

.text
.global main
main:
    push %rbp
    subq longitud, %rsp
    movq longitud, %rcx
    movq $arr, %rax                 # base
    movq longitud, %rbx             # indice
    decq %rbx
    jmp apilar

apilar:                             # apilo top 4 3 2 1 bottom
    xorq %rdx, %rdx
    movb (%rax, %rbx, 1), %dl
    movb %dl, (%rsp)
    decq %rbx
    incq %rsp
    loop apilar

seguir:
    subq longitud, %rsp
    movq $arr, %rax
    movq longitud, %rcx
    jmp invertir


invertir:
    movb (%rsp), %dl         # Cargar el byte en %dl desde la dirección apuntada por %rsp
    movb %dl, (%rax)         # Guardar el byte en la dirección apuntada por %rax
    incq %rax
    incq %rsp
    loop invertir

continuar:
    pop %rbp
    ret

.section .note.GNU-stack, "", @progbits
