#include "cluster.hpp"
#include "vector.hpp"
#include <cstdint>
#include <iostream>
#include <stdexcept>

void Cluster::add_vector(uint32_t index)
{
    // TODO: Add bounds check
    vectorsIndexes[size++] = index;
#ifdef IS_DEBUG
    if(size > cap)
    {
        cerr << "OVERFLOW AT CLUSTER VECTORS";
        exit(1);
    }
#endif
}



uint16_t Cluster::euclidian_distance(Vector vector)
{
    return ::euclidian_distance(vector, centroid);
}
