#include <time.h>
#include <naiveConsole.h>

static unsigned long ticks = 0;

void timer_handler() {
	ticks++;
	if(ticks % 18 == 0 && ticks != 0){
		ncPrintDec(ticks/18);
		ncPrint(" ");
	}

}

int ticks_elapsed() {
	return ticks;
}

int seconds_elapsed() {
	return ticks / 18;
}
