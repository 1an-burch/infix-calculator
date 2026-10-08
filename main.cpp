#include <iomanip>
#include <iostream>

#include "Calculator.h"

int main()
{
    std::cout << std::fixed << std::setprecision(2);

    std::cout << "Infix Calculator\n";
    std::cout << "Enter an expression with spaces between every number, operator, "
                 "and parenthesis,\n";
    std::cout << "e.g. \"3 + 4 * ( 2 - 1 )\"\n> ";

    std::string infixInput;
    if (!std::getline(std::cin, infixInput) || infixInput.empty())
    {
        std::cerr << "No expression entered.\n";
        return 1;
    }

    Calculator calculator;

    try
    {
        std::string postfix = calculator.infixToPostfix(infixInput);
        std::cout << "Postfix: " << postfix << "\n";

        double result = calculator.evaluatePostfix(postfix);
        std::cout << "Result:  " << result << "\n";
    }
    catch (const SyntaxException &e)
    {
        std::cerr << "Syntax error: " << e.what() << "\n";
        return 1;
    }
    catch (const SemanticException &e)
    {
        std::cerr << "Math error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
