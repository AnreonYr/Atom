#include "../include/tty.h"
#include "../include/dt.h"
#include "../include/mem.h"
#include <stdint.h>

void kernel_init() {
	// Init TTY
	tty_screen_clear();
	tty_set_theme(TTY_COLOR_GREEN, TTY_COLOR_BLACK);
	tty_string_print("kernel_init");

	// Init gdt
	// Init idt
	idt_init();

	mmap(0x40000000, 0x800000, 7);
	mmap(0x50000000, 0x800000, 7);

	asm volatile ("xchg %bx, %bx");
	ummap(0x40000000);
	asm volatile ("xchg %bx, %bx");
	ummap(0x50000000);
}

void kernel() {
	kernel_init();
	while (1) {}
}
