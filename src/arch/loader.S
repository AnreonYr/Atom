.section .loader, "ax"
	.global loader_
	.global examination

	.code16

	loader_:
	# Shut interrupt
		cli
	
	# Shut A20 bus
		inw $0x92, %ax
		orw $0x2, %ax
		outw %ax, $0x92
	
	# Load gdt
		lgdt (gdt_describer)
	
	# Enable protect mode
		movl %cr0, %eax
		orl $0x1, %eax
		movl %eax, %cr0

	# Refresh register
		ljmp $code_selector, $protect_mode

	.code32

	protect_mode:
	# Init registers
		movw $data_selector, %ax
		movw %ax, %ds
		movw %ax, %es
		movw %ax, %ss
		movw %ax, %fs
		movw %ax, %gs

	# Load kernel

	# .text
		movl $0x500000, %edi
		movl $0x8, %ecx
		movw $0x8, %bx
		call read
	
	# .data
		movl $0x501000, %edi
		movl $0x10, %ecx
		movw $0x8, %bx
		call read

	# .rodata
		movl $0x502000, %edi
		movl $0x18, %ecx
		movw $0x8, %bx
		call read

	# .bss 0x503000 ~ 0x503FFF

	# stack
		movl $0x505FFF, %esp

		call create_pde
		call create_pte
		call enable_page

		call kernel

		jmp .


	.equ pa_pde, 0x100000
	.equ pa_pte, 0x101000

	create_pde:
		xchg %bx, %bx
		movl $pa_pde, %ebx
	# map pte0 to pde0
		movl $pa_pte, %eax
		orl $0x7, %eax
		movl %eax, (%ebx)

	# map pte0 to pde768
		add $0xc00, %ebx
		movl $pa_pte, %eax
		orl $0x7, %eax
		movl %eax, (%ebx)

	# map pde0 to pde769
	# map all page table to 0xC0004000 to 0xC0008000
		add $0x4, %ebx
		movl $pa_pde, %eax
		orl $0x107, %eax
		movl %eax, (%ebx)

	# map kernel to 0xC0008000 ~ 0xC0CFFFFF
		add $0x4, %ebx
		movl $pa_pte + 0x1000, %eax
		orl $0x7, %eax
		movl %eax, (%ebx)

		ret

	create_pte:
	# map 0x0 ~ 0x100000 to 0x0 ~ 0x100000
	# map 0x0 ~ 0x100000 to 0xC000000 to 0xC00FFFFF
		movl $pa_pte, %ebx
		movl $256, %ecx
		movl $0x0, %eax
		orl $0x7, %eax
	2:
		movl %eax, (%ebx)
		addl $0x1000, %eax
		addl $0x4, %ebx
		loop 2b

	# map kernel to 0xC0800000 ~ 0xC0CFFFFF
		movl $pa_pte + 0x1000, %ebx
		movl $256, %ecx
		movl $0x500000, %eax
		orl $0x7, %eax
	3:
		movl %eax, (%ebx)
		addl $0x1000, %eax
		addl $0x4, %ebx
		loop 3b

		ret

	enable_page:
		xchg %bx, %bx
		movl $pa_pde, %eax
		movl %eax, %cr3
		movl %cr0, %eax
		orl $0x80000000, %eax
		movl %eax, %cr0
	
	# stack in VA
		movl %esp, %eax
		subl $0x500000, %eax
		addl $0xC0800000, %eax
		movl %eax, %esp

		ret


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
gdt_e:


.fill 0x7fe-(.-loader_), 1, 0
examination:
	.word 0xaa55
