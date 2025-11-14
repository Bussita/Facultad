.data
str: .asciz "%d %d %f %d %d %d %d %d %d %d %f\n"
f: .double 3.14
g: .double 45.5

.text
.global main
main:
        pushq %rbp
        movq %rsp, %rbp
        movq $str, %rdi
        movl $1, %esi
        movl $2, %edx
        movl $3, %ecx
        movl $4, %r8d
        movl $5, %r9d
        # Argumentos adicionales en la pila (en orden inverso)
        subq $32, %rsp         	# Reserva espacio para alinear la pila
        movq $9, 24(%rsp)       # Poner 9 en la pila
        movq $8, 16(%rsp)       # Poner 8 en la pila
        movq $7, 8(%rsp)       	# Poner 7 en la pila
        movq $6, 0(%rsp)        # Poner 6 en la pila
        movl $1, %eax     	    # Necesario para llamadas a printf
        movsd f, %xmm0
        movsd g, %xmm1
        call printf
        xor %eax, %eax
        movq %rbp, %rsp
        popq %rbp
        ret

