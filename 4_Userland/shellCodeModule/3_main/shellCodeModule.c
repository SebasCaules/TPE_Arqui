#include <shellFunctions.h>

int main() {
    puts(WELCOME_MESSAGE);
    showTime();
    askForUser();
    putchar('\n');
    help();
    putchar('\n');

    while(1) {
        getCmdInput();
    }
}
