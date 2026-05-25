#ifndef VECTOR_H
#define VECTOR_H

#include <cstdint>

#define VECTOR_DIMENSIONS 14

#define NVECTORS 3000000
#define SQRT_NVECTORS 1733

struct Vector
{
    uint16_t components[VECTOR_DIMENSIONS];
};



uint16_t simple_distance(Vector v1, Vector v2);
uint16_t euclidian_distance(Vector v1, Vector v2);

#endif /* VECTOR_H */
