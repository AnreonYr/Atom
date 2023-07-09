.section .text

.global _boot
.global print

.code16

_boot:
	movw $0x3, %ax
	int	 $0x10

	movw $0x0, %ax
	movw %ds, %ax
	movw %ax, %ss
	movw %ax, %es
	movw $0x7c00, %sp

	xchg %bx, %bx
	leaw message_1, %bx
	call print

	xchg %bx, %bx
	leaw message_2, %bx
	call print
	call disk_read

	jmp _loader

	jmp .

disk_read:

	movl $0x8000, %edi
	movl $0x1, %ecx
	movb $0x4, %bl

	movw $0x1f2, %dx
	movb %bl, %al
	outb %al, %dx

	inc %dx
	movb %cl, %al
	outb %al, %dx

	inc %dx
	shrl $8, %ecx
	movb %cl, %al
	outb %al, %dx
	
	inc %dx
	shrl $8, %ecx
	movb %cl, %al
	outb %al, %dx

	shrl $8, %ecx
	andb $0b1111, %cl

	inc %dx
	movb $0b11100000, %al
	orb %cl, %al
	outb %al, %dx

	inc %dx
	movb $0x20, %al
	outb %al, %dx

	xorl %ecx, %ecx
	movb %bl, %cl

	do:
		pushw %cx
		call delay
		call read
		popw %cx
		loop do
	ret

	delay:
		movw $0x1f7, %dx
			check:
				inb %dx, %al
				andb $0b10001000, %al
				cmpb $0b00001000, %al
				jnz check
	ret

	read:
		movw $0x1f0, %dx
		movw $256, %cx
			r:
				inw %dx, %ax
				movw %ax, (%edi)
				addl $0x2, %edi
				loop r
	ret

print:
	movb $0x0e, %ah
	movw %bx, %si
s:
	movb (%si), %al
	cmp $0, %al
	je e
	int $0x10
	inc %si
	jmp s
e:
	ret

message_1:
	.asciz "BOOTING ..."
	.byte	10, 13, 0
message_2:
	.byte	10, 13
	.asciz "LOADING ..."
	.byte	10, 13, 0

.fill 0x1FE-(.-_boot), 1, 0
	.word 0xaa55
