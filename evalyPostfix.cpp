#include <iostream>
#include <string>
#include <vector>
#include <evaluator.h>
using namespace std;

void Evaluator::EvaluatePostfix()
{
    int valorDireita, valorEsquerda;
    bool isBoolDireita, isBoolEsquerda;

    // Separa os elementos da expressão
    int index = 0;
    while (!error && index < postfix.size())
    {
        string token = postfix[index];
        index++;
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
            isBoolDireita = boolPositions.back();
            boolPositions.pop_back();
            isBoolEsquerda = boolPositions.back();
            boolPositions.pop_back();

            if (isBoolDireita != isBoolEsquerda)
            {
                error = true;
                break;
            }

            // Adiciona o tipo do resultado da operação ao vetor boolPositions
            bool resultType = !(token == "+" || token == "-" || token == "*" || token == "/");
            boolPositions.push_back(resultType);

            // Garante que o operador é válido para o tipo dos operandos
            if (isBoolDireita && !(token == "&&" || token == "||" || token == "==") || !isBoolDireita && (token == "&&" || token == "||"))
            {
                error = true;
                break;
            }

            // Adquire os últimos dois valores na solveStack e os remove dela para operação
            valorDireita = solveStack.back();
            solveStack.pop_back();
            valorEsquerda = solveStack.back();
            solveStack.pop_back();

            // Realiza a operação com os dois últimos valores da solveStack
            try
            {
                int result = Operations(valorEsquerda, valorDireita, token); // Chama metodo para operação
                solveStack.push_back(result);                                // Adiciona resultado a solvestack
                cout << valorEsquerda << " " << token << " " << valorDireita << " = " << result << endl;
            }
            catch (const invalid_argument &)
            {
                error = true;
            }
        }
    }
}