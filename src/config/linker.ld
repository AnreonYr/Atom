OUTPUT_FORMAT(elf32-i386)
OUTPUT_ARCH(i386)
ENTRY(boot_)

SECTIONS {

	gdt = 0xC0806000;
	pde = 0xC0400000;
	pte = 0xC0401000;

	. = 0x7C00;
	.boot : AT (0x0) {
		* (.boot)
	}

	. = 0x8000;
	.loader : AT (0x200) {
		* (.loader) 
	}

	. = 0xC0800000;
	.text : AT(0x1000) ALIGN(4K) {
		text = .;
		* (.text)
	}

	. = 0xC0801000;
	.data : ALIGN(4K) {
		data = .;
		* (.data)
	}

	. = 0xC0802000;
	.rodata : ALIGN(4K) {
		rodata = .;
		* (.rodata)
	}

	. = 0xC0803000;
	.bss : ALIGN(4K) {
		bss = .;
		* (.bss)
	}

	. = 0xC0804000;
	.note.gnu.property : ALIGN(4K) {
		*(.note.gnu.property)
	}
}
