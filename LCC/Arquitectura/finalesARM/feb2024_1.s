.data
string: .asciz "%f\n"
str2: .asciz "La suma de las componentes es: %f\n"
.align 16
a: .float 1.0, 2.0, 3.0, 4.0, 5.0
b: .float 2.0, 4.0, 6.0, 8.0, 10.0
c: .float 0.0, 0.0, 0.0, 0.0, 0.0
.text
.global main
main:
    push {ip,lr}
    mov r0, #0
    vmov.f32 s16, r0
    vcvt.f32.s32 s16, s16
    ldr r4, =a
    ldr r5, =b
    ldr r6, =c
    mov r7, #0
    b loop
    
loop:
    vldr.f32 s0, [r4]
    vldr.f32 s1, [r5]

    vadd.f32 s0, s1, s0
    vstr s0, [r6]

    vcvt.f64.f32 d0, s0
    vmov r2, r3, d0
    ldr r0, =string
    bl printf

    vldr s0, [r6]
    vadd.f32 s16, s16, s0
    add r7, r7, #4
    add r4, r4, #4
    add r5, r5, #4
    add r6, r6, #4
    cmp r7, #20
    BNE loop

    ldr r0, =str2
    vcvt.f64.f32 d0, s16
    vmov r2, r3, d0
    bl printf

    mov r0, #0
    pop {ip,lr}
    bx lr

