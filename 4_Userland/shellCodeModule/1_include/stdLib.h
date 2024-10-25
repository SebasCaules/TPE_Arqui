#include <stdarg.h>
#include <stdint.h>

#ifndef TPE_ARQUI_STDLIB_H
#define TPE_ARQUI_STDLIB_H

#define MAX_COMMAND_LENGTH 128
#define MAX_USERNAME_LENGTH 32
#define MAX_WORDS 4
#define MAX_WORD_LENGTH 32

uint64_t strlen(const char *str);

int	printf(const char * str, ...);

int getchar();

int putchar(char c);

int scanf(const char *format, ...);

int putsNoNewLine(const char *str);

int puts(const char *str);

int gets(char *buffer, int n);

int strcmp(const char *str1, const char *str2);

void interactive_keyboard();

int setFontScale();

int stringToInt(const char *str);

int splitString(const char* input, char words[MAX_WORDS][MAX_WORD_LENGTH]);

#endif //TPE_ARQUI_STDLIB_H
