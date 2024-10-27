#include <stdarg.h>
#include <stdint.h>
#include <syscallsInt.h>
#include <strLib.h>

#ifndef TPE_ARQUI_STDLIB_H
#define TPE_ARQUI_STDLIB_H

#define MAX_COMMAND_LENGTH 128
#define MAX_USERNAME_LENGTH 32
#define EOF (-1)

typedef enum {
	STDIN = 0,
    STDOUT,
    STDERR,
    STDMARK,
} fileDesc;

typedef enum {
	INT_TYPE = 0,
    HEX_TYPE,
    BIN_TYPE,
    OCT_TYPE,
	FLOAT_TYPE,
	DOUBLE_TYPE,
	CHAR_TYPE,
	STR_TYPE,
} Types;

int fdprintf(uint64_t fd, const char* fmt, ...);

int	printf(const char * str, ...);

int getchar();

int readInput(char * c);

int putchar(char c);

int scanf(const char *format, ...);

int putsNoNewLine(const char *str);

int puts(const char *str);

int gets(char *buffer, int n);

int setFontScale(int scale);

void clearView();

void drawRectangle(int x, int y, int width, int height, int color);

void sleep(int milliseconds);

void resetCursor();

void beep(int freq, int milliseconds);

void convert(char initBase, char finalBase, char* num);

#endif //TPE_ARQUI_STDLIB_H
