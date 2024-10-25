#include <stdLib.h>

#define WELCOME_MESSAGE "Bienvenido a la terminal!\n"
#define PROMPT "%s@userland ~ $ "
#define NUM_MODULES 2

typedef struct module {
    char *name;
    void (*function)();
} module;

static char username[MAX_USERNAME_LENGTH];

static void help() {
    puts("\nComandos disponibles:\n");
    puts("- help: Muestra todos los modulos disponibles del sistema operativo.");
    puts("- time: Muestra la hora actual del sistema.");
    puts("- clear: Limpia la pantalla.");
    putchar('\n');
}

static module modules[] = {
    {"help", help},
    // {"time", showcurrentTime},
    // {"eliminator", eliminator},
    {"setfont", setFontScale},
    // {"getregs", getRegs},
    // {"dividebyzero", div0},
    // {"opcode", op_code},
    // {"clear", clear},
    // {"ipod", ipod_menu}
};

void askForUser() {
    putsNoNewLine("Ingrese su nombre de usuario: ");
    gets(username, MAX_USERNAME_LENGTH);
}

void prompt() {
    printf(PROMPT, username);
}

void commandLine() {

}

void getCmdInput() {
    prompt();
    char command[MAX_COMMAND_LENGTH + 1];
    gets(command, MAX_COMMAND_LENGTH);
    if(strlen(command) == 0){
        return;
    }
    char words[MAX_WORDS][MAX_WORD_LENGTH];
    int wordCount = splitString(command, words);

    for (int i = 0; i < NUM_MODULES; i++) {
        
    }

    if (strcmp(words[0], modules[0].name) == 0) {
        modules[0].function();
        return;
    }

    if (strcmp(words[0], modules[1].name) == 0) {
        if (wordCount != 2) {
            puts("Invalid command. (setfont <scale>)");
            return;
        }
        changeFontScale(stringToInt(words[1]));
        return;
    }
    
    printf("Command not found: %s\n", words[0]); // Hay que agarrar solo la primera palabra
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

void changeFontScale(int scale) {
    printf("%d", scale);
    int returnValue = setFontScale(scale);
    if (returnValue == -1) {
        puts("Invalid font scale. Provide a number between 1 and 3");
    }
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
