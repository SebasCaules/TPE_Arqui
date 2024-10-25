#ifndef TPE_ARQUI_SYSCALLS_H
#define TPE_ARQUI_SYSCALLS_H

#include <stdint.h>

int64_t sys_read(uint64_t fd, uint16_t * buffer, uint64_t amount);

int64_t sys_write(uint64_t fd, const char * buffer, uint64_t amount);

int64_t sys_set_font_scale(uint64_t scale);

#endif
