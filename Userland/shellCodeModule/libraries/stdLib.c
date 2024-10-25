#include "stdlib.h"
#include <stdarg.h>
#include "syscallsInt.h"

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
    char c;
    if (sys_read(STDIN, &c, 1) > 0) {
        return c;
    } else {
        return EOF;
    }
}

int putchar(char c) {
    if (sys_write(STDOUT, &c, 1) > 0) {
        return c;
    } else {
        return EOF;
    }
}



int puts(const char *str) {
    while (*str) {
        if (putchar(*str++) == EOF) return EOF;
    }
    return putchar('\n');
}

char *gets(char *str) {
    char *s = str;
    char c;
    while ((c = getchar()) != '\n' && c != EOF) {
        *s++ = c;
    }
    *s = '\0';
    return str;
}


int strcmp(const char *str1, const char *str2) {
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return *(unsigned char *)str1 - *(unsigned char *)str2;
}


void interactive_keyboard() {
    char c;
    while ((c = getchar()) != '\n'){
        putchar(c);
    }
}

