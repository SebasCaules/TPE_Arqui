#include <stdarg.h>
#include <stdint.h>
#include <syscallsInt.h>

#ifndef TPE_ARQUI_STDLIB_H
#define TPE_ARQUI_STDLIB_H

#define MAX_COMMAND_LENGTH 128
#define MAX_USERNAME_LENGTH 32
#define MAX_WORDS 4
#define MAX_WORD_LENGTH 32

uint64_t strlen(const char *str);

int	printf(const char * str, ...);

int getchar();

int readInput(char * c);

int putchar(char c);

int scanf(const char *format, ...);

int putsNoNewLine(const char *str);

int puts(const char *str);

int gets(char *buffer, int n);

int strcmp(const char *str1, const char *str2);

void interactive_keyboard();

int setFontScale(int scale);

int stringToInt(const char *str);

int splitString(const char* input, char words[MAX_WORDS][MAX_WORD_LENGTH]);

char toLowercase(char c);

void clearView();

void drawRectangle(int x, int y, int width, int height, int color);

void sleep(int milliseconds);

void resetCursor();

#endif //TPE_ARQUI_STDLIB_H
