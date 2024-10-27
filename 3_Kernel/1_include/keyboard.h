#ifndef KEYBOARD_H_
#define KEYBOARD_H_

extern int getPressedKey();

/**
 * @brief Retrieves the currently pressed key.
 * @return The character representation of the pressed key.
 */
void pressedKey();

/**
 * @brief Gets the next character from the input buffer.
 * @return The next character in the buffer.
 */
unsigned char bufferNext();

#endif