.code16

.section .text

_start:
	.word 0xaa55
	.asciz "TESTING ..."
	.fill 0x1000-(.-_start), 1, 0xff
