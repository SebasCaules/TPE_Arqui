#include <stdint.h>

#ifndef FONT_H
#define FONT_H

#define HEIGHT_BITMAP 16
#define NCHARS 95

#define CHAR_WIDTH 8
#define CHAR_HEIGHT 16

void drawChar(unsigned char c, int x, int y, int fgcolor, int bgcolor, int font);

#endif
