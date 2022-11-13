#include "io.h"

void print_err(enum e_error error, void *data) {
    switch (error) {
        case FILE_DOES_NOT_EXIST:
            mx_printerr("error: file ");
            mx_printerr((char*)data);
            mx_printerr(" does not exist\n");
            break;
        case FILE_IS_EMPTY:
            mx_printerr("error: file ");
            mx_printerr((char*)data);
            mx_printerr(" is empty\n");
            break;
        case LINE_IS_NOT_VALID:
            {
                char *line_str = mx_itoa(*(int*)data);

                mx_printerr("error: line ");
                mx_printerr(line_str);
                mx_printerr(" is not valid\n");
                mx_strdel(&line_str);
            }
            break;
        case INVALID_NUMBER_OF_ISLANDS:
            mx_printerr("error: invalid number of islands\n");
            break;
        case DUPLICATE_BRIDGES:
            mx_printerr("error: duplicate bridges\n");
            break;
        case INVALID_BRIDGES_SUM:
            mx_printerr("error: sum of bridges lengths is too big\n");
            break;
    }
}

static void print_line(void) {
    for (int i = 0; i < 40; i++) {
        mx_printstr("=");
    }
    mx_printstr("\n");
}

static void print_route(t_graph *graph, t_list *path) {
    mx_printstr("Route: ");

    while (path != NULL) {
        t_path_node *node = (t_path_node*)path->data;

        if (node->distance != 0) {
            mx_printstr(" -> ");
        }
        mx_printstr(graph->islands[node->island]);
        path = path->next;
    }
}

static void print_distance(t_list *path) {
    mx_printstr("Distance: ");

    while (path != NULL && path->next != NULL) {
        t_path_node *node = (t_path_node*)path->data;
        t_path_node *next = (t_path_node*)path->next->data;

        if (node->distance != 0) {
            mx_printstr(" + ");
        }
        mx_printint(next->distance - node->distance);
        if (node->distance != 0 && path->next->next == NULL) {
            mx_printstr(" = ");
            mx_printint(next->distance);
        }
        path = path->next;
    }
}

static void print_path(t_graph *graph, t_list *path, int start, int end) {    
    print_line();
    mx_printstr("Path: ");
    mx_printstr(graph->islands[start]);
    mx_printstr(" -> ");
    mx_printstr(graph->islands[end]);
    mx_printstr("\n");
    print_route(graph, path);
    mx_printstr("\n");
    print_distance(path);
    mx_printstr("\n");
    print_line();
}

static void print_paths_from(t_graph *graph, int start) {
    t_path_node *nodes = path_search(graph, start);

    for (int end = start + 1; end < graph->count; end++) {
        t_list *paths = trace_all_paths(&nodes[end]);
        t_list *current_path = paths;

        while (current_path != NULL) {
            t_list *path = (t_list*)current_path->data;
            print_path(graph, path, start, end);
            mx_clear_list(&path);
            current_path = current_path->next;
        }
        mx_clear_list(&paths);
    }
    clear_nodes(nodes, graph->count);
}

void print_all_paths(t_graph *graph) {
    for (int i = 0; i < graph->count; i++) {
        print_paths_from(graph, i);
    }
}
