#ifndef UTILS
#define UTILS

char* trim_string(char *str);

char* str_replace(char* orig, char* rep, char* with);

char* remove_leading_zeros(char* str);

char* remove_all_spaces_from_str(char* str);

char* string_to_lower(char* str);

char* get_input_string();

char** read_file_by_lines(char* file_name, int* error_code, int* count_of_lines);

void int_to_char(int value, char* str);

char* str_reverse(char* str);

int get_digits_from_int(int temp);

char* insert_substring(char* a, char* b, int position);

char* get_substring(char* string, int position, int length);

char* str_remove_substring(char *str, char* substr);

int find_char_index_in_hex_string(char c);

#endif