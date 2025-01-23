#include <iostream>
#include <string>
#include "../headers/stack.h"
#include "../headers/evaluator.h"
using namespace std;

void Evaluator::ExpressionToPostfix()
{ // Usa o algoritmo shunting yard para converter a expressão da forma infixa para a pós-fixa

    // Itera sobre cada elemento da expressão infixa
    const size_t lim = expression.length();
    for (size_t i = 0; i < lim; i++)
    {
        const string &token = expression[i];
        try
        {
            if (token == "true" || token == "false")
            {
                postfix.append(token); // Adicona valor booleano à pós-fixa
            }
            else
            {
                stoi(token);           // Checa se é um número, gera uma excecção se não
                postfix.append(token); // Adiciona o número à pós-fixa
            }
        }
        catch (invalid_argument &)
        {
            // Em caso de exceção, assume que token é parêntesis ou operador

            // Caso ache um parêntesis de esquerda, adiciona-o a holding stack
            if (token == "(")
            {
                holdingStack.append("(");
            }

            // Caso ache um parêntese de direita, adiciona os operadores da holdingStack à pós-fixa até achar o parêntese respectivo de esquerda
            else if (token == ")")
            {
                while (holdingStack.back() != "(")
                {
                    postfix.append(holdingStack.pop());
                }

                // Para remover o parenteses esquerdo sem o adicionar à pós-fixa
                holdingStack.pop();
            }

            else
            {
                // Determina a precedência do ultimo operador na holding stack e a precedência do novo operador.
                // O novo operador só pode ser adicionado caso a precedência no topo da holding stack seja menor
                int topStackPrecedence = holdingStack.length() > 0 ? OperatorPrecedence(holdingStack.back()) : -1;
                int newOperatorPrecedence = OperatorPrecedence(token);

                // Caso a precedencia do topo da stack seja maior, remove operadores até poder adicionar o novo operador
                while (newOperatorPrecedence <= topStackPrecedence)
                {
                    // Adiciona operadores removidos à pós-fixa
                    postfix.append(holdingStack.back());
                    holdingStack.pop();

                    // Atualiza precedência do topo da stack
                    topStackPrecedence = holdingStack.length() > 0 ? OperatorPrecedence(holdingStack.back()) : -1;
                }
                // Adiciona novo operador à holdingStack
                holdingStack.append(token);
            }
        }
    }

    // Adiciona todos os operadores restantes na holding stack à expressão pós-fixa depois que as tokens da expressão são processadas
    while (holdingStack.length() > 0)
    {
        postfix.append(holdingStack.pop());
    }
}