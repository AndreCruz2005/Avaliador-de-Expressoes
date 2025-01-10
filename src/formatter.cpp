#include <iostream>
#include <string>
#include <vector>
#include "../headers/formatter.h"
#include "../headers/list.h"
using namespace std;

ExpressionFormatter::ExpressionFormatter(string expression)
{
    this->expression = expression;
}

void ExpressionFormatter::ConvertToVector()
{ // Converte a expressão de string para vetor

    // Itera sobre os caracteres da string
    for (auto i = 0; i < expression.size(); i++)
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
            formattedExpression.insert(character);
        }

        // Caso o último caractere não tenho sido vazio, concatena o caractere ao último elemento do vetor, de modo a preservar elementos com múltiplos caracteres
        else
        {
            formattedExpression.at(formattedExpression.length() - 1) += character;
        }

        // Atualiza último caractere
        lastCharacter = character;
    }
}

void ExpressionFormatter::HandleUnaryMinus()
{
    for (auto i = 0; i < formattedExpression.length(); i++)
    {
        // Itera sobre os elementos do vetor da expressão
        string token = formattedExpression.at(i);
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
                formattedExpression.at(i) = "-1";
                formattedExpression.insert("***", i + 1);
            }
            lastTokenWasNumber = false;
        }
    }
}

List<string> ExpressionFormatter::Format()
{
    ConvertToVector();
    HandleUnaryMinus();
    return formattedExpression;
}
