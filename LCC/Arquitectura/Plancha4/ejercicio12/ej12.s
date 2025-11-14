.data
a: .word 1, 2, 3, 4
b: .word 2, 3, 4, 5
string: .asciz "La suma es %d\n"
.align 16

.text
.global main
main:
    push {lr}
    mov r3, #4
    push {r3}
    mov r2, r3
    ldr r0, =a
    ldr r1, =b
    bl suma

    mov r1, r0
    ldr r0, =string
    bl printf

    mov r0, #0
    pop {r3, lr}
    bx lr

suma:
    push {lr}
    push {r4,r5}
    mov r3, #0
    cmp r3, r2
    mov r4, #0
    blt loop
    pop {r4,r5,lr}
    mov r0, r3
    bx lr

loop:
    ldr r5, [r0, r4]
    add r3, r3, r5
    ldr r5, [r1, r4]
    add r3, r3, r5
    add r4, r4, #4
    cmp r4, r2, LSL #2
    BNE loop
    mov r0, r3
    pop {r4,r5,lr}
    bx lr
