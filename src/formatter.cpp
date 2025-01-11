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
            formattedExpression.insert(character);
        }

        // Caso o último caractere não tenho sido vazio, concatena o caractere ao último elemento do lista, de modo a preservar elementos com múltiplos caracteres
        else
        {
            *formattedExpression.at(formattedExpression.length() - 1) += character;
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
        string token = *formattedExpression.at(i);

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
        catch (const invalid_argument &)
        {
            // Checa se a token é um '-' após um operador, ou seja, um operador unário
            if (token == "-" && !lastTokenWasNumber)
            {
                // Substitui o operador unário por -1 ***. *** opera como multiplicação mas com mais prioridade
                *formattedExpression.at(i) += "1";
                formattedExpression.insert("***", i + 1);
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

int main()
{
    // Test case 1: Simple expression
    string expression1 = "3 + 5";
    ExpressionFormatter formatter1(expression1);
    List<string> result1 = formatter1.Format();
    cout << "Formatted Expression 1: ";
    for (int i = 0; i < result1.length(); i++)
    {
        cout << *result1.at(i) << " ";
    }
    cout << endl;

    // Test case 2: Expression with unary minus
    string expression2 = "- 3 + 5";
    ExpressionFormatter formatter2(expression2);
    List<string> result2 = formatter2.Format();
    cout << "Formatted Expression 2: ";
    for (int i = 0; i < result2.length(); i++)
    {
        cout << *result2.at(i) << " ";
    }
    cout << endl;

    // Test case 3: Complex expression
    string expression3 = "3 + 5 * ( 2 - 8 )";
    ExpressionFormatter formatter3(expression3);
    List<string> result3 = formatter3.Format();
    cout << "Formatted Expression 3: ";
    for (int i = 0; i < result3.length(); i++)
    {
        cout << *result3.at(i) << " ";
    }
    cout << endl;

    return 0;
}
