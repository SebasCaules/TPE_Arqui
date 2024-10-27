#include <stdint.h>
#include <syscalls.h>
#include <lib.h>

#define ZERO_EXCEPTION_ID 0
#define OPCODE_EXCEPTION_ID 6

extern uint64_t * getSnap();

static throwException(char* msg);
static void dumpRegisters();

static char *regNames[] = {
    "rax   ", "rbx   ", "rcx   ", "rdx   ", "rsi   ", "rdi   ", "rbp   ",
    "r8    ", "r9    ", "r10   ", "r11   ", "r12   ", "r13   ", "r14   ",
    "r15   ", "rsp   ", "rip   ", "rflags", "cs    ", "ss    "
};

static int regsAmount = (sizeof(regNames) / sizeof(regNames[0]));


void exceptionDispatcher(int exception) {
	char* msg;
	if(exception == ZERO_EXCEPTION_ID) { 
		msg = "ERROR 0x00: Division by zero exception\n";
	}
	if(exception == OPCODE_EXCEPTION_ID) { 
		msg = "ERROR 0x06: Invalid Opcode exception\n";
	}
	throwException(msg);
	return;
}

static throwException(char* msg) { 
	sys_clear();
	sys_write(STDERR, msg, strlength(msg));
	dumpRegisters();

    char * continueMessage = "\nPress any key to relaunch shell...\n";
    sys_write(1, continueMessage , strlength(continueMessage));

    int readBytes = 0;
    char c;
    _sti();
    while(readBytes == 0){
        readBytes = sys_read(0, &c, 1);
    }
}

static void dumpRegisters(){
    uint64_t * registers = getSnap();
    char buffer[17];

    for(int i = 0; i < regsAmount; i++){
        itoaHex(registers[i], buffer);
        int zeroDigits = 16 - strlength(buffer);

        sys_write(STDOUT, regNames[i], strlength(regNames[i]));
        sys_write(STDOUT, ": 0x", 4);
        for(int j = 0; j < zeroDigits; j++){
            sys_write(STDOUT, "0", 1);
        }
        sys_write(STDOUT, itoaHex(registers[i], buffer), strlength(buffer));
        sys_write(STDOUT, "\n", 1);
    }
}