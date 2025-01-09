#include <iostream>
#include <string>
#include <vector>
#include "../headers/evaluator.h"
using namespace std;

void Evaluator::ExpressionToPostfix()
{ // Usa o algoritmo shunting yard para converter a expressão da forma infixa para a pós-fixa

    // Itera sobre cada elemento da expressão infixa
    for (string token : expression)
    {
        try
        {
            if (token == "true" || token == "false")
            {
                postfix.push_back(token); // Adicona valor booleano à pós-fixa
            }
            else
            {
                stoi(token);              // Checa se é um número, gera uma excecção se não
                postfix.push_back(token); // Adiciona o número à pós-fixa
            }
        }
        catch (const invalid_argument &)
        {
            // Em caso de exceção, assume que token é parêntesis ou operador

            // Caso ache um parêntesis de esquerda, adiciona-o a holding stack
            if (token == "(")
            {
                holdingStack.push_back("(");
            }

            // Caso ache um parêntesis de direita, adiciona todos os items entre parêntesis à pós-fixa
            else if (token == ")")
            {
                while (holdingStack.back() != "(")
                {
                    // Adicona o último operador a pós-fixa caso nao seja o (
                    postfix.push_back(holdingStack.back());
                    holdingStack.pop_back();
                }
                holdingStack.pop_back();
            }

            else
            {
                // Determina a precedência do ultimo operador na holding stack e a precedência do novo operador
                int topStackPrecedence = holdingStack.size() > 0 ? OperatorPrecedence(holdingStack.back()) : -1;
                int newOperatorPrecedence = OperatorPrecedence(token);

                // Caso a precedencia do topo da stack seja maior, remove operadores até poder adicionar o novo operador
                while (newOperatorPrecedence <= topStackPrecedence)
                {
                    // Adiciona operadores removidos à pós-fixa
                    postfix.push_back(holdingStack.back());
                    holdingStack.pop_back();
                    // Atualiza precedência do topo da stack
                    topStackPrecedence = holdingStack.size() > 0 ? OperatorPrecedence(holdingStack.back()) : -1;
                }
                // Adiciona novo operador à holdingStack
                holdingStack.push_back(token);
            }
        }
    }

    // Adiciona todos os operadores restantes na holding stack à expressão pós-fixa depois que as tokens da expressão são processadas
    while (!holdingStack.empty())
    {
        postfix.push_back(holdingStack.back());
        holdingStack.pop_back();
    }
}