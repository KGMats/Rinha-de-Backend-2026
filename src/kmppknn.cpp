#include "vector.hpp"
#include "cluster.hpp"
#include "kmknn.hpp"

#include <cfloat>
#include <iostream>

#define CALCULATE_DISTANCE euclidian_distance

/*
 * @brief basic binary search with varible type definition on array
 */


size_t KMKNN::binary_search(float* array, float target, uint8_t b, uint8_t e)
{
    while (b <= e)
    {
        uint8_t mid = b + (e - b) / 2;
        if (array[mid] == target)
            return mid;
        else if (array[mid] < target)
        {
            b = mid + 1;
        }
        else{
            e = mid - 1;
        }
    }

    return 0;
}

/*
 * @brief inserts and order a small array of varible type
 */
void KMKNN::order_smallest(size_t* indexes,size_t index,float* array, float target){
	size_t idx = binary_search(array, target, 0, 5);
	if(idx==4)
	{
		array[4] = target;
		indexes[4] = index;
	}
	else
	{
		for(size_t i = 4; i > idx; i--)
		{
			array[i] = array[i-1];
			indexes[i] = indexes[i-1];
		}
		array[idx] = target;
		indexes[idx] = index;
	}
}

/*
 * @brief kmknn algorithm, look at README.md for details
 */
Vector** KMKNN::kmppknn(Vector v, uint8_t k, Cluster* clusters, Vector* vectors){
	Vector** k_closest_vectors = new Vector*[k];
	uint8_t kcvindex = 0;

	// lista de tamanho SQRT_NVECTORS para armazenar distXcentroid
	float distances_to_centroids[SQRT_NVECTORS];	
	float smallest_distance = FLT_MAX; uint16_t index = 0;

	for(int i = 0; i < SQRT_NVECTORS; i++)
	{
		distances_to_centroids[i] = CALCULATE_DISTANCE(clusters[i].centroid, v);	
		// guarda o valor da menor distancia => indice = cluster que contem essa menor distancia
		if(distances_to_centroids[i] < smallest_distance)
		{ 
			smallest_distance = distances_to_centroids[i]; 
			index = i;
	       	}
	}
	
	Cluster& c1 = clusters[index]; // get the closest one
	size_t smallest_indexes[k] = {};
	float smallest_distances[k] = {FLT_MAX, FLT_MAX, FLT_MAX, FLT_MAX, FLT_MAX};
	float biggest_small_distance = FLT_MAX; // edge case get the smallest in first iteration
	uint8_t jump = 0; // at least 1, max 5

	do{
		float cur_distance=CALCULATE_DISTANCE(vectors[c1.vectorsIndexes[jump]], v);
		order_smallest(smallest_indexes,jump,smallest_distances,cur_distance);
		biggest_small_distance = smallest_distances[4];
		jump++;
	}while(jump < 5 && jump < c1.size);

	// if jump == even (par) can draw!
	if(jump < 5){
		while(jump != 0)
		{
			k_closest_vectors[kcvindex] = &vectors[c1.vectorsIndexes[smallest_indexes[kcvindex]]];
			kcvindex++; jump--;
		}
		return k_closest_vectors;
	}	
	else
	{
		for(size_t j = jump; j < c1.size; j++)
		{
			float cur_distance = CALCULATE_DISTANCE(vectors[c1.vectorsIndexes[j]], v);
			if(cur_distance < biggest_small_distance)
			{
				order_smallest(smallest_indexes,j,smallest_distances,cur_distance);
				biggest_small_distance = smallest_distances[4];
			}
		}
		for(uint8_t h = 0; h < 5; h++)
		{
			k_closest_vectors[kcvindex] = &vectors[c1.vectorsIndexes[smallest_indexes[kcvindex]]];
			kcvindex++;
		}
		return k_closest_vectors;
	}
}
