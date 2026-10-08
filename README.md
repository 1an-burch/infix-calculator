# Infix Calculator

A command-line calculator that parses standard infix math expressions (e.g. `3 + 4 * ( 2 - 1 )`), converts them to postfix (Reverse Polish) notation using the Shunting Yard algorithm, and evaluates the result.

```
Infix Calculator
Enter an expression with spaces between every number, operator, and parenthesis,
e.g. "3 + 4 * ( 2 - 1 )"
> 3 + 4 * ( 2 - 1 )
Postfix: 3 4 2 1 - * +
Result:  7.00
```

## Features

- Handles `+ - * /`, parentheses, and correct operator precedence
- Supports negative numbers and decimals
- No recursion, both conversion and evaluation are done with explicit stacks

## Build & run

Requires a C++17 compiler.

```bash
g++ -std=c++17 -Wall -Wextra main.cpp Calculator.cpp -o calculator
./calculator
```

## Project structure

```
├── Calculator.h     # class interface + custom exception types
├── Calculator.cpp   # Shunting Yard conversion + postfix evaluation
└── main.cpp         # CLI entry point
```

## Example expressions to try

| Input | Result |
|---|---|
| `3 + 4 * ( 2 - 1 )` | `7.00` |
| `( 3 + 4 ) * 2` | `14.00` |
| `-5 + 3` | `-2.00` |
| `3.5 * 2` | `7.00` |
| `10 / 0` | Math error: Division by zero |
| `( 3 + 4` | Syntax error: Missing ) |


