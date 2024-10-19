#include <stdint.h>
#include <string.h>
#include <lib.h>
#include <moduleLoader.h>
#include <naiveConsole.h>


char scanCodeToAscii(char shift_flag){
    uint8_t scanCode = getKeyPressed();

    if(shift_flag){
        switch (scanCode) {
            // // Shifted versions (capital letters, punctuation)
            // // Note: This requires Shift key handling, here only as an example.
            case 0x02: return '!';  // Shift + 1
            case 0x03: return '@';  // Shift + 2
            case 0x04: return '#';  // Shift + 3
            case 0x05: return '$';  // Shift + 4
            case 0x06: return '%';  // Shift + 5
            case 0x07: return '^';  // Shift + 6
            case 0x08: return '&';  // Shift + 7
            case 0x09: return '*';  // Shift + 8 //NO ANDA
            case 0x0A: return '(';  // Shift + 9
            case 0x0B: return ')';  // Shift + 0

            case 0x1E: return 'A';  // Shift + a
            case 0x30: return 'B';  // Shift + b
            case 0x2E: return 'C';  // Shift + c
            case 0x20: return 'D';  // Shift + d
            case 0x12: return 'E';  // Shift + e
            case 0x21: return 'F';  // Shift + f
            case 0x22: return 'G';  // Shift + g
            case 0x23: return 'H';  // Shift + h
            case 0x17: return 'I';  // Shift + i
            case 0x24: return 'J';  // Shift + j
            case 0x25: return 'K';  // Shift + k
            case 0x26: return 'L';  // Shift + l
            case 0x32: return 'M';  // Shift + m
            case 0x31: return 'N';  // Shift + n
            case 0x18: return 'O';  // Shift + o
            case 0x19: return 'P';  // Shift + p
            case 0x10: return 'Q';  // Shift + q
            case 0x13: return 'R';  // Shift + r
            case 0x1F: return 'S';  // Shift + s
            case 0x14: return 'T';  // Shift + t
            case 0x16: return 'U';  // Shift + u
            case 0x2F: return 'V';  // Shift + v
            case 0x11: return 'W';  // Shift + w
            case 0x2D: return 'X';  // Shift + x
            case 0x15: return 'Y';  // Shift + y
            case 0x2C: return 'Z';  // Shift + z

            case 0x29: return '~';  // Shift + `
            case 0x0C: return '_';  // Shift + -
            case 0x0D: return '+';  // Shift + =
            case 0x1A: return '{';  // Shift + [
            case 0x1B: return '}';  // Shift + ]
            case 0x2B: return '|';  // Shift + 
            case 0x27: return ':';  // Shift + ;
            case 0x28: return '"';  // Shift + '
            case 0x33: return '<';  // Shift + ,
            case 0x34: return '>';  // Shift + .
            case 0x35: return '?';  // Shift + /
            
            default: return 0;
        }
    }

    switch (scanCode) {
        // Control characters
        case 0x39: return ' ';   // Space

        // Digits
        case 0x02: return '1';
        case 0x03: return '2';
        case 0x04: return '3';
        case 0x05: return '4';
        case 0x06: return '5';
        case 0x07: return '6';
        case 0x08: return '7';
        case 0x09: return '8';
        case 0x0A: return '9';
        case 0x0B: return '0';

        // Letters (lowercase by default)
        case 0x1E: return 'a';
        case 0x30: return 'b';
        case 0x2E: return 'c';
        case 0x20: return 'd';
        case 0x12: return 'e';
        case 0x21: return 'f';
        case 0x22: return 'g';
        case 0x23: return 'h';
        case 0x17: return 'i';
        case 0x24: return 'j';
        case 0x25: return 'k';
        case 0x26: return 'l';
        case 0x32: return 'm';
        case 0x31: return 'n';
        case 0x18: return 'o';
        case 0x19: return 'p';
        case 0x10: return 'q';
        case 0x13: return 'r';
        case 0x1F: return 's';
        case 0x14: return 't';
        case 0x16: return 'u';
        case 0x2F: return 'v';
        case 0x11: return 'w';
        case 0x2D: return 'x';
        case 0x15: return 'y';
        case 0x2C: return 'z';

        // Punctuation and special characters
        case 0x29: return '`';  // Backtick
        case 0x0C: return '-';
        case 0x0D: return '=';
        case 0x1A: return '[';
        case 0x1B: return ']';
        case 0x2B: return '\\';
        case 0x27: return ';';
        case 0x28: return '\'';
        case 0x33: return ',';
        case 0x34: return '.';
        case 0x35: return '/';

        default: return 0;  // Return 0 for any unhandled scan code
    }

}

void pressKey(){
    char pressed;
    char shift_flag = 0;
    char write = 1;

    pressed = scanCodeToAscii(shift_flag);

    switch(pressed){
        // case 8:
        //     ncDelete(); //Falta implementar
        //     break;
        case 13:
            ncNewline();
            break;
        case (char)0xAA:
            shift_flag = 0;
            write = 0;
            break;
        case 0x2A:
            shift_flag = 1;
            write = 1;
        case (char)0x90:
            write = 0;
            break;
        default:
            ncPrintChar(pressed);
    }
    if(write)
        pressed = scanCodeToAscii(shift_flag);
    write = 1;
	
    
}