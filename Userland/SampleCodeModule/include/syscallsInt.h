#ifndef TPE_ARQUI_SYSCALLS_H
#define TPE_ARQUI_SYSCALLS_H

#include <stdint.h>
#include <stdlib.h>

int64_t read(uint64_t fd, uint16_t * buffer, uint64_t length);

int64_t write(uint64_t fd, uint16_t * buffer, uint64_t length);

#endif //TPE_ARQUI_SYSCALLS_H
