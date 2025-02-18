#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "menu.h"
#include "utils.h"
#include "long_arithmetic.h"
#include "expression.h"
#include "defines.h"

void work_with_file(char **str, int* count_of_lines) {
    char mode = MODE_DEC;
    int i;

    for (i = 0; i < *count_of_lines; i++) {
        mode = menu(&mode, str[i]);
    }
}

void start_work() {
    char mode = MODE_DEC;

    while ((mode = menu(&mode, NULL)) != MODE_QUIT);
}

char menu(char* mode, char* str) {
    int success_flag;
    char return_result;
    char* input;
    
    if (!mode) {
        return MODE_QUIT;
    }

    printf("> ");
    if (str) {
        printf("%s\n", str);
    }
    
    return_result = *mode;
    if (!str) {
        input = get_input_string();
    } 
    else {
        input = str;
    }

    input = trim_string(input);

    if (!strcmp(input, MENU_DEC)) {
        puts(MENU_DEC);
        return_result = MODE_DEC;
    } else 
    if (!strcmp(input, MENU_BIN)) {
        puts(MENU_BIN);
        return_result = MODE_BIN;
    } else 
    if (!strcmp(input, MENU_HEX)) {
        puts(MENU_HEX);
        return_result = MODE_HEX;
    } else 
    if (!strcmp(input, MENU_OUT)) {
        switch (*mode) {
            case MODE_DEC: puts(MENU_DEC); break;
            case MODE_BIN: puts(MENU_BIN); break;
            case MODE_HEX: puts(MENU_HEX); break;
        }
    } else 
    if (!strcmp(input, MENU_QUIT)) {
        return_result = MODE_QUIT;
    } else 
    if (is_it_an_arithmetical_expression(input)) {
        
        success_flag = STATUS_OK;
        if (!work_with_expression(input, *mode, &success_flag)) {
            if (success_flag == STATUS_OK) {
                puts("Syntax error!");
            }
        }
    
    } else {
        puts("Invalid command \"some_missing_command\"!");
    }

    free(input);

    return return_result;
}