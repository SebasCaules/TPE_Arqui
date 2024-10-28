#include <stdint.h>
#include <syscallsInt.h>

typedef enum {
    REDONDA = 16,
    BLANCA = 8,
    NEGRA = 4,
    COCRCHEA = 2,
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

void play_song(Song song);