#include "../include/tty.h"
#include "../include/dt.h"
#include "../include/page.h"
#include <stdint.h>

void kernel_init() {
	// Init TTY
	tty_screen_clear();
	tty_set_theme(TTY_COLOR_GREEN, TTY_COLOR_BLACK);
	tty_string_put("kernel_init");

	// Init gdt
	gdt_init();
}

void kernel() {
	kernel_init();
	while (1) {}
}
