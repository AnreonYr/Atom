.section .boot, "ax"
	.global boot_
	.global print

	.code16

	boot_:
	# Set display mode to 80*25
		movw $0x3, %ax
		int	 $0x10
	
	# Init registers
		movw $0x0, %ax
		movw %ds, %ax
		movw %ax, %ss
		movw %ax, %es
		movw $0x7c00, %sp

		leaw message_1, %bx
		call print
	
	# Load loader
	# %edi memory address | %ecx start sector | %bl sector number
		movl $0x8000, %edi
		movl $0x1, %ecx
		movb $0x4, %bl
		call read
	
	# Examine
		cmpw $0xaa55, (examination)
		jz finish
		jnz error
	error:
		leaw message_3, %bx
		call print
		hlt
	finish:
		leaw message_2, %bx
		call print
	
		jmp loader_
		
	print:
		movb $0x0e, %ah
		movw %bx, %si
	1:
		movb (%si), %al
		cmp $0, %al
		je 2f
		int $0x10
		inc %si
		jmp 1b
	2:
		ret

	read:
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
			call sread
			popw %cx
			loop do
		ret

		delay:
			movw $0x1f7, %dx
				1:
					inb %dx, %al
					andb $0b10001000, %al
					cmpb $0b00001000, %al
					jnz 1b
		ret

		sread:
			movw $0x1f0, %dx
			movw $256, %cx
				2:
					inw %dx, %ax
					movw %ax, (%edi)
					addl $0x2, %edi
				loop 2b
		ret

message_1:
	.asciz "BOOT OK"
	.byte	10, 13, 0
message_2:
	.byte	10, 13
	.asciz "LOAD OK"
	.byte	10, 13, 0
message_3:
	.byte	10, 13
	.asciz "LOAD NO"
	.byte	10, 13, 0

.fill 0x1FE-(.-boot_), 1, 0
.word 0xaa55
