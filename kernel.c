#include "tty.h"
#include "vga.h"

void kmain(void) {
  char *str = "Color kernel. :D";
  terminal_init();
  terminal_set_color(vga_color(red, white));
  terminal_write(str);
}



