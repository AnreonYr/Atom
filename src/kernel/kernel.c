// Copyright (c) 2023 AnreonYr. All Rights Reserved.

#include "../includes/tty.h"
#include <stdint.h>

extern void kernel_init() {
  tty_screen_clear();
  tty_set_theme(VGA_COLOR_BLUE, VGA_COLOR_BLACK);
  tty_string_put("HELLO WORLD\nSECOND LINNE");
}
