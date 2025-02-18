/*
* @file expression.h - header file of expression.c
* @author Maxim Lyutikov
* @version 1.0
* @date 25.12.2022
* @details connecting this file, it is important to check 
* that the header file stdbool.h is connected,
* as this file uses bool.
* @copyright © 2022 Maxim Lyutikov, All Rights Reserved.
*/
#ifndef EXPRESSION
#define EXPRESSION

/*
* @details This function checks whether the input is an arithmetical expression or not.
* @param input - char pointer ("c string") of the entry string from which the desired operation will be executed.
* @return bool - true will be returned if this char pointer is an arithmetical expression, false if not.
*/
bool is_it_an_arithmetical_expression(char* input);

/*
* @details This function will check for the correctness of the arithmetical expression record,
* specifically the correctly scaled brackets, the correctness of the numbers in binary, 
* hexadecimal and decimal numerals.
* @param input - char pointer ("c string") of arithmetical expression, 
* this parameter should be checked beforehand by is_it_an_arithmetical_expression function.
* @return bool - true will be returned if this arithmetical expression is correct, false if not.
*/
bool is_the_expression_correct(char* input);

/*
* @details This function will identify all unary minuses in the char pointer ("c string") 
* and replace them with char '_', and move them by number (or bracket expression),
* this is necessary for correct operation of the stack of operations. 
* @example '-1' will be changed on '1_'.
* @example '-(1+1)' will be changed on '(1+1)_'.  
* @param input - char pointer ("c string") of the entry string from which the desired operation will be executed.
* @return char* - char pointer ("c string") with modified unary minuses.
*/
char* replace_unary_minus(char* input);

/*
* @details This function returns a predefined operand that is passed as a function parameter.
* @param c - operand which priority the function should return.
* @return int - operand priority, which was predefined.
* Predefined priorities:
* operand '-' -> priority '1';
* operand '+' -> priority '1';
* operand '%' -> priority '2';
* operand '/' -> priority '3';
* operand '*' -> priority '3';
* operand '_' -> priority '3';
* operand '^' -> priority '4';
* operand '!' -> priotiry '4';
* other operands -> priority '-1'; - will be returned if parameter is undefined.
*/
int get_operand_priority(char c);

/*
* @details This method will clear (free) the memory of the stack passed to it like the first parameter,
* which contains pointers to big_int.
* @param number_stack - 
* @param number_stack_size - stack length.
* @return big_int** - NULL, stack will be cleared (memory free).
*/
big_int** clear_number_stack(big_int** number_stack, int number_stack_size);

/*
* @details
* @param operand_stack -
* @return char* - 
*/
char* clear_operand_stack(char* operand_stack);

/*
* @details
* @param operand_stack -
* @param operand -
* @return char* - 
*/
char* add_operand_to_stack(char* operand_stack, char operand);

/*
* @details
* @param operand_stack -
* @return char* - 
*/
char* remove_top_operand_from_stack(char* operand_stack);

/*
* @details
* @param number_stack - 
* @param number_stack_size - 
* @param operand_stack -
* @return big_int** - 
*/
big_int** proceed_stack(big_int** number_stack, int* number_stack_size, char* operand_stack, int* success_flag);

/*
* @details
* @param input - char pointer("c string") of the entry string from which the desired operation will be executed.
* @param mode -
* @return bool - 
*/
bool work_with_expression(char* input, char mode, int* success_flag);

#endif