#include "tty.h"
#include "vga.h"

static size_t terminal_row;
static size_t terminal_col;
static uint8_t terminal_color;
static uint16_t *terminal_buffer;

void terminal_init(void) {
    terminal_row = 0;
    terminal_col = 0;
    terminal_color = vga_color(light_grey, black);
    terminal_buffer = (uint16_t *) 0xb8000;

    for (size_t r = 0; r < ROWS; r++) {
        for (size_t c = 0; c < COLS; c++) {
            size_t index = r * COLS + c;
            terminal_buffer[index] = vga_entry(' ', terminal_color);
        }
    }
}

void terminal_write(const char *data) {
    while (*data) {
        if (*data == '\n') {
            terminal_col = 0;
            terminal_row += 1;

            if (terminal_row >= ROWS) {
                terminal_row = 0;
            }
        } else {
            size_t index = terminal_row * COLS + terminal_col;
            terminal_buffer[index] = vga_entry(*data, terminal_color);

            terminal_col += 1;

            if (terminal_col == COLS) {
                terminal_col = 0;

                terminal_row += 1;

                if (terminal_row == ROWS) {
                    terminal_row = 0;
                }
            }
        }

        data++;
    }
}

void terminal_set_color(uint8_t color) {
    terminal_color = color;
}