#include <stdLib.h>

#define WELCOME_MESSAGE "Bienvenido a la terminal!\n"
#define PROMPT "%s@userland ~ $ "

#define MAX_COMMAND_LENGTH 128
#define MAX_USERNAME_LENGTH 32
#define NUM_MODULES 1

typedef struct module {
    char *name;
    void (*function)();
} module;

static char username[MAX_USERNAME_LENGTH];


static void help() {
    puts("\nComandos disponibles:\n\n");
    puts("- help: Muestra todos los modulos disponibles del sistema operativo.\n");
    puts("- time: Muestra la hora actual del sistema.\n");
    puts("- clear: Limpia la pantalla.\n");
}

static module modules[] = {
    {"help", help}
    // {"time", showcurrentTime},
    // {"eliminator", eliminator},
    // {"zoomin", zoomIn},
    // {"zoomout", zoomOut},
    // {"getregs", getRegs},
    // {"dividebyzero", div0},
    // {"opcode", op_code},
    // {"clear", clear},
    // {"ipod", ipod_menu}
};

void askForUser() {
    puts("Porfavor ingrese su nombre de usuario: \t");
    gets(username, MAX_USERNAME_LENGTH);
}

void prompt() {
    printf(PROMPT, username);
}

void commandLine() {

}

void getCmdInput() {
    prompt();
    char cmdBuffer[MAX_COMMAND_LENGTH + 1];
    gets(cmdBuffer, MAX_COMMAND_LENGTH);
    if(strlen(cmdBuffer) == 0){
        return;
    }
    for(int i = 0; i < NUM_MODULES; i++){
        if(strcmp(cmdBuffer,modules[i].name)==0){
            modules[i].function();
            return;
        }
    }
    printf("Command not found: %s\n", cmdBuffer); //Hay que agarrar solo la primera palabra
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
}

// static void toUtcMinus3(time_struct * time) {
//     if (time->hour < 3) {
//         time->hour += 21;
//         time->day--;
//         if (time->day == 0) {
//             time->month--;
//             if (time->month == 0) {
//                 time->month = 12;
//                 time->year--;
//             }
//             if(time->month == 2){
//                 time->day = 28;
//                 if(time->year % 4 == 0){
//                     time->day = 29;
//                 }
//             } else if(time->month == 4 || time->month == 6 || time->month == 9 || time->month == 11){
//                 time->day = 30;
//             } else {
//                 time->day = 31;
//             }
//         }
//     }
//     else{
//         time->hour = time->hour - 3;
//     }
// }

int main() {
    puts(WELCOME_MESSAGE);
    askForUser();
    help();

    while(1) {
        getCmdInput();
    }
}

