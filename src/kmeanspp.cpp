#ifndef KMEANSPP_H
#define KMEANSPP_H

#include "../include/cluster.hpp"
#include "../include/vector.hpp"
#include <cstdint>
#include <cstdlib>



Cluster *kmeans(k, vectors, centroids)
{
    bool converged = false;
    while (!converged)
    {
        for (int i = 0; i < NVECTORS; i++)
        {
            Cluster clusters[SQRT_NVECTORS];
            Vector *vector = &vectors[i];
            size_t closest_index = 0;
            int16_t min_distance = euclidian_distance(*vector, centroids[0]);
            for (int j = 1; j < k; j++)
            {
                int16_t distance = euclidian_distance(*vector, *centroids[j]);
                if (distance < min_distance)
                {
                    min_distance = distance;
                    closest_index = j;
                }
            }
            clusters[closest_index].centroid = *vector;
        }
        // Recalculando os centroids como a media dos clusters
    }
}

Cluster *kmeanspp(size_t k, Vector *vectors)
{
    // Inicialmente selecionamos um vetor aleatorio
    size_t n_centroids = 0;

    auto **centroids = static_cast<Vector **>(calloc(k, sizeof(Vector *)));
    size_t first_index = rand() % NVECTORS;
    centroids[n_centroids] = &vectors[first_index];
    n_centroids += 1;


    // Selecionando o restante dos pontos
    auto *distanceSquared = static_cast<uint32_t *>(calloc(k, sizeof(uint32_t)));

    while (n_centroids < k)
    {
        for (int i = 0; i < NVECTORS; i++)
        {
            uint16_t min_distance = euclidian_distance(vectors[i], *centroids[0]);
            for (int j = 1; j < n_centroids; j++)
            {
                uint16_t distance = euclidian_distance(vectors[i], *centroids[j]);
                if (distance < min_distance)
                {
                    min_distance = distance;
                }
            }
            distanceSquared[i] = min_distance;

            // Escolhendo o proximo centroide com probabilidade proporcional a D(x) ^2
        }
        uint64_t total = 0;
        for (int i = 0; i < n_centroids; i++)
        {
            total += distanceSquared[i];
        }
        uint64_t threadshold = rand() % total + 1;
        uint64_t cumulative = 0;

        for (int i = 0; i < NVECTORS; i++)
        {
            cumulative += distanceSquared[i];
            if (cumulative >= threadshold)
            {
                centroids[n_centroids] = &vectors[i];
                n_centroids += 1;
                break;
            }
        }
    }


    free(distanceSquared);
    // KMEANS AQUI

    Clusters *clusters = kmeans(k, vectors, centroids);

    free(centroids);
}


#endif /* KMEANSPP_H */
