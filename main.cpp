#include <iostream>
#include <string>
#include "headers/list.h"
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
        cout << "xabeu";
        // Pega a expressão como string
        string expressao;
        getline(cin, expressao);

        cout << "xabeu";
        ExpressionFormatter *formatString = new ExpressionFormatter(expressao); // Cria a instância do formatador de expressão
        List<string> returnList = formatString->Format();
        delete formatString;

        cout << "xabeu";
        Evaluator *eval = new Evaluator(returnList); // Cria uma instância do evaluator com a lista retornado pela formatString
        eval->Evaluate();
    }

    return 0;
}
