#include "fastrng.h"
uint64_t state;

void init_rng(const uint32_t seed)
{
    state = seed;
    state = (state << 32) | state;
}

// Xorshift* random number generator
// Implementation from https://en.wikipedia.org/wiki/Xorshift
#define XORSHIFT_MAGIC 0x2545F4914F6CDD1DULL;
uint64_t rng(uint64_t *state)
{
    uint64_t x = *state;
    x ^= x >> 12;
    x ^= x << 25;
    x ^= x >> 27;
    *state = x;
    return x * XORSHIFT_MAGIC;
}
