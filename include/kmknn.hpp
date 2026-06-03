#ifndef KMKNN_H
#define KMKNN_H

#include "vector.hpp"
#include "cluster.hpp"

#include <cstdint>

class KMKNN
{
public:
    static size_t binary_search(float* array,float target,uint8_t b,uint8_t e);
    static void order_smallest(size_t* indexes,size_t index,float* array, float target);
    static Vector **kmppknn(Vector v, uint8_t k, Cluster* clusters);

protected:
};

#endif /* KMKNN_H */


