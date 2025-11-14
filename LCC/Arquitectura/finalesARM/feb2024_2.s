.data
    string: .asciz "El resultado es %d\n"
    stringFallo: .asciz "Todos los argumentos deben ser positivos."
.align 16
.text
.global main
.global calculo

calculo:
    push {lr}
    push {r4}
    ldr r4, [sp, #8]
    push {r0-r3}

    cmp r0, #0
    cmpGT r1, #0
    cmpGT r2, #0
    cmpGT r3, #0
    cmpGT r4, #0

    BLLE foo
    
    cmp r0, #-1
    BEQ end_function

    pop {r0-r3}

    add r0, r0, r4
    add r0, r0, r1
    add r0, r0, r2
    add r0, r0, r3

    mov r1, r0
    ldr r0, =string
    push {r5}
    mov r5, r1
    bl printf
    
    pop {r5}
    mov r0, r5
    pop {r4, lr}
    bx lr

foo:
    push {lr}
    ldr r0, =stringFallo
    bl printf

    mvn r0, #0
    pop {lr}
    bx lr

end_function:
    pop {r0-r4, lr}
    bx lr

main:
    push {lr}
    mov r3, #5
    push {r3}
    mov r0, #1
    mov r1, #2
    mvn r2, #0
    mov r3, #4
    
    bl calculo

    pop {r3,lr}
    bx lr

