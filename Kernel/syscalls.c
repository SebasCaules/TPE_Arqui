#include <stdint.h>
#include "videoDriver.h"
#include "keyboard.h"


void sysCallHandler(){

}

int64_t sys_read(uint64_t fd, uint16_t * buffer, uint64_t length){
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

