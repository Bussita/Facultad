.text
.global main
main:
    movq $0xffffffff11111111, %rax # caso de prueba
    movl %eax, %ebx
    rolq $32, %rbx
    rorq $32, %rax
    orq %rbx, %rax
    ret
# Parece ser que las instrucciones ror/rol, desplaza el bit menos significativo al mas significativo y o visceversa
# Por lo tanto no es necesario usar el registro rbx y el programa es simplemente una linea ror $32, %rax.


