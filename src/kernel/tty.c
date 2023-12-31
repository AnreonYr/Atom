#include "../include/tty.h"
#include <stdint.h>

// 颜色
uint16_t theme = 0;

// 文本缓冲区
uint16_t *buffer = (uint16_t *)(0xC04B8000);

// 列 行
uint16_t ROW, COL = 0;

void tty_set_theme(uint16_t fg, uint16_t bg) {
	theme = (bg << 4 | fg) << 8;
}

void tty_char_print(char symbol) {
	if (symbol == '\n') {
		ROW = 0;
		COL++;
	} else if (symbol == '\b') {
		ROW--;
	} else if (symbol == '\r') {
		ROW = 0;
	} else {
		*(buffer + ROW + COL * TTY_ROW) = (theme | symbol);
		ROW++;
		if (ROW >= TTY_ROW) {
			ROW = 0;
			COL++;
		}
	}
}

void tty_string_print(char *symbol) {
	while (*symbol != '\0') {
		tty_char_print(*symbol);
		symbol++;
	}
}

void tty_sreen_scroll() {}

void tty_screen_clear() {
	ROW = 0;
	COL = 0;
	for (uint16_t C = 0; C < TTY_COL; C++) {
		for (uint16_t R = 0; R < TTY_ROW; R++) {
			*(buffer + R + C * TTY_ROW) = theme;
		}
	}
}
