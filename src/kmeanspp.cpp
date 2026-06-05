#ifndef KMEANSPP_H
#define KMEANSPP_H

#include "cluster.hpp"
#include "vector.hpp"
#include <algorithm>
#include <cfloat>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <ostream>
#include <random>
#include <iostream>

Cluster *kmeans(uint32_t k, Vector *vectors, Vector **centroids)
{
    bool converged = false;
    auto *clusters = static_cast<Cluster *>(malloc(sizeof(Cluster) * k)); // Fixed allocation size

    std::vector<uint8_t> centroid_changed(k, 1);
    auto *owner         = static_cast<uint32_t *>(malloc(NVECTORS * sizeof(uint32_t)));

    // u(x): distancia atual do vetor ao seu centroide
    auto *vector_dist   = static_cast<float *>(malloc(NVECTORS * sizeof(float)));

    // quanto cada centroide se moveu na ultima iteracao
    auto *centroid_delta = static_cast<float *>(malloc(k * sizeof(float)));

    std::fill(owner, owner + NVECTORS, UINT32_MAX);
    std::fill(vector_dist, vector_dist + NVECTORS, 0.0f);
    std::fill(centroid_delta, centroid_delta + k, FLT_MAX);

    size_t iterations = 0;
    while (!converged)
    {
        iterations++;
        cout << "ITERATIONS: " << iterations << endl;
        converged = true;

        for (size_t i = 0; i < k; i++)
        {
            clusters[i].size = 0;
        }

        for (size_t i = 0; i < NVECTORS; i++) // iterates through 3M Vec
        {
            // Se a distancia atual do vetor ao seu centroide
            // e menor que metade do quanto o centroide se moveu, ele não pode ter trocado de dono
            if (owner[i] != UINT32_MAX && vector_dist[i] * 2.0f <= centroid_delta[owner[i]])
            {
                clusters[owner[i]].add_vector(i);
                continue;
            }

            Vector *vector = &vectors[i];
            size_t closest_index = 0;
            float min_distance = euclidian_distance(*vector, *centroids[0]);
            for (size_t j = 1; j < k; j++)
            {
                float distance = euclidian_distance(*vector, *centroids[j]);
                if (distance < min_distance)
                {
                    min_distance = distance;
                    closest_index = j;
                }
            }

            if (owner[i] != closest_index)
            {
                owner[i] = closest_index;
            }

            vector_dist[i] = min_distance;
            clusters[closest_index].add_vector(i);
        }

        // Recalculando os centroids como a media dos clusters
        for (size_t i = 0; i < k; i++)
        {
            if (clusters[i].size == 0) continue; // Evitando divisao por 0
            Cluster &cluster = clusters[i];

            Vector new_centroid = {};
            size_t cluster_size = cluster.size;

            // Usando uint64_t para evitar overflow dos acumuladores
            uint64_t sum_amount = 0;
            uint64_t sum_amount_vs_avg = 0;
            uint64_t sum_day_of_week = 0;
            uint64_t sum_hour_of_day = 0;
            uint64_t sum_installments = 0;
            uint64_t sum_km_from_home = 0;
            uint64_t sum_km_from_last_tx = 0;
            uint64_t sum_mcc_risk = 0;
            uint64_t sum_merchant_avg_amount = 0;
            uint64_t sum_minutes_since_last_tx = 0;
            uint64_t sum_tx_count_24h = 0;

            uint32_t is_online = 0;
            uint32_t card_present = 0;
            uint32_t unknown_merchant = 0;

            for (size_t j = 0; j < cluster.size; j++)
            {
                Vector vector = vectors[cluster.vectorsIndexes[j]];

                sum_amount += vector.components.amount;
                sum_amount_vs_avg += vector.components.amount_vs_avg;
                sum_day_of_week += vector.components.day_of_week;
                sum_hour_of_day += vector.components.hour_of_day;
                sum_installments += vector.components.installments;
                sum_km_from_home += vector.components.km_from_home;
                sum_km_from_last_tx += vector.components.km_from_last_tx;
                sum_mcc_risk += vector.components.mcc_risk;
                sum_merchant_avg_amount += vector.components.merchant_avg_amount;
                sum_minutes_since_last_tx += vector.components.minutes_since_last_tx;
                sum_tx_count_24h += vector.components.tx_count_24h;

                is_online += vector.components.is_online;
                card_present += vector.components.card_present;
                unknown_merchant += vector.components.unknown_merchant;
            }

            // The new centroid has each component as the mean of their vectors values at this component
            new_centroid.components.amount = sum_amount / cluster_size;
            new_centroid.components.amount_vs_avg = sum_amount_vs_avg / cluster_size;
            new_centroid.components.day_of_week = sum_day_of_week / cluster_size;
            new_centroid.components.hour_of_day = sum_hour_of_day / cluster_size;
            new_centroid.components.installments = sum_installments / cluster_size;
            new_centroid.components.km_from_home = sum_km_from_home / cluster_size;
            new_centroid.components.km_from_last_tx = sum_km_from_last_tx / cluster_size;
            new_centroid.components.mcc_risk = sum_mcc_risk / cluster_size;
            new_centroid.components.merchant_avg_amount = sum_merchant_avg_amount / cluster_size;
            new_centroid.components.minutes_since_last_tx = sum_minutes_since_last_tx / cluster_size;
            new_centroid.components.tx_count_24h = sum_tx_count_24h / cluster_size;

            new_centroid.components.is_online = (is_online * 2) >= cluster_size;
            new_centroid.components.card_present = (card_present * 2) >= cluster_size;
            new_centroid.components.unknown_merchant = (unknown_merchant * 2) >= cluster_size;

            if (!vector_is_equals(new_centroid, cluster.centroid))
            {
                centroid_delta[i] = euclidian_distance(cluster.centroid, new_centroid);
                cluster.centroid = new_centroid;
                *centroids[i] = new_centroid;
                converged = false;
                centroid_changed[i] = 1;
                continue;
            }
            centroid_delta[i] = 0.0f;
            centroid_changed[i] = 0;
        }
    }


    // Initializing the cluster size and the distances vector
    for (uint32_t i = 0; i < k; i++)
    {
        Cluster &cluster = clusters[i];

        uint32_t size = cluster.size;
        float max_distance = 0.0f;

        for (uint32_t j = 0; j < size; j++)
        {
            float distance = euclidian_distance(cluster.centroid, vectors[cluster.vectorsIndexes[j]]);
            cluster.vector_distances[j] = distance;
            if (distance > max_distance)
            {
                max_distance = distance;
            }
        }

        cluster.radius = max_distance;

    }



    return clusters;
}


Cluster *kmeanspp(size_t k, Vector *vectors)
{
    // Aparentemente rand() nao eh aleatorio de fato e eh limitado a 2^31 - 1. Usar lib <random> corrige isso
    std::random_device rd;
    std::mt19937_64 gen(rd());
    // Inicialmente selecionamos um vetor aleatorio
    size_t n_centroids = 0;
    auto **centroids = static_cast<Vector **>(calloc(k, sizeof(Vector *)));
    std::uniform_int_distribution<size_t> dist_index(0, NVECTORS - 1);
    size_t first_index = dist_index(gen);
    centroids[n_centroids] = &vectors[first_index];
    n_centroids += 1;

    // Selecionando o restante dos pontos
    // Changed to double to hold large unnormalized squared euclidian distances without overflow
    auto *min_dist = static_cast<double *>(calloc(NVECTORS, sizeof(double)));

    // Inicializa min_dist com a distância ao primeiro centroide
    for (size_t i = 0; i < NVECTORS; i++)
    {
        min_dist[i] = euclidian_distance(vectors[i], *centroids[0]);
    }

    while (n_centroids < k)
    {
        // Otimização: ao invés de recalcular contra todos os centroids existentes (O(n*k^2)),
        // mantemos min_dist[] persistente e apenas atualizamos com o centroide recém adicionado (O(n*k))
        Vector *last_centroid = centroids[n_centroids - 1];
        for (size_t i = 0; i < NVECTORS; i++)
        {
            double distance = euclidian_distance(vectors[i], *last_centroid);
            if (distance < min_dist[i])
            {
                min_dist[i] = distance;
            }
        }

        // Escolhendo o proximo centroide com probabilidade proporcional a D(x)^2
        double total = 0.0;
        for (size_t i = 0; i < NVECTORS; i++)
        {
            total += min_dist[i];
        }
        std::uniform_real_distribution<double> dist_prob(0.0, total);
        double threadshold = dist_prob(gen);
        double cumulative = 0.0;
        for (size_t i = 0; i < NVECTORS; i++)
        {
            cumulative += min_dist[i];
            if (cumulative >= threadshold)
            {
                centroids[n_centroids] = &vectors[i];
                n_centroids += 1;
                break;
            }
        }
    }

    free(min_dist);
    // KMEANS AQUI
    Cluster *clusters = kmeans(k, vectors, centroids);
    free(centroids);
    return clusters;
}
#endif /* KMEANSPP_H */
