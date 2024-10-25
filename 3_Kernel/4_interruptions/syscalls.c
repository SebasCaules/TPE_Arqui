#include <stdint.h>
#include <videoDriver.h>
#include <keyboard.h>
#include <syscalls.h>
#include <rtc.h>

typedef enum {
    SLEEP = 0,
    TIME,
    FONT,
    READ,
    WRITE,
    CLEAR
} syscallsNum;


typedef struct {
    uint64_t r15, r14, r13, r12, r11, r10, r9, r8, rsi, rdi, rbp, rdx, rcx, rbx, rax;
} Registers;

uint64_t sysCallHandler(Registers * regs) {
    uint64_t ret;
    switch (regs->rax) {
    case TIME: return sys_time(regs->rdi);
    case READ: return sys_read(regs->rdi, regs->rsi, regs->rdx);
    case WRITE: return sys_write(regs->rdi, regs->rsi, regs->rdx);      
    case CLEAR: return sys_clear();
    default: return 0;
        break;
    }
    return ret;
}

int64_t sys_time(time_struct* time) {
    time->seconds = getRTCSeconds();
    time->minutes = getRTCMinutes();
    time->hour = getRTCHours();
    time->day = getRTCDayOfMonth();
    time->month = getRTCMonth();
    time->year = getRTCYear();
    return 0;
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

int64_t sys_clear() {
    clear();
    return 0;
}
