#include <stdint.h>

#ifndef TPE_ARQUI_STRLIB_H
#define TPE_ARQUI_STRLIB_H

#define MAX_WORDS 4
#define MAX_WORD_LENGTH 32
#define BUFFER_SIZE 1024


uint64_t strlen(const char *str);

int strcmp(const char *str1, const char *str2);

char toLowercase(char c);

char toUppercase(char c);

int isspace(int c);

int splitString(const char* str, char words[MAX_WORDS][MAX_WORD_LENGTH]);

uint64_t intToString(int value, char* buffer, uint64_t length);

uint64_t decimalToString(double value, char* buffer);

int convert_to_base_string(int number, int base, char *buffer);

int stringToInt(const char *str);

#endif //TPE_ARQUI_STRLIB_H

