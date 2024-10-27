#include <stdint.h>
#include <stdlib.h>
#include <snake.h>
#include <exceptions.h>
#include <stddef.h>

#define WELCOME_MESSAGE "Welcome to the terminal %s!\n"
#define PROMPT "%s@userland ~ $ "
#define NUM_MODULES 9

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

void initShell();
