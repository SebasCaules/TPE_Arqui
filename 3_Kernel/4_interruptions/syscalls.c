#include <stdint.h>
#include <videoDriver.h>
#include <keyboard.h>
#include <syscalls.h>
#include <rtc.h>
#include <time.h>
#include <audioDriver.h>

extern uint64_t regs[17];

typedef enum {
    SLEEP = 0,
    TIME,
    SETFONT,
    READ,
    WRITE,
    CLEAR,
    DRAW_RECTANGLE,
    TICK,
    RESET_CURSOR,
    GET_REGS,
    BEEP
} syscallsNum;


typedef struct {
    uint64_t r15, r14, r13, r12, r11, r10, r9, r8, rsi, rdi, rbp, rdx, rcx, rbx, rax;
} Registers;

uint64_t sysCallHandler(Registers * regs) {
    switch (regs->rax) {
    case SLEEP: return sys_sleep((uint64_t)regs->rdi);
    case TIME: return sys_time((time_struct *)regs->rdi);
    case SETFONT: return sys_set_font_scale((uint64_t)regs->rdi);
    case READ: return sys_read((uint64_t)regs->rdi, (uint16_t *)regs->rsi, (uint64_t)regs->rdx);
    case WRITE: return sys_write((uint64_t)regs->rdi, (uint16_t *)regs->rsi, (uint64_t)regs->rdx);      
    case CLEAR: return sys_clear();
    case DRAW_RECTANGLE: return sys_draw_rectangle((uint64_t)regs->rdi, (uint64_t)regs->rsi, (uint64_t)regs->rdx, (uint64_t)regs->rcx, (uint32_t)regs->r8);
    case TICK: return sys_tick();
    case RESET_CURSOR: return sys_reset_cursor();
    case GET_REGS: return sys_get_regs((uint64_t *)regs->rdi);
    case BEEP: return sys_beep((uint64_t)regs->rdi, (uint64_t)regs->rsi);
    default: return 0;
    }
}

uint64_t sys_sleep(uint64_t milliseconds) {
    unsigned long long initial_time = ms_elapsed();
    unsigned long long currentTime = initial_time;
    // Activate interrupts
    _sti();
    while ((currentTime - initial_time) <= milliseconds) {
        currentTime = ms_elapsed();
    }
    // Deactivate interrupts
    _cli();
    return 1;
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

int64_t sys_set_font_scale(uint64_t scale) {
    return setFontScale(scale);
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
    return printStrByLength((char *)buffer, fileDescriptorStyle[fd], 0x00000000, length);
}

int64_t sys_clear() {
    clear();
    return 0;
}

int64_t sys_draw_rectangle(uint64_t x, uint64_t y, uint64_t width, uint64_t height, uint32_t color) {
    drawRectangle(x, y, width, height, color);
    return 0;
}

uint64_t sys_tick() {
    return ticks_elapsed();
}

uint64_t sys_reset_cursor() {
    resetCursor();
    return 0;
}

uint64_t sys_get_regs(uint64_t * r) {
    return getRegisters(r);
}

uint64_t sys_beep(uint64_t freq, uint64_t milliseconds) {
    beep(freq, milliseconds);
    return 0;
}

