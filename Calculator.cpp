#include "Calculator.h"

#include <cctype>
#include <sstream>
#include <stack>

const std::unordered_map<std::string, int> Calculator::precedence = {
    {"/", 2}, {"*", 2}, {"+", 1}, {"-", 1}};

bool Calculator::isOperator(const std::string &token) const
{
    return precedence.count(token) > 0;
}

int Calculator::precedenceOf(const std::string &symbol) const
{
    auto it = precedence.find(symbol);
    return it != precedence.end() ? it->second : 0;
}

double Calculator::applyOperator(double lhs, double rhs, char op) const
{
    switch (op)
    {
    case '+':
        return lhs + rhs;
    case '-':
        return lhs - rhs;
    case '*':
        return lhs * rhs;
    case '/':
        if (rhs == 0.0)
        {
            throw SemanticException("Division by zero");
        }
        return lhs / rhs;
    default:
        throw std::runtime_error("Unknown operator");
    }
}

std::vector<std::string> Calculator::tokenize(const std::string &expression) const
{
    std::vector<std::string> tokens;
    std::stringstream ss(expression);
    std::string token;
    while (ss >> token)
    {
        tokens.push_back(token);
    }
    return tokens;
}

std::string Calculator::infixToPostfix(const std::string &infix) const
{
    std::vector<std::string> tokens = tokenize(infix);
    std::stack<std::string> operatorStack;
    std::string postfix;

    for (const std::string &token : tokens)
    {
        bool isOperand = false;
        try
        {
            std::stod(token);
            isOperand = true;
        }
        catch (...)
        {
            // Not a number, fall through to operator/parenthesis handling.
        }

        if (isOperand)
        {
            postfix += token + " ";
            continue;
        }

        char symbol = (token.length() == 1) ? token[0] : '\0';

        switch (symbol)
        {
        case '(':
            operatorStack.push(token);
            break;

        case ')':
            while (!operatorStack.empty() && operatorStack.top() != "(")
            {
                postfix += operatorStack.top() + " ";
                operatorStack.pop();
            }
            if (operatorStack.empty())
            {
                throw SyntaxException("Missing (");
            }
            operatorStack.pop(); // discard the matching "("
            break;

        case '+':
        case '-':
        case '*':
        case '/':
            while (!operatorStack.empty())
            {
                const std::string &top = operatorStack.top();
                if (top == "(" || precedenceOf(token) > precedenceOf(top))
                {
                    break;
                }
                postfix += top + " ";
                operatorStack.pop();
            }
            operatorStack.push(token);
            break;

        default:
            throw SyntaxException("Invalid token: " + token);
        }
    }

    while (!operatorStack.empty())
    {
        if (operatorStack.top() == "(")
        {
            throw SyntaxException("Missing )");
        }
        postfix += operatorStack.top() + " ";
        operatorStack.pop();
    }

    if (!postfix.empty() && postfix.back() == ' ')
    {
        postfix.pop_back();
    }

    return postfix;
}

double Calculator::evaluatePostfix(const std::string &postfix) const
{
    std::vector<std::string> tokens = tokenize(postfix);
    std::stack<double> values;

    for (const std::string &token : tokens)
    {
        bool looksNumeric = std::isdigit(static_cast<unsigned char>(token[0])) ||
                             (token.size() > 1 && std::isdigit(static_cast<unsigned char>(token[1])) &&
                              (token[0] == '-' || std::isdigit(static_cast<unsigned char>(token[0]))));

        if (looksNumeric)
        {
            try
            {
                values.push(std::stod(token));
            }
            catch (...)
            {
                throw SyntaxException("Invalid number format: " + token);
            }
        }
        else if (isOperator(token))
        {
            if (values.size() < 2)
            {
                throw SyntaxException("Insufficient operands for '" + token + "'");
            }

            double rhs = values.top();
            values.pop();
            double lhs = values.top();
            values.pop();

            values.push(applyOperator(lhs, rhs, token[0]));
        }
        else
        {
            throw SyntaxException("Invalid token: " + token);
        }
    }

    if (values.size() != 1)
    {
        throw SyntaxException("Malformed expression: leftover operands");
    }

    return values.top();
}
