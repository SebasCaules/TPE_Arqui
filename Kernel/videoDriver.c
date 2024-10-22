#include <videoDriver.h>
#include "font.h"


#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768
#define BORDER_PADDING 50
#define VERTICAL_PADDING 4
#define CHAR_HEIGHT 16
#define CHAR_WIDTH 8

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

void putPixel(uint32_t hexColor, uint64_t x, uint64_t y) {
    uint8_t * framebuffer = (uint8_t *) VBE_mode_info->framebuffer;
    uint64_t offset = (x * ((VBE_mode_info->bpp)/8)) + (y * VBE_mode_info->pitch);
    framebuffer[offset]     =  (hexColor) & 0xFF;
    framebuffer[offset+1]   =  (hexColor >> 8) & 0xFF; 
    framebuffer[offset+2]   =  (hexColor >> 16) & 0xFF;
}

uint16_t getWidth() {
	return VBE_mode_info->width;
}

uint16_t getHeight() {
	return VBE_mode_info->height;
}

int currentX = BORDER_PADDING;
int currentY = BORDER_PADDING;


// Global variables to store the current position
void printStr(char* str, int fgcolor, int bgcolor) {
    while (*str) {
        // Handle newlines in the string
        if (*str == '\n') {
            currentX = BORDER_PADDING;  // Reset x to the left margin
            currentY += CHAR_HEIGHT + VERTICAL_PADDING;  // Move y to the next line with padding
            str++;  // Move to the next character
            continue;
        }

        // Find the length of the next word (sequence of non-space characters)
        int word_start = 0;
        while (str[word_start] && str[word_start] != ' ' && str[word_start] != '\n') {
            word_start++;
        }
        int word_length = word_start;

        // Check if the word fits in the remaining space on the current line
        if (currentX + word_length * CHAR_WIDTH > WINDOW_WIDTH - BORDER_PADDING) {
            // Move to the next line if the word doesn't fit
            currentX = BORDER_PADDING;  // Reset to the start of the new line
            currentY += CHAR_HEIGHT + VERTICAL_PADDING;  // Move to the next line with padding
        }

        // Check if we're hitting the bottom boundary
        if (currentY + CHAR_HEIGHT > WINDOW_HEIGHT - BORDER_PADDING) {
            // Stop printing if we're beyond the allowed window space
            return;
        }

        // Print the word character by character
        for (int i = 0; i < word_length; i++) {
            drawchar(str[i], currentX, currentY, fgcolor, bgcolor);
            currentX += CHAR_WIDTH;
        }

        // Skip consecutive spaces and handle them as a single space
        str += word_length;
        if (*str == ' ') {
            // Handle the first space after the word
            if (currentX + CHAR_WIDTH > WINDOW_WIDTH - BORDER_PADDING) {
                currentX = BORDER_PADDING;  // Reset x to the start of the next line
                currentY += CHAR_HEIGHT + VERTICAL_PADDING;  // Move to the next line with padding
            } else {
                currentX += CHAR_WIDTH;  // Move x for the space
            }

            // Skip any consecutive spaces after the first one
            while (*str == ' ') {
                str++;  // Skip multiple spaces
            }
        }
    }
}

void printCharBW(char c) {
    // Define character width, height, and space limits
    const int charWidth = 8;
    const int charHeight = 16;

    // Check if the character is a space or newline
    if (c == ' ') {
        // Handle space character by advancing the current position
        currentX += charWidth;
    } else if (c == '\n') {
        // Handle newline by resetting x position and moving to the next line
        currentX = BORDER_PADDING;
        currentY += charHeight + VERTICAL_PADDING;
    } else {
        // Check if the character will go out of bounds and wrap if needed
        if (currentX + charWidth > WINDOW_WIDTH - BORDER_PADDING) {
            // Move to the next line if no space for the character
            currentX = BORDER_PADDING;
            currentY += charHeight + VERTICAL_PADDING;
        }
        
        // Call drawchar() to print the character at the current position
        drawchar(c, currentX, currentY, 0x00FFFFFF, 0x00000000);
        
        // Update currentX for the next character
        currentX += charWidth;
    }
    
    // Check if we go beyond the window height
    if (currentY + charHeight > WINDOW_HEIGHT - BORDER_PADDING) {
        // Reset Y position or handle screen overflow as necessary
        currentY = BORDER_PADDING;  // Optionally reset or scroll
    }
}

void printStrBW(char* str){
	uint32_t foregroundColor = 0x00FFFFFF; // White color in RGB
    uint32_t backgroundColor = 0x00000000; // Black color in RGB
	printStr(str, foregroundColor, backgroundColor);
}

void printNewLine(){
	currentX = BORDER_PADDING;
	currentY += CHAR_HEIGHT + VERTICAL_PADDING;
}

void printTab(){
	for (int i = 0; i < 4; i++) {
		printCharBW(' ');
	}
}

void drawRectangle(uint64_t x, uint64_t y, uint64_t width, uint64_t height, uint32_t color) {
    for (uint64_t i = 0; i < width; i++) {
        for (uint64_t j = 0; j < height; j++) {
            putPixel(color, x + i, y + j);
        }
    }
}

void deleteChar() {
    currentX -= CHAR_WIDTH;
    drawRectangle(currentX, currentY - CHAR_HEIGHT, CHAR_WIDTH, CHAR_HEIGHT, 0x00000000);
}

void reverseStr(char *str, int length) {
    int start = 0;
    int end = length - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

void intToStr(int num, char *str) {
    int i = 0;
    do {
        str[i++] = (num % 10) + '0';
        num /= 10;
    } while (num > 0);
    str[i] = '\0';
    reverseStr(str, i);
}

void printInt(int num){
    char aux[20];
    intToStr(num, aux);
    printStrBW(aux);
}