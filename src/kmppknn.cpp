#include "cluster.hpp"
#include "vector.hpp"
#include "kmknn.hpp"

Vector** kmppknn(Vector v, uint8_t k, Cluster* clusters){
  	/*	
	 * Assumindo-se c1 ja parseado e um array de cluster ordenado,
	 * e tambem um array dos k-indices dos pontos mais prox:
	 *
	 * ps1: cj is the centroid of the j'th cluster Cj
	 * ps2: dk = biggest_small_distance do nosso code
	 *
	 * distance_to_centroid = euclidian_distance(v, cj);
	 *
	 * if distance_to_centroid - Cj.radius (private) >= dk
	 * 	skip this cluster and goto next one
	 *
	 * for(size_t el = 0; el < SQRT_NVECTORS; el++){
	 * 	
	 * 	if(abs(distance_to_centroid - euclidian_distance(Cj.vectorsIndexes[el],cj)) > dk:
	 * 		skip this vector (data point) continue;
	 *
	 * 	else{
	 *		float cur_distance = euclidian_distance(v,Cj.vectorsIndexes[el]);
	 *		if(cur_distance < dk){
				order_smallest(smallest_indexes,el,smallest_distances,cur_distance);
	 *			biggest_small_distance = smallest_distances[4];
	 *		}
	 * 	}
	 * }
	 *
	 * PS: IT WOULD BE AWESOME IF WE COULD HAVE ALL THE DISTANCES
	 * FROM EACH AND EVERY OF THE DATA POINTS (VECTORS) OF A 
	 * CLUSTER TO ITS CENTROID PRE-CALCULATED SO THAT 
	 * LINE 18 GETS DONE INSTA
	 *
	 * idea: Cluster instance holds a array of pre-calculated distances acessed by the same index as Cluster.vectosIndexes
	 *
	 * 			OR
	 *
	 * second idea: we hold onto a struct:
	 *
	 * struct idea2{
	 * 	Vector* v;
	 * 	float distance_to_centroid;
	 * }
	 *
	 * and have an array of type: idea2 array[] to hold onto
	 * both this information at the same time!!!
	 *
	 */
}
