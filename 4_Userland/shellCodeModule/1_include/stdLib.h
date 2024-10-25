#include <stdarg.h>
#include <stdint.h>
#include <syscallsInt.h>

#ifndef TPE_ARQUI_STDLIB_H
#define TPE_ARQUI_STDLIB_H

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

#endif //TPE_ARQUI_STDLIB_H
