#include <iostream>
#include <string>
#include "../headers/list.h"
#include "../headers/evaluator.h"
using namespace std;

void Evaluator::EvaluatePostfix()
{ // Processa a operação pós-fixa, ao final o vetor solveStack possuirá apenas 1 elemento que será o resultado

    // Variáveis que conterão os operandos de cada operação, e identificarão se cada valor é booleano ou não
    int operandLeft, operandRight;
    bool isBoolLeft, isBoolRight;

    // Itera sobre os elementos da expressão
    int lim = postfix.length();
    for (auto i = 0; i < lim; i++)
    {
        string token = postfix[i];
        try
        {
            if (token == "true" || token == "false")
            {
                int booleanValue = (token == "true") ? 1 : 0; // Converte a string para 0 ou 1
                solveStack.insert(booleanValue);              // Adicona valor booleano à solveStack
                boolPositions.insert(true);                   // Marca valor como bool
            }
            else
            {
                int number = stoi(token);    // Checa se token é um inteiro, gera uma excecção se não
                solveStack.insert(number);   // Adiciona o número à solveStack
                boolPositions.insert(false); // Marca valor como não bool
            }
        }
        catch (invalid_argument &)
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
            if (isBoolRight && !(token == "&&" || token == "||" || token == "==") || !isBoolRight && (token == "&&" || token == "||"))
            {
                goto errorCaught;
            }

            // Adquire os últimos dois valores na solveStack e os remove dela para operação
            operandRight = solveStack.pop();
            operandLeft = solveStack.pop();

            // Realiza a operação com os dois últimos valores da solveStack
            try
            {
                int result = Operations(operandLeft, operandRight, token); // Chama metódo para operação
                solveStack.insert(result);                                 // Adiciona resultado à solvestack

                // Adiciona o tipo do resultado da operação ao vetor boolPositions
                bool resultType = !(token == "+" || token == "-" || token == "*" || token == "/" || token == "***");
                boolPositions.insert(resultType);

                // Debug
                // cout << operandLeft << " " << token << " " << operandRight << " = " << result << endl;
            }
            catch (invalid_argument &)
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