#include "vector.hpp"

#include <cmath>


uint16_t simple_distance(Vector v1, Vector v2)
{
    uint16_t distance = 0;
    for (int i = 0; i < VECTOR_DIMENSIONS; i++)
    {
        distance += std::abs(v1.components[i] - v2.components[i]);
    }
    return distance;
}

uint16_t euclidian_distance(Vector v1, Vector v2)
{
    uint16_t distance = 0;
    for (int i = 0; i < VECTOR_DIMENSIONS; i++)
    {
        distance += pow(v1.components[i] - v2.components[i], 2);
    }
    return distance;
}
