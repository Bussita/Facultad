.data
    array: .word 1,2,3,4,5,6,7,8,9,10
.text
.global main
main:
    mov r0, #15
    mov r1, #10
    ldr r2, =array
    ldr r3, [r2,#24]
    add r0, r3, r1

    ldr r3, [r2, #28]
    add r4, r3, r1
    str r4, [r2, #36]
    bx lr

