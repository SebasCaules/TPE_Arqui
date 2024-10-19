#include <stdint.h>
#include <string.h>
#include <lib.h>
#include <moduleLoader.h>
#include <naiveConsole.h>

#include <videoDriver.h>
#include "idtLoader.h"

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
#define WHITE_ON_GREEN 0xA2  // 0xA2 is white background and green text

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

void * initializeKernelBinary()
{
	char buffer[10];

	ncPrint("[x64BareBones]");
	ncNewline();

	ncPrint("CPU Vendor:");
	ncPrint(cpuVendor(buffer));
	ncNewline();

	ncPrint("[Loading modules]");
	ncNewline();
	void * moduleAddresses[] = {
		sampleCodeModuleAddress,
		sampleDataModuleAddress
	};

	loadModules(&endOfKernelBinary, moduleAddresses);
	ncPrint("[Done]");
	ncNewline();
	ncNewline();

	ncPrint("[Initializing kernel's binary]");
	ncNewline();

	clearBSS(&bss, &endOfKernel - &bss);

	ncPrint("  text: 0x");
	ncPrintHex((uint64_t)&text);
	ncNewline();
	ncPrint("  rodata: 0x");
	ncPrintHex((uint64_t)&rodata);
	ncNewline();
	ncPrint("  data: 0x");
	ncPrintHex((uint64_t)&data);
	ncNewline();
	ncPrint("  bss: 0x");
	ncPrintHex((uint64_t)&bss);
	ncNewline();

	ncPrint("[Done]");
	ncNewline();
	ncNewline();
	return getStackBase();
}

int main() {
	load_idt();
	// putPixel(0x00FF0000, 20, 20); //Imprime un pixel rojo

    uint32_t foregroundColor = 0x00FFFFFF; // White color in RGB
    uint32_t backgroundColor = 0x00000000; // Black color in RGB
    
    // char *sampleText = "Once upon a time, in a land far, far away, there lived a brave knight. \
    // He ventured across mountains, valleys, and forests in search of a mysterious treasure. \
    // However, the journey was not easy. He faced fierce dragons, treacherous paths, and endless \
    // storms. Yet, his determination was unshaken. \
    // One day, after a long and tiresome quest, he found a hidden cave. Inside, the treasure \
    // sparkled like the stars in the night sky. But the knight realized something: the real \
    // treasure was not gold or jewels, but the wisdom he had gained along the way.";

    // printStr(sampleText, foregroundColor, backgroundColor);

    // char widthStr[10];
    // intToStr(getWidth(), widthStr);
    // printStr(widthStr, foregroundColor, backgroundColor);
    // // Width = 1024

    // char heightStr[10];
    // intToStr(getHeight(), heightStr);
    // printStr(heightStr, foregroundColor, backgroundColor);
    
	// // Height = 768
	printStrBW("hola");
	while(1);

	return 0;
}


