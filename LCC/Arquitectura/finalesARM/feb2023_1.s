.data
    a: .word 1, 2, 3, 4
    b: .word 5, 6, 7, 8
    c: .word 0, 0, 0, 0

.text
.global main
.global suma

suma:
    sub sp, sp, #4
    mov r3, #0
    str r3, [sp]

    push {r4,r5,r6,r7,r8}
    ldr r4, =c


    b loop

loop:
    cmp r3, r2
    BGE end_function
    
    mov r8, #4
    mul r5, r3, r8
    ldr r6, [r0,r5]
    ldr r7, [r1, r5]
    add r6, r6, r7
    str r6, [r4, r5]

    add r3, r3, #1
    b loop

end_function:
    pop {r4,r5,r6,r7,r8}
    add sp, sp, #4
    bx lr

main:
    push {lr}
    sub sp, sp, #8
    mov r0, #4
    str r0, [sp]

    ldr r0, =a
    ldr r1, =b
    ldr r2, [sp]
    bl suma

    mov r0, #0
    add sp, sp, #8
    pop {lr}
    bx lr

