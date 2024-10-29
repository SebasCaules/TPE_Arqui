#include <shellFunctions.h>

static void toUtcMinus3(time_struct * time);

static char username[MAX_USERNAME_LENGTH] = { 0 };

static module modules[] = {
    {"help", help},
    {"time", showTime},
    {"setfont", setFontScale},
    {"clear", clearTerminal},
    {"convert", convert},
    {"snake", snake},
    {"getregs", getRegs},
    {"opcode", opCode},
    {"divzero", divZero},
    {"song", spotifyInterface},
    {"piano", playKeys}
};


void spotifyInterface() {
	clearView();
    puts("Welcome to the Spotify (clone) interface!\n");
    puts("Here is a list of our repertoire:\n");
    puts("1-The scale of C4. \n");
    puts("2-The happy birthday song. \n");
    puts("3-Rezo por vos, Charly García y Luis Alberto Spinetta. \n");
    puts("4-Money, Pink Floyd. \n");
    puts("Press q to go back to the terminal.\n");
    char c[MAX_COMMAND_LENGTH + 1];
    int readLength;
    do {
        putsNoNewLine("Please choose the number of option you want to play: ");
        readLength = gets(c, MAX_COMMAND_LENGTH);
        if(readLength > 1) {
            puts("Input only one digit");
        } else if(c[0] >= '1' && c[0] <= (NUMBER_OF_SONGS+48)) {
            playSong(c[0]);
        } else {
            puts("Input a number between 1 and 4");
        }
    } while (c[0] != 'q');
    clearView();
}

void help() {
    puts("Available Commands: ");
    puts("  help            - Shows all available commands.");
    puts("  time            - Display the current system time.");
    puts("  setfont <scale> - Adjust the font size. Replace <scale> with 1 or 2.");
    puts("  clear           - Clear the terminal screen.");
    puts("  convert         - Converts a number of any base to any other base (EX: convert d b 8, OUT: 1000b)");
    puts("  snake           - Starts the Snake game.");
    puts("  getregs         - Display the contents of the CPU's registers.");
    puts("  divzero         - Throws the exception division by zero");
    puts("  opcode          - Throws the exception invalid Opcode");
}

void showTime() {
    time_struct time;
    sys_time(&time);
    toUtcMinus3(&time);
    printf("[dd/mm/yyyy] - [hh:mm:ss]\n");
    printf(" %d/%d/20%d  -  %d:%d:%d  \n", time.day, time.month, 
    time.year, time.hour, time.minutes, time.seconds); //Porque year es solo 2 digs?
    return;
}

void changeFontScale(int scale) {
    if (setFontScale(scale) == -1) {
        puts("Invalid font scale. Enter a number between 1 and 2");
    }
}

void clearTerminal() {
    clearView();
}

void getRegs() {
    uint64_t r[17];
    sys_get_regs(r);
    puts("Register snapshot:");
    printf("rax: %x\n", r[0]);
    printf("rbx: %x\n", r[1]);
    printf("rcx: %x\n", r[2]);
    printf("rdx: %x\n", r[3]);
    printf("rsi: %x\n", r[4]);
    printf("rdi: %x\n", r[5]);
    printf("rbp: %x\n", r[6]);
    printf("r8:  %x\n", r[7]);
    printf("r9:  %x\n", r[8]);
    printf("r10: %x\n", r[9]);
    printf("r11: %x\n", r[10]);
    printf("r12: %x\n", r[11]);
    printf("r13: %x\n", r[12]);
    printf("r14: %x\n", r[13]);
    printf("r15: %x\n", r[14]);
    printf("rsp: %x\n", r[15]);
    printf("rip: %x\n", r[16]);
}

void askForUser() {
    putsNoNewLine("Enter a username: ");
    gets(username, MAX_USERNAME_LENGTH);
}

static void prompt() {
    printf(PROMPT, username);
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

    for(int i = 0; i < NUM_MODULES; i++){
        if(strcmp(command,modules[i].name)==0){
            modules[i].function();
            return;
        }
    }
    if (strcmp(words[0], modules[2].name) == 0) {
        if (wordCount != 2) {
            puts("Invalid command. (setfont <scale>)");
            return;
        }
        changeFontScale(stringToInt(words[1]));
        return;
    }

    if(strcmp(words[0], modules[4].name) == 0){
        convert(words[1][0], words[2][0], words[3]);
        return;
    }
    printf("Command not found: %s\n", words[0]); // Hay que agarrar solo la primera palabra
}

void initShell() {
    askForUser();
    clearTerminal();
    printf(WELCOME_MESSAGE, username);
    showTime();
    putchar('\n');
    help();
    putchar('\n');
}

static void toUtcMinus3(time_struct * time) {
    if (time->hour < 3) {
        time->hour += 21;
        time->day--;
        if (time->day == 0) {
            time->month--;
            if (time->month == 0) {
                time->month = 12;
                time->year--;
            }
            if(time->month == 2){
                time->day = 28;
                if(time->year % 4 == 0) {
                    time->day = 29;
                }
            } else if(time->month == 4 || time->month == 6 || time->month == 9 || time->month == 11) {
                time->day = 30;
            } else {
                time->day = 31;
            }
        }
    }
    else {
        time->hour = time->hour - 3;
    }
}
