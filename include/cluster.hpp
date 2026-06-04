#ifndef CLUSTER_H
#define CLUSTER_H

#include "../include/vector.hpp"
#include <cstddef>
#include <cmath>
#include <cstdint>

class Cluster
{
private:
    // TODO: Fix buffer overflow
    constexpr static size_t cap = SQRT_NVECTORS * 10;

public:
    float radius = 0;
    uint32_t vectorsIndexes[cap];
    float vector_distances[cap];
    size_t size = 0;
    Vector centroid;
    void add_vector(uint32_t index);
    uint16_t euclidian_distance(Vector vector);
};

#endif /* CLUSTER_H */
