#include <iostream>
#include <string>
#include "../headers/formatter.h"
#include "../headers/list.h"
using namespace std;

ExpressionFormatter::ExpressionFormatter(string expression)
{
    this->expression = expression;
}

void ExpressionFormatter::ConvertToList()
{ // Converte a expressão de string para lista

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

        // Adiciona caractere como novo elemento do lista caso o último caractere tenha sido vazio
        if (lastCharacter == " ")
        {
            formattedExpression.append(character);
        }

        // Caso o último caractere não tenho sido vazio, concatena o caractere ao último elemento do lista, de modo a preservar elementos com múltiplos caracteres
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
    for (auto i = 0; i < formattedExpression.length(); i++)
    {
        // Itera sobre os elementos do lista da expressão
        string token = formattedExpression[i];

        try
        {
            // Considera parentêses direito como número
            if (token == ")")
            {
                goto wasNumber;
            }

            // Checa se o elemento é número, gera uma exceção caso não seja
            stoi(token);

        wasNumber:
            lastTokenWasNumber = true;
        }
        catch (invalid_argument &)
        {
            // Checa se a token é um '-' após um operador, ou seja, um operador unário
            if (token == "-" && !lastTokenWasNumber)
            {
                // Substitui o operador unário por -1 ***. *** opera como multiplicação mas com mais prioridade
                // Essa representação permite que a operação (- int) possa ser processada corretamente pela classe Evaluator
                formattedExpression[i] += "1";
                formattedExpression.append("***", i + 1);
            }
            lastTokenWasNumber = false;
        }
    }
}

List<string> ExpressionFormatter::Format()
{
    ConvertToList();
    HandleUnaryMinus();
    return formattedExpression;
}
