#include <stdint.h>
#include <syscallsInt.h>
#include <stdLib.h>
#include <strLib.h>

#define NUMBER_OF_SONGS 7

typedef enum {
    REDONDA = 16,
    BLANCA = 8,
    NEGRA = 4,
    CORCHEA = 2,
    SEMI_CORCHEA = 1
} NoteTypes;

typedef struct {
    uint64_t freq;
    NoteTypes type;
    char isSilence;
} Note;

typedef struct {
    Note* notes;
    uint64_t bpm;
    uint64_t numberOfNotes;
} Song;

void playSong(char number);