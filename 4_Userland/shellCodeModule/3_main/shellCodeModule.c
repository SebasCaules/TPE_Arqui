#include <stdLib.h>

#define WELCOME "Bienvenido a la terminal!\n"

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


int main() {
    puts(WELCOME);
    // char usernameBuffer[256];
    // puts("Entro a la func");
    // askForUser(usernameBuffer);
    // puts("Salio de la func");
    // puts(usernameBuffer);
    // help();
}

