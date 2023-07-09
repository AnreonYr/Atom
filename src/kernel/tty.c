#include "../includes/tty.h"
#include <stdint.h>

vga_atrributes theme = VGA_COLOR_BLACK;
vga_atrributes *buffer = (vga_atrributes *)(0xb8000);

uint8_t ROW;
uint8_t COL;

void tty_set_theme(vga_atrributes fg, vga_atrributes bg) {
	theme = (bg << 4 | fg) << 8;
}

void tty_char_put(char symbol) {
	*(buffer + COL + ROW  * TTY_ROW) = (theme | symbol);
}

void tty_string_put(char *symbol) {
	while (*symbol != '\0') {
		tty_char_put(*symbol);
		symbol ++;
	}
}

void tty_sreen_scroll() {

}

void tty_screen_clear() {
	for (uint8_t C = 0; C < ROW; C++) {
		for (uint8_t R = 0; R < COL; R++) {
			*(buffer + C + R * TTY_ROW) = theme;
		}
	}
}
