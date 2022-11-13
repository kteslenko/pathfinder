#pragma once

#include "graph.h"

typedef struct s_path_node {
    bool visited;
    int distance;
    int island;
    t_list *prev;
}              t_path_node;

t_path_node *path_search(t_graph *graph, int start);
t_list *trace_path(t_path_node *nodes, int end);
t_list *trace_all_paths(t_path_node *node);
