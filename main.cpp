#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

class Evaluator
{
    string expression;

    vector<string> postfix;

    vector<string> holdingStack;
    vector<int> solveStack;
    vector<bool> boolPositions;

    bool error = false;

    int OperatorPrecedence(string operador)
    {
        if (operador == "/" || operador == "*")
            return 6;
        else if (operador == "+" || operador == "-")
            return 5;
        else if (operador == "<" || operador == ">" || operador == ">=" || operador == "<=")
            return 4;
        else if (operador == "==")
            return 3;
        else if (operador == "&&")
            return 2;
        else if (operador == "||")
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
                if (token == "true" || token == "false")
                {
                    postfix.push_back(token); // Adicona valor booleano à pos-fixa
                }
                else
                {
                    int number = stoi(token); // Checa se é um número, gera uma excecção se não
                    postfix.push_back(token); // Adiciona o número à pos-fixa
                }
            }
            catch (const invalid_argument &)
            {
                // Em caso de exceção, assume que token é parêntesis ou operador

                // Caso ache um parêntesis de esquerda, adiciona-o a holding stack
                if (token == "(")
                {
                    holdingStack.push_back("(");
                }

                // Caso ache um parêntesis de direita, adiciona todos os items entre parêntesis à pos-fixa
                else if (token == ")")
                {
                    while (holdingStack.back() != "(")
                    {
                        // Adicona o último operador a pos-fixa caso nao seja o (
                        postfix.push_back(holdingStack.back());
                        holdingStack.pop_back();
                    }
                    holdingStack.pop_back();
                }

                else
                {
                    // Determina a precedência do ultimo operador na holding stack e a precedência do novo operador
                    int topStackPrecedence = holdingStack.size() > 0 ? OperatorPrecedence(holdingStack.back()) : -1;
                    int newOperatorPrecedence = OperatorPrecedence(token);

                    // Caso a precedencia do topo da stack seja maior, remove operadores até poder adicionar o operador atual
                    while (newOperatorPrecedence <= topStackPrecedence)
                    {
                        // Adiciona operadores removidos à pos-fixa
                        postfix.push_back(holdingStack.back());
                        holdingStack.pop_back();
                        // Atualiza precedência do topo da stack
                        topStackPrecedence = holdingStack.size() > 0 ? OperatorPrecedence(holdingStack.back()) : -1;
                    }
                    // Adiciona novo operador à holdingStack
                    holdingStack.push_back(token);
                }
            }
        }

        // Adiciona todos os operadores restantes na holding stack à expressão pos-fixa depois que as tokens da expressão são processadas
        while (!holdingStack.empty())
        {
            postfix.push_back(holdingStack.back());
            holdingStack.pop_back();
        }
    }

    // Determina o resultado da expressão na forma pos-fixa
    void EvaluatePostfix()
    {
        int valorDireita, valorEsquerda;
        bool isBoolDireita, isBoolEsquerda;

        // Separa os elementos da expressão
        int index = 0;
        while (!error && index < postfix.size())
        {
            string token = postfix[index];
            index++;
            try
            {
                if (token == "true" || token == "false")
                {
                    int booleanValue = (token == "true") ? 1 : 0; // Converte a string para 0 ou 1
                    solveStack.push_back(booleanValue);           // Adicona valor booleano à solveStack
                    boolPositions.push_back(true);                // Marca valor como bool
                }
                else
                {
                    int number = stoi(token);       // Checa se token é um inteiro, gera uma excecção se não
                    solveStack.push_back(number);   // Adiciona o número à solveStack
                    boolPositions.push_back(false); // Marca valor como não bool
                }
            }
            catch (const invalid_argument &)
            {
                // Se houver uma exceção, assume-se que token é um operador

                // Garante que os operandos são ambos boolean ou ambos números
                isBoolDireita = boolPositions.back();
                boolPositions.pop_back();
                isBoolEsquerda = boolPositions.back();
                boolPositions.pop_back();

                if (isBoolDireita != isBoolEsquerda)
                {
                    error = true;
                    break;
                }

                // Adiciona o tipo do resultado da operação ao vetor boolPositions
                bool resultType = !(token == "+" || token == "-" || token == "*" || token == "/");
                boolPositions.push_back(resultType);

                // Garante que o operador é válido para o tipo dos operandos
                if (isBoolDireita && !(token == "&&" || token == "||" || token == "==") || !isBoolDireita && (token == "&&" || token == "||"))
                {
                    error = true;
                    break;
                }

                // Adquire os últimos dois valores na solveStack e os remove dela para operação
                valorDireita = solveStack.back();
                solveStack.pop_back();
                valorEsquerda = solveStack.back();
                solveStack.pop_back();

                // Realiza a operação com os dois últimos valores da solveStack
                try
                {
                    int result = Operations(valorEsquerda, valorDireita, token); // Chama metodo para operação
                    solveStack.push_back(result);                                // Adiciona resultado a solvestack
                    cout << valorEsquerda << " " << token << " " << valorDireita << " = " << result << endl;
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
        delete this;
    }

    ~Evaluator()
    {
        // Imprime resultado antes de destruir a instância da classe
        if (!error && !solveStack.empty())
        {

            if (boolPositions.back())
            {
                // Imprime true ou false se o resultado final for bool
                string result = solveStack.back() ? "true" : "false";
                cout << "Resultado: " << result << endl;
            }
            else
            {
                cout << "Resultado: " << solveStack.back() << endl;
            }
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
