.text
.global main
main:
    mov r3, #0x8000
    str r6, [r3, #12]
    strb r7,