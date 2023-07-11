.section .loader, "ax"
	.global loader_

	.code16

	loader_:
		xchg %bx, %bx
		cmpw $0xaa55, (magic_number)
		jz s
		jnz e
	s:
		leaw message_3, %bx
		call print
		jmp o
	e:
		leaw message_4, %bx
		call print
		jmp o
	o:
		jmp preparer_protect_mode

	preparer_protect_mode:
		cli

		inw $0x92, %ax
		orw $0x2, %ax
		outw %ax, $0x92

		lgdt (gdt_describer)

		movl %cr0, %eax
		orl $0x1, %eax
		movl %eax, %cr0

		ljmp $code_selector, $entry_protect_mode


	.code32

	entry_protect_mode:
		movw $data_selector, %ax
		movw %ax, %ds
		movw %ax, %es
		movw %ax, %ss
		movw %ax, %fs
		movw %ax, %gs

		movl $0x100000, %edi

		movl $0x5, %ecx
		movw $0x1, %bx
		call read

		call kernel_init

		jmp .
	
	read:
		movl $0x1f2, %edx
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
		movw %bx, %cx

		do:
			pushw %cx
			call delay
			call sread
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

		sread:
			movw $0x1f0, %dx
			movw $256, %cx
				r:
					inw %dx, %ax
					movw %ax, (%edi)
					addl $0x2, %edi
				loop r
		ret


.equ code_selector, 0x8
.equ data_selector, 0x10
.equ kernel_code, 0x18
.equ kernel_data, 0x20

gdt_describer:
	.word gdt_e - gdt_s -1
	.long gdt_null

gdt_s:
gdt_null:
	.quad 0
gdt_code:
	.long 0x0000ffff
	.long 0x00cf9a00
gdt_data:
	.long 0x0000ffff
	.long 0x00cf9200
kernel_code:
	.long 0x0000ffff
	.long 0x004f9a10
kernel_data:
	.long 0x0000ffff
	.long 0x004f9210
gdt_e:

message_3:
	.byte	10, 13
	.asciz "LOADER OK"
	.byte	10, 13, 0
message_4:
	.byte	10, 13
	.asciz "LOADER NO"
	.byte	10, 13, 0

.fill 0x7fe-(.-loader_), 1, 0
magic_number:
	.word 0xaa55
