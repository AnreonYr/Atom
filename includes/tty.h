#define TTY_COL 80
#define TTY_ROW 25

#define VGA_COLOR_BLACK				0x0
#define VGA_COLOR_BLUE				0x1
#define VGA_COLOR_GREEN				0x2
#define VGA_COLOR_CYAN				0x3
#define VGA_COLOR_RED				0x4
#define VGA_COLOR_MAGAENTA			0x5
#define VGA_COLOR_BROWN				0x6
#define VGA_COLOR_LIGHT_GREY		0x7
#define VGA_COLOR_DARK_GREY			0x8
#define VGA_COLOR_LIGHT_BLUE		0x9
#define VGA_COLOR_LIGHT_GREEN		0xa
#define VGA_COLOR_LIGHT_CYAN		0xb
#define VGA_COLOR_LIGHT_RED			0xc
#define VGA_COLOR_LIGHT_MAGAENTA	0xd
#define VGA_COLOR_LIGHT_BROWN		0xe
#define VGA_COLOR_WHITE				0xf

typedef unsigned short vga_atrributes;

void tty_set_theme (vga_atrributes fg, vga_atrributes bg);
void tty_char_put (char symbol);
void tty_string_put (char* symbol);
void tty_screen_clear ();
void tty_sreen_scroll ();
