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

    delete this;
}

Evaluator::~Evaluator()
{
    // Imprime resultado antes de destruir a instância da classe
    if (!error && solveStack.length() > 0)
    {

        if (*boolPositions.at(0))
        {
            // Imprime true ou false se o resultado final for bool
            string result = *solveStack.at(0) ? "true" : "false";
            cout << result << endl;
        }
        else
        {
            cout << *solveStack.at(0) << endl;
        }
    }
    else
    {
        cout << "error" << endl;
    }
}
