#ifndef TOY_KERNEL_VGA_H
#define TOY_KERNEL_VGA_H

#include <stddef.h>
#include <stdint.h>

typedef enum color {
    black = 0,
    blue = 1,
    green = 2,
    cyan = 3,
    red = 4,
    magenta = 5,
    brown = 6,
    light_grey = 7,
    dark_grey = 8,
    light_blue = 9,
    light_green = 10,
    light_cyan = 11,
    light_red = 12,
    light_magenta = 13,
    light_brown = 14,
    white = 15,
} color;

typedef uint16_t entry_color;

uint8_t vga_color(color fg, color bg);
uint16_t vga_entry(entry_color color, char ch);

#endif //TOY_KERNEL_VGA_H
