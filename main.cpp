#include <iostream>
#include <string>
#include <vector>
#include "headers/evaluator.h"
#include "headers/formatter.h"
using namespace std;

int main()
{
    // Recebe o número de casos a ser processado
    cout << "Número de casos: " << endl;
    int cases;
    cin >> cases;
    cin.ignore();

    // Recebe cada caso
    for (auto i = 0; i < cases; i++)
    {
        // Pega a expressão como string
        string expressao;
        getline(cin, expressao);

        ExpressionFormatter *formatString = new ExpressionFormatter(expressao);
        formatString->ConvertToVector();
        formatString->HandleUnaryMinus();
        Evaluator *eval = new Evaluator(formatString->formattedExpression);
        delete formatString;
        eval->Evaluate();
        
        
    }

    return 0;
}
