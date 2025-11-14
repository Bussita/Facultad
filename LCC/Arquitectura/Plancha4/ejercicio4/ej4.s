.text
.global main
main:
    push {lr}
    mov r7, #0x8c, 4
    mov r7, #0x42, 30
    mvn r7, #2
    mvn r7, #0x8c, 4
    pop {lr}
    bx lr
