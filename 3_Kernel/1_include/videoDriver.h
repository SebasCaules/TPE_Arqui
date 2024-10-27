#include <stdint.h>

/**
 * @brief Puts a pixel on the screen at the specified coordinates with the given color.
 * @param hexColor The color of the pixel in hexadecimal format.
 * @param x The x-coordinate of the pixel.
 * @param y The y-coordinate of the pixel.
 */
void putPixel(uint32_t hexColor, uint64_t x, uint64_t y);

/**
 * @brief Prints a string to the screen with specified foreground and background colors.
 * @param str The string to print.
 * @param fgcolor The color of the text.
 * @param bgcolor The color of the background.
 */
void printStr(char* str, int fgcolor, int bgcolor);

/**
 * @brief Prints a string in black and white format.
 * @param str The string to print.
 */
void printStrBW(char* str);

/**
 * @brief Prints a single character in black and white format.
 * @param c The character to print.
 */
void printCharBW(char c);

/**
 * @brief Prints a newline character to the screen.
 */
void printNewLine();

/**
 * @brief Prints a tab character to the screen.
 */
void printTab();

/**
 * @brief Deletes the last character printed on the screen.
 */
void deleteChar();

/**
 * @brief Draws a rectangle on the screen at the specified coordinates with the given color.
 * @param x The x-coordinate of the top-left corner of the rectangle.
 * @param y The y-coordinate of the top-left corner of the rectangle.
 * @param width The width of the rectangle.
 * @param height The height of the rectangle.
 * @param color The color of the rectangle.
 */
void drawRectangle(uint64_t x, uint64_t y, uint64_t width, uint64_t height, uint32_t color);

/**
 * @brief Converts an integer to a string.
 * @param num The integer to convert.
 * @param str The buffer to store the resulting string.
 */
void intToStr(int num, char *str);

/**
 * @brief Prints an integer to the screen.
 * @param num The integer to print.
 */
void printInt(int num);

/**
 * @brief Displays a command prompt with the specified username, hostname, and current directory.
 * @param username The username to display.
 * @param hostname The hostname to display.
 * @param currentDir The current directory to display.
 */
void displayPrompt(char* username, char* hostname, char* currentDir);

/**
 * @brief Prints a character to the screen with specified foreground and background colors.
 * @param c The character to print.
 * @param fgcolor The color of the text.
 * @param bgcolor The color of the background.
 * @return The total number of characters printed.
 */
uint64_t printChar(char c, int fgcolor, int bgcolor);

/**
 * @brief Prints a newline and then displays the prompt.
 */
void printNewLineWPrompt();

/**
 * @brief Clears the screen.
 */
void clear();

/**
 * @brief Resets the cursor position to the top-left corner of the screen.
 */
void resetCursor();

/**
 * @brief Prints a decimal value to the screen.
 * @param value The decimal value to print.
 */
void printDec(uint64_t value);

/**
 * @brief Prints a hexadecimal value to the screen.
 * @param value The hexadecimal value to print.
 */
void printHex(uint64_t value);

/**
 * @brief Prints a binary value to the screen.
 * @param value The binary value to print.
 */
void printBin(uint64_t value);

/**
 * @brief Prints a string to the screen up to a specified length with foreground and background colors.
 * @param str The string to print.
 * @param fgcolor The color of the text.
 * @param bgcolor The color of the background.
 * @param length The maximum number of characters to print.
 * @return The total number of characters printed.
 */
uint64_t printStrByLength(char* str, int fgcolor, int bgcolor, int length);

/**
 * @brief Sets the font scale for printed text.
 * @param scale The desired font scale.
 * @return An integer indicating the success or failure of the operation.
 */
int64_t setFontScale(uint64_t scale);

