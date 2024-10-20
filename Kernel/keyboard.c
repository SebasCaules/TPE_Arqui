#include <stdint.h>
#include <string.h>
#include <lib.h>
#include <moduleLoader.h>
#include <naiveConsole.h>
#include <videoDriver.h>
#include <keyboard.h>

static uint16_t buffer[BUFFER_SIZE];
static uint64_t buffer_dim = 0;
static uint64_t buffer_current = 0;
static uint8_t reg_shot_flag = 0;

#define specialKeyPressedMapIdx(code) (code - FIRST_SPECIAL_KEY)

static int isSpecialKey(uint16_t code){
    return (code >= FIRST_SPECIAL_KEY) && (code <= LAST_SPECIAL_KEY);
}

extern uint8_t getPressedKey();
extern uint16_t pressedKeyMap[][2];

static uint16_t specialKeyPressedMap[SPECIAL_KEYS_NUMBER] = {0};

static uint8_t isReleased(uint8_t key) {
    return (key & 0x80);
}

static uint8_t isPressed(uint8_t key) {
    return !isReleased(key);
}

static int specialKeyPressed(uint16_t code) {
    if (!isSpecialKey(code)) {
        return -1;
    }
    return specialKeyPressed;
}

static int shiftPressed() {
    return (specialKeyPressed(LEFT_SHIFT) || specialKeyPressed(RIGHT_SHIFT)) ? 1 : 0;
}
static int capsLockPressed() {
    return specialKeyPressed(CAPS_LOCK);
}
// Como en MacOS. Si Caps Lock y Shift estan activados, no se unshiftea.
static int isKeyShifted() {
    return shiftPressed() || (!shiftPressed() && capsLockPressed());
}

static uint8_t releasedKeyToPressedMask(uint8_t key) {
    return (key & 0x7F);
}

uint64_t bufferHasNext() {
    return ( buffer_dim > 0 ) && ( buffer_current < buffer_dim );
}

uint64_t getCurrent() {
    if (bufferHasNext()) {
        return buffer[buffer_current++];
    }
    return 0;
}

void keyboardHandler() {
    uint8_t key = getPressedKey();

    uint8_t isKeyPressed = isPressed(key) ? 1 : 0;

    if (!isKeyPressed) {
        key = releasedKeyToPressedMask(key);
    }

    uint16_t code = pressedKeyMap[key][isKeyShifted()];

    if (isSpecialKey(code)) {
        if (code != CAPS_LOCK && code != NUM_LOCK && code != SCROLL_LOCK) {
            specialKeyPressedMap[specialKeyPressedMapIdx(code)] = isKeyPressed;
        } else if (isKeyPressed) {
            specialKeyPressedMap[specialKeyPressedMapIdx(code)] = 1 - specialKeyPressedMap[specialKeyPressedMapIdx(code)];
        }
    }

    if (!isKeyPressed) {
        return;
    }
    
    buffer[buffer_dim] = code;
    if (buffer_dim < BUFFER_SIZE){
        buffer_dim++;
    } else {
        buffer_dim = 1;
    }
    printCharBW(code);

    
}


// void pressKey() {
//     char pressed;
//     char shift_flag = 0;
//     char write = 1;

//     pressed = scanCodeToAscii(shift_flag);

//     switch(pressed){
//         // case 8:
//         //     ncDelete(); //Falta implementar
//         //     break;
//         case 13:
//             //Rellenar
//             break;
//         case (char)0xAA:
//             shift_flag = 0;
//             write = 0;
//             break;
//         case 0x2A:
//             shift_flag = 1;
//             write = 1;
//         case (char)0x90:
//             write = 0;
//             break;
//         default:
//             printStrBW(pressed);
//     }
//     if(write)
//         pressed = scanCodeToAscii(shift_flag);
//     write = 1;
	
    
// }
