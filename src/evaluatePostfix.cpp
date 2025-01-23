#include <iostream>
#include <string>
#include "../headers/stack.h"
#include "../headers/evaluator.h"
using namespace std;

void Evaluator::EvaluatePostfix()
{ // Processa a expressão pós-fixa, ao final a lista solveStack possuirá apenas 1 elemento que será o resultado

    // Variáveis que conterão os operandos de cada operação, e identificarão se cada valor é booleano ou não
    int operandLeft, operandRight;
    bool isBoolLeft, isBoolRight;

    // Itera sobre os elementos da expressão pós-fixa
    const size_t lim = postfix.length();
    for (size_t i = 0; i < lim; i++)
    {
        const auto &token = postfix[i];
        try
        {
            if (token == "true" || token == "false")
            {
                const int booleanValue = (token == "true") ? 1 : 0; // Converte a string para 0 ou 1
                solveStack.append(booleanValue);                    // Adicona valor booleano à solveStack
                boolPositions.append(true);                         // Marca valor como bool
            }
            else
            {
                const int number = stoi(token); // Checa se token é um inteiro, gera uma excecção se não
                solveStack.append(number);      // Adiciona o número à solveStack
                boolPositions.append(false);    // Marca valor como não bool
            }
        }
        catch (const invalid_argument &)
        {
            // Se houver uma exceção, assume-se que token é um operador

            // Garante que os operandos são ambos boolean ou ambos números
            isBoolRight = boolPositions.pop();
            isBoolLeft = boolPositions.pop();

            if (isBoolRight != isBoolLeft)
            {
                goto errorCaught;
            }

            // Garante que o operador é válido para o tipo dos operandos
            if (isBoolRight && !(token == "&&" || token == "||" || token == "==" || token == "!=") || !isBoolRight && (token == "&&" || token == "||"))
            {
                goto errorCaught;
            }

            // Remove os dois valores na solveStack para realizar a operação
            operandRight = solveStack.pop();
            operandLeft = solveStack.pop();

            try
            {
                const int result = Operations(operandLeft, operandRight, token); // Chama metódo para operação
                solveStack.append(result);                                       // Adiciona resultado à solvestack

                // Adiciona o tipo do resultado da operação ao lista boolPositions
                const bool resultType = !(token == "+" || token == "-" || token == "*" || token == "/" || token == "***");
                boolPositions.append(resultType);

                // Debug
                // cout << operandLeft << " " << token << " " << operandRight << " = " << result << endl;
            }
            catch (const invalid_argument &)
            {
                goto errorCaught;
            }

            continue;

        errorCaught:
            error = true;
            break;
        }
    }
}