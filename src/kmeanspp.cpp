#ifndef KMEANSPP_H
#define KMEANSPP_H

#include "../include/cluster.hpp"
#include "../include/vector.hpp"
#include <cstdint>
#include <cstdlib>
#include <cstring>

Cluster *kmeans(uint32_t k, Vector *vectors, Vector *centroids)
{
    bool converged = false;
    auto *clusters = static_cast<Cluster *>(malloc(sizeof(Cluster) * SQRT_NVECTORS));

    while (!converged)
    {
        converged = true;
        for (int i = 0; i < NVECTORS; i++) // iterates through 3M Vec
        {
            Vector *vector = &vectors[i];
            size_t closest_index = 0;
            uint16_t min_distance = euclidian_distance(*vector, centroids[0]);
            for (int j = 1; j < k; j++)
            {
                uint16_t distance = euclidian_distance(*vector, centroids[j]);
                if (distance < min_distance)
                {
                    min_distance = distance;
                    closest_index = j;
                }
            }
            clusters[closest_index].add_vector(vector);
        }
        // Recalculando os centroids como a media dos clusters

        for (int i = 0; i < k; i++)
        {
            Cluster cluster = clusters[i];
            Vector new_centroid = {};
            size_t cluster_size = cluster.size;

            // The new centroid has each component as the mean of their vectors values at this component
            uint16_t is_online = 0;
            uint16_t card_present = 0;
            uint16_t unknown_merchant = 0;

            for (int j = 0; j < cluster.size; j++)
            {
                Vector vector = *cluster.vectorsIndexes[j];

                new_centroid.components.amount += vector.components.amount / cluster_size;
                new_centroid.components.amount_vs_avg += vector.components.amount_vs_avg / cluster_size;
                new_centroid.components.card_present += vector.components.card_present / cluster_size;
                new_centroid.components.day_of_week += vector.components.day_of_week / cluster_size;
                new_centroid.components.hour_of_day += vector.components.hour_of_day / cluster_size;
                new_centroid.components.installments += vector.components.installments / cluster_size;
                new_centroid.components.km_from_home += vector.components.km_from_home / cluster_size;
                new_centroid.components.km_from_last_tx += vector.components.km_from_last_tx / cluster_size;
                new_centroid.components.mcc_risk += vector.components.mcc_risk / cluster_size;
                new_centroid.components.merchant_avg_amount += vector.components.merchant_avg_amount / cluster_size;
                new_centroid.components.minutes_since_last_tx += vector.components.minutes_since_last_tx / cluster_size;
                new_centroid.components.tx_count_24h += vector.components.tx_count_24h / cluster_size;


                is_online += vector.components.is_online;
                card_present += vector.components.card_present;
                unknown_merchant += vector.components.unknown_merchant;
            }

            new_centroid.components.is_online = (is_online / cluster_size) >= .5;
            new_centroid.components.card_present = (card_present / cluster_size) >= .5;
            new_centroid.components.unknown_merchant = (unknown_merchant / cluster_size) >= .5;
            if (!vector_is_equals(new_centroid, cluster.centroid))
            {
                converged = false;
            }

        }
    }
    return clusters;
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
    Cluster *clusters = kmeans(k, vectors, *centroids);

    free(centroids);
    return clusters;
}

#endif /* KMEANSPP_H */
