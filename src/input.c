#include "io.h"

bool file_exists(const char *name) {
    int fd = open(name, O_RDONLY);

    if (fd == -1) {
        return false;
    }

    close(fd);
    return true;
}

bool file_empty(const char *name) {
    int fd = open(name, O_RDONLY);

    if (fd == -1) {
        return false;
    }

    char buf;
    int bytes_read = read(fd, &buf, 1);

    close(fd);
    return bytes_read == 0;
}

int parse_count(int fd) {
    int count = 0;
    char *line = NULL;
    int result = mx_read_line(&line, 1, '\n', fd);

    if (result < 0) {
        return -1;
    }
    mx_atoi(line, &count);
    mx_strdel(&line);
    return count;
}

bool validate_island(const char *island) {
    if (mx_strlen(island) == 0) {
        return false;
    }

    for (int i = 0; i < mx_strlen(island); i++) {
        if (!mx_isalpha(island[i])) {
            return false;
        }
    }

    return true;
}

int parse_line(int fd, char **island1, char **island2, int *distance) {
    char *distance_str = NULL;
    int result = mx_read_line(island1, 1, '-', fd);

    if (result < 0) {
        return 0;
    }

    result = mx_read_line(island2, 1, ',', fd);
    if (result < 0) {
        mx_strdel(island1);
        return -1;
    }

    result = mx_read_line(&distance_str, 1, '\n', fd);
    if (result < 0) {
        mx_strdel(island1);
        mx_strdel(island2);
        return -1;
    }
    mx_atoi(distance_str, distance);
    mx_strdel(&distance_str);

    if (!validate_island(*island1)
        || !validate_island(*island2)
        || mx_strcmp(*island1, *island2) == 0
        || *distance <= 0) {
        mx_strdel(island1);
        mx_strdel(island2);
        return -1;
    }

    return 1;
}

int insert_line(char *island1, char *island2, int distance, t_graph *graph) {
    int index1 = insert_or_find(graph, island1);
    int index2 = insert_or_find(graph, island2);

    if (index1 == -1 || index2 == -1) {
        print_err(INVALID_NUMBER_OF_ISLANDS, NULL);
        return -1;
    }

    if (!connect(graph, index1, index2, distance)) {
        print_err(DUPLICATE_BRIDGES, NULL);
        return -1;
    }

    return 0;
}

t_graph *parse_file(int fd) {
    int result = 0;
    int count = parse_count(fd);
    t_graph *graph = NULL;

    if (count <= 0) {
        int line = 1;

        print_err(LINE_IS_NOT_VALID, &line);
        return NULL;
    }

    graph = new_graph(count);
    
    for (int i = 2;; i++) {
        char *island1 = NULL;
        char *island2 = NULL;
        int distance = 0;

        result = parse_line(fd, &island1, &island2, &distance);
        if (result <= 0) {
            if (result < 0) {
                print_err(LINE_IS_NOT_VALID, &i);
            }
            break;
        }

        result = insert_line(island1, island2, distance, graph);
        mx_strdel(&island1);
        mx_strdel(&island2);
        if (result < 0) {
            break;
        }
    }

    if (result == 0 && !is_full(graph)) {
        print_err(INVALID_NUMBER_OF_ISLANDS, NULL);
        result = -1;
    }
    if (result == 0 && get_sum(graph) > INT_MAX) {
        print_err(INVALID_BRIDGES_SUM, NULL);
        result = -1;
    }

    if (result < 0) {
        clear_graph(graph);
        graph = NULL;
    }

    return graph;
}
