#include "path_search.h"

static t_path_node *init_nodes(t_graph *graph, int start) {
    t_path_node *nodes = (t_path_node*)malloc(sizeof(t_path_node) * graph->count);

    for (int i = 0; i < graph->count; i++) {
        nodes[i].visited = false;
        nodes[i].distance = -1;
        nodes[i].island = i;
        nodes[i].prev = NULL;
    }

    nodes[start].distance = 0;
    return nodes;
}

void clear_nodes(t_path_node *nodes, int count) {
    for (int i = 0; i < count; i++) {
        mx_clear_list(&nodes[i].prev);
    }
    free(nodes);
}

t_path_node *path_search(t_graph *graph, int start) {
    t_path_node *nodes = init_nodes(graph, start);
    int current = start;

    while (current != -1) {
        nodes[current].visited = true;

        for (int i = 0; i < graph->count; i++) {
            int bridge = graph->bridges[current][i];

            if (!nodes[i].visited && bridge != -1) {
                int distance = nodes[current].distance + bridge;

                if (nodes[i].distance == -1 || distance <= nodes[i].distance) {
                    if (distance < nodes[i].distance) {
                        mx_clear_list(&nodes[i].prev);
                    }
                    nodes[i].distance = distance;
                    mx_push_back(&nodes[i].prev, &nodes[current]);
                }
            }
        }

        current = -1;
        for (int i = 0; i < graph->count; i++) {
            if (!nodes[i].visited && nodes[i].distance != -1) {
                if (current == -1 || nodes[i].distance < nodes[current].distance) {
                    current = i;
                }
            }
        }
    }

    return nodes;
}

static bool cmp_island(void *node1, void *node2) {
    return ((t_path_node*)node1)->island > ((t_path_node*)node2)->island;
}

t_list *trace_all_paths(t_path_node *node) {
    t_list *paths = NULL;

    if (node->distance == 0) {
        return mx_create_node(mx_create_node(node));
    }

    t_list *prev = node->prev;
    mx_sort_list(prev, cmp_island);
    while (prev != NULL) {
        t_list *temp = trace_all_paths((t_path_node*)prev->data);
        t_list *current = temp;
        while (current != NULL) {
            mx_push_back((t_list**)&current->data, node);
            mx_push_back(&paths, current->data);
            current = current->next;
        }
        mx_clear_list(&temp);
        prev = prev->next;
    }

    return paths;
}
