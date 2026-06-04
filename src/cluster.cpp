#include "cluster.hpp"
#include "vector.hpp"
#include <cstdint>

void Cluster::add_vector(uint32_t index)
{
    // TODO: Add bounds check
    vectorsIndexes[size++] = index;
}



uint16_t Cluster::euclidian_distance(Vector vector)
{
    return ::euclidian_distance(vector, centroid);
}
