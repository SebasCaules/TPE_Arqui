#include <songplayer.h>

void play_song(Song song) {
	for (int i = 0; i < song.numberOfNotes; i++) {
		Note notei = song.notes[i];
		if(!notei.isSilence) {
			beep(notei.freq, (notei.type*1000)/4);
		} else {
			sys_sleep((notei.type*1000)/4);
		}
	}
}