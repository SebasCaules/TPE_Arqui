#include <stdarg.h>
#include <stdint.h>

#ifndef TPE_ARQUI_STDLIB_H
#define TPE_ARQUI_STDLIB_H

int	printf(const char * str, ...);

int getchar();

int putchar(char c);

int scanf(const char *format, ...);

int puts(const char *str);

char *gets(char *str);

int strcmp(const char *str1, const char *str2);

void interactive_keyboard();

#endif //TPE_ARQUI_STDLIB_H
