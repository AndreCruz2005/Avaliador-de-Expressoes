#include <iostream>
#include <string>
#include <vector>
#include "../headers/formatter.h"
using namespace std;

ExpressionFormatter::ExpressionFormatter(string expression)
{
    this->expression = expression;
    
}

void ExpressionFormatter::ConvertToVector()
{

    for (int i = 0; i < expression.size(); i++)
    {
        string character(1, expression[i]);
        if (character == " ")
        {
            lastCharacter = " ";
            continue;
        }
        if (lastCharacter == " ")
        {
            formattedExpression.push_back(character);
            lastCharacter = character;
        }
        else
        {
            formattedExpression.back() += character;
            lastCharacter = character;
        }
    }
}

void ExpressionFormatter::HandleUnaryMinus()
{
    for (int i = 0; i < formattedExpression.size(); i++)
    {
        string token = formattedExpression[i];
        try
        {
            stoi(token);
            lastTokenWasNumber = true;
        }
        catch (const invalid_argument &)
        {
            // Checa se a token é um '-' após um operador, ou seja, um operador unário
            if (token == "-" && !lastTokenWasNumber)
            {
                // Substitui a operação por -1 ***. *** opera como multiplicação mas com mais prioridade
                formattedExpression[i] = "-1";
                formattedExpression.insert(formattedExpression.begin() + i + 1, "***");
            }
            lastTokenWasNumber = false;
        }
    }
}
