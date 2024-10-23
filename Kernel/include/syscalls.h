#ifndef SYSCALLS_H
#define SYSCALLS_H

#include <stdint.h>

typedef enum {
    STDIN = 0,
    STDOUT,
    STDERR,
    STDMARK,
} fileDesc;

uint64_t sysCallHandler(uint64_t id, ...);

int64_t sys_read(uint64_t fd, uint16_t * buffer, uint64_t length);

int64_t sys_write(uint64_t fd, uint16_t * buffer, uint64_t length);

#endif // !SYSCALLS_H
