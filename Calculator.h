#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

// Thrown for malformed expressions: mismatched parentheses, unknown
// tokens, missing operands, etc.
class SyntaxException : public std::runtime_error
{
public:
    explicit SyntaxException(const std::string &message)
        : std::runtime_error(message) {}
};

// Thrown for expressions that are well-formed but invalid to evaluate,
// e.g. division by zero.
class SemanticException : public std::runtime_error
{
public:
    explicit SemanticException(const std::string &message)
        : std::runtime_error(message) {}
};

// Converts a whitespace-separated infix expression to postfix (Shunting
// Yard algorithm) and evaluates postfix expressions, both using an
// explicit stack rather than recursion.
//
// Supported operators: + - * /
// Expressions must have spaces between every token, e.g. "3 + 4 * ( 2 - 1 )"
class Calculator
{
public:
    // Converts an infix expression to postfix notation.
    // Throws SyntaxException on malformed input (mismatched parens,
    // invalid tokens).
    std::string infixToPostfix(const std::string &infix) const;

    // Evaluates a postfix expression and returns the numeric result.
    // Throws SyntaxException on malformed postfix input, or
    // SemanticException on division by zero.
    double evaluatePostfix(const std::string &postfix) const;

private:
    // Operator precedence table, e.g. * and / bind tighter than + and -.
    static const std::unordered_map<std::string, int> precedence;

    bool isOperator(const std::string &token) const;
    int precedenceOf(const std::string &symbol) const;
    double applyOperator(double lhs, double rhs, char op) const;
    std::vector<std::string> tokenize(const std::string &expression) const;
};

#endif // CALCULATOR_H
