#ifndef KMKNN_H
#define KMKNN_H

#include "vector.hpp"
#include "cluster.hpp"

#include <cstdint>

class KMPPKNN
{
public:
    static size_t binary_search(float* array, float target, size_t b, size_t e);
    static void order_smallest(size_t* indexes,size_t index,float* array, float target);
    static Vector **kmppknn(Vector v, uint8_t k, Cluster* clusters, Vector* vectors);

    static void order_smallest(size_t* clusters,size_t cluster_idx,size_t* indexes,size_t index,float* array, float target, size_t b, size_t e);

    static float kmknn(Vector v, uint8_t k, Cluster* clusters, float distances_to_centroids[], size_t index_of_distances[], float smallest_distances[], size_t smallest_indexes[],size_t clusters_indexes[], Vector *vectors);
};

#endif /* KMKNN_H */


