#pragma once

#include "limits.h"
#include "graph.h"

enum e_error {
    FILE_DOES_NOT_EXIST,
    FILE_IS_EMPTY,
    LINE_IS_NOT_VALID,
    INVALID_NUMBER_OF_ISLANDS,
    DUPLICATE_BRIDGES,
    INVALID_BRIDGES_SUM,
};

void print_err(enum e_error, void *data);
bool file_exists(const char *name);
bool file_empty(const char *name);
t_graph *parse_file(int fd);
