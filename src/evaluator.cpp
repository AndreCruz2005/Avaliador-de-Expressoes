#include <iostream>
#include <string>
#include "../headers/list.h"
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

        if (boolPositions[0])
        {
            // Imprime true ou false se o resultado final for bool
            string result = solveStack[0] ? "true" : "false";
            cout << result << endl;
        }
        else
        {
            cout << solveStack[0] << endl;
        }
    }
    else
    {
        cout << "error" << endl;
    }
}
