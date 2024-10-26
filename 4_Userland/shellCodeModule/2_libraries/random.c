#include <random.h>
#include <stdint.h>

unsigned int seed;

void updateSeed(unsigned int newSeed) {
    seed = newSeed;
}

// termina siendo predecible si se generan muy rapido
unsigned int getRandomInt(int min, int max) {
    seed = sys_tick();
    seed = (seed * 1103515245 + 12345) & 0x7fffffff;
    return min + (seed % (max - min + 1));
}
