#include <stdint.h>
#include <string.h>
#include <lib.h>
#include <moduleLoader.h>
#include <naiveConsole.h>

#include <videoDriver.h>
#include "idtLoader.h"
#include <stdlib.h>

extern uint8_t text;
extern uint8_t rodata;
extern uint8_t data;
extern uint8_t bss;
extern uint8_t endOfKernelBinary;
extern uint8_t endOfKernel;

static const uint64_t PageSize = 0x1000;

static void * const sampleCodeModuleAddress = (void*)0x400000;
static void * const sampleDataModuleAddress = (void*)0x500000;

#define VIDEO_MEMORY 0xB8000

typedef int (*EntryPoint)();

void clearBSS(void * bssAddress, uint64_t bssSize)
{
	memset(bssAddress, 0, bssSize);
}

void * getStackBase()
{
	return (void*)(
		(uint64_t)&endOfKernel
		+ PageSize * 8				//The size of the stack itself, 32KiB
		- sizeof(uint64_t)			//Begin at the top of the stack
	);
}

void * initializeKernelBinary() {
	void * moduleAddresses[] = {
		sampleCodeModuleAddress,
		sampleDataModuleAddress
	};
	loadModules(&endOfKernelBinary, moduleAddresses);
	clearBSS(&bss, &endOfKernel - &bss);
	return getStackBase();
}

int main() {
	load_idt();
	displayPrompt("username", "kernel", "~");

	// printf("Hola %d<->%d, %s, \n", 64, 99, "Hola, mundo!");

    // Test cases
    printf("%d %d %d \n", 20, 20);  // Should print error about missing arguments
    printf("%d %d %d \n", 20, 20, 20, 20);  // Should print error about too many arguments
    printf("%d %d %s \n", 20, 20, 20);  // Should print error about type mismatch

	// double n1 = 50.1, n2 = 10.0;
	// printf("%d", (uint64_t) (n1*n2));
	//NO ANDA

	// double g = 20.0;
	// printf("%g double", 10);
	// printf("%g double", 1);
	// printf("%g double", 20);
	// printf("%g double", 1954);
	// printf("%g double", g);
	// float f = 10.5;
	// printf("%f float", f);

	// double n1 = 50.1, n2 = 10.0;
	// printf("%d", (uint64_t) (n1*n2));

	// printf("Type in a character: ");
	// int character = getchar();
	// putchar(character);

	int c = getchar();
	putchar(c);

	while(1);
	return 0;
}