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

	asm volatile ("xchg %bx, %bx");

	map(0x3ff00000, 0x800000, PG_PR | PG_CD | PG_RW | PG_US, 0);
}

void kernel() {
	kernel_init();
	while (1) {}
}
