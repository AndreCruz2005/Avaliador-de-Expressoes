#include <iostream>
#include <string>
#include "../headers/stack.h"
#include "../headers/evaluator.h"
using namespace std;

Evaluator::Evaluator(List<string> expression)
{
    this->expression = expression;
}

void Evaluator::Evaluate()
{
    ExpressionToPostfix();
    EvaluatePostfix();
}

Evaluator::~Evaluator()
{
    // Imprime resultado antes de destruir a instância da classe
    if (!error && solveStack.length() > 0)
    {

        if (boolPositions.back())
        {
            // Imprime true ou false se o resultado final for bool
            const string result = solveStack.back() ? "true" : "false";
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
