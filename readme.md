# PROJETO - AVALIADOR DE EXPRESSÕES 
- Aluno: André Vinícius Nascimento Cruz
- Período: 2024.2
- Disciplina: CIN0135 - Estrutura de Dados Orientada a Objetos 

## Visão geral
Programa feito em C++ que recebe strings contendo expressões matemáticas e lógicas, as avalia e imprime o resultado da expressão ou uma mensagem de erro.

## Compilação
```
g++ -o main main.cpp src/formatter.cpp src/evaluator.cpp src/operations.cpp src/expressionToPostfix.cpp src/evaluatePostfix.cpp 
```

## Execução
```            
./main
```

## Estrutura do projeto
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
- **evaluator.h**: Declara a classe Evaluator e seus métodos.
- **formatter.h**: Declara a classe ExpressionFormatter e seus métodos.
- **formatter.cpp**: Implementa a classe ExpressionFormatter.
- **evaluator.cpp**: Implementa o construtor, destrutor e método Evaluate da classe Evaluator.
- **operations.cpp**: Implementa os métodos OperatorPrecedence e Operations da classe Evaluator.
- **expressionToPostfix.cpp**: Implementa o método ExpressionToPostfix da classe Evaluator.
- **evaluatePostfix.cpp**: Implementa o método EvaluatePostfix da classe Evaluator.
- **main.cpp**: Contém a função main que recebe as expressões a serem avaliadas, instancia as classes e chama seus métodos.

## Funcionamento do Programa

### Entrada de Dados

O programa, no main.cpp, recebe o número de casos a serem processados
```
7
```
Para cada caso, o programa recebe uma expressão como string
```
1
2 + 3 * 2
( 2 - - -3 ) * 2
3 / 2
true || false == false
( true || false ) == false
true + 3
```
### Formatação da Expressão:

Para cada caso, uma instância da classe ExpressionFormatter é iniciada com a expressão em string, o metódo *vector<string> Format()* é chamado em main.cpp que por sua vez chama *void ConvertToVector()* para transformar a expressão em um vetor de strings.
```
{"1"}
{"2", "+", "3", "*", "2"}
{"(", "2", "-", "-", "-3", ")", "*", "2"}
{"3", "/", "2"}
{"true", "||", "false", "==", "false"}
{"(", "true", "||", "false", ")", "==", "false"}
{"true", "+", "3"}
``` 

Em seguida, é chamado o método *void HandleUnaryMinus()* que itera sobre os vetores e caso encontre um '-' em frente a outro operador considera-o um operador unário e o substitui por 2 items '-1' e '***', estes representam a mesma operação mas tornam-a mais fácil de ser processada pelos algoritmos usados nos métodos da classe Evaluator.
```
{"1"}
{"2", "+", "3", "*", "2"}
{"(", "2", "-", "-1", "***", "-3", ")", "*", "2"}
{"3", "/", "2"}
{"true", "||", "false", "==", "false"}
{"(", "true", "||", "false", ")", "==", "false"}
{"true", "+", "3"}
``` 
### Conversão para Pós-Fixa
O vetor retornado pelo método *vector<string> Format()* é então usado para iniciar uma instância da classe Evaluator. O método *void Evaluate()* é chamado em main.cpp que por sua vez chama *void ExpressionToPostfix()*. Este método itera sobre os items do vetor *expression* onde está armazenada a expressão na notação infixa, e usa o algoritmo Shunting Yard para criar outro vetor *postfix* que representa a expressão na notação pós-fixa. Durante este processo o método *int OperatorPrecedence(string)* é chamado para determinar a precedênia dos operadores na expressão.
```
{"1"}
{"2", "3", "2", "*", "+"}
{"2", "-1", "-3", "***", "-", "2", "*"}
{"3", "2", "/"}
{"true", "false", "||", "false", "=="}
{"true", "false", "||", "false", "=="}
{"true", "3", "+"}
```
### Avaliação da expressão pós-fixa
Uma vez realizada a conversão, o metódo *void EvaluatePostfix()* é chamado. Ele itera sobre os items de *postfix*, adicionando operandos ao vetor solveStack. Quando encontra um operador, remove os dois últimos operandos de *solveStack*, chama o metódo *int Operations(int, int, string)* para realizar a operação e adiciona o resultado à *solveStack*. Paralelamente, o método também atualiza o vetor de bool *boolPositions* que identifica quais operandos na *solveStack* são booleanos e quais são inteiros. O método irá identificar um erro caso ocorra uma operação entre int e bool, caso um operador seja usado com o tipo inapropriado de operando ou caso haja uma divisão por 0, em todos esses casos a iteração sobre *postfix* será interrompida e o bool *error* será modificado para true. Ao final do funcionamento sem erros do método *void EvaluatePostfix()*, o único elemento restante na *solveStack* será o resultado da expressão.

### Impressão do Resultado
Após a avaliação, o destrutor da classe Evaluator imprime o resultado final. Caso o bool *error* seja false e o resultado for booleano, imprime "true" ou "false", caso o resultando não seja booleano, imprime o valor numérico, caso *error* seja true, imprime "error".
```
1
8
-2
1
true
false
error
```
