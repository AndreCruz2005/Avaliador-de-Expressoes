#ifndef FORMATTER_H
#define FORMATTER_H
#include <string>
#include "list.h"
using namespace std;

class ExpressionFormatter
{
    // Variável que contém a expressão original em string
    string expression;

    // lista que conterá a expressão formatada a partir da string
    List<string> formattedExpression;

    // Variáveis para conversão da expressão de string para lista
    string lastCharacter = " ";

    // Varíavel para formatação de operadores unários
    bool lastTokenWasNumber = false;

    // Converte a expressão de string para lista e armazena-a em formattedExpression
    void ConvertToList();

    // Converte os menos unários no lista para uma representação que pode ser mais facilmente processada pela classe Evaluator
    void HandleUnaryMinus();

public:
    // Inicialiaza a instância da classe com expressão em string
    ExpressionFormatter(string);

    // Chama metódos privados para processar a string e retornar a string formatada como lista
    List<string> Format();
};

#endif