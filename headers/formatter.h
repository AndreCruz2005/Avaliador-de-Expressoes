#ifndef FORMATTER_H
#define FORMATTER_H
#include <string>
#include <vector>
using namespace std;

class ExpressionFormatter
{
    // Variável que contém a expressão original em string
    string expression;

    // Variáveis para conversão da expressão de string para vetor
    string lastCharacter = " ";

    // Varíaveis para formatação de operadores unários
    bool lastTokenWasNumber = false;

    // Converte a expressão de string para vetor e armazena-a em formattedExpression
    void ConvertToVector();

    // Converte os menos unários no vetor para uma representação que pode ser mais facilmente processada
    void HandleUnaryMinus();

public:
    // Vetor que conterá a expressão formatada a partir da string
    vector<string> formattedExpression;

    // Inicialiaza a instância da classe com expressão em string
    ExpressionFormatter(string);

    // Chama metódos privados para processar a string e retornar a string formatada como vetor
    vector<string> Format();
};

#endif