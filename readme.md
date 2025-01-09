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
- **evaluator.h**: Declaração da classe *Evaluator*.
- **formatter.h**: Declaração da classe *ExpressionFormatter*.
- **formatter.cpp**: Implementação da classe *ExpressionFormatter*.
- **evaluator.cpp**: Implementação do construtor, destrutor e método *Evaluate* da classe *Evaluator*.
- **operations.cpp**: Implementação dos métodos *OperatorPrecedence* e *Operations* da classe *Evaluator*.
- **expressionToPostfix.cpp**: Implementação do método *ExpressionToPostfix* da classe *Evaluator*.
- **evaluatePostfix.cpp**: Implementação do método *EvaluatePostfix* da classe *Evaluator*.
- **main.cpp**: Contém a função *main* responsável por receber as expressões a serem avaliadas, instanciar as classes e chamar seus métodos.

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
### Conversão de String para Vetor

Para cada caso, uma instância da classe ExpressionFormatter é iniciada com a expressão em string, o metódo *vector[string] Format()* é chamado em main.cpp que por sua vez chama *void ConvertToVector()* para transformar a expressão em um vetor de strings.
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
O vetor retornado pelo método *vector[string] Format()* é então usado para iniciar uma instância da classe Evaluator. O método *void Evaluate()* é chamado em main.cpp que por sua vez chama *void ExpressionToPostfix()*. Este método itera sobre os items do vetor *expression* onde está armazenada a expressão na notação infixa, e usa o algoritmo Shunting Yard para criar outro vetor *postfix* que representa a expressão na notação pós-fixa. Durante este processo o método *int OperatorPrecedence(string)* é chamado para determinar a precedênia dos operadores na expressão.
```
{"1"}
{"2", "3", "2", "*", "+"}
{"2", "-1", "-3", "***", "-", "2", "*"}
{"3", "2", "/"}
{"true", "false", "false", "==", "||"}
{"true", "false", "||", "false", "=="}
{"true", "3", "+"}
```
### Avaliação da expressão pós-fixa
Uma vez realizada a conversão, o metódo *void EvaluatePostfix()* é chamado. Este itera sobre os items de *postfix*, adicionando operandos ao vetor *solveStack*. Quando um operador é achado, os dois últimos operandos de *solveStack* são removidos e o método *int Operations(int, int, string)* é chamado para realizar a operação, com o resultado sendo adicionanado à *solveStack*. Paralelamente, o método também atualiza o vetor de bool *boolPositions* que identifica quais operandos na *solveStack* são booleanos e quais são inteiros. Ao final de uma execucação do método sem erros, o único elemento restante na *solveStack* será o resultado da expressão.

### Identificação de erros
O método *void EvaluatePostfix()* irá identificar um erro caso ocorra uma operação entre int e bool, caso um operador seja usado com o tipo inapropriado de operando ou caso haja uma divisão por 0. Em todos esses casos a iteração sobre *postfix* será interrompida e o bool *error* será modificado para true.

### Impressão do Resultado
Após a avaliação, a instância de Evaluator é deletada e o método destrutor da classe Evaluator imprime o resultado final. Caso o bool *error* seja false e o resultado for booleano, "true" ou "false" são imprimidos, caso o resultando não seja booleano, o valor numérico é imprimido e caso *error* seja true, "error" é imprimido.
```
1
8
-2
1
true
false
error
```

