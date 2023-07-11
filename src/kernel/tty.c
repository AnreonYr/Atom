// Copyright (c) 2023 AnreonYr. All Rights Reserved.

#include "../includes/tty.h"
#include <stdint.h>

// 颜色
uint16_t theme = VGA_COLOR_BLACK;

// 文本缓冲区
uint16_t *buffer = (uint16_t *)(0xB8000);

// 列 行
uint16_t ROW, COL = 0;

void tty_set_theme(uint8_t fg, uint8_t bg) { theme = (bg << 4 | fg) << 8; }

void tty_char_put(char symbol) {
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

void tty_string_put(char *symbol) {
  while (*symbol != '\0') {
    tty_char_put(*symbol);
    symbol++;
  }
}

void tty_sreen_scroll() {}

void tty_screen_clear() {
  for (uint8_t C = 0; C < TTY_COL; C++) {
    for (uint8_t R = 0; R < TTY_ROW; R++) {
      *(buffer + R + C * TTY_ROW) = theme;
    }
  }
}
