#include "tty.h"
#include "vga.h"

void kmain(void) {
    terminal_init();
    char* str = "Booting kernel.\n";
    terminal_set_color(vga_color(red, white));
    terminal_write(str);

    str = "New lines are now accepted by the tty.\n";
    terminal_set_color(vga_color(light_blue, dark_grey));
    terminal_write(str);
}

