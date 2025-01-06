# PROJETO - AVALIADOR DE EXPRESSÕES 
- Aluno: André Vinícius Nascimento Cruz
- Período: 2024.2
- Disciplina: CIN0135 - Estrutura de Dados Orientada a Objetos 

### Visão geral
Programa feito em C++ que recebe strings contendo expressões matemáticas e lógicas, as avalia e imprime o resultado da expressão ou uma mensagem de erro.

### Compilação
```
g++ -o main main.cpp src/formatter.cpp src/evaluator.cpp src/operations.cpp src/expressionToPostfix.cpp src/evaluatePostfix.cpp 
```

### Execução
```            
./main
```

### Estrutura do projeto
```
headers/
    evaluator.h
    formatter.h

src/
    evaluatePostfix.cpp
    evaluator.cpp
    expressionToPostfix.cpp
    formatter.cpp
    operations.cpp
    
main.cpp

```
Estrutura do Projeto
headers/

evaluator.h: Declara a classe Evaluator e seus métodos.
formatter.h: Declara a classe ExpressionFormatter e seus métodos.
src/

evaluatePostfix.cpp: Implementa o método EvaluatePostfix da classe Evaluator.
evaluator.cpp: Implementa o construtor, destrutor e método Evaluate da classe Evaluator.
expressionToPostfix.cpp: Implementa o método ExpressionToPostfix da classe Evaluator.
formatter.cpp: Implementa a classe ExpressionFormatter.
operations.cpp: Implementa os métodos OperatorPrecedence e Operations da classe Evaluator.
main.cpp: Contém a função main que coordena a execução do programa.

Funcionamento do Programa
Entrada de Dados:

O programa começa lendo o número de casos a serem processados.
Para cada caso, lê uma expressão na forma de string.
Formatação da Expressão:

A expressão é passada para uma instância da classe ExpressionFormatter, que a formata e converte para um vetor de strings.
O método Format da classe ExpressionFormatter chama ConvertToVector para dividir a expressão em tokens e HandleUnaryMinus para tratar operadores unários.
Avaliação da Expressão:

A expressão formatada é passada para uma instância da classe Evaluator.
O método Evaluate da classe Evaluator chama ExpressionToPostfix para converter a expressão infixa para pós-fixa usando o algoritmo Shunting Yard.
Em seguida, chama EvaluatePostfix para avaliar a expressão pós-fixa.
Conversão para Pós-Fixa:

O método ExpressionToPostfix itera sobre os tokens da expressão infixa, utilizando uma pilha (holdingStack) para operadores e parênteses.
Os operadores são adicionados à expressão pós-fixa (postfix) de acordo com sua precedência, determinada pelo método OperatorPrecedence.
Avaliação Pós-Fixa:

O método EvaluatePostfix itera sobre os tokens da expressão pós-fixa, utilizando uma pilha (solveStack) para operandos.
Quando encontra um operador, remove os dois últimos operandos da pilha, realiza a operação (usando o método Operations) e coloca o resultado de volta na pilha.
Impressão do Resultado:

Após a avaliação, o destrutor da classe Evaluator imprime o resultado final.
Se o resultado for booleano, imprime "true" ou "false". Caso contrário, imprime o valor numérico.
Exemplo de Execução
Dado um exemplo de entrada:

O programa processará cada expressão, convertendo-as para pós-fixa e avaliando-as, imprimindo os resultados.

Arquivos e Métodos Importantes
main.cpp:

Função main: Coordena a leitura de dados, formatação e avaliação das expressões.
headers/evaluator.h e src/evaluator.cpp:

Classe Evaluator: Contém métodos para converter e avaliar expressões.
Métodos: Evaluate, ExpressionToPostfix, EvaluatePostfix, OperatorPrecedence, Operations.
headers/formatter.h e src/formatter.cpp:

Classe ExpressionFormatter: Formata a expressão de string para vetor de tokens.
Métodos: ConvertToVector, HandleUnaryMinus, Format.
src/operations.cpp:

Métodos OperatorPrecedence e Operations: Determinam a precedência dos operadores e realizam operações aritméticas e lógicas.
Conclusão
O programa é um avaliador de expressões que utiliza classes para modularizar a formatação, conversão e avaliação das expressões. Ele suporta operações aritméticas e lógicas, incluindo tratamento de operadores unários
