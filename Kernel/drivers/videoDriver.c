#include <videoDriver.h>
#include "font.h"

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768
#define BORDER_PADDING 15
#define VERTICAL_PADDING 4
#define HORIZONTAL_PADDING 2
#define WHITE 0x00FFFFFF
#define BLACK 0x00000000
#define BUFFER_SIZE 256

struct vbe_mode_info_structure {
	uint16_t attributes;		// deprecated, only bit 7 should be of interest to you, and it indicates the mode supports a linear frame buffer.
	uint8_t window_a;			// deprecated
	uint8_t window_b;			// deprecated
	uint16_t granularity;		// deprecated; used while calculating bank numbers
	uint16_t window_size;
	uint16_t segment_a;
	uint16_t segment_b;
	uint32_t win_func_ptr;		// deprecated; used to switch banks from protected mode without returning to real mode
	uint16_t pitch;			// number of bytes per horizontal line
	uint16_t width;			// width in pixels
	uint16_t height;			// height in pixels
	uint8_t w_char;			// unused...
	uint8_t y_char;			// ...
	uint8_t planes;
	uint8_t bpp;			// bits per pixel in this mode
	uint8_t banks;			// deprecated; total number of banks in this mode
	uint8_t memory_model;
	uint8_t bank_size;		// deprecated; size of a bank, almost always 64 KB but may be 16 KB...
	uint8_t image_pages;
	uint8_t reserved0;

	uint8_t red_mask;
	uint8_t red_position;
	uint8_t green_mask;
	uint8_t green_position;
	uint8_t blue_mask;
	uint8_t blue_position;
	uint8_t reserved_mask;
	uint8_t reserved_position;
	uint8_t direct_color_attributes;

	uint32_t framebuffer;		// physical address of the linear frame buffer; write here to draw to the screen
	uint32_t off_screen_mem_off;
	uint16_t off_screen_mem_size;	// size of memory in the framebuffer but not being displayed on the screen
	uint8_t reserved1[206];
} __attribute__ ((packed));

typedef struct vbe_mode_info_structure * VBEInfoPtr;

VBEInfoPtr VBE_mode_info = (VBEInfoPtr) 0x0000000000005C00;

uint8_t fontScale = 1; // NUMERO ENTERO
uint64_t currentX = BORDER_PADDING;
uint64_t currentY = BORDER_PADDING;
uint64_t currentLinePosition = 0;

static char buffer[BUFFER_SIZE] = { '0' };

typedef enum CursorMovementType {
    CURSOR_TYPING,
    CURSOR_DELETING,
    CURSOR_NEWLINE,
    CURSOR_MOVING,
} CursorMovementType;

void putPixel(uint32_t hexColor, uint64_t x, uint64_t y) {
    uint8_t * framebuffer = (uint8_t *) VBE_mode_info->framebuffer;
    uint64_t offset = (x * ((VBE_mode_info->bpp)/8)) + (y * VBE_mode_info->pitch);
    framebuffer[offset]     =  (hexColor) & 0xFF;
    framebuffer[offset+1]   =  (hexColor >> 8) & 0xFF; 
    framebuffer[offset+2]   =  (hexColor >> 16) & 0xFF;
}

uint64_t printChar(char c, int fgcolor, int bgcolor) {
    switch (c) {
    case '\n':
        printNewLine();
        return 1;
    case '\b':
        deleteChar();
        return -1;
    case '\t':
        return 0;
    default:
        break;
    }

    // Si es un caracter ASCII no imprimible devuelve 0
    if (c <= 31){
        return 0;
    }

    // Chequea que la palabra no se pase de los margenes de la pantalla
    if (currentX + CHAR_WIDTH * fontScale + HORIZONTAL_PADDING > WINDOW_WIDTH - BORDER_PADDING) {
        // Si no hay espacio para la plabra salta de linea
        currentX = BORDER_PADDING;
        currentY += (CHAR_HEIGHT + VERTICAL_PADDING) * fontScale;
    }

    if (currentY + CHAR_HEIGHT > WINDOW_HEIGHT - BORDER_PADDING) {
        clear();
        currentY = BORDER_PADDING; //Hay que hacer el scroll aca
    }
    currentLinePosition++;
    drawChar(c, currentX + HORIZONTAL_PADDING, currentY, fgcolor, bgcolor, fontScale);
    currentX += (CHAR_WIDTH * fontScale + HORIZONTAL_PADDING);
    updateTextCursor(CURSOR_TYPING);
    return 1;
}

void printCharBW(char c){
    printChar(c, WHITE, BLACK);
}

void printStr(char* str, int fgcolor, int bgcolor) {
    while(*str){
        printChar(*str++, fgcolor, bgcolor);
    }
}

uint64_t printStrByLength(char* str, int fgcolor, int bgcolor, int length){
    uint64_t i, printed = 0;
	for (i = 0; i < length && str[i] != 0; i++)
		printed += printChar(str[i], fgcolor, bgcolor);
	return printed;
}

void printStrBW(char* str) {
	printStr(str, WHITE, BLACK);
}

void printNewLine() {
    updateTextCursor(CURSOR_NEWLINE);
	currentX = BORDER_PADDING;
	currentY += (CHAR_HEIGHT + VERTICAL_PADDING) * fontScale;
}

// void printNewLineWPrompt() {
//     printNewLine();
//     displayPrompt("username", "kernel", "~");
//     currentLinePosition = 0;
// }

void printTab() {
    // currentX += 4 * CHAR_WIDTH;
    // updateTextCursor(CURSOR_TAB); // no va lo suficiente hacia atras para borrar
}

uint8_t canDelete() {
    return currentLinePosition > 0;
}

void deleteChar() {
    if (!canDelete()) {
        return;
    }
    
    // no anda del todo bien todavia
    // Check if we are at the beginning of the line
    if (currentX <= BORDER_PADDING) {
        // Move to the previous line
        currentY -= (CHAR_HEIGHT + VERTICAL_PADDING) * fontScale;
        // Set currentX to the end of the previous line
        currentX = WINDOW_WIDTH - BORDER_PADDING - CHAR_WIDTH * fontScale - HORIZONTAL_PADDING;
    } else {
        // Regular delete on the same line
        currentX -= CHAR_WIDTH * fontScale + HORIZONTAL_PADDING;
    }
    drawRectangle(currentX, currentY, CHAR_WIDTH * fontScale, CHAR_HEIGHT * fontScale, 0x00000000); // ACA
    updateTextCursor(CURSOR_DELETING);
    currentLinePosition--;
}

void clear() {
    drawRectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0x00000000);
}

void drawRectangle(uint64_t x, uint64_t y, uint64_t width, uint64_t height, uint32_t color) {
    for (uint64_t i = 0; i <= width; i++) {
        for (uint64_t j = 0; j <= height; j++) {
            putPixel(color, x + i, y + j);
        }
    }
}

void updateTextCursor(CursorMovementType movementType) {
    uint64_t xOffset = 0, yOffset = 0;
    switch (movementType) {
        case CURSOR_DELETING:
            xOffset = (CHAR_WIDTH * fontScale + 1.5 * HORIZONTAL_PADDING);
            break;
        case CURSOR_TYPING:
            xOffset = -(CHAR_WIDTH * fontScale + HORIZONTAL_PADDING / 2);
            break;
        case CURSOR_NEWLINE:
            xOffset = HORIZONTAL_PADDING / 2;
            break;
        case CURSOR_MOVING:
            // Para cuando usemos las flechas?
            break;
        default:
            break;
    }
    drawRectangle(currentX + HORIZONTAL_PADDING / 2, currentY, 1, CHAR_HEIGHT * fontScale, 0xFFFFFFFF); // place new one
    drawRectangle(currentX + xOffset, currentY + yOffset, 1, CHAR_HEIGHT * fontScale, 0x0000000); // remove previous one
}

//Ej: sebascaules@kernel:~$ "codigo usuario"
void displayPrompt(char* username, char* hostname, char*currentDir) {
    if(currentX == BORDER_PADDING){
        printStrBW(username);
        printCharBW('@');
        printStrBW(hostname);
        printCharBW(':');
        printStrBW(currentDir);
        printCharBW('$');
        printCharBW(' ');
    }
    currentLinePosition = 0;
}

void setFontScale(uint8_t scale) {
    fontScale = scale;
}


// Imprimir numeros
static uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base) {
	char *p = buffer;
	char *p1, *p2;
	uint32_t digits = 0;

	//Calculate characters for each digit
	do {
		uint32_t remainder = value % base;
		*p++ = (remainder < 10) ? remainder + '0' : remainder + 'A' - 10;
		digits++;
	}
	while (value /= base);

	// Terminate string in buffer.
	*p = 0;

	//Reverse string in buffer.
	p1 = buffer;
	p2 = p - 1;
	while (p1 < p2) {
		char tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
		p1++;
		p2--;
	}

	return digits;
}

void printDec(uint64_t value) {
    printBase(value, 10);
}

void printHex(uint64_t value) {
    printBase(value, 16);
}

void printBin(uint64_t value) { 
    printBase(value, 2);
}

void printBase(uint64_t value, uint32_t base) {
    uintToBase(value, buffer, base);
    ncPrint(buffer);
}
