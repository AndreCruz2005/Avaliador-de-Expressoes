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
        cout << "Expressão: " << endl;
        // Pega a expressão como string
        string expressao;
        getline(cin, expressao);

        ExpressionFormatter *formatString = new ExpressionFormatter(expressao); // Cria a instância do formatador de expressão
        List<string> returnList = formatString->Format();

        cout << "Lista: ";
        for (auto i = 0; i < returnList.length(); i++)
        {
            cout << *returnList.at(i) << " ";
        }
        cout << "\n";

        delete formatString;
    }

    return 0;
}
