#ifndef FASTRNG_H_
#define FASTRNG_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
void init_rng(const uint32_t seed);
uint64_t xorshift_rng(uint64_t *state);
uint64_t rng();

#ifdef __cplusplus
}
#endif

#endif // FASTRNG_H_
