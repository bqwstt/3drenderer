#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#include <stdio.h>

typedef float   float32_t;
typedef double  float64_t;
typedef int32_t bool_t;

#define countof(a)  (size_t)(sizeof(a) / sizeof(*(a)))
#define lengthof(s) (countof(s) - 1)

#define assert(c)  while (!(c)) __builtin_unreachable()
#define todo(msg) do { \
    fprintf(stderr, "TODO: %s (%s:%d)\n", msg, __FILE__, __LINE__); \
    __builtin_trap(); \
} while (0)

#define swap(a, b) do { \
    a=a^b; \
    b=a^b; \
    a=b^a; \
} while(0)

#endif // UTILS_H