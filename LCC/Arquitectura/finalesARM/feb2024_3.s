.data
    string: .asciz "El resultado es %f\n"

.align 16

.text
.global main
.global promedio

main:
    push {lr}

    ldr r0, =0x00000fff
    vmov.f32 s0, r0
    vcvt.f32.s32 s0, s0

    mov r1, #80
    vmov.f32 s1, r1
    vcvt.f32.s32 s1, s1

    mul r2, r0, r1
    vmov.f32 s2, r2
    vcvt.f32.s32 s2, s2

    vpush {s0-s2}

    bl promedio

    vcvt.f64.f32 d0, s0
    vmov r2, r3, d0
    ldr r0, =string
    bl printf

    vpop {s0-s2}
    pop {lr}
    bx lr

promedio:
    vadd.f32 s0, s0, s1
    vadd.f32 s0, s0, s2
    vadd.f32 s0, s0, s3

    mov r1, #3
    vmov.f32 s4, r1
    vcvt.f32.s32 s4, s4

    vdiv.f32 s0, s0, s4
    bx lr

