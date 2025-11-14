.data
	a: .float 4095
	b: .float 80
	strin: .asciz "El resultado es: %f\n"
.text
.global main
.global promedio
main: 
	@include <stdio.h>
	@
	@float promedio(float a, float b, float c){
	@	return (a+b+c)/3;
	@}
	@
	@int main(){
	@	float a = 4095, b = 80, c;
	@	c=a*b;
	@	printf("El resultado es: %f\n", promedio(a,b,c));
	@	return 0;
	@}
	push {lr, ip}
	LDR r3, =a
	VLDR.f32 s0, [r3]
	LDR r3, =b
	VLDR.f32 s1, [r3]
	VMUL.f32 s2, s0, s1
	BL promedio
	LDR r0, =strin
	VCVT.f64.f32 d0, s0
	VMOV r2, r3, d0
	bl printf
	pop {lr, ip}
	bx lr
promedio:
	push {lr}
	VADD.f32 s4, s0, s1
	VADD.f32 s4, s4, s2
	MOV r0, #3
	VMOV s1, r0
	VCVT.f32.s32 s0, s1
	VDIV.f32 s0, s4, s0
	pop {lr}
	bx lr
