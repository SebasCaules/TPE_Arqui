#include <stdint.h>
#include <videoDriver.h>
#include <keyboard.h>
#include <sysCalls.h>

typedef enum {
    SLEEP = 0,
    TIME,
    PLACEHOLDER,
    READ,
    WRITE
} syscallsNum;


uint64_t sysCallHandler(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t rax) {
    uint64_t ret;
    switch (rax) {
    case READ: return sys_read(rdi, (char *) rsi, rdx);
    case WRITE: return sys_write(rdi, (char *) rsi, rdx);      
    default: return 0;
    }
}

int64_t sys_read(uint64_t fd, uint16_t * buffer, uint64_t length) {
    unsigned char character;
    uint64_t i = 0;
    while (i < length && (character = bufferNext()) != 0) {
        if (character == '\r' || character == '\n') {
            buffer[i++] = '\n';  // Store newline in buffer
            break;               // Exit on newline
        }
        buffer[i++] = character;
    }
    return i;
}

int64_t sys_write(uint64_t fd, uint16_t * buffer, uint64_t length) {
    uint32_t fileDescriptorStyle[] = {0, 0x00FFFFFF, 0x00FF0000, 0x0000FF00};
    return printStrByLength(buffer, fileDescriptorStyle[fd], 0x00000000, length);
}
