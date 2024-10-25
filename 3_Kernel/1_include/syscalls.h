#ifndef SYSCALLS_H
#define SYSCALLS_H

#include <stdint.h>

typedef enum {
    STDIN = 0,
    STDOUT,
    STDERR,
    STDMARK,
} fileDesc;

typedef struct time {
    uint8_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minutes;
    uint8_t seconds;
} time_struct;

int64_t sys_time(time_struct* time);

int64_t sys_read(uint64_t fd, uint16_t * buffer, uint64_t length);

int64_t sys_write(uint64_t fd, uint16_t * buffer, uint64_t length);

int64_t sys_clear();

#endif // !SYSCALLS_H
