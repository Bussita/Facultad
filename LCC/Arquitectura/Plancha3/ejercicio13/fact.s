.text
.global fact2
.global fact1

fact2:
    movq $1, %rax
    movl %edi, %ecx
fact2aux:
    mul %rcx
    loop fact2aux

fact1:
    movq $1, %r10
    cmpq %rdi, %r10
    jbe end
    mul %rdi
    decq %rdi
    call fact1

end:
    ret

