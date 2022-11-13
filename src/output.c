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
