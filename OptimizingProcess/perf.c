
#include "perf.h"

uint32_t cluster_num_nodes(cluster *c) {
    return c->num_nodes;
}

uint32_t cluster_dims(cluster *c) {
    return c->dimensions;
}

int64_t get_point(cluster *c, uint32_t dim, uint32_t node, int64_t *dest) {
    if (dim < 0 || dim >= c->dimensions || node < 0 || node >= c->num_nodes)
        return 0;
    *dest = c->data[dim][node];
    return 1;
}

/* This kernel would serve as part of a k-means clustering algorithm.
 * Namely, it recalculates the center of each cluster in Euclidean space
 * YOU SHOULD NOT EDIT THIS FUNCTION. */
void naive_kmeans(cluster *clusters, uint32_t num_clusters) {
    for (int i = 0; i < num_clusters; i++) {
        // zero out center
        memset(clusters[i].center, 0, sizeof(int64_t) * clusters[i].dimensions);

        // calculate center based on current nodes
        for (int j = 0; j < cluster_num_nodes(&clusters[i]); j++) {
            for (int k = 0; k < cluster_dims(&clusters[i]); k++) {
                int64_t data_point;
                get_point(&clusters[i], k, j, &data_point);
                clusters[i].center[k] += data_point;
            }
        }
        for (int k = 0; k < clusters[i].dimensions; k++) {
            clusters[i].center[k] /= clusters[i].num_nodes;
        }
    }
}

// TODO: FILL IN THESE IMPLEMENTATIONS

void elim_loop_inefficiencies_and_reduce_calls_and_memrefs(cluster *clusters, uint32_t num_clusters) {


	for (int i = 0; i < num_clusters; i++)
	{
		memset(clusters[i].center, 0, sizeof(int64_t) * clusters[i].dimensions);

		uint32_t numnodes = clusters[i].num_nodes;
		uint32_t numdims  = clusters[i].dimensions;

		for (int j = 0; j < numdims;  j++)
		{
			int64_t data_point = 0;

			for (int k = 0; k < numnodes; k++)
			{
				data_point = data_point + clusters[i].data[j][k];
			}

			clusters[i].center[j] = (data_point / numnodes);

		}

	}
}

void modest_loop_unrolling(cluster *clusters, uint32_t num_clusters) {

	for (int i = 0; i < num_clusters; i++)
	{
		memset(clusters[i].center, 0, sizeof(int64_t) * clusters[i].dimensions);

		uint32_t numnodes = clusters[i].num_nodes;
		uint32_t numdims  = clusters[i].dimensions;
		int k;

		for (int j = 0; j < numdims; j++)
		{
			int64_t data_point = 0;

			for (k = 0; k < numnodes - 1; k = k + 2)
			{
				data_point = data_point + clusters[i].data[j][k] + clusters[i].data[j][k+1];
			}

			if (k < numnodes)
			{
				data_point = data_point + clusters[i].data[j][k];
			}

			clusters[i].center[j] = (data_point / numnodes);

		}

	}
}

void enhanced_parallelism(cluster *clusters, uint32_t num_clusters)
{

	int k;

	for (int i = 0; i < num_clusters; i++)
	{
		memset(clusters[i].center, 0, sizeof(int64_t) * clusters[i].dimensions);

		uint32_t numnodes = clusters[i].num_nodes;
		uint32_t limit = numnodes - 2;
		int64_t val = 0;
		uint32_t numdims  = clusters[i].dimensions;


		for (int j = 0; j < numdims; j++)
		{
			int64_t data_point1 = 0;
			int64_t data_point2 = 0;
			int64_t data_point3 = 0;

			for (k = 0; k < limit; k += 3)
			{
				data_point1 += clusters[i].data[j][k];
				data_point2 += clusters[i].data[j][k + 1];
				data_point3 += clusters[i].data[j][k + 2];
			}

			for (; k < numnodes; k++)
			{
				data_point1 += clusters[i].data[j][k];
			}
			val = data_point1 + data_point2 + data_point3;
			clusters[i].center[j] = val / numnodes;
		}
	}
}
