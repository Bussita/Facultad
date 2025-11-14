.data

    N1: .byte 100
    N2: .byte 120
    N3: .byte -63
    N4: .byte -56
    N5: .byte -91
    S1: .byte 0
    S2: .byte 0
    S3: .byte 0
    S4: .byte 0
    S5: .byte 0
.text
.global main

main:
    movb N1, %al
    addb N2, %al #Se activa OF ya que 220 no es representable con 8 bits
    movb %al, S1

    movb N3, %al
    addb N4, %al #Se activa CF ya que la operacion es incorrecta sin signo
    movb %al, S2

    movb N3, %al
    addb N5, %al #Se activan OF y CF, ya que hay acarreo en la suma en el BMS y ademas la suma produce desbordamiento y el res es incorrecto con signo
    movb %al, S3

    movb N2, %al
    subb N4, %al #Se activan ambas
    movb %al, S4

    movb N5, %al
    subb N2, %a #Se prende OF
    movb %al, S5    
    ret

