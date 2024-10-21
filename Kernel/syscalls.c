#include <stdint.h>
#include "videoDriver.h"
#include "keyboard.h"


void sysCallHandler(){

}

int64_t sys_read(uint64_t fd, uint16_t * buffer, uint64_t length){
    uint64_t i = 0;
    return i;
}

int64_t sys_write(uint64_t fd, uint16_t * buffer, uint64_t length) {
    printStrBW(buffer); //hay que hacer otra func en video driver
}

