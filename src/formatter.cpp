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
{ // Converte a expressão de string para vetor

    // Itera sobre os caracteres da string
    for (int i = 0; i < expression.size(); i++)
    {
        string character(1, expression[i]);

        // Ignora caractere vazio
        if (character == " ")
        {
            lastCharacter = " ";
            continue;
        }

        // Adiciona caractere como novo elemento do vetor caso o último caractere tenha sido vazio
        if (lastCharacter == " ")
        {
            formattedExpression.push_back(character);
        }

        // Caso o último caractere não tenho sido vazio, concatena o caractere ao último elemento do vetor, de modo a preservar elementos com múltiplos caracteres
        else
        {
            formattedExpression.back() += character;
        }

        // Atualiza último caractere
        lastCharacter = character;
    }
}

void ExpressionFormatter::HandleUnaryMinus()
{
    for (int i = 0; i < formattedExpression.size(); i++)
    {   
        // Itera sobre os elementos do vetor da expressão
        string token = formattedExpression[i];
        try
        {   
            // Checa se o elemento é número, gera uma exceção caso não seja
            stoi(token);
            lastTokenWasNumber = true;
        }
        catch (const invalid_argument &)
        {
            // Checa se a token é um '-' após um operador, ou seja, um operador unário
            if (token == "-" && !lastTokenWasNumber)
            {
                // Substitui o operador unário por -1 ***. *** opera como multiplicação mas com mais prioridade
                formattedExpression[i] = "-1";
                formattedExpression.insert(formattedExpression.begin() + i + 1, "***");
            }
            lastTokenWasNumber = false;
        }
    }
}

vector<string> ExpressionFormatter::Format(){
    ConvertToVector();
    HandleUnaryMinus();
    return formattedExpression;
}
