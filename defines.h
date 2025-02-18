#ifndef DEFINES
#define DEFINES

#define CHAR_NEW_LINE            '\n'
#define CHAR_END_LINE            '\0'
#define CHAR_CARRIAGE_RETURN     '\r'
#define CHAR_MINUS               '-'
#define CHAR_SPACE               ' '
#define CHAR_A                   'A'
#define CHAR_F                   'f'
#define CHAR_Z                   'Z'
#define CHAR_ZERO                '0'
#define CHAR_ONE                 '1'
#define CHAR_TO_LOWER_DIFFERENCE ('Z' - 'z')
#define CHAR_TAB                 ((char)9)

#define STRING_ZERO          "0"
#define STRING_ONE           "1"
#define BASE_HEX             "16"
#define BASE_BIN             "2"

#define PREFIX_BIN           "0b"
#define PREFIX_HEX           "0x"
#define PREFIX_HEX_NEGATIVE  "0xf"
#define PREFIX_HEX_POSITIVE  "0x0"
#define PREFIX_SYMB_POSITION 1
#define POSITION_SIGN        2

#define SIGN_POSITIVE  127
#define SIGN_NEGATIVE -127

#define ARITHMETIC_BASE 10

#define LENGTH_SYMBOLS_HEX_ALLOWED 16

#define SYMBOLS_ALLOWED         "0123456789abcdefx!^-*/%+()"
#define SYMBOLS_OPERANDS        "!^-*/%+()_"
#define SYMBOLS_HEX_ALLOWED     "0123456789abcdef"
#define SYMBOLS_BIN_ALLOWED     "01"
#define SYMBOLS_DEC_ALLOWED     "0123456789"
#define SYMBOLS_LETTERS_ALLOWED "abcdef"
#define SYMBOLS_BRACKETS        "()"

#define OPERATOR_MINUS       '-'
#define OPERATOR_PLUS        '+'
#define OPERATOR_MOD         '%'
#define OPERATOR_DIV         '/'
#define OPERATOR_MULTIPLY    '*'
#define OPERATOR_UNARY_MINUS '_'
#define OPERATOR_POWER       '^'
#define OPERATOR_FACTORIAL   '!'

#define PRECEDENCE_MINUS -1
#define PRECEDENCE_ZERO   0
#define PRECEDENCE_ONE    1
#define PRECEDENCE_TWO    2
#define PRECEDENCE_THREE  3
#define PRECEDENCE_FOUR   4
#define PRECEDENCE_FIVE   5

#define ALLOCATE_SIZE       4096
#define DEFAULT_STRING_SIZE 100000

#define ARGUMENT_COUNT 2

#define STATUS_NOT_OK -1
#define STATUS_OK      1

#define MODE_DEC  'd'
#define MODE_BIN  'b'
#define MODE_HEX  'h'
#define MODE_QUIT 'q'

#define MENU_DEC  "dec"
#define MENU_BIN  "bin"
#define MENU_HEX  "hex"
#define MENU_OUT  "out"
#define MENU_QUIT "quit"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#endif