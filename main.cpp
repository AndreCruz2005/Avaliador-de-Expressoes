#include <iostream>
#include <string>
#include "headers/list.h"
#include "headers/evaluator.h"
#include "headers/formatter.h"
using namespace std;

int main()
{
    int cases;
    cin >> cases;
    cin.ignore();

    for (auto i = 0; i < cases; i++)
    {
        string expression;
        getline(cin, expression);

        ExpressionFormatter inputFormatter(expression);
        List<string> returnList = inputFormatter.Format();

        Evaluator inputEvaluator(returnList);
        inputEvaluator.Evaluate();

        returnList.free();
    }

    return 0;
}