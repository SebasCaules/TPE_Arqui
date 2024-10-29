#include <spotify.h>

#define D_SHARP_4 311    // D#4
#define F4 349           // F4
#define F_SHARP_4 370    // F#4
#define G4 392           // G4
#define G_SHARP_4 415    // G#4
#define A_SHARP_4 466    // A#4
#define C5 523           // C5
#define D5 587           // D5

static Note do4_scale[] = {
    {261, NEGRA, 0},  // C4
    {293, NEGRA, 0},  // D4
    {329, NEGRA, 0},  // E4
    {349, NEGRA, 0},  // F4
    {392, NEGRA, 0},  // G4
    {440, NEGRA, 0},  // A4
    {493, NEGRA, 0},  // B4
    {523, NEGRA, 0}   // C5
};

static Note happy_birthday_notes[] = {
    // First line
    {392, NEGRA, 0}, {392, CORCHEA, 0}, {440, NEGRA, 0}, {392, NEGRA, 0},
    {523, NEGRA, 0}, {494, BLANCA, 0},
    // Second line
    {392, NEGRA, 0}, {392, CORCHEA, 0}, {440, NEGRA, 0}, {392, NEGRA, 0},
    {587, NEGRA, 0}, {523, BLANCA, 0},
    // Third line
    {392, NEGRA, 0}, {392, CORCHEA, 0}, {784, NEGRA, 0}, {659, NEGRA, 0},
    {523, NEGRA, 0}, {494, NEGRA, 0}, {440, BLANCA, 0},
    // Fourth line
    {698, NEGRA, 0}, {698, CORCHEA, 0}, {659, NEGRA, 0}, {523, NEGRA, 0},
    {587, NEGRA, 0}, {523, BLANCA, 0}
};

static Note rezo_por_vos_notes[] = {
    // Part 1
    {440, NEGRA, 0}, {523, CORCHEA, 0}, {494, CORCHEA, 0}, {440, NEGRA, 0},
    {329, NEGRA, 0}, {392, BLANCA, 0},
    // Part 2
    {349, NEGRA, 0}, {329, CORCHEA, 0}, {293, CORCHEA, 0}, {261, NEGRA, 0},
    {392, NEGRA, 0}, {440, BLANCA, 0},
    // Chorus Variation
    {329, NEGRA, 0}, {392, CORCHEA, 0}, {349, CORCHEA, 0}, {329, NEGRA, 0},
    {293, NEGRA, 0}, {261, BLANCA, 0}
};

Note layla_riff_notes[] = {
    // Part 1
    {587, SEMI_CORCHEA, 0}, {523, SEMI_CORCHEA, 0}, {440, NEGRA, 0},
    {587, CORCHEA, 0}, {523, CORCHEA, 0}, {440, CORCHEA, 0},
    // Part 2
    {698, SEMI_CORCHEA, 0}, {659, SEMI_CORCHEA, 0}, {587, NEGRA, 0},
    {523, CORCHEA, 0}, {440, NEGRA, 0},
    // Part 3 (Repeat with Variation)
    {587, SEMI_CORCHEA, 0}, {523, SEMI_CORCHEA, 0}, {440, CORCHEA, 0},
    {784, CORCHEA, 0}, {698, CORCHEA, 0}, {587, NEGRA, 0},
    // Additional Variations
    {523, SEMI_CORCHEA, 0}, {440, CORCHEA, 0}, {587, SEMI_CORCHEA, 0},
    {698, CORCHEA, 0}, {440, CORCHEA, 0}
};


Note adios_nonino_notes[] = {
	{D_SHARP_4, BLANCA, 0}, {D_SHARP_4, NEGRA, 0}, {A_SHARP_4, CORCHEA, 0}, {G_SHARP_4, CORCHEA, 0},
	{D_SHARP_4, BLANCA, 0}, {D_SHARP_4, NEGRA, 0}, {C5, CORCHEA, 0}, {A_SHARP_4, CORCHEA, 0},
	{D_SHARP_4, BLANCA, 0}, {D_SHARP_4, NEGRA, 0}, {F4, CORCHEA, 0}, {F_SHARP_4, CORCHEA, 0},
	{F_SHARP_4, BLANCA, 0}, {F4, NEGRA, 0}, {F4, NEGRA, 0}
};

Note wish_you_were_here_riff[] = {
	// Opening arpeggio pattern
	{392, CORCHEA, 0},    // G4
	{440, CORCHEA, 0},    // A4
	{392, NEGRA, 0},      // G4
	{0, CORCHEA, 1},      // Brief pause
	
	{392, CORCHEA, 0},    // G4
	{440, CORCHEA, 0},    // A4
	{392, NEGRA, 0},      // G4
	{0, CORCHEA, 1},      // Brief pause
	
	// Variation
	{349, CORCHEA, 0},    // F4
	{392, CORCHEA, 0},    // G4
	{349, NEGRA, 0},      // F4
	{0, CORCHEA, 1},      // Brief pause
	
	{349, CORCHEA, 0},    // F4
	{392, CORCHEA, 0},    // G4
	{349, NEGRA, 0},      // F4
	{0, CORCHEA, 1},      // Brief pause
	
	// Bridge section
	{440, NEGRA, 0},      // A4
	{392, NEGRA, 0},      // G4
	{349, NEGRA, 0},      // F4
	{329, NEGRA, 0},      // E4
	
	// Repeat with variation
	{440, NEGRA, 0},      // A4
	{392, NEGRA, 0},      // G4
	{349, NEGRA, 0},      // F4
	{329, NEGRA, 0},      // E4
	
	// Ending phrase
	{392, CORCHEA, 0},    // G4
	{440, CORCHEA, 0},    // A4
	{392, NEGRA, 0},      // G4
	{349, NEGRA, 0},      // F4
	
	{392, BLANCA, 0},     // G4
	{0, NEGRA, 1},        // Pause
	{349, BLANCA, 0},     // F4
	{0, NEGRA, 1}         // Final pause
};

Note magalenha_melody[] = {
    // Intro Section
    {330, SEMI_CORCHEA, 0},  // E4
    {392, CORCHEA, 0},       // G4
    {440, SEMI_CORCHEA, 0},  // A4
    {494, CORCHEA, 0},       // B4
    {659, SEMI_CORCHEA, 0},  // E5

    // Main Phrase
    {392, CORCHEA, 0},       // G4
    {494, SEMI_CORCHEA, 0},  // B4
    {440, SEMI_CORCHEA, 0},  // A4
    {392, CORCHEA, 0},       // G4
    {330, NEGRA, 0},         // E4
    {494, CORCHEA, 0},       // B4
    {440, CORCHEA, 0}        // A4
};

static Song songList[NUMBER_OF_SONGS] = {
	{do4_scale, 240, sizeof(do4_scale) / sizeof(Note)}, 
	{happy_birthday_notes, 120, sizeof(happy_birthday_notes) / sizeof(Note)}, 
	{rezo_por_vos_notes, 100, sizeof(rezo_por_vos_notes) / sizeof(Note)},
	{adios_nonino_notes, 78, sizeof(adios_nonino_notes) / sizeof(Note)},
	{layla_riff_notes, 116, sizeof(layla_riff_notes) / sizeof(Note)},
	{wish_you_were_here_riff, 120, sizeof(wish_you_were_here_riff) / sizeof(Note)},
	{magalenha_melody, 116, sizeof(magalenha_melody) / sizeof(Note)}
};

void playSong(char number) {
	number -= 48; //Pasa el ascii a int
	Song song = songList[number - 1]; // Le resta 1 para acceder a la cancion correcta
	double timePerQuarter = (60000.0 / song.bpm);
	for (int i = 0; i < song.numberOfNotes; i++) {
		Note notei = song.notes[i];
		double duration = (notei.type / 4.0) * timePerQuarter; 
		if(!notei.isSilence) {
			beep(notei.freq, duration);
		} else {
			sys_sleep(duration);
		}
	}
}