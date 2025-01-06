#include <iostream>
#include <string>
#include <vector>
#include "headers/evaluator.h"
#include "headers/formatter.h"
using namespace std;

int main()
{
    // Recebe o número de casos a ser processado
    int cases;
    cin >> cases;
    cin.ignore();

    // Recebe cada caso
    for (auto i = 0; i < cases; i++)
    {
        // Pega a expressão como string
        string expressao;
        getline(cin, expressao);

        ExpressionFormatter *formatString = new ExpressionFormatter(expressao); // Cria a instância do formatador de expressão
        Evaluator *eval = new Evaluator(formatString->Format());                // Cria uma instância do evaluator com o vetor retornado pela formatString
        delete formatString;
        eval->Evaluate();
    }

    return 0;
}
