#ifndef FORMATTER_H
#define FORMATTER_H
#include <string>
#include <vector>
using namespace std;

class ExpressionFormatter
{
    string expression;

    // Variáveis para conversão da expressão de string para vetor
    string lastCharacter = " ";

    // Varíaveis para formatar operadores unários
    bool lastTokenWasNumber = false;
    void ConvertToVector();
    void HandleUnaryMinus();

public:
    vector<string> formattedExpression;
    ExpressionFormatter(string);
};

#endif