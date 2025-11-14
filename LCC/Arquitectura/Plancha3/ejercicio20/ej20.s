.data
    salida: .asciz "La cantidad de argumentos es insuficiente\n"
.text
.global main

main:
    movq $2, %r11
    cmpq %rdi, %r11 
    jb fin
    
    
fin:
    movq $salida, %rdi
    call printf
    xorq %rax, %rax
    ret

