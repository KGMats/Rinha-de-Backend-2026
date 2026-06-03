#include "cluster.hpp"
#include "vector.hpp"
#include <cstdint>

void Cluster::add_vector(Vector* vector)
{
    // TODO: Add bounds check
    vectorsIndexes[size++] = vector;
}



uint16_t Cluster::euclidian_distance(Vector vector)
{
    return ::euclidian_distance(vector, centroid);
}
