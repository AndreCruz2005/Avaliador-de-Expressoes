#include <iostream>
#include <string>
#include "../headers/evaluator.h"
using namespace std;

int Evaluator::OperatorPrecedence(string op)
{
    if (op == "***")
        return 7;
    else if (op == "/" || op == "*")
        return 6;
    else if (op == "+" || op == "-")
        return 5;
    else if (op == "<" || op == ">" || op == ">=" || op == "<=")
        return 4;
    else if (op == "==" || "!=")
        return 3;
    else if (op == "&&")
        return 2;
    else if (op == "||")
        return 1;
    else
        return 0;
}

int Evaluator::Operations(int a, int b, string op)
{
    if (op == "+")
        return (a + b);
    else if (op == "-")
        return (a - b);
    else if (op == "*" || op == "***")
        return (a * b);
    else if (op == "/")
        return (b != 0) ? (a / b) : throw invalid_argument("Divisão por 0");
    else if (op == "||")
        return (a || b);
    else if (op == "&&")
        return (a && b);
    else if (op == ">=")
        return (a >= b);
    else if (op == "<=")
        return (a <= b);
    else if (op == "==")
        return (a == b);
    else if (op == "!=")
        return (a != b);
    else if (op == ">")
        return (a > b);
    else if (op == "<")
        return (a < b);
    else
        throw invalid_argument("Operador inválido");
}