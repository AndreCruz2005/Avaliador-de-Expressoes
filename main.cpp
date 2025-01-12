#include <iostream>
#include <string>
#include "headers/list.h"
#include "headers/evaluator.h"
#include "headers/formatter.h"
using namespace std;

int main()
{
    // Recebe número de casos
    int cases;
    cin >> cases;
    cin.ignore();

    for (auto i = 0; i < cases; i++)
    {
        // Recebe a expressão como string em cada caso
        string expression;
        getline(cin, expression);

        // Transforma string em lista e formata operadores unários
        ExpressionFormatter inputFormatter(expression);
        List<string> returnList = inputFormatter.Format();

        // Avalia expressão
        Evaluator inputEvaluator(returnList);
        inputEvaluator.Evaluate();

        // Libera memória alocada pela lista
        returnList.free();
    }

    return 0;
}