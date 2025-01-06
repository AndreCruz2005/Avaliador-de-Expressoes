#include <iostream>
#include <string>
#include <vector>
#include "../headers/evaluator.h"
using namespace std;

Evaluator::Evaluator(vector<string> expression)
{
    this->expression = expression;
}

void Evaluator::Evaluate()
{
    ExpressionToPostfix();
    EvaluatePostfix();
    delete this;
}

Evaluator::~Evaluator()
{
    // Imprime resultado antes de destruir a instância da classe
    if (!error && !solveStack.empty())
    {

        if (boolPositions.back())
        {
            // Imprime true ou false se o resultado final for bool
            string result = solveStack.back() ? "true" : "false";
            cout << result << endl;
        }
        else
        {
            cout << solveStack.back() << endl;
        }
    }
    else
    {
        cout << "error" << endl;
    }
}
