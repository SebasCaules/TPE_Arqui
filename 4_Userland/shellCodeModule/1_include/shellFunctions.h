#include <stdint.h>
#include <stdlib.h>
#include <snake.h>
#include <exceptions.h>

#define WELCOME_MESSAGE "Bienvenido a la terminal!\n"
#define PROMPT "%s@userland ~ $ "
#define NUM_MODULES 8

typedef struct module {
    char *name;
    void (*function)();
} module;

void help();

void showTime();

void changeFontScale(int scale);

void clearTerminal();

void getRegs();

void askForUser();

void getCmdInput();
