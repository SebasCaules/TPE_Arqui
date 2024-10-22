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

int64_t sys_read(uint64_t fd, uint16_t * buffer, uint64_t length) {
    uint64_t i = 0;
    char c;
    while (i < length && (c = bufferNext()) != 0) {
        buffer[i++] = c;
    }
    return i;
}

int64_t sys_write(uint64_t fd, uint16_t * buffer, uint64_t length) {
    uint32_t fileDescriptorStyle[] = {0, 0x00FFFFFF, 0x00FF0000, 0x0000FF00};
    return printStrByLength(buffer, fileDescriptorStyle[fd], 0x00000000, length);
}
