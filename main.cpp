#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "evaluator.h"
#include "formatter.h"
using namespace std;

int main()
{
    // Recebe o número de casos a ser processado
    cout << "Número de casos: " << endl;
    int cases;
    cin >> cases;
    cin.ignore();

    // Recebe cada caso e cria uma instância do Evaluator para imprimir o resultado
    for (int i = 0; i < cases; i++)
    {
        string expressao;
        getline(cin, expressao);

        ExpressionFormatter *formatString = new ExpressionFormatter(expressao);
        Evaluator *eval = new Evaluator(formatString->formattedExpression);
        delete formatString;
        eval->Evaluate();
        }

    return 0;
}
