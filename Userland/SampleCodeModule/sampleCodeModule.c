/* sampleCodeModule.c */
#include <stdLib.h>

char * v = (char*)0xB8000 + 79 * 2;

static int var1 = 0;
static int var2 = 0;


int main() {
	// //Test if BSS is properly set up
	// if (var1 == 0 && var2 == 0)
	// 	return 0xDEADC0DE;

	printf("%g gola", 20.0); 

	return 0xDEADBEEF;
}