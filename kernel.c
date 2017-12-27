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

    char junk[80*25 + 1];

    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 80; j++) {
            char new_char = (char) ('a' + ((i * COLS + j) % 26));
            junk[i * COLS + j] = new_char;
        }
    }

    junk[80*25] = 'A';

    terminal_write(junk);
}

