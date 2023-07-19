#include <stdint.h>

#ifndef TTY
#define TTY

#define TTY_COL 25
#define TTY_ROW 80

#define TTY_COLOR_BLACK				0x0
#define TTY_COLOR_BLUE				0x1
#define TTY_COLOR_GREEN				0x2
#define TTY_COLOR_CYAN				0x3
#define TTY_COLOR_RED				0x4
#define TTY_COLOR_MAGAENTA			0x5
#define TTY_COLOR_BROWN				0x6
#define TTY_COLOR_LIGHT_GREY		0x7
#define TTY_COLOR_DARK_GREY			0x8
#define TTY_COLOR_LIGHT_BLUE		0x9
#define TTY_COLOR_LIGHT_GREEN		0xA
#define TTY_COLOR_LIGHT_CYAN		0xB
#define TTY_COLOR_LIGHT_RED			0xC
#define TTY_COLOR_LIGHT_MAGAENTA	0xD
#define TTY_COLOR_LIGHT_BROWN		0xE
#define TTY_COLOR_WHITE				0xF

void tty_set_theme(uint16_t fg, uint16_t bg);
void tty_char_print(char symbol);
void tty_string_print(char *symbol);
void tty_screen_clear();
void tty_sreen_scroll();

#endif
