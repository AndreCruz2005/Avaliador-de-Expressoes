#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

class Evaluator
{
    string expression;

    string postfix;

    vector<string> holdingStack;
    vector<int> solveStack;
    bool error = false;

    int operatorPrecedence(string operador)
    {
        if (operador == "/" || operador == "*")
            return 5;
        else if (operador == "+" || operador == "-")
            return 4;
        else if (operador == "||" || operador == "&&")
            return 3;
        else if (operador == "<" || operador == ">" || operador == ">=" || operador == "<=")
            return 2;
        else if (operador == "==")
            return 1;
        else
            return 0;
    }

    int Operations(int a, int b, string operador)
    {
        if (operador == "+")
            return (a + b);
        else if (operador == "-")
            return (a - b);
        else if (operador == "*")
            return (a * b);
        else if (operador == "/")
            return (b != 0) ? (a / b) : throw invalid_argument("Divisão por 0");
        else if (operador == "||")
            return (a || b);
        else if (operador == "&&")
            return (a && b);
        else if (operador == ">=")
            return (a >= b);
        else if (operador == "<=")
            return (a <= b);
        else if (operador == "==")
            return (a == b);
        else if (operador == ">")
            return (a > b);
        else if (operador == "<")
            return (a < b);
        else
            throw invalid_argument("Operador inválido");
    }

public:
    Evaluator(string expression)
    {
        this->expression = expression;
    }

    // Usa o algoritmo Shunting Yard para converter a expressão infixa fornecida para pós-fixa
    void ExpressionToPostfix()
    {
        // Usado para pegar cada item separado por um espaço vazio na expressão fornecida
        stringstream stream(expression);
        string token;
        while (stream >> token && !error)
        {

            try
            {
                // Se a token for um número adicona-o a expressão pos-fixa
                int number = stoi(token);
                postfix += token + " ";
            }
            catch (const invalid_argument &)
            {

                // Caso ache um parenteses de esquerda, adiciona-o a holding stack
                if (token == "(")
                {
                    holdingStack.push_back("(");
                }

                // Caso ache um parenteses de direita, adiciona todos os items entre parenteses à pos-fixa
                else if (token == ")")
                {
                    while (holdingStack.back() != "(")
                    {
                        // Adicona o último operador a pos-fixa caso nao seja o (
                        postfix += holdingStack.back() + " ";
                        holdingStack.pop_back();
                    }
                    holdingStack.pop_back();
                }

                else
                {
                    // Determina a precedência do ultimo operador na holding stack e a precedência do novo operador
                    int topStackPrecedence = holdingStack.size() > 0 ? operatorPrecedence(holdingStack.back()) : -1;
                    int newOperatorPrecedence = operatorPrecedence(token);

                    // Caso a precedencia do topo da stack seja maior, remove operadores até poder adicionar o operador atual
                    while (newOperatorPrecedence <= topStackPrecedence)
                    {
                        // Adiciona operadores removidos à pos-fixa
                        postfix += holdingStack.back() + " ";
                        holdingStack.pop_back();
                        // Atualiza precedência do topo da stack
                        topStackPrecedence = holdingStack.size() > 0 ? operatorPrecedence(holdingStack.back()) : -1;
                    }
                    // Adiciona novo operador à holdingStack
                    holdingStack.push_back(token);
                }
            }
        }

        // Adiciona todos os operadores restantes na holding stack à expressão pos-fixa depois que as tokens da expressão são processadas
        while (!holdingStack.empty())
        {
            postfix += holdingStack.back() + " ";
            holdingStack.pop_back();
        }
    }

    // Determina o resultado da expressão na forma pos-fixa
    void EvaluatePostfix()
    {
        int valor_direita, valor_esquerda;

        // Separa os elementos da expressão pelos espaços vazios
        stringstream stream(postfix);
        string token;

        while (stream >> token && !error)
        {

            try
            {
                // Tenta converter token para inteiro
                int number = stoi(token);
                solveStack.push_back(number);
            }
            catch (const invalid_argument &)
            {
                // Se houver uma exceção, assume-se que token é um operador

                // Adquire os últimos dois valores na solveStack e os remove dela
                valor_direita = solveStack.back();
                solveStack.pop_back();
                valor_esquerda = solveStack.back();
                solveStack.pop_back();

                // Realiza a operação com os dois últimos valores da solveStack
                try
                {
                    int result = Operations(valor_esquerda, valor_direita, token);
                    cout << valor_esquerda << " " << token << " " << valor_direita << " = " << result << endl;
                    solveStack.push_back(result);
                }
                catch (const invalid_argument &)
                {
                    error = true;
                }
            }
        }
    }

    void Evaluate()
    {
        ExpressionToPostfix();
        EvaluatePostfix();
        delete this; // Suicídio :(
    }

    ~Evaluator()
    {
        // Imprime resultado antes de destruir a instância da classe
        if (!error && !solveStack.empty())
        {
            cout << "Resultado: " << solveStack.back() << endl;
        }
        else
        {
            cout << "Resultado: error" << endl;
        }
    }
};

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
