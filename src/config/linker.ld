OUTPUT_FORMAT(elf32-i386)
OUTPUT_ARCH(i386)
ENTRY(_boot)

SECTIONS
{
	.boot 0x7c00 : AT(0x0) { boot.o(.text) }
	.loader 0x8000 : AT(0x200) { loader.o(.text) }
}
