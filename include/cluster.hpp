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
    constexpr static size_t cap = SQRT_NVECTORS;

public:
    size_t radius = 0;
    uint32_t vectorsIndexes[cap];
    uint16_t vector_distances[cap];
    size_t size = 0;
    Vector centroid;
    void add_vector(uint32_t index);
    uint16_t euclidian_distance(Vector vector);
};

#endif /* CLUSTER_H */
