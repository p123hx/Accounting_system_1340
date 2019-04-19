#ifndef FASTRNG_H_
#define FASTRNG_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
void init_rng(const uint32_t seed);
uint64_t rng(uint64_t *state);

#ifdef __cplusplus
}
#endif

#endif // FASTRNG_H_
