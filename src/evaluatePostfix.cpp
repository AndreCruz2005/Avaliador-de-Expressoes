#include <iostream>
#include <string>
#include <vector>
#include "../headers/evaluator.h"
using namespace std;

void Evaluator::EvaluatePostfix()
{ // Processa a operação pós-fixa, ao final o vetor solveStack possuirá apenas 1 elemento que será o resultado

    // Variáveis que conterão os operandos de cada operação, e identificarão se cada valor é booleano ou não
    int operandLeft, operandRight;
    bool isBoolLeft, isBoolRight;

    // Itera sobre os elementos da expressão
    for (string token : postfix)
    {
        try
        {
            if (token == "true" || token == "false")
            {
                int booleanValue = (token == "true") ? 1 : 0; // Converte a string para 0 ou 1
                solveStack.push_back(booleanValue);           // Adicona valor booleano à solveStack
                boolPositions.push_back(true);                // Marca valor como bool
            }
            else
            {
                int number = stoi(token);       // Checa se token é um inteiro, gera uma excecção se não
                solveStack.push_back(number);   // Adiciona o número à solveStack
                boolPositions.push_back(false); // Marca valor como não bool
            }
        }
        catch (const invalid_argument &)
        {
            // Se houver uma exceção, assume-se que token é um operador

            // Garante que os operandos são ambos boolean ou ambos números
            isBoolRight = boolPositions.back();
            boolPositions.pop_back();
            isBoolLeft = boolPositions.back();
            boolPositions.pop_back();

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
            operandRight = solveStack.back();
            solveStack.pop_back();
            operandLeft = solveStack.back();
            solveStack.pop_back();

            // Realiza a operação com os dois últimos valores da solveStack
            try
            {
                int result = Operations(operandLeft, operandRight, token); // Chama metódo para operação
                solveStack.push_back(result);                              // Adiciona resultado à solvestack

                // Adiciona o tipo do resultado da operação ao vetor boolPositions
                bool resultType = !(token == "+" || token == "-" || token == "*" || token == "/" || token == "***");
                boolPositions.push_back(resultType);

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