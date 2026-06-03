#ifndef CLUSTER_H
#define CLUSTER_H

#include "../include/vector.hpp"
#include <cstddef>
#include <cmath>
#include <cstdint>

class Cluster
{
private:
    constexpr static size_t cap = SQRT_NVECTORS;
    size_t radius = 0;

public:
    Vector* vectorsIndexes[cap];
    size_t size = 0;
    Vector centroid;
    void add_vector(Vector *vector);
    uint16_t euclidian_distance(Vector vector);
    Cluster();
    virtual ~Cluster();
};

#endif /* CLUSTER_H */
