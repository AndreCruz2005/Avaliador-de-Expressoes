#ifndef EVALUATOR_H
#define EVALUATOR_H
#include <string>
#include <vector>
using namespace std;

class Evaluator
{
public:
    // Inicia a instância da classe com a expressão em vetor
    Evaluator(vector<string>);

    // Chama os metódos privados para processar a expressão e destrói a instância após
    void Evaluate();

    // Imprime o resultado quando a instância é destruída
    ~Evaluator();

private:
    // Vetor com a expressão na forma infixa
    vector<string> expression;

    // Vetors usados para converter a expressão da notação infixa para a pós-fixa
    vector<string> postfix;
    vector<string> holdingStack;

    // Vectors usados para o algoritmo de resolução da expressão pos-fixa
    vector<int> solveStack;
    vector<bool> boolPositions;

    // Variável que determina se há um erro na expressão
    bool error = false;

    // Metódos para determinar operações e suas precedências
    int OperatorPrecedence(string);
    int Operations(int, int, string);

    // Metódo que converte a expressão na forma infixa para a pós-fixa
    void ExpressionToPostfix();

    // Metódo que avalia a expressão pós-fixa e chega ao seu resultado
    void EvaluatePostfix();
};
#endif
