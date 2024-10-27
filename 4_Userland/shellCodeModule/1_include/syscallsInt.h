#ifndef TPE_ARQUI_SYSCALLS_H
#define TPE_ARQUI_SYSCALLS_H

#include <stdint.h>

typedef struct time {
    uint8_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minutes;
    uint8_t seconds;

} time_struct;

int64_t sys_time(time_struct* time);

int64_t sys_set_font_scale(uint64_t scale);

int64_t sys_read(uint64_t fd, uint16_t * buffer, uint64_t amount);

int64_t sys_write(uint64_t fd, const char * buffer, uint64_t amount);

int64_t sys_clear();

int64_t sys_draw_rectangle(uint64_t x, uint64_t y, uint64_t width, uint64_t height, uint32_t color);

uint64_t sys_tick();

uint64_t sys_sleep(uint64_t milliseconds);

uint64_t sys_reset_cursor();

uint64_t sys_get_regs(uint64_t * r);

uint64_t sys_beep(uint64_t freq, uint64_t milliseconds);

#endif
