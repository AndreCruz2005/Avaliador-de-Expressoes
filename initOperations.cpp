#include <iostream>
#include <string>
#include "evaluator.h"
using namespace std;

int Evaluator::OperatorPrecedence(string operador)
{
    if (operador == "***")
        return 7;
    else if (operador == "/" || operador == "*")
        return 6;
    else if (operador == "+" || operador == "-")
        return 5;
    else if (operador == "<" || operador == ">" || operador == ">=" || operador == "<=")
        return 4;
    else if (operador == "==")
        return 3;
    else if (operador == "&&")
        return 2;
    else if (operador == "||")
        return 1;
    else
        return 0;
}

int Evaluator::Operations(int a, int b, string operador)
{
    if (operador == "+")
        return (a + b);
    else if (operador == "-")
        return (a - b);
    else if (operador == "*" || operador == "***")
        return (a * b);
    else if (operador == "/")
        return (b != 0) ? (a / b) : throw invalid_argument("Divisão por 0");
    else if (operador == "||")
        return (a || b);
    else if (operador == "&&")
        return (a && b);
    else if (operador == ">=")
        return (a >= b);
    else if (operador == "<=")
        return (a <= b);
    else if (operador == "==")
        return (a == b);
    else if (operador == ">")
        return (a > b);
    else if (operador == "<")
        return (a < b);
    else
        throw invalid_argument("Operador inválido");
}