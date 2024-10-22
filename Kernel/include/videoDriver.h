#include <stdint.h>

void putPixel(uint32_t hexColor, uint64_t x, uint64_t y);

void printStr(char* str, int fgcolor, int bgcolor);

void printStrBW(char* str);

void printCharBW(char c);

void printNewLine();

void printTab();

void deleteChar();

void drawRectangle(uint64_t x, uint64_t y, uint64_t width, uint64_t height, uint32_t color);

void intToStr(int num, char *str);

void printInt(int num);

void displayPrompt(char* username, char* hostname, char*currentDir);

uint64_t printChar(char c, int fgcolor, int bgcolor);

void printNewLineWPrompt();

void clear();

void printDec(uint64_t value);

void printHex(uint64_t value);

void printBin(uint64_t value);

uint64_t printStrByLength(char* str, int fgcolor, int bgcolor, int length);


