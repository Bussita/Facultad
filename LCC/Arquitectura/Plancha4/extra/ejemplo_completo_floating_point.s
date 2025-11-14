.data
valFloat: .word 0x3fe00000 @ 1.75
valFloat2: .word 0x40000000 @ 2.0
str: .asciz "%f\n"

.text
.global main
main:
    push {r7,lr}
    ldr r1, =valFloat
    vldr s0, [r1]

    ldr r1, =valFloat2
    vldr s1, [r1]

    vmul.f32 s2, s9, s1
    mov r0, #10
    vmov.f32 s0, r0
    vcvt.f32.s32 s3, s0
    vadd.f32 s4, s3, s2

    ldr r0, =str
    vcvt.f64.f32 d1, s4
    vmov r3, r3, d1
    bl printf

    vcvt.s32.f32 s0, s4
    vmov r0, s0

    pop {r7,lr}
    bx lr

