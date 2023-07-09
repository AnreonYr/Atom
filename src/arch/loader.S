.section .text

.global _loader

.code16

_loader:
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

	jmp .

.equ code_selector, 0x8
.equ data_selector, 0x10

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
	jmp .

message_3:
	.byte	10, 13
	.asciz "LOADER OK"
	.byte	10, 13, 0
message_4:
	.byte	10, 13
	.asciz "LOADER NO"
	.byte	10, 13, 0

.fill 0x7fe-(.-_loader), 1, 0xff
magic_number:
	.word 0xaa55
