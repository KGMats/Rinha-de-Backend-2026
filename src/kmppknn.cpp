#include "vector.hpp"
#include "cluster.hpp"
#include "kmppknn.hpp"

#include <cfloat>
#include <iostream>

#define CALCULATE_DISTANCE euclidian_distance

/*
 * @brief binary search that returns the position where a target float should be inserted to maintain the array sorted in growing order 
 */
size_t KMPPKNN::binary_search(float* array, float target, size_t b, size_t e)
{
    while (b < e)
    {
        size_t mid = (b + e)/2;
        if (array[mid] < target)
        {
            b = mid + 1;
        }
        else{
            e = mid;
        }
    }
    return b;
}

/*
 * @brief inserts and order an primary float array and maintains the correspondness of the auxiliar arrays 
 */
void KMPPKNN::order_smallest(size_t* clusters,size_t cluster_idx,size_t* indexes,size_t index,float* array, float target, size_t b, size_t e){
        size_t idx = binary_search(array, target, b, e);
        for(size_t i = (e-1); i > idx; i--) // 0 and e-1 edge cases
        {
                array[i] = array[i-1];
                indexes[i] = indexes[i-1];
                clusters[i] = clusters[i-1];
        }
        array[idx] = target;
        indexes[idx] = index;
        clusters[idx] = cluster_idx;
}

/*
 * @brief kmknn algorithm, look at README.md for details
 *
 * returns the biggest_small_distance from the calculations
 * of the nearest cluster vectors parameter = centroid
 *
 */
float KMPPKNN::kmknn(Vector v, uint8_t k, Cluster* clusters, float distances_to_centroids[], size_t index_of_distances[], float smallest_distances[], size_t smallest_indexes[],size_t clusters_indexes[], Vector *vectors)
{
        size_t dummy_clusters[SQRT_NVECTORS] = {0};
        for(size_t i = 0; i < SQRT_NVECTORS; i++)
        {
                float cur_dist = CALCULATE_DISTANCE(clusters[i].centroid, v);
                order_smallest(dummy_clusters, 0, index_of_distances, i, distances_to_centroids, cur_dist, 0, i + 1);
        }
        Cluster c1 = clusters[index_of_distances[0]]; // get the closest one
        float biggest_small_distance = FLT_MAX; // !!!edge case get the smallest in first iteration
        uint8_t jump = 0; // at least 1, max k

        while(jump < k && jump < c1.size){
                float cur_distance=CALCULATE_DISTANCE(vectors[c1.vectorsIndexes[jump]], v);
                order_smallest(clusters_indexes, index_of_distances[0], smallest_indexes, jump, smallest_distances, cur_distance, 0, jump + 1);
                biggest_small_distance = smallest_distances[jump];
                jump++;
        };

        if(jump == k)
        {
                for(size_t j = jump; j < c1.size; j++)
                {
                        float cur_distance = CALCULATE_DISTANCE(vectors[c1.vectorsIndexes[j]], v);
                        if(cur_distance < biggest_small_distance)
                        {
                                order_smallest(clusters_indexes, index_of_distances[0], smallest_indexes, j, smallest_distances, cur_distance, 0, k);
                                biggest_small_distance = smallest_distances[k-1];
                        }
                }
        }
        return biggest_small_distance;
}

/*
 * @brief kmppknn algorithm, look at README.md for details
 *
 * returns 5 vector instances representing the five closest vectors
 * in a space T to the new/strange vector v
 */
Vector** KMPPKNN::kmppknn(Vector v, uint8_t k, Cluster* clusters, Vector* vectors)
{
        Vector** k_closest_vectors = new Vector*[k]; // return type

        float distances_to_centroids[SQRT_NVECTORS]; //float distance vlaues
        for(int i = 0; i < SQRT_NVECTORS; i++)distances_to_centroids[i] = FLT_MAX;

        size_t indexes_of_distances[SQRT_NVECTORS]; // vector index of that distance
        for(int i = 0; i < SQRT_NVECTORS; i++)indexes_of_distances[i] = 0;

        size_t clusters_indexes[k]; // cluster index of clusters arr
        for(int i = 0; i < k; i++)clusters_indexes[i] = 0;

        // k_closest_vectors dist and indexes respect.
        float smallest_distances[k];
        for(int i = 0; i < k; i++)smallest_distances[i] = FLT_MAX;
        size_t smallest_indexes[k];
        for(int i = 0; i < k; i++)smallest_indexes[i] = 0;

        // Assumindo-se c1 ja parseado e um array de cluster ordenado e tambem um array dos k-indices dos pontos mais prox:
        float dk = kmknn(v,k,clusters,distances_to_centroids,indexes_of_distances,smallest_distances,smallest_indexes,clusters_indexes, vectors);

        // itera pelos cluster restantes em ordem crescente de distancia ao novo vector v inserido no espaco
        for(size_t j = 1; j < SQRT_NVECTORS; j++)
        {
                 size_t cluster_idx = indexes_of_distances[j];
                 float distance_to_centroid = distances_to_centroids[j];

                 // se a distancia do novo vetor ao centroid desse cluster for maior q a biggest_smallest_distance,
                 // nao devemos considerar calcular os data points desse cluster, pula completamente ele
                 if ((distance_to_centroid - clusters[cluster_idx].radius) >= dk)continue;

                 for(size_t el = 0; el < clusters[cluster_idx].size; el++)
                 {
                        float cur_distance = euclidian_distance(v,vectors[clusters[cluster_idx].vectorsIndexes[el]]);
                        if(cur_distance < dk)
                        {
                                order_smallest(clusters_indexes,cluster_idx,smallest_indexes,el,smallest_distances,cur_distance,0,k);
                                dk = smallest_distances[k-1];
                        }

                }
        }
        cout << "==================== FIM DA BUSCA ====================" << endl;
        for(int i = 0; i < k; i++)
        {
            k_closest_vectors[i] = &vectors[clusters[clusters_indexes[i]].vectorsIndexes[smallest_indexes[i]]];
            print_vector(*k_closest_vectors[i]);
        }
        return k_closest_vectors;
}
