#include <stdint.h>
#include <videoDriver.h>
#include <keyboard.h>
#include <syscalls.h>

typedef enum {
    SLEEP = 0,
    TIME,
    SETFONT,
    READ,
    WRITE
} syscallsNum;


typedef struct {
    uint64_t r15, r14, r13, r12, r11, r10, r9, r8, rsi, rdi, rbp, rdx, rcx, rbx, rax;
} Registers;

uint64_t sysCallHandler(Registers * regs) {
    uint64_t ret;
    switch (regs->rax) {
    case 2:
        ret = sys_set_font_scale(regs->rdi);
        break;
    case 3:
        ret = sys_read(regs->rdi, regs->rsi, regs->rdx);
        break;
    case 4:
        ret = sys_write(regs->rdi, regs->rsi, regs->rdx);      
        break;
    default:
        break;
    }
    return ret;
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

int64_t sys_set_font_scale(uint64_t scale) {
    return setFontScale(scale);
}
