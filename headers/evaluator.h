#ifndef EVALUATOR_H
#define EVALUATOR_H
#include <string>
#include "list.h"
#include "stack.h"
using namespace std;

class Evaluator
{
public:
    // Inicia a instância da classe com a expressão em vetor
    Evaluator(List<string>);

    // Chama os metódos privados para processar a expressão e destrói a instância após
    void Evaluate();

    // Imprime o resultado quando a instância é destruída
    ~Evaluator();

private:
    // Lista com a expressão na forma infixa
    List<string> expression;

    // Listas usadas para converter a expressão da notação infixa para a pós-fixa
    List<string> postfix;
    Stack<string> holdingStack;

    // Listas usadas para o algoritmo de resolução da expressão pos-fixa
    Stack<int> solveStack;
    Stack<bool> boolPositions;

    // Variável que determina se há um erro na expressão
    bool error = false;

    // Métdos para determinar operações e suas precedências
    int OperatorPrecedence(string);
    int Operations(int, int, string);

    // Métodos que converte a expressão na forma infixa para a pós-fixa
    void ExpressionToPostfix();

    // Métodos que avaliam a expressão pós-fixa e chega ao seu resultado
    void EvaluatePostfix();
};
#endif
