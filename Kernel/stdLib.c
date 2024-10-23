#include <stdint.h>
#include <stdarg.h>
#include "syscalls.h"

#define NOFMODS 5
#define LOWEST_MODIFIER 99
#define BUFFER_SIZE 1024

// typedef enum {
// 	STDIN = 0,
//     STDOUT,
//     STDERR,
//     STDMARK,
// } fileDesc;

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

int	printf(const char * str, ...);

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

// Helper function to count the number of format specifiers in the string
int countFormatSpecifiers(const char *str) {
    int count = 0;
    for (uint64_t i = 0; str[i]; i++) {
        if (str[i] == '%' && str[i + 1] != '\0') {
            count++;
            i++;  // Skip the format specifier
        }
    }
    return count;
}


int	printf(const char * str, ...) {
	// sysCallHandler(4, STDOUT, "antes va_list \n", 16);
    va_list ap;
	// sysCallHandler(4, STDOUT, "antes va_ap12 \n", 16);
    va_start(ap, str);

    char buffer[BUFFER_SIZE];
    uint64_t length = 0;
    uint64_t modCounter = 0;

	int formatSpecifierCount = 0;
    int argumentCount = 0;

    // First, count format specifiers
    formatSpecifierCount = countFormatSpecifiers(str);

    // Ej: printf("El numero es: %d +- %f. %c: %s", 12, 0.145, '$', "signo de pesos");
    for (uint64_t i = 0; str[i]; i++) {
        char fmtSpecifier;
        if(str[i] == '%' && (fmtSpecifier = str[i + 1]) != '\0') {
            switch (fmtSpecifier) {
            case 'd':
				argumentCount++;
				length = typeToBuffer(buffer, length, ap, INT_TYPE);
                break;
            case 'f':
				argumentCount++;
				length = typeToBuffer(buffer, length, ap, FLOAT_TYPE);
                break;
            case 'g':
				argumentCount++;
				length = typeToBuffer(buffer, length, ap, DOUBLE_TYPE);
                break;
            case 'c':
				argumentCount++;
				buffer[length++] = (char)va_arg(ap, int);
                break;
            case 's':
				argumentCount++;
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

	// Error handling for missing or extra arguments
    if (argumentCount < formatSpecifierCount) {
        sysCallHandler(4, STDOUT, "Error: Missing arguments\n", 25);
        return -1;
    }
    if (argumentCount > formatSpecifierCount) {
        sysCallHandler(4, STDOUT, "Error: Too many arguments\n", 26);
        return -1;
    }
	
    return sysCallHandler(4, STDOUT, buffer, length);
}

int scanf(const char * str, ...) {
    va_list ap;
    va_start(ap, str);

    char buffer[BUFFER_SIZE];
    uint64_t length = 0;

	for (uint8_t i = 0; str[i]; i++) {
		char fmtSpecifier;
        if(str[i] == '%' && (fmtSpecifier = str[i + 1]) != '\0') {
			
		}
	}
}
	

uint64_t readLine(char buffer[], uint64_t count) {

}


int getSingleChar(void) {
	uint8_t c;
	while (sysCallHandler(3, STDIN, &c, 1) < 1);
	return c;
}

int getchar(void) {
	int c = getSingleChar();
	int n = getSingleChar();
	if (n == '\n') {
		printf("second IS new line");
		return c;
	}
	printf("second IS NOT new line");
	return -1;
}

int putchar(int c) {
	char buffer[1] = {c};
	sysCallHandler(4, STDOUT, buffer, 1);
	return c;
}

int strcmp(const char * str1, const char * str2) {
	while (*str1 && (*str1 == *str2)) {
		str1++;
		str2++;
	}
	return *(unsigned char *)str1 - *(unsigned char *)str2;
}

