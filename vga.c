#include "vga.h"

inline uint8_t vga_color(color fg, color bg) {
    return fg | bg << 4;
}

inline uint16_t vga_entry(entry_color color, char ch) {
    return (uint16_t) color | (((uint16_t) ch) << 8);
}
