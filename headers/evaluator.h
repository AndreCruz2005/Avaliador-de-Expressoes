#ifndef EVALUATOR_H
#define EVALUATOR_H
#include <string>
#include <vector>
using namespace std;

class Evaluator
{
public:
    Evaluator(vector<string>);
    void Evaluate();
    ~Evaluator();

private:
    // Vetor com a expressão na forma infixa
    vector<string> expression;

    // Vetor para armazenar a expressão em forma pos-fixa
    vector<string> postfix;

    // Vectors usados para o algoritmo de resolução da expressão pos-fixa
    vector<string> holdingStack;
    vector<int> solveStack;
    vector<bool> boolPositions;

    // Variável que determina se há um erro na expressão
    bool error = false;

    int OperatorPrecedence(string);
    int Operations(int, int, string);
    void ExpressionToPostfix();
    void EvaluatePostfix();
};
#endif