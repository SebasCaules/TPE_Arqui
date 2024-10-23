#include <stdint.h>
#include <stdarg.h>
#include "syscalls.h"

#define NOFMODS 5
#define LOWEST_MODIFIER 99
#define BUFFER_SIZE 1024

// userland

typedef enum {
	INT_TYPE = 0,
	FLOAT_TYPE,
	DOUBLE_TYPE,
	CHAR_TYPE,
	STR_TYPE,
} Types;

char mods[NOFMODS] = { 0 };

uint64_t syscall(uint64_t rax, uint64_t rbx, uint64_t rdx, uint64_t rcx);

// Hay que hacerla bien
uint64_t checkNmbArgs(va_list ap, uint64_t expectedNmb){
	int argd;
	float argf;
	double argg;
	char argc;
	char* args;

    for (uint64_t i = 0; i < expectedNmb; i++) {
		argd = va_arg(ap, int);
		argf = va_arg(ap, float);
		argg = va_arg(ap, double);
		argc = va_arg(ap, char);
		args = va_arg(ap, char*);
    }

	return expectedNmb;
}

uint64_t intToString(int value, char* buffer) {
    int isNegative = 0;
    uint64_t i = 0;
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

uint64_t decimalToString(double value, char* buffer, char floatFlag){
	int intPart = (int)value;
	uint64_t length = 0;
	length += intToString(intPart, buffer);
	buffer[length++] = '.';

	if(floatFlag){
		float decimalPart = (value - intPart) * 10;
		length += intToString(decimalPart, buffer);
	} else {
		double decimalPart = (value - intPart) * 10;
		length += intToString(decimalPart, buffer);
	}
	return length;
}

uint64_t typeToBuffer(char* buffer, uint64_t length, va_list ap, Types type){
	uint64_t ret = length;
	char auxBuffer[BUFFER_SIZE];
	uint64_t auxLength = 0;

	char numberFlag = 0;

	switch (type)
	{
	case INT_TYPE:
		int intNum = va_arg(ap, int);
		auxLength = intToString(intNum, auxBuffer);
		numberFlag = 1;
		break;
	case DOUBLE_TYPE:
		double doubleNum = va_arg(ap, double);
		auxLength = decimalToString(doubleNum, auxBuffer, 0);
		numberFlag = 1;
		break;
	case FLOAT_TYPE:
		float floatNum = (float)va_arg(ap, double);
		auxLength = decimalToString(floatNum, auxBuffer, 1);
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

    // Ej: printf("El numero es: %d +- %f. %c: %s", 12, 0.145, '$', "signo de pesos");
    for (uint64_t i = 0; str[i]; i++) {
        char fmtSpecifier;
        if(str[i] == '%' && (fmtSpecifier = str[i + 1]) != '\0') {
            modCounter++;
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
    return sysCallHandler(4, STDOUT, buffer, length);
}

int scanf(const char * __restrict, ...) {

}

int getchar(void) {

}

int putchar(int) {

}

int strcmp(const char * str1, const char * str2) {
	while (*str1 && (*str1 == *str2)) {
		str1++;
		str2++;
	}
	return *(unsigned char *)str1 - *(unsigned char *)str2;
}

