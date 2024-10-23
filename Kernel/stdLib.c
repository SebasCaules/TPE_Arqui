#include <stdint.h>
#include <stdarg.h>
#include "syscalls.h"

#define NOFMODS 5
#define LOWEST_MODIFIER 99
#define BUFFER_SIZE 1024

char mods[NOFMODS] = { 0 };

int	printf(const char * str, ...) {
    char buffer[BUFFER_SIZE];
    uint64_t length = 0;
    // Ej: printf("El numero es: %d +- %f. %c: %s", 12, 0.145, '$', "signo de pesos");
    for (uint64_t i = 0; str[i]; i++) {
        if(str[i] == '%') {
            switch (str[i + 1]) {
            case 'd':
                buffer[length++];
                break;
            case 'f':
                break;
            case 'g':
                break;
            case 'c':
                break;
            case 's':
                break;
            
            default:
                break;
            }
            i++;
        } else {
            buffer[length++] = str[i];
        }
    }
    return sysCallHandler(4, STDOUT, buffer, length);
    
    
    
}

int	 scanf(const char * __restrict, ...) {

}

int	 getchar(void) {

}

int	 putchar(int) {

}

