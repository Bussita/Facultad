.data
    str: .asciz "Cantidad de argumentos ingresados %d. La suma es %d."

.text
.global main

main:
    call suma


suma:
    # Prologo
    pushq %rbp
    movq %rsp, %rbp
    