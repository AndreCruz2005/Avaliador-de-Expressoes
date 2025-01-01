#ifndef EVALUATOR_H
#define EVALUATOR_H
#include <string>
#include <vector>
using namespace std;

class Evaluator
{
public:
    Evaluator(string expression);
    void Evaluate();
    ~Evaluator();

private:
    string expression;

    // Vetor para armazenar a expressão em forma pos-fixa
    vector<string> postfix;

    // Vectors usados para o algoritmo de resolução da expressão pos-fixa
    vector<string> holdingStack;
    vector<int> solveStack;
    vector<bool> boolPositions;

    // Variável que determina se há um erro na expressão
    bool error = false;

    int OperatorPrecedence(string operador);
    int Operations(int a, int b, string operador);
    void ExpressionToPostfix();
    void EvaluatePostfix();
};
#endif