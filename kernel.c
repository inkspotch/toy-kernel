enum color {
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
};

void print(char *str, enum color bg, enum color text_color);
void clear();

void kmain(void) {
  char *str = "Color kernel. :D";
  clear();
  print(str, black, black);
}

void print(char *str, enum color bg, enum color text_color) {
  char* video_buffer = (char*) 0xb8000;
  
  while(*str) {
    *video_buffer++ = *str++;
    *video_buffer++ = 0x07;
  }
}

void clear() {
  char* video_buffer = (char*) 0xb8000;
  
  int size = 80 * 25 * 2;
  for (int i = 0; i < size; i++) {
    *video_buffer++ = 0;
    *video_buffer++ = 0;
  }  
}

