#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "long_arithmetic.h"
#include "defines.h"
#include "utils.h"

big_int* bin_to_big(char* number) {
    char *zero_str, *two_str, *power_result_str;
    big_int *big_number, *two_object, *power_result, *big_number_copy, 
            *power_result_copy;
    int i;
    unsigned long int number_len;

    if (!number) {
        return NULL;
    }

    number_len = strlen(number);

    zero_str = (char*)malloc(2 * sizeof(char));
    if (!zero_str) {
        return NULL;
    }

    two_str = (char*)malloc(2 * sizeof(char));
    if (!two_str) {
        free(zero_str);
        return NULL;
    }

    power_result_str = (char*)malloc(2 * sizeof(char));
    if (!power_result_str) {
        free(zero_str);
        free(two_str);
        return NULL;
    }
    
    strcpy(zero_str, STRING_ZERO);
    strcpy(two_str, BASE_BIN);
    strcpy(power_result_str, STRING_ONE);
    
    big_number = create_bigint_object(SIGN_POSITIVE, zero_str);
    two_object = create_bigint_object(SIGN_POSITIVE, two_str);
    power_result = create_bigint_object(POSITION_SIGN, power_result_str);

    for (i = number_len - 1; i > POSITION_SIGN; i--) {
        if (number[i] != CHAR_ZERO) {
            big_number_copy = plus(big_number, power_result);
            destroy_bigint_object(big_number);
            big_number = create_bigint_copy(big_number_copy);
            destroy_bigint_object(big_number_copy);
        }

        power_result_copy = plus(power_result, power_result);
        destroy_bigint_object(power_result);
        power_result = create_bigint_copy(power_result_copy);
        destroy_bigint_object(power_result_copy);
    }

    if (POSITION_SIGN == number_len - 1 && number[POSITION_SIGN] == CHAR_ONE) {
        big_number_copy = minus(big_number, power_result);
        destroy_bigint_object(big_number);
        big_number = create_bigint_copy(big_number_copy);
        destroy_bigint_object(big_number_copy); 
    } else 
    if (number[POSITION_SIGN] == CHAR_ONE) {
        big_number_copy = minus(big_number, power_result);
        destroy_bigint_object(big_number);
        big_number = create_bigint_copy(big_number_copy);
        destroy_bigint_object(big_number_copy);
    }

    destroy_bigint_object(power_result);
    destroy_bigint_object(two_object);

    return big_number;
}

big_int* hex_to_big(char* number) {
    char *sixteen_str, *zero_str, *one_str;
    big_int *sixteen_object, *big_number, *current_power, *big_result_digit, 
             *big_number_copy, *current_power_copy, *big_result_digit_copy;
    unsigned long int i, j, result_digit; 
    
    if (!number) {
        return NULL;
    }

    sixteen_str = (char*)malloc(3 * sizeof(char));
    if (!sixteen_str) {
        return NULL;
    }
    
    strcpy(sixteen_str, BASE_HEX);
    sixteen_object = create_bigint_object(SIGN_POSITIVE, sixteen_str);

    zero_str = (char*)malloc(2 * sizeof(char));
    if (!zero_str) {
        destroy_bigint_object(sixteen_object);
        return NULL;
    }
    
    strcpy(zero_str, STRING_ZERO);
    big_number = create_bigint_object(SIGN_POSITIVE, zero_str);

    one_str = (char*)malloc(2 * sizeof(char));
    if (!one_str) {
        destroy_bigint_object(sixteen_object);
        destroy_bigint_object(big_number);
        return NULL;
    }
    
    strcpy(one_str, STRING_ONE);
    current_power = create_bigint_object(SIGN_POSITIVE, one_str);

    for (i = strlen(number) - 1; i > POSITION_SIGN; i--) {
        result_digit = 0;
        for (j = 0; j < LENGTH_SYMBOLS_HEX_ALLOWED; j++) {
            if (number[i] == SYMBOLS_HEX_ALLOWED[j]) {
                result_digit = j;
                break;
            }
        }

        /*
        * We need to assign zero to this variable.
        * The most quickest decision is to use 'minus' function with one variable
        * (and this variable has short length as a perfect case).
        */
        big_result_digit = minus(sixteen_object, sixteen_object);
        for (j = 0; j < result_digit; j++) {
            big_result_digit_copy = plus(big_result_digit, current_power);
            destroy_bigint_object(big_result_digit);
            big_result_digit = create_bigint_copy(big_result_digit_copy);
            destroy_bigint_object(big_result_digit_copy);
        }

        big_number_copy = plus(big_number, big_result_digit);
        destroy_bigint_object(big_number);
        big_number = create_bigint_copy(big_number_copy);
        destroy_bigint_object(big_number_copy);

        destroy_bigint_object(big_result_digit);

        for (j = 0; j < 4; j++) {
            current_power_copy = plus(current_power, current_power);
            destroy_bigint_object(current_power);
            current_power = create_bigint_copy(current_power_copy);
            destroy_bigint_object(current_power_copy);
        }
    }

    if (number[POSITION_SIGN] != CHAR_ZERO) {
        big_number_copy = minus(big_number, current_power);
        destroy_bigint_object(big_number);
        big_number = create_bigint_copy(big_number_copy);
        destroy_bigint_object(big_number_copy);
    }

    destroy_bigint_object(sixteen_object);
    destroy_bigint_object(current_power);

    return big_number;
}

char* big_to_bin(big_int* a) {
    char res_char;
    char *result_str, *one_str, *temp;
    big_int *big_number, *abs_number, *current_power, *current_power_copy, *big_number_copy;
    big_int **powers;
    int len;
    unsigned long int power_number, size, real_size, i, number_power_len;

    if (!a) {
        return NULL;
    }

    result_str = (char*)malloc(4 * sizeof(char));
    if (!result_str) { 
        return NULL;
    }

    power_number = 1;

    if (a->sign == SIGN_POSITIVE) {
        strcpy(result_str, "0b0");
        big_number = create_bigint_copy(a);
    } else {
        strcpy(result_str, "0b1");
        
        abs_number = create_bigint_copy(a);
        abs_number->sign = SIGN_POSITIVE;

        one_str = (char*)malloc(2 * sizeof(char));
        if (!one_str) {
            free(result_str);
            destroy_bigint_object(abs_number);
            return NULL;
        }
        strcpy(one_str, STRING_ONE);
        current_power = create_bigint_object(SIGN_POSITIVE, one_str);

        number_power_len = strlen(abs_number->str_dec);
        while (is_less_fixed_length(current_power, abs_number, strlen(current_power->str_dec), number_power_len)) {
            ++power_number;

            current_power_copy = plus(current_power, current_power);
            destroy_bigint_object(current_power);
            current_power = create_bigint_copy(current_power_copy);
            destroy_bigint_object(current_power_copy);
        }

        big_number = minus(current_power, abs_number);

        destroy_bigint_object(abs_number);
        destroy_bigint_object(current_power);
    }

    one_str = (char*)malloc(2 * sizeof(char));
    if (!one_str) {
        free(result_str);
        destroy_bigint_object(big_number);
        return NULL;
    }
    strcpy(one_str, STRING_ONE);
    current_power = create_bigint_object(SIGN_POSITIVE, one_str);

    real_size = ALLOCATE_SIZE;
    size = 0;
    powers = (big_int**)malloc(real_size * sizeof(big_int*));
    if (!powers) {
        free(result_str);
        destroy_bigint_object(big_number);
        destroy_bigint_object(current_power);
        return NULL;
    }

    number_power_len = strlen(big_number->str_dec);
    while (!is_less_fixed_length(big_number, current_power, number_power_len, strlen(current_power->str_dec))) {
        ++size;
        if (size > real_size) {
            real_size += ALLOCATE_SIZE;
            powers = (big_int**)realloc(powers, real_size * sizeof(big_int*));
            if (!powers) {
                free(result_str);
                destroy_bigint_object(big_number);
                destroy_bigint_object(current_power);
                return NULL;
            }
        }
        powers[size - 1] = create_bigint_copy(current_power);

        current_power_copy = plus(current_power, current_power);
        destroy_bigint_object(current_power);
        current_power = create_bigint_copy(current_power_copy);
        destroy_bigint_object(current_power_copy);
    }

    /*
    * We know size of the result string, because we have already found the neccessary amount of powers
    */
    result_str = (char*)realloc(result_str, (a->sign == SIGN_NEGATIVE ? power_number : size) + strlen(result_str) + 1);
    if (!result_str) {
        destroy_bigint_object(big_number);
        destroy_bigint_object(current_power);
        for (i = 0; i < size; i++) {
            destroy_bigint_object(powers[i]);
        }
        free(powers);
        return NULL;
    }

    for (i = size; i > 0; i--) {
        res_char = CHAR_ZERO;
        if (!is_less(big_number, powers[i - 1])) { 
            big_number_copy = minus(big_number, powers[i - 1]);
            destroy_bigint_object(big_number);
            big_number = create_bigint_copy(big_number_copy);
            destroy_bigint_object(big_number_copy);

            res_char = CHAR_ONE;
        }

        len = strlen(result_str) + 2;
        result_str[len - 2] = res_char;
        result_str[len - 1] = CHAR_END_LINE;
    }

    destroy_bigint_object(current_power);
    destroy_bigint_object(big_number);
    for (i = 0; i < size; i++) {
        destroy_bigint_object(powers[i]);
    }
    free(powers);

    if (a->sign == SIGN_NEGATIVE) {
        temp = (char*)malloc(2 * sizeof(char));
		strcpy(temp, STRING_ZERO);
        while (strlen(result_str) - 2 < power_number) {    
            result_str = insert_substring(result_str, temp, 4);
        }
        free(temp);
    }

    return result_str;
}

char* big_to_hex(big_int* a) {
    char *result_str, *sixteen_str, *one_str, *temp;
    big_int *big_number, *sixteen_object, *abs_number, *current_power,
            *current_power_copy, *big_number_copy;
    big_int **powers, **sums;
    int size, i, result_digit, len, sixteen_plus_counter;
    unsigned long int power_number, j;
    
    if (!a) {
        return NULL;
    }

    result_str = (char*)malloc(4 * sizeof(char));
    if (!result_str) { 
        return NULL;
    }

    power_number = 1;

    sixteen_str = (char*)malloc(3 * sizeof(char));
    if (!sixteen_str) {
        free(result_str);
        return NULL;
    }
    strcpy(sixteen_str, BASE_HEX);
    sixteen_object = create_bigint_object(SIGN_POSITIVE, sixteen_str);

    if (a->sign == SIGN_POSITIVE) {
        strcpy(result_str, PREFIX_HEX_POSITIVE);
        big_number = create_bigint_copy(a);
    } else {
        strcpy(result_str, PREFIX_HEX_NEGATIVE);
        
        abs_number = create_bigint_copy(a);
        abs_number->sign = SIGN_POSITIVE;

        one_str = (char*)malloc(2 * sizeof(char));
        if (!one_str) {
            free(result_str);
            destroy_bigint_object(sixteen_object);
            destroy_bigint_object(abs_number);
            return NULL;
        }
        strcpy(one_str, STRING_ONE);
        current_power = create_bigint_object(SIGN_POSITIVE, one_str);

        while (is_less(current_power, abs_number)) {
            ++power_number;

            for (sixteen_plus_counter = 0; sixteen_plus_counter < 4; sixteen_plus_counter++) {
                current_power_copy = plus(current_power, current_power);
                destroy_bigint_object(current_power);
                current_power = create_bigint_copy(current_power_copy);
                destroy_bigint_object(current_power_copy);
            }
        }

        big_number = minus(current_power, abs_number);

        destroy_bigint_object(abs_number);
        destroy_bigint_object(current_power);
    }

    one_str = (char*)malloc(2 * sizeof(char));
    if (!one_str) {
        free(result_str);
        destroy_bigint_object(sixteen_object);
        destroy_bigint_object(big_number);
        return NULL;
    }
    strcpy(one_str, STRING_ONE);
    current_power = create_bigint_object(SIGN_POSITIVE, one_str);

    size = 0;
    powers = (big_int**)malloc(size * sizeof(big_int*));

    while (!is_less(big_number, current_power)) {
        ++size;
        powers = (big_int**)realloc(powers, size * sizeof(big_int*));
        powers[size - 1] = create_bigint_copy(current_power);

        for (sixteen_plus_counter = 0; sixteen_plus_counter < 4; sixteen_plus_counter++) {
            current_power_copy = plus(current_power, current_power);
            destroy_bigint_object(current_power);
            current_power = create_bigint_copy(current_power_copy);
            destroy_bigint_object(current_power_copy);
        }
    }

    /*
    * We know size of the result string, because we have already found the neccessary amount of powers
    */
    result_str = (char*)realloc(result_str, size + strlen(result_str) + 1);
    if (!result_str) {
        destroy_bigint_object(big_number);
        destroy_bigint_object(current_power);
        destroy_bigint_object(sixteen_object);
        for (i = 0; i < size; i++) {
            destroy_bigint_object(powers[i]);
        }
        free(powers);
        return NULL;
    }

    len = strlen(result_str);
    for (i = size - 1; i >= 0; i--) {
        sums = (big_int**)malloc(16 * sizeof(big_int*));
        sums[0] = minus(sixteen_object, sixteen_object);

        for (result_digit = 1; result_digit < 16; result_digit++) {
            sums[result_digit] = plus(sums[result_digit - 1], powers[i]);
        }

        for (result_digit = 15; result_digit >= 0; result_digit--) {
            if (!is_less(big_number, sums[result_digit])) {
                break;
            }
        }

        big_number_copy = minus(big_number, sums[result_digit]);
        destroy_bigint_object(big_number);
        big_number = create_bigint_copy(big_number_copy);
        destroy_bigint_object(big_number_copy);

        len = strlen(result_str) + 2;
        result_str[len - 2] = SYMBOLS_HEX_ALLOWED[result_digit];
        result_str[len - 1] = CHAR_END_LINE;

        for (result_digit = 0; result_digit < 16; result_digit++) {
            destroy_bigint_object(sums[result_digit]);
        }
        free(sums);
    }

    destroy_bigint_object(sixteen_object);
    destroy_bigint_object(current_power);
    destroy_bigint_object(big_number);
    for (i = 0; i < size; i++) {
        destroy_bigint_object(powers[i]);
    }
    free(powers);

    if (a->sign == SIGN_NEGATIVE) {
        while (strlen(result_str) - 2 < power_number) {
            temp = (char*)malloc(2 * sizeof(char));
            if (!temp) {
                free(result_str);
                return NULL;
            }
			strcpy(temp, STRING_ZERO);
            result_str = insert_substring(result_str, temp, 4);
            free(temp);
        }
    }

    if (strlen(result_str) - 1 > POSITION_SIGN && 
       ((result_str[POSITION_SIGN] == CHAR_ZERO && find_char_index_in_hex_string(result_str[POSITION_SIGN + 1]) < 8) || 
        (result_str[POSITION_SIGN] == CHAR_F && find_char_index_in_hex_string(result_str[POSITION_SIGN + 1]) >= 8))) { /* <8, because of carry bit, which will define number as negative if char < 8 */
        len = strlen(result_str);
        for (j = POSITION_SIGN; j < strlen(result_str); j++) {
            result_str[j] = result_str[j + 1];
        }
        result_str = (char*)realloc(result_str, len);
        if (!result_str) {
            return NULL;
        }
    }

    return result_str;
}

char* bin_to_hex(char* number) {
    char *result_str, *temp, *number_copy;
    int result_digit;
    unsigned long int i, result_len, number_len, additional_count;

    if (!number) {
        return NULL;
    }

    number_len = strlen(number);

    number_copy = (char*)malloc((number_len + 1) * sizeof(char));
    if (!number_copy) {
        return NULL;
    }
    strcpy(number_copy, number);

    additional_count = ((number_len - 2) / 4) - !((number_len - 2) % 4) + 1;
    result_str = (char*)malloc((additional_count + 4) * sizeof(char));
    if (!result_str) {
        free(number_copy);
        return NULL;
    }

    if (number[POSITION_SIGN] == CHAR_ZERO) {
        strcpy(result_str, PREFIX_HEX_POSITIVE);
    } else {
        strcpy(result_str, PREFIX_HEX_NEGATIVE);
    }

    additional_count = !((number_len - 2) % 4) ? 0 : (4 - ((number_len - 2) % 4));
    number_copy = (char*)realloc(number_copy, (additional_count + strlen(number_copy) + 1) * sizeof(char));
    if (!number_copy) {
        free(result_str);
        return NULL;
    }
    temp = (char*)malloc(2 * sizeof(char));
    if (!temp) {
        free(result_str);
        free(number_copy);
        return NULL;
    }
    for (i = 0; i < additional_count; i++) {
        
        if (number[POSITION_SIGN] == CHAR_ONE) {
		    strcpy(temp, STRING_ONE);
        } else {
            strcpy(temp, STRING_ZERO);
        }
        
        number_copy = insert_substring(number_copy, temp, 3);
    }
    free(temp);

    for (i = POSITION_SIGN; i < strlen(number_copy); i += 4) {
        result_digit = 0;
        if (number_copy[i] == CHAR_ONE) {
            result_digit += 8;
        }
        if (number_copy[i + 1] == CHAR_ONE) {
            result_digit += 4;
        }
        if (number_copy[i + 2] == CHAR_ONE) {
            result_digit += 2;
        }
        if (number_copy[i + 3] == CHAR_ONE) {
            result_digit += 1;
        }

        result_len = strlen(result_str) + 2;
        result_str[result_len - 2] = SYMBOLS_HEX_ALLOWED[result_digit];
        result_str[result_len - 1] = CHAR_END_LINE;
    }

    if (strlen(result_str) - 1 > POSITION_SIGN && 
       ((result_str[POSITION_SIGN] == CHAR_ZERO && find_char_index_in_hex_string(result_str[POSITION_SIGN + 1]) < 8) || 
        (result_str[POSITION_SIGN] == CHAR_F && find_char_index_in_hex_string(result_str[POSITION_SIGN + 1]) >= 8))) { /* <8, because of carry bit, which will define number as negative if char < 8 */
        result_len = strlen(result_str);
        for (i = POSITION_SIGN; i < strlen(result_str); i++) {
            result_str[i] = result_str[i + 1];
        }
        
        result_str = (char*)realloc(result_str, result_len);
        if (!result_str) {
            free(result_str);
            free(number_copy);
            return NULL;
        }
    }

    free(number_copy);
    return result_str;
}

char* to_string(big_int* a, char mode) {
    char *result_str, *temp_bin, *temp_hex;
    int len;

    if (!a || !mode) {
        return NULL;
    }

    if (mode == MODE_DEC) {
        len = strlen(a->str_dec) + 1;
        if (a->sign == SIGN_NEGATIVE && !is_zero(a)) {
            ++len;
        }
        result_str = (char*)malloc(len * sizeof(char));
		strcpy(result_str, "");

        if (a->sign == SIGN_NEGATIVE && !is_zero(a)) {
            strcat(result_str, "-");
        }
        strcat(result_str, a->str_dec);

        return result_str;
    } 
    if (mode == MODE_BIN) {
        return big_to_bin(a);
    } 
    if (mode == MODE_HEX) {
        temp_bin = big_to_bin(a);
        temp_hex = bin_to_hex(temp_bin);

        free(temp_bin);
        return temp_hex;
    } 

    return NULL;
}
