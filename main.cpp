#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <evaluator.h>
using namespace std;

int main()
{
    int cases;
    cin >> cases;
    cin.ignore();

    for (int i = 0; i < cases; i++)
    {
        string expressao;
        getline(cin, expressao);

        Evaluator *eval = new Evaluator(expressao);
        eval->Evaluate();
    }

    return 0;
}
