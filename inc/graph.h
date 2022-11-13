#pragma once

#include "libmx.h"

typedef struct s_graph {
    int count;
    int capacity;
    char **islands;
    int **bridges;
}              t_graph;

t_graph *new_graph(int capacity);
void clear_graph(t_graph *graph);
bool is_full(t_graph *graph);
long get_sum(t_graph *graph);
int get_index(t_graph *graph, char *island);
int insert_or_find(t_graph *graph, char *island);
bool connect(t_graph *graph, int index1, int index2, int distance);
