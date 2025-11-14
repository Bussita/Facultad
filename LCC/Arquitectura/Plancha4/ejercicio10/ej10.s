.data
    string: .asciz "El valor calculado es %d\n"

.align 16

.text
.global main
main:
    push {ip,lr}
    mov r0, #8

    bl potencia

    mov r1, r0
    ldr r0, =string
    bl printf

    pop {ip, lr}
    bx lr

potencia:
    mov r2, #1
    mov r0, r2, LSL r0
    bx lr

