// Copyright (c) 2023 AnreonYr. All Rights Reserved.

#include <stdint.h>

#ifndef TTY
#define TTY

#define TTY_COL 25
#define TTY_ROW 80

#define VGA_COLOR_BLACK 0x0
#define VGA_COLOR_BLUE 0x1
#define VGA_COLOR_GREEN 0x2
#define VGA_COLOR_CYAN 0x3
#define VGA_COLOR_RED 0x4
#define VGA_COLOR_MAGAENTA 0x5
#define VGA_COLOR_BROWN 0x6
#define VGA_COLOR_LIGHT_GREY 0x7
#define VGA_COLOR_DARK_GREY 0x8
#define VGA_COLOR_LIGHT_BLUE 0x9
#define VGA_COLOR_LIGHT_GREEN 0xa
#define VGA_COLOR_LIGHT_CYAN 0xb
#define VGA_COLOR_LIGHT_RED 0xc
#define VGA_COLOR_LIGHT_MAGAENTA 0xd
#define VGA_COLOR_LIGHT_BROWN 0xe
#define VGA_COLOR_WHITE 0xf

void tty_set_theme(uint8_t fg, uint8_t bg);
void tty_char_put(char symbol);
void tty_string_put(char *symbol);
void tty_screen_clear();
void tty_sreen_scroll();

#endif
