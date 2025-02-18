/*
* @file converter.h - header file of converter.c
* @author Maxim Lyutikov
* @version 1.0
* @date 25.12.2022
* @details connecting this file, it is important to check 
* that the header file long_arithmetic.h is connected,
* as this file uses big_int structure.
* @copyright © 2022 Maxim Lyutikov, All Rights Reserved.
*/
#ifndef CONVERTER
#define CONVERTER

/*
* @details This function will convert char pointer of binary number to big_int pointer
* of sign decimal number.
* @param number - char pointer - number in binary format (the number must be verified
* to match the binary format with the third-party function).
* @return big_int* - pointer to big_int structure which represents sign decimal integer.
*/
big_int* bin_to_big(char* number);

/*
* @details This function will convert char pointer of hexadecimal number to big_int pointer
* of sign decimal number.
* @param number - char pointer - number in hexadecimal format (the number must be verified
* to match the hexadecimal format with the third-party function).
* @return big_int* - pointer to big_int structure which represents sign decimal integer.
*/
big_int* hex_to_big(char* number);

/*
* @details This function will convert big_int pointer of sign decimal number
* to char pointer of binary number 
* @param a - pointer to big_int structure which represents sign decimal integer. 
* @return char* - number in binary format.
*/
char* big_to_bin(big_int* a);

/*
* @details This function will convert big_int pointer of sign decimal number
* to char pointer of hexadecimal number 
* @param a - pointer to big_int structure which represents sign decimal integer. 
* @return char* - number in hexadecimal format.
*/
char* big_to_hex(big_int* a);

char* bin_to_hex(char* number);

/*
* @details This function prepares big_int for display in the specified format.
* @param a - pointer to big_int structure which represents sign decimal integer.
* @param mode - variable that indicates in which format the number will be prepared for displaying.
* Predefined modes:
*   MODE_DEC  -> char 'd'
*   MODE_BIN  -> char 'b'
*   MODE_HEX  -> char 'h'
*   MODE_QUIT -> char 'q'
* in other cases error will occured.
* @return char* - prepared number for displaying.
*/
char* to_string(big_int* a, char mode);

#endif