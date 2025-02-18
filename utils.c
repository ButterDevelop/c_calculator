#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"
#include "defines.h"

char* trim_string(char* str) {
    if (!str) {
        return NULL;
    }

    str = remove_all_spaces_from_str(str);
    str = string_to_lower(str);
    
    return str;
}

char* str_replace(char* orig, char* rep, char* with) {
    char* str;
    int rep_len, with_len, tail_len;
    
    if (!(str = strstr(orig, rep))) {
        return NULL;
    }

    rep_len = strlen(rep);
    with_len = strlen(with);
    tail_len = strlen(str + rep_len);

    memmove(str + with_len, str + rep_len, tail_len + 1);
    memcpy(str, with, with_len);

    return str;
}

char* remove_leading_zeros(char* str) {
    int non_space_count;
    unsigned long int i, index, str_len;
    
    if (!str) {
        return NULL;
    }

    str_len = strlen(str);
    index = 0;
    for (i = 0; i < str_len; i++) {
        if (str[i] == CHAR_ZERO) {
            ++index;
        } else {
            break;
        }
    }
    
    if (!index) {
        return str;
    }
    
    if (index == str_len) {
        --index;
    }

    non_space_count = 0;
    for (i = index; i < str_len; i++) {
        str[non_space_count] = str[i];
        ++non_space_count;
    }
    
    str = (char*)realloc(str, (non_space_count + 1) * sizeof(char));
    if (!str) { 
        return NULL;
    }

    str[non_space_count] = CHAR_END_LINE;

    return str;
}

char* remove_all_spaces_from_str(char* str) {
    int non_space_count, i;
    
    if (!str) {
        return NULL;
    }

    non_space_count = 0;
    for (i = 0; str[i] != CHAR_END_LINE; i++) {
        if (str[i] != CHAR_SPACE && str[i] != CHAR_TAB) {
            str[non_space_count] = str[i];
            non_space_count++;
        }    
    }
    
    str = (char*)realloc(str, (non_space_count + 1)*sizeof(char));
    str[non_space_count] = CHAR_END_LINE;

    return str;
}

char* string_to_lower(char* str) {
    int i;

    if (!str) {
        return NULL;
    } 

    for (i = 0; str[i] != CHAR_END_LINE; i++) {
        if (str[i] >= CHAR_A && str[i] <= CHAR_Z) {
            str[i] -= CHAR_TO_LOWER_DIFFERENCE;
        }    
    }

    return str;
}

char* get_input_string() {
	int current_size = DEFAULT_STRING_SIZE;
    int counter;

	char* my_str = (char*)malloc(DEFAULT_STRING_SIZE * sizeof(char));
    if (!my_str) {
        return NULL;
    }

	counter = 0;
	while ((my_str[counter++] = (char)getchar()) != CHAR_NEW_LINE) {
        if (counter < current_size) {
            my_str = (char*)realloc(my_str, current_size + DEFAULT_STRING_SIZE);
            if (!my_str) {
                free(my_str);
                return NULL;
            }

            current_size += DEFAULT_STRING_SIZE;
        }
    }

    my_str[--counter] = CHAR_END_LINE;
	my_str = (char*)realloc(my_str, counter + 1);
    if (!my_str) {
        free(my_str);
        return NULL;
    }

	return my_str;
}

char** read_file_by_lines(char* file_name, int* error_code, int* count_of_lines) {
    char **lines;
    FILE* file;
    char ch, previous_char;
    int i, current_line, counter, initialize_counter;
    
    *error_code = STATUS_NOT_OK;

    if (!file_name || !error_code) {
        return NULL;
    }

    file = fopen(file_name, "rb");
    if (!file) {
        return NULL;
    }

    *count_of_lines = 0;
    ch = 0;
    previous_char = ch;
    while (!feof(file)) {
        previous_char = ch;
        ch = fgetc(file);
        if (ch == CHAR_NEW_LINE || ch == EOF) {
            ++(*count_of_lines);
        }
    }

    
    if ((previous_char == CHAR_NEW_LINE && ch == EOF) || (!previous_char && ch == EOF)) {
        --(*count_of_lines);
    }

    fclose(file);
    if (!(*count_of_lines)) {
        return NULL;
    }

    file = fopen(file_name, "rb");

    if (!file) {
        return NULL;
    }

    lines = malloc((*count_of_lines) * sizeof(char*));
    for (i = 0; i < (*count_of_lines); i++) {
        lines[i] = malloc((DEFAULT_STRING_SIZE + 1) * sizeof(char));
    }

    current_line = 0;
    do {
        initialize_counter = -1;
        while (++initialize_counter < DEFAULT_STRING_SIZE) {
            lines[current_line][initialize_counter] = CHAR_ZERO;
        }
        lines[current_line][DEFAULT_STRING_SIZE] = CHAR_END_LINE;

        fgets(lines[current_line], DEFAULT_STRING_SIZE, file);
        
        counter = 0;
        
        while (lines[current_line][counter++] != CHAR_NEW_LINE && counter < DEFAULT_STRING_SIZE);

        if (counter > 1 && lines[current_line][counter - 2] != CHAR_CARRIAGE_RETURN) {
            ++counter;
        }

        lines[current_line] = (char*)realloc(lines[current_line], --counter);    
    
        if (!lines[current_line]) {
            for (i = 0; i < *count_of_lines; i++) {
                free(lines[i]);
            }

            free(lines);
            fclose(file);
            
            return NULL;
        }
        lines[current_line][--counter] = CHAR_END_LINE;

        ++current_line;
    } while (current_line < (*count_of_lines));

    fclose(file);

    *error_code = STATUS_OK;
    
    return lines;
}

void int_to_char(int value, char* str) {
    if (!str) {
        return;
    }

    sprintf(str, "%d", value);
}

char* str_reverse(char* str) {
    int len, i, left, right;

    if (!str) {
        return NULL;
    }

    len = strlen(str), left = 0, right = len - 1;
    for (i = left; i < right; i++) {
        char temp = str[i];
        str[i] = str[right];
        str[right] = temp;
        right--;
    }

    return str;
}

int get_digits_from_int(int temp) {
    int counter;

    if (!temp) {
        return 1;
    }

    counter = 0;
    while (temp) {
        temp /= 10;
        ++counter;
    }
    
    return counter;
}

char* insert_substring(char* a, char* b, int position) {
    int length = strlen(a);
    char *f, *e;
    
    f = get_substring(a, 1, position - 1);      
    e = get_substring(a, position, length - position + 1);
 
    strcpy(a, "");
    strcat(a, f);
    free(f);
    strcat(a, b);
    strcat(a, e);
    free(e);
 
    return a;
}

char* get_substring(char* string, int position, int length) {
    char* pointer = (char*)malloc((length + 1) * sizeof(char));
    int i;
   
    if (!pointer) {
        return NULL;
    }
 
    for (i = 0; i < length; i++) {
        pointer[i] = *((string+position-1) + i);
    }
    
    pointer[i] = CHAR_END_LINE;
 
    return pointer;
}

char* str_remove_substring(char *str, char* substr) {
    char *p, *q, *r;
    int len;

    if (*substr && (q = r = strstr(str, substr)) != NULL) {
        len = strlen(substr);
        while ((r = strstr(p = r + len, substr)) != NULL) {
            memmove(q, p, r - p);
            q += r - p;
        }
        memmove(q, p, strlen(p) + 1);
    }
    
    return str;
}

int find_char_index_in_hex_string(char c) {
    int i;

    for (i = 0; i < LENGTH_SYMBOLS_HEX_ALLOWED; i++) {
        if (SYMBOLS_HEX_ALLOWED[i] == c) {
            return i;
        }
    }

    return STATUS_NOT_OK;
}