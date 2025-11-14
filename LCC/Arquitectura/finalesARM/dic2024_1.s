.data
    array: .word 0xff00000f, 0x00001f80, 0xe0000000, 0x00f00000, 0x00000111
    string1: .asciz "El determinante es positivo. Su valor es %d\n"
    string2: .asciz "El determinante es negativo. Su valor es %d\n"
    string3: .asciz "El determinante es nulo.\n"

.text
.global main
.global determinante

determinante:
    push {r4,r5}
    mul r4, r0, r2
    mul r5, r1, r3
    sub r0, r4, r5
    pop {r4, r5}
    bx lr

main:
    push {lr}
    
    ldr r0, =array
    ldr r1, [r0,#4]
    ldr r2, [r0,#8]
    ldr r3, [r0,#12]
    ldr r0, [r0]
    push {r0-r3}

    bl determinante

    push {r0}

    mov r1, r0    
    cmp r1, #0
    ldrGT r0, =string1
    ldrLT r0, =string2
    ldrEQ r0, =string3
    bl printf

    pop {r0}
    pop {r0-r3}
    mov r0, #0
    pop {lr}
    bx lr

