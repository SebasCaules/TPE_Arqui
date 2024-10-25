#include <stdint.h>
#include <stdarg.h>
#include "videoDriver.h"
#include "keyboard.h"
#include "syscalls.h"


uint64_t sysCallHandler(uint64_t id, ...) {
    va_list args;
    va_start(args, id);
    uint64_t ret;
    switch (id) {
    case 3:
    case 4:
        fileDesc fd = va_arg(args, fileDesc);
        char *buffer = va_arg(args, char *);
        uint64_t count = va_arg(args, uint64_t);
        if (id == 3)
            ret = sys_read(fd, buffer, count);
        else
            ret = sys_write(fd, buffer, count);
        break;
    default:
        break;
    }
    va_end(args);
    return ret;
}


// typedef struct {
//     uint64_t r15, r14, r13, r12, r11, r10, r9, r8, rsi, rdi, rbp, rdx, rcx, rbx, rax;
// } Registers;

// uint64_t sysCallHandler(Registers * regs) {
//     uint64_t ret;
//     switch (regs->rax) {
//     case 3:
//         ret = sys_read(regs->rdi, regs->rsi, regs->rdx);
//     case 4:
//         ret = sys_write(regs->rdi, regs->rsi, regs->rdx);      
//         break;
//     default:
//         break;
//     }
//     return ret;
// }

int64_t sys_read(uint64_t fd, uint16_t * buffer, uint64_t length) {
    unsigned char character;
    uint64_t i = 0;
    while (i < length && (character = bufferNext) != 0)
    {
        buffer[i++] = character;
    }
    return i;
}

int64_t sys_write(uint64_t fd, uint16_t * buffer, uint64_t length) {
    uint32_t fileDescriptorStyle[] = {0, 0x00FFFFFF, 0x00FF0000, 0x0000FF00};
    return printStrByLength(buffer, fileDescriptorStyle[fd], 0x00000000, length);
}
