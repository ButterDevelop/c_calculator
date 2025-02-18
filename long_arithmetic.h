#ifndef LONG_ARITHMETIC
#define LONG_ARITHMETIC

typedef struct {
    short int sign;
    char* str_dec;
} big_int;

big_int* plus(big_int* a, big_int* b);

big_int* minus(big_int* a, big_int* b);

big_int* multiply(big_int* a, big_int* b);

big_int* divide_div(big_int* a, big_int* b);

big_int* divide_mod(big_int* a, big_int* b);

big_int* factorial(big_int* a);

big_int* power(big_int* a, big_int* b);

big_int* reverse(big_int* a);

bool is_equal_abs(big_int* a, big_int* b);

bool is_equal(big_int* a, big_int* b);

bool is_less_abs(big_int* a, big_int* b);

bool is_less(big_int* a, big_int* b);

bool is_less_fixed_length(big_int* a, big_int* b, unsigned long int len_a, unsigned long int len_b);

bool is_equal_fixed_length(big_int* a, big_int* b, unsigned long int len_a, unsigned long int len_b);

bool is_zero_fixed_length(big_int* a, unsigned long int len);

bool is_zero(big_int* a);

bool is_odd(big_int* a);

big_int* create_bigint_object(short int sign, char* str_dec);

big_int* create_bigint_copy(big_int* a);

void destroy_bigint_object(big_int *a);

#endif