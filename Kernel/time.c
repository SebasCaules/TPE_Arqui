#include <time.h>
#include <naiveConsole.h>
#include "videoDriver.h"

static unsigned long ticks = 0;

void timer_handler() {
	ticks++;
	if(ticks % 18 == 0 && ticks != 0){
		char str[20];
		intToStr(ticks/18, str);
		//printStrBW(str);
	}
}

int ticks_elapsed() {
	return ticks;
}

int seconds_elapsed() {
	return ticks / 18;
}

void nano_sleep(int time){
	int start = ticks;
	while(ticks - start < time) {
		_hlt();
	}
}
