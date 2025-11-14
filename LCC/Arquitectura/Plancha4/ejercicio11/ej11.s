.data
    a: .float 1.0, 2.0, 3.0, 4.0
    string: .asciz "El determinante es %f\n"
.align 16

.text
.global main
main:
    push {r4,lr}
    ldr r4, =a

    vldr s0, [r4]
    vldr s1, [r4, #4]
    vldr s2, [r4, #8]
    vldr s3, [r4, #12]
    bl determinante

    vcvt.f64.f32 d0, s0
    vmov r2, r3, d0
    ldr r0, =string
    bl printf

    pop {r4, lr}
    bx lr

determinante:
    vmul.f32 s0, s0, s2
    vmul.f32 s1, s1, s3
    vsub.f32 s0, s0, s1
    bx lr
