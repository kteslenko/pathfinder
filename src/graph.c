#include "graph.h"

t_graph *new_graph(int capacity) {
    t_graph *graph = (t_graph*)malloc(sizeof(t_graph));

    graph->count = 0;
    graph->capacity = capacity;
    graph->islands = (char**)malloc(sizeof(char*) * capacity);
    graph->bridges = (int**)malloc(sizeof(int*) * capacity);

    for (int i = 0; i < capacity; i++) {
        graph->islands[i] = NULL;
        graph->bridges[i] = (int*)malloc(sizeof(int) * capacity);
        for (int j = 0; j < capacity; j++) {
            graph->bridges[i][j] = -1;
        }
    }

    return graph;
}

void clear_graph(t_graph *graph) {
    for (int i = 0; i < graph->count; i++) {
        mx_strdel(&graph->islands[i]);
        free(graph->bridges[i]);
    }

    free(graph->islands);
    free(graph->bridges);
    free(graph);
}

bool is_full(t_graph *graph) {
    return graph->count == graph->capacity;
}

long get_sum(t_graph *graph) {
    long sum = 0;

    for (int i = 0; i < graph->count; i++) {
        for (int j = i + 1; j < graph->count; j++) {
            sum += graph->bridges[i][j];
        }
    }

    return sum;
}

int get_index(t_graph *graph, char *island) {
    for (int i = 0; i < graph->count; i++) {
        if (mx_strcmp(island, graph->islands[i]) == 0) {
            return i;
        }
    }

    return -1;
}

int insert_or_find(t_graph *graph, char *island) {
    int index = get_index(graph, island);

    if (index == -1 && !is_full(graph)) {
        graph->islands[graph->count] = mx_strdup(island);
        graph->bridges[graph->count][graph->count] = 0;
        index = graph->count;
        graph->count++;
    }

    return index;
}

bool connect(t_graph *graph, int index1, int index2, int distance) {
    if (graph->bridges[index1][index2] != -1) {
        return false;
    }

    graph->bridges[index1][index2] = distance;
    graph->bridges[index2][index1] = distance;

    return true;
}
