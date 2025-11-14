.data
    a: .long 1, 2, 3, 4 # a empieza 0x404028
    g: .quad 0x1122334455667788
    msg: .asciz "Imprime %c\n"
.text
.global main
main:
    subq $8, %rsp # rsp = 0x7fffffffebc0
    movq $g, %rax # rax = 0x404038 (es la direccion de a, con un corrimiento de 16 bytes ya que cada long ocupa 4)
    movl g+4, %eax # rax = 0x11223344 (4 lugares luego de la direccion de g)
    movq $3, %rbx # rbx = 0x3
    movb a(,%rbx,4), %al # rax = 0x11223304(guarda en al 1 byte del valor en a+12, esto es donde empieza el dato 4   de la lista. Como se guarda en little endian, esto copia a al 0x03)
    leaq msg, %rdi # rdi =0x40403f
    movb (%rdi, %rbx, 2), %sil # sil = "i" (Guarda el byte en la direccion 0x404045)
    xorl %eax, %eax # rax = 0x0
    call printf # rax =0xa
    addq $8, %rsp # rsp = 0x7fffffffebc8 (el rsp es calee saved según la convención de llamada)
    ret
