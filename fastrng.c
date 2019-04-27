#include "fastrng.h"
#include <time.h>
uint64_t state;
int initialize;

void init_rng(const uint32_t seed)
{
    state = seed;
    state = (state << 32) | state;
}

// Xorshift* random number generator
// Implementation from https://en.wikipedia.org/wiki/Xorshift
#define XORSHIFT_MAGIC 0x2545F4914F6CDD1DULL;
uint64_t xorshift_rng(uint64_t *state)
{
    uint64_t x = *state;
    x ^= x >> 12;
    x ^= x << 25;
    x ^= x >> 27;
    *state = x;
    return x * XORSHIFT_MAGIC;
}

uint64_t rng()
{
    if(initialize == 0)
    {
        init_rng(time(NULL));
        initialize = 1;
    }
    return xorshift_rng(&state);
}
