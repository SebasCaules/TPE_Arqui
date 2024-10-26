#include "stdlib.h"
#include <stdarg.h>


#define NOFMODS 5
#define LOWEST_MODIFIER 99
#define BUFFER_SIZE 1024
#define EOF (-1)

typedef enum {
	STDIN = 0,
    STDOUT,
    STDERR,
    STDMARK,
} fileDesc;

// userland
typedef enum {
	INT_TYPE = 0,
	FLOAT_TYPE,
	DOUBLE_TYPE,
	CHAR_TYPE,
	STR_TYPE,
} Types;

char mods[NOFMODS] = { 0 };


//Estaria mejor esta func
void reverseStr(char* buffer, uint64_t length){
	int start = 0;
    int end = length - 1;
    while (start < end) {
        char temp = buffer[start];
        buffer[start] = buffer[end];
        buffer[end] = temp;
        start++;
        end--;
    }
}

uint64_t strlen(const char *str) {
    const char *s = str;
    while (*s) {
        ++s;
    }
    return s - str;
}

uint64_t intToString(int value, char* buffer, uint64_t length) {
    int isNegative = 0;
    uint64_t i = length;
    if (value < 0) {
        isNegative = 1;
        value = -value;  
    }
    do {
        buffer[i++] = (value % 10) + '0';
        value /= 10;
    } while (value > 0);
    if (isNegative) {
        buffer[i++] = '-';
    }

	int start = 0;
    int end = i - 1;
    while (start < end) {
        char temp = buffer[start];
        buffer[start] = buffer[end];
        buffer[end] = temp;
        start++;
        end--;
    }
	return i;
}

uint64_t decimalToString(double value, char* buffer){
	int intPart = value;
	uint64_t length = 0;
	length += intToString(intPart, buffer, length);
	buffer[length++] = '.';

	char auxBuffer[BUFFER_SIZE];
	uint64_t auxLength = 0;
	int decimalPart = (value - intPart) * 10;
	auxLength += intToString(decimalPart, auxBuffer, auxLength);
	for (uint8_t i = 0; i < auxLength; i++) {
		buffer[length++] = auxBuffer[i];
	}
	return length;
}

uint64_t typeToBuffer(char* buffer, uint64_t length, va_list ap, Types type){
	uint64_t ret = length;
	char auxBuffer[BUFFER_SIZE];
	uint64_t auxLength = 0;
	char numberFlag = 0;

	switch (type) {
	case INT_TYPE:
		auxLength = intToString(va_arg(ap, int), auxBuffer, auxLength);
		numberFlag = 1;
		break;
	case DOUBLE_TYPE:
		auxLength = decimalToString(va_arg(ap, double), auxBuffer);
		numberFlag = 1;
		break;
	case FLOAT_TYPE:
		auxLength = decimalToString((float)va_arg(ap, double), auxBuffer);
		numberFlag = 1;
		break;
	case STR_TYPE:
		char* str = va_arg(ap, char*);
		while (*str) {
			buffer[ret++] = *str;
			str++;
		}
		break;
	default:
		break;
	}
	if(numberFlag){
		for (uint8_t i = 0; i < auxLength; i++) {	
			buffer[ret++] = auxBuffer[i];
		}
	}
	return ret;
}


int	printf(const char * str, ...) {
    va_list ap;
    va_start(ap, str);

    char buffer[BUFFER_SIZE];
    uint64_t length = 0;
    uint64_t modCounter = 0;

	int formatSpecifierCount = 0;
    int argumentCount = 0;

    // Ej: printf("El numero es: %d +- %f. %c: %s", 12, 0.145, '$', "signo de pesos");
    for (uint64_t i = 0; str[i]; i++) {
        char fmtSpecifier;
        if(str[i] == '%' && (fmtSpecifier = str[i + 1]) != '\0') {
            switch (fmtSpecifier) {
            case 'd':
				length = typeToBuffer(buffer, length, ap, INT_TYPE);
                break;
            case 'f':
				length = typeToBuffer(buffer, length, ap, FLOAT_TYPE);
                break;
            case 'g':
				length = typeToBuffer(buffer, length, ap, DOUBLE_TYPE);
                break;
            case 'c':
				buffer[length++] = (char)va_arg(ap, int);
                break;
            case 's':
				length = typeToBuffer(buffer, length, ap, STR_TYPE);
                break;
            default:
                break;
            }
            i++;
        } else {
            buffer[length++] = str[i];
        }
    }
    va_end(ap);
	
    return sys_write(STDOUT, buffer, length);
}

int scanf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    int result = 0;
    char buffer[BUFFER_SIZE];
    int index = 0;


    while (sys_read(STDIN, &buffer[index], 1) > 0 && buffer[index] != '\n') {
        index++;
    }
    buffer[index] = '\0'; 

    const char *fmt = format;
    int *int_ptr;
    char *str_ptr;
    int i = 0;

    while (*fmt) {
        if (*fmt == '%') {
            fmt++;
            if (*fmt == 'd') { 
                int_ptr = va_arg(args, int *);
                *int_ptr = 0;
                while (buffer[i] >= '0' && buffer[i] <= '9') {
                    *int_ptr = *int_ptr * 10 + (buffer[i++] - '0');
                }
                result++;
            } else if (*fmt == 's') {
                str_ptr = va_arg(args, char *);
                int j = 0;
                while (buffer[i] && buffer[i] != ' ') {
                    str_ptr[j++] = buffer[i++];
                }
                str_ptr[j] = '\0';
                result++;
            }
        } else if (*fmt != buffer[i++]) {
            break;
        }
        fmt++;
    }

    va_end(args);
    return result;
}

int getchar() {
    // char c;
    // if (sys_read(STDIN, &c, 1) > 0) {
    //     return c;
    // } else {
    //     return EOF;
    // }
    uint16_t c;
    while (sys_read(STDIN, &c, 1) == 0 || c > 255);
    return (char) c;
}

int putchar(char c) {
    // if (sys_write(STDOUT, &c, 1) > 0) {
    //     return c;
    // } else {
    //     return EOF;
    // }
    sys_write(STDOUT, &c, 1);
}

int putsNoNewLine(const char *str) {
    int len;
    while (*str) {
        putchar(*str++);
        len++;
    }
    return len;
}

int puts(const char *str) {
    putsNoNewLine(str);
    return putchar('\n');
}

int gets(char* buffer, int n) {
    int c;
    int i = 0;

    while ((c = getchar()) != '\n') {
        if (c == '\b' && i > 0) {
            putchar(c);
            i--;
        }
        if (c != '\b' && i < n - 1) {
            putchar(c);
            buffer[i++] = (char)c;
        }
    }
    putchar('\n');
    buffer[i] = '\0';

    return i;
}

int strcmp(const char *str1, const char *str2) {
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return *(unsigned char *)str1 - *(unsigned char *)str2;
}

void getInput(char* buffer, int length){
    gets(buffer, length);
}

int isspace(int c) {
    return (c == ' ' || c == '\t' || c == '\n' ||
            c == '\v' || c == '\f' || c == '\r');
}

int splitString(const char* str, char words[MAX_WORDS][MAX_WORD_LENGTH]) {
    int wordCount = 0;
    int charIndex = 0;
    
    for (int i = 0; str[i] != '\0'; i++) {
        if (isspace(str[i])) {
            // If we're at a space and a word has been started, end the current word
            if (charIndex > 0) {
                words[wordCount][charIndex] = '\0'; // Null-terminate the word
                wordCount++;  // Move to the next word
                charIndex = 0;  // Reset character index for the next word

                // Ensure we don't exceed the maximum word count
                if (wordCount >= MAX_WORDS) {
                    break;
                }
            }
        } else {
            // Add character to the current word if within max length
            if (charIndex < MAX_WORD_LENGTH - 1) {
                words[wordCount][charIndex++] = str[i];
            }
        }
    }

    // Add the last word if it wasn't followed by whitespace
    if (charIndex > 0 && wordCount < MAX_WORDS) {
        words[wordCount][charIndex] = '\0';
        wordCount++;
    }

    return wordCount;
}

int stringToInt(const char *str) {
    int result = 0;
    int i = 0;

    // Skip leading whitespaces
    while (str[i] == ' ') {
        i++;
    }

    // Check if the string is empty after trimming spaces
    if (str[i] == '\0') {
        return -1;  // Return -1 for empty or invalid input
    }

    // Convert each character to integer
    while (str[i] >= '0' && str[i] <= '9') {
        result = result * 10 + (str[i] - '0');
        i++;
    }

    // If we encounter any non-numeric characters, return -1
    if (str[i] != '\0') {
        return -1;
    }

    return result;
}

char toLowercase(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c + 32;
    }
    return c;
}

int setFontScale(int scale) {
    return sys_set_font_scale(scale);
}

void clearView() {
    sys_clear();
}

void drawRectangle(int x, int y, int width, int height, int color) {
    sys_draw_rectangle(x, y, width, height, color);
}

