#ifndef PERF_H
#define PERF_H

/* Lab 3: Optimizing Program Performance
 * You should not edit this header
 */


#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    uint32_t num_nodes;
    uint32_t dimensions;
    int64_t **data;
    int64_t *center;
} cluster;

uint32_t cluster_num_nodes(cluster *c);

uint32_t cluster_dims(cluster *c);

int64_t get_point(cluster *c, uint32_t dim, uint32_t node, int64_t *dest);


void naive_kmeans(cluster *clusters, uint32_t num_clusters);

void elim_loop_inefficiencies_and_reduce_calls_and_memrefs(cluster *clusters, uint32_t num_clusters);

void modest_loop_unrolling(cluster *clusters, uint32_t num_clusters);

void enhanced_parallelism(cluster *clusters, uint32_t num_clusters);

#endif