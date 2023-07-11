OUTPUT_FORMAT(elf32-i386)
OUTPUT_ARCH(i386)
ENTRY(boot_)

MEMORY {
	boot (RX): ORIGIN = 0x7c00, LENGTH = 512
	loader (RX): ORIGIN = 0x8000, LENGTH = 2K
	kernel (RX): ORIGIN = 0x100000, LENGTH = 1M
}

SECTIONS {

	.boot : AT (0x0) {
		boot.o (.boot)
	} > boot
	.loader : AT (0x200) {
		loader.o (.loader) 
	} > loader

	.text : AT(0xa00) ALIGN(4K) {
		* (.text)
	} > kernel
	.data : {
		* (.data)
	} > kernel
	.rodata : {
		* (.rodata)
	} > kernel
	.bss : {
		* (.bss)
	} > kernel
	.note.gnu.property : ALIGN(4K) {
		*(.note.gnu.property)
	} > kernel
}
