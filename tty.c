#include "tty.h"
#include "vga.h"
#include "ll_io.h"

static uint16_t *const terminal_buffer = (uint16_t *) 0xb8000;
static size_t terminal_row;
static size_t terminal_col;
static uint8_t terminal_color;

static void scroll_up_row(void);
static void enable_cursor(void);
static void disable_cursor(void);
static void update_cursor(void);

void terminal_init(void) {
    terminal_row = 0;
    terminal_col = 0;
    terminal_color = vga_color(light_grey, white);

    size_t i = 0;
    for (size_t r = 0; r < ROWS; r++) {
        for (size_t c = 0; c < COLS; c++) {
            terminal_buffer[i++] = vga_entry(' ', terminal_color);
        }
    }

    enable_cursor();
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
            if (terminal_row == ROWS) {
                terminal_row -= 1;
                scroll_up_row();
            }

            size_t index = terminal_row * COLS + terminal_col;
            terminal_buffer[index] = vga_entry(*data, terminal_color);

            terminal_col += 1;

            if (terminal_col == COLS) {
                terminal_col = 0;

                terminal_row += 1;
            }
        }

        data++;
    }
    update_cursor();
}

void terminal_set_color(uint8_t color) {
    terminal_color = color;
}

static void scroll_up_row() {
    size_t end = ROWS * COLS;

    size_t readPosition = COLS;
    size_t writePosition = 0;

    while (writePosition < end) {
        terminal_buffer[writePosition++] =
                readPosition < end
                ? terminal_buffer[readPosition++]
                : vga_entry(' ', terminal_color);
    }
}

static void enable_cursor() {
    outb(0x3D4, 0x0A);
    outb(0x3D5, 0xC0 | 14);

    outb(0x3D4, 0x0B);
    outb(0x3D5, 0xE0 | 15);
}

static void update_cursor() {
    uint16_t position = terminal_row * COLS + terminal_col;

    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint8_t) (position & 0xFF));

    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint8_t) ((position >> 8) & 0xFF));
}

static void disable_cursor() {
    outb(0x3D4, 0x0A);
    outb(0x3D5, 0x20);
}