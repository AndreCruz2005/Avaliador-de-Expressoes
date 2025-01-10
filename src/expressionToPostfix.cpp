#include <iostream>
#include <string>
#include "../headers/list.h"
#include "../headers/evaluator.h"
using namespace std;

void Evaluator::ExpressionToPostfix()
{ // Usa o algoritmo shunting yard para converter a expressão da forma infixa para a pós-fixa

    // Itera sobre cada elemento da expressão infixa
    int lim = expression.length();
    for (auto i = 0; i < lim; i++)
    {
        string token = *expression.at(i);
        try
        {
            if (token == "true" || token == "false")
            {
                postfix.insert(token); // Adicona valor booleano à pós-fixa
            }
            else
            {
                stoi(token);           // Checa se é um número, gera uma excecção se não
                postfix.insert(token); // Adiciona o número à pós-fixa
            }
        }
        catch (const invalid_argument &)
        {
            // Em caso de exceção, assume que token é parêntesis ou operador

            // Caso ache um parêntesis de esquerda, adiciona-o a holding stack
            if (token == "(")
            {
                holdingStack.insert("(");
            }

            // Caso ache um parêntesis de direita, adiciona todos os items entre parêntesis à pós-fixa
            else if (token == ")")
            {
                while (*holdingStack.at(holdingStack.length() - 1) != "(")
                {
                    // Adicona o último operador a pós-fixa caso nao seja o (
                    postfix.insert(holdingStack.pop());
                }
                holdingStack.pop();
            }

            else
            {
                // Determina a precedência do ultimo operador na holding stack e a precedência do novo operador
                int topStackPrecedence = holdingStack.length() > 0 ? OperatorPrecedence(*holdingStack.at(holdingStack.length() - 1)) : -1;
                int newOperatorPrecedence = OperatorPrecedence(token);

                // Caso a precedencia do topo da stack seja maior, remove operadores até poder adicionar o novo operador
                while (newOperatorPrecedence <= topStackPrecedence)
                {
                    // Adiciona operadores removidos à pós-fixa
                    postfix.insert(*holdingStack.at(holdingStack.length() - 1));
                    holdingStack.pop();
                    // Atualiza precedência do topo da stack
                    topStackPrecedence = holdingStack.length() > 0 ? OperatorPrecedence(*holdingStack.at(holdingStack.length() - 1)) : -1;
                }
                // Adiciona novo operador à holdingStack
                holdingStack.insert(token);
            }
        }
    }

    // Adiciona todos os operadores restantes na holding stack à expressão pós-fixa depois que as tokens da expressão são processadas
    while (holdingStack.length() > 0)
    {
        postfix.insert(holdingStack.pop());
    }
}