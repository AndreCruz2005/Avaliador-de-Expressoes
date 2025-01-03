#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "evaluator.h"
using namespace std;

void Evaluator::ExpressionToPostfix()
{ // Usado para pegar cada item separado por um espaço vazio na expressão fornecida
    int index = 0;
    while (!error && index < postfix.size())
    {
        string token = expression[index];
        try
        {
            if (token == "true" || token == "false")
            {
                postfix.push_back(token); // Adicona valor booleano à pos-fixa
            }
            else
            {
                stoi(token);              // Checa se é um número, gera uma excecção se não
                postfix.push_back(token); // Adiciona o número à pos-fixa
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

            // Caso ache um parêntesis de direita, adiciona todos os items entre parêntesis à pos-fixa
            else if (token == ")")
            {
                while (holdingStack.back() != "(")
                {
                    // Adicona o último operador a pos-fixa caso nao seja o (
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

                // Caso a precedencia do topo da stack seja maior, remove operadores até poder adicionar o operador atual
                while (newOperatorPrecedence <= topStackPrecedence)
                {
                    // Adiciona operadores removidos à pos-fixa
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

    // Adiciona todos os operadores restantes na holding stack à expressão pos-fixa depois que as tokens da expressão são processadas
    while (!holdingStack.empty())
    {
        postfix.push_back(holdingStack.back());
        holdingStack.pop_back();
    }
}