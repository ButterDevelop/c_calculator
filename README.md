# Arbitrary Precision Integer Calculator

This project is a portable console application written in ANSI C that acts as an interpreter for arithmetic expressions with integers of unlimited size. It is designed to overcome the limitations of standard data types by implementing arbitrary precision arithmetic and working really, really fast.

## Features

- **Multi-Base Support**  
  The calculator accepts integer operands in three formats:
  - **Decimal** (no prefix)
  - **Binary** (prefix `0b`)
  - **Hexadecimal** (prefix `0x`)  
  All numbers use two's complement notation, ensuring proper handling of negative numbers and bit lengths.

- **Arithmetic Operations**  
  Supported operators include:
  - **Factorial**: `!` (highest precedence)
  - **Exponentiation**: `^`
  - **Unary Minus**: `-` (negation)
  - **Multiplication**: `*`
  - **Integer Division**: `/` (using integer division semantics)
  - **Modulo**: `%`
  - **Addition**: `+`
  - **Subtraction**: `-`  
  Parentheses `(` and `)` can be used to enforce evaluation order.

- **Input Modes**  
  - **Interactive Mode**: Run without parameters to enter expressions and commands interactively. The program continuously evaluates input until the `quit` command is entered.
  - **File Input Mode**: Provide an input file as a parameter (e.g., `calc.exe input.txt`) to evaluate expressions line-by-line. The program will output each result immediately and terminate after processing the last expression. If the file does not exist, it will display an error message and exit with a failure status.

- **Output Format Control**  
  The numeric base for output can be switched between binary, decimal, and hexadecimal via runtime commands. Results are printed using the minimal number of digits required by the two's complement representation.

## Technical Decisions

- **Arbitrary Precision Arithmetic**  
  Instead of using fixed-size types like `int` or `long int`, numbers are stored as arrays of characters. This approach allows the calculator to handle numbers limited only by the available RAM, thus ensuring support for arbitrarily large integers.

- **Conversion to Decimal**  
  Although it is easier to work with binary internally, all input numbers (including those in binary and hexadecimal formats) are converted to their decimal representation. This decision was made because the arithmetic operations (such as addition and multiplication) are implemented using column-based algorithms, similar to those taught in elementary school.

- **Two's Complement Representation**  
  Using two's complement for both binary and hexadecimal inputs simplifies the conversion process and ensures that negative numbers are handled correctly across all supported bases.

- **String-Based Computation**  
  All arithmetic operations are performed using algorithms that operate on strings. This includes handling addition, subtraction, multiplication, division, and even factorial and exponentiation, allowing the program to accurately compute results without encountering overflow issues.

## Compilation

This project is designed to be portable across different operating systems. It includes build scripts for both Linux and Windows.

- **Linux**  
  To compile on Linux, run:
  ```bash
  make
  ```

- **Windows**
  For Windows, use the provided Makefile:
  ```bash
  nmake -f Makefile.win
  ```

Ensure that your environment has a C compiler that supports ANSI C.

## Usage

### Interactive Mode

Run the executable without any parameters:
```bash
./calc.exe
```

You can then enter arithmetic expressions or interpreter commands. Type quit to exit the interactive mode.

### File Input Mode

To evaluate expressions from a file, pass the file name as an argument:

```bash
./calc.exe input.txt
```

Each expression in the file is processed sequentially, with the result printed immediately. If the file is not found, the program outputs:

```plaintext
Invalid input file!
```

and exits with a failure status.

## Project Structure

- **Source Files:** All source code files necessary for compiling the project are included.
- **Makefile / Makefile.win:** Build files for Linux and Windows, respectively.

## License

[MIT License](LICENSE)

---

*Happy C coding and using this powerful calculator!*