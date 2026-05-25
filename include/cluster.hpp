#ifndef CLUSTER_H
#define CLUSTER_H

#include "vector.hpp"
#include <cstddef>
#include <cmath>



class Cluster
{
private:
    constexpr static size_t size = SQRT_NVECTORS;
    size_t cap;
    size_t radius;
    uint32_t vectorsIndexes[size];



public:
    Vector centroid;
    Cluster();
    virtual ~Cluster();
};

#endif /* CLUSTER_H */
