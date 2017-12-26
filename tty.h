
#ifndef TOY_KERNEL_TTY_H
#define TOY_KERNEL_TTY_H

#include <stddef.h>
#include <stdint.h>

static const size_t ROWS = 25;
static const size_t COLS = 80;

void terminal_init(void);
void terminal_set_color(uint8_t color);
void terminal_write(const char* data);

#endif //TOY_KERNEL_TTY_H
