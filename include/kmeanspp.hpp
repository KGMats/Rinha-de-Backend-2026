#ifndef KMEANSPP_H
#define KMEANSPP_H

#include "cluster.hpp"

Cluster *kmeans(uint32_t k, Vector *vectors, Vector **centroids);
Cluster *kmeanspp(size_t k, Vector *vectors);
#endif /* KMEANSPP_H */
