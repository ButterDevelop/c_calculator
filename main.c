#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"
#include "menu.h"
#include "defines.h"

int main(int argc, char *argv[]) {
    char** file_lines;
    int code, count_of_lines, i;
    
    if (argc == ARGUMENT_COUNT) {
        code = STATUS_NOT_OK;
        file_lines = read_file_by_lines(argv[1], &code, &count_of_lines);
        if (code == STATUS_NOT_OK) { 
            printf("Invalid input file!\n");
            return EXIT_FAILURE;
        }

        work_with_file(file_lines, &count_of_lines);

        for (i = 0; i < count_of_lines; i++) {
            if (!file_lines[i]) {
                free(file_lines[i]);
            }
        }

        free(file_lines);
        
        return EXIT_SUCCESS;
    }

    start_work();

    return EXIT_SUCCESS;
}