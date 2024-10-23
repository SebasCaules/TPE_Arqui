#include <stdint.h>
#include <stdarg.h>
#include "syscalls.h"

#define NOFMODS 5
#define LOWEST_MODIFIER 99
#define BUFFER_SIZE 1024

char mods[NOFMODS] = { 0 };

int	printf(const char * str, ...){
    // Ej: printf("El numero es: %d +- %f. %c: %s", 12, 0.145, '$', "signo de pesos");
    for (uint64_t i = 0; str[i]; i++) {
        
    }
    
    
    
}

int	 scanf(const char * __restrict, ...) {

}

int	 getchar(void) {

}

int	 putchar(int) {

}

