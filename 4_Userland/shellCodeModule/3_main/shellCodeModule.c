#include <stdLib.h>

#define WELCOME_MESSAGE "Bienvenido a la terminal!\n"
#define PROMPT "user@kernel ~ $ "

#define MAX_COMMAND_LENGTH 128

static void help() {
    puts("\nComandos disponibles:\n\n");
    puts("- help: Muestra todos los modulos disponibles del sistema operativo.\n");
    puts("- time: Muestra la hora actual del sistema.\n");
    puts("- clear: Limpia la pantalla.\n");

}

uint64_t askForUser(char* usernameBuffer) {
    puts("Porfavor ingrese su nombre de usuario: \t");

    uint64_t length = 0;
    char c;
    puts("Entro al while");
    while (1) {
        c = getchar();  // Get character from keyboard
        if (c == 'q') break;  // Exit if 'q' is pressed
        usernameBuffer[length++] = c;
        putchar(c);  // Echo character back
    }
    puts("Salio del while");
    usernameBuffer[length++] = '\n';
    usernameBuffer[length] = '\0';
    puts("Esta por salir");
    return length;
}

void commandLine() {

}

// imprime lo que el usuario escribio. para testeo.
void getAndPrintInput() {
    char buffer[MAX_COMMAND_LENGTH];
    int i = 0;
    putsNoNewLine(PROMPT);
    char c;
    while ((c = getchar()) != '\n') {
        if (putchar(c) != -1) {
            buffer[i++] = c;
        }
    }
    buffer[i] = 0;
    putchar('\n');
    puts(buffer);
    
    // descomentar para probarlo bien (escribir, return, escribir, return, etc.)
    // getAndPrintInput();
}

int main() {
    puts(WELCOME_MESSAGE);
    getAndPrintInput();
    puts("imprime bien"); // chequear que no este recursiva la funcion getAndPrintInput()

    // char usernameBuffer[256];
    // puts("Entro a la func");
    // askForUser(usernameBuffer);
    // puts("Salio de la func");
    // puts(usernameBuffer);
    // help();
}

