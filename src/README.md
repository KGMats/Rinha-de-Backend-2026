# KNN aka K-Nearest Neighbors

Based on a pre defined space with data, when a new undefined data X is inserted, the KNN algorithm gets the K nearest neighbors of X and classifies it as the class with the most appearences on this limited space.

Its a lazy algorithm, because it needs to pre-compute all the data previously to its calculation, so its nos scalable, as well as, if added new dimensions (parameters of classification) the data become sparse and its eficiency is doomed.

ps: how to chose the value of K: K = sqrt(n), where n is the total number of data points such that K is a odd number to avoid draws.

## The Problem with this algorithm:

The searching process inside the space of instances T, specially with a high number D of dimensions of this space, makes so the simplicity of its implementation has some downsides in eficiency. 

To escape from this disavantage, two categories of searching were implemented:

- ANN (Approximate Nearest Neighbor), look for a faster search in exchange of result precision;
- ENN (Exact Neares Neighbor), look for a faster seach withour losing the result precision, divided into two subcategories:
	- Tree-based: construct trees in the pre-processing phase to map the space T so that it optimize the searching step. EX: KD-tree.
	- Group-based: apply grouping methods to divide the space into diferent and efficient fields.

In this implementation, we will focus on the last presented idea.

## Motivation and Problem description:

The usual KNN implementation uses the euclidian distance formula, so that, for each K, requires D subtractions, D multiplications and one square root. That being said, in a space T with N instances with D dimensions, the distance calculation between a new instance X and all the other instances of T require  a complexity of O(DN).

## k-Means algorithm:

Groups $M$ fields by, randomly defining $k$ points in $T$, called centroids, while the $k$ points dont have a shared space, for each vector in $T$, it calculates the distance (Manhattam or Euclidian) to the nearest centroid (need to store the locality in space of each centroid) and define the vector as belonging to that group. For each $M$, calculates the arithmetic average of the data and define the result as the new centroid of that field (updates the centroid value).
	- In each loop iteration (N times), its needed to calculate the distance of that point $n$ to each and every of the centroids (initially $k-centroids => O(NK)$);
	- It is needed to store the $M$ centroids position vector in disk, such that it will be used on the next phase as well (stored in order => sort this group), with its respectifully number of elements.

## The kMkNN algorithm:

This implementation's idea is to pre-process $T$ in order to optimze the searching phase, It is divided into two: phase one, or `offline` and phase two, or `online`, respectifully.

- `offline`: The k-Means algorithm divides $T$ into $M$ = $sqrt(N)$ groups;
- `online`: Uses the concept of triangular inequality for minimizing the number of euclidian distance calculations.

	if ($(d(x,cj) - rj) < dk)$ // if false, no need to caulcate the distances between X and all the instances of the group Cj
		for i in Nj
			if ($|d(x,cj) - d(yji,cj)| > dk)$ // if true, there is no need to calculate d(x,yji)	

## km++kNN algorithm

This algorithm was proposed in order to show a better centroid chosing stategy than th k-Means, used by the kMkNN algorithm.

Diferences from kMkNN:
	- Uses k-Means++ to group T fields;
	- Doesent consider d(x,yji) = dk, only smaller;
	- Dont necessarily need at least k instances from the closest group to work.

k-Means++ algorithm O(log k) $k == M$:

Diferencial: "random starting centers with very specific probabilities". While centroids_num != M:
	- Select a initial singular centroid $c1$ randomly from $T$; 
		ps: Specifically, we choose a point $p$ as a center with probability proportional to p’s contribution to the overall potential => average of all vectors  == mass center ?????
		ps: I've seen people chosing a random $t ∈ T$ as the initial cluster, should look for a better/+efficient way!
		- Choose the next center $ci$, selecting $ci ∈ T$ with probability: $\frac{D(c1)^2}{\sum_{x ∈ T} D(x)^2}$;
		ps: The further data points have a higher probability of being chosen as the next centroid;
		- Repeat this until we have chosen the total $k = M$ total centroids;

utils:
- https://youtu.be/b6uHw7QW_n4
- https://youtu.be/4HKqjENq9OU
- https://cc.unifaccamp.edu.br/Dissertacoes/RaphaelLopesSouza.pdf
- https://theory.stanford.edu/~sergei/papers/kMeansPP-soda.pdf
