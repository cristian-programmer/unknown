
.set IRQ_BASE, 0x20
.section .text

.extern _ZN16InterruptManager15handleInterruptEhj

.macro HandleExeception num
.global _ZN16InterruptManager16HandleExeception\num\()Ev
 _ZN16InterruptManager16HandleExeception\num\()Ev:
    movb $\num, (interruptnumber)
    jmp int_bottom
.endm


.macro HandleInterruptRequest num
.global _ZN16InterruptManager26HandleInterruptRequest\num\()Ev
 _ZN16InterruptManager26HandleInterruptRequest\num\()Ev:
    movb $\num + IRQ_BASE, (interruptnumber)
    jmp int_bottom
.endm


HandleInterruptRequest 0x00
HandleInterruptRequest 0x01


int_bottom:

    pusha
    pushl %ds
    pushl %es
    pushl %fs
    pushl %gs

    pushl %esp
    push (interruptnumber)
    call _ZN16InterruptManager15handleInterruptEhj
    # addl $5, %esp

    movl %eax, %esp 

    popl %gs
    popl %fs
    popl %es
    popl %ds
    popa


.global _ZN16InterruptManager15InterruptIgnoreEv
_ZN16InterruptManager15InterruptIgnoreEv:
    iret


.data
    interruptnumber: .byte 0
