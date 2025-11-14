.data
    a: .word 1

.text
.global main

main:
    push {lr}
    ldr r6, =0xBEEFFACE
    ldr r3, =a
    str r6, [r3]
    ldrb r4, [r3]
    pop {lr}
    bx lr
