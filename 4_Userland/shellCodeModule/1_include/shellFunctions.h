#include <stdint.h>
#include <stdlib.h>
#include <snake.h>
#include <exceptions.h>
#include <stddef.h>
#include <spotify.h>
#include <piano.h>

#define WELCOME_MESSAGE "Welcome to the terminal %s!\n"
#define PROMPT "%s@userland ~ $ "
#define NUM_MODULES 11

typedef struct module {
    char *name;
    void (*function)();
} module;

void spotifyInterface();

/**
 * @brief Displays a help message listing available commands.
 */
void help();

/**
 * @brief Shows the current system time on the terminal.
 */
void showTime();

/**
 * @brief Changes the font scale in the terminal.
 * @param scale The new font scale factor.
 */
void changeFontScale(int scale);

/**
 * @brief Clears the terminal screen.
 */
void clearTerminal();

/**
 * @brief Retrieves and displays the current values of CPU registers.
 */
void getRegs();

/**
 * @brief Prompts the user for input, used for the username.
 */
void askForUser();

/**
 * @brief Captures and processes user input for commands in the shell.
 */
void getCmdInput();

/**
 * @brief Initializes and starts the shell environment.
 */
void initShell();
