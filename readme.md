# PROJETO - AVALIADOR DE EXPRESSÕES

- Aluno: André Vinícius Nascimento Cruz
- Período: 2024.2
- Disciplina: CIN0135 - Estrutura de Dados Orientada a Objetos

## Visão geral

Programa feito em C++ que recebe strings contendo expressões matemáticas e lógicas, as avalia e imprime o resultado da expressão ou uma mensagem de erro.

## Compilação

```
g++ -o main main.cpp src/dynamicArray.cpp src/formatter.cpp src/evaluator.cpp src/operations.cpp src/expressionToPostfix.cpp src/evaluatePostfix.cpp
```

## Execução

```
./main
```

## Estrutura do projeto

```
headers/
    dynamicArray.h
    evaluator.h
    formatter.h
    list.h
    stack.h

src/
    dynamicArray.cpp
    evaluatePostfix.cpp
    evaluator.cpp
    expressionToPostfix.cpp
    formatter.cpp
    operations.cpp

main.cpp

```

#### Header

- **dynamicArray.h**: declaração da classe **DynamicArray**.
- **list.h**: declaração da classe **List** que herda **DynamicArray**.
- **stack.h**: declaração da classe **Stack** que herda **DynamicArray**.
- **formatter.h**: declaração da classe **ExpressionFormatter**.
- **evaluator.h**: declaração da classe **Evaluator**.

#### Source

- **dynamicArray.cpp**: implementação da classe **DynamicArray**
- **formatter.cpp**: implementação da classe **ExpressionFormatter**.
- **evaluator.cpp**: implementação do construtor, destrutor e método _Evaluate_ da classe **Evaluator**.
- **operations.cpp**: implementação dos métodos _OperatorPrecedence_ e _Operations_ da classe **Evaluator**.
- **expressionToPostfix.cpp**: implementação do método _ExpressionToPostfix_ da classe **Evaluator**.
- **evaluatePostfix.cpp**: implementação do método _EvaluatePostfix_ da classe **Evaluator**.
- **main.cpp**: contém a função _main_ responsável por receber as expressões a serem avaliadas, instanciar as classes e chamar seus métodos.

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

### Conversão de String para Lista

Para cada caso, uma instância da classe _ExpressionFormatter_ é iniciada com a expressão em string, o método _List[string] Format()_ é chamado em main.cpp que por sua vez chama _void ConvertToList()_ para transformar a expressão em uma lista de strings.

```
{"1"}
{"2", "+", "3", "*", "2"}
{"(", "2", "-", "-", "-3", ")", "*", "2"}
{"3", "/", "2"}
{"true", "||", "false", "==", "false"}
{"(", "true", "||", "false", ")", "==", "false"}
{"true", "+", "3"}
```

Em seguida, é chamado o método _void HandleUnaryMinus()_ que itera sobre as listas e caso encontre um '-' em frente a outro operador considera-o um operador unário e o substitui por 2 itens '-1' e '*\*\*', estes representam a mesma operação, mas tornam-na mais fácil de ser processada pelos algoritmos usados nos métodos da classe *Evaluator*.

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

O lista retornado pelo método _List[string] Format()_ é então usado para iniciar uma instância da classe _Evaluator_. O método _void Evaluate()_ é chamado em main.cpp que por sua vez chama _void ExpressionToPostfix()_. Este método itera sobre os items da lista _expression_ onde está armazenada a expressão na notação infixa, e usa o algoritmo Shunting Yard para criar outra lista _postfix_ que representa a expressão na notação pós-fixa. Durante este processo, o método _int OperatorPrecedence(string)_ é chamado para determinar a precedênia dos operadores na expressão.

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

Uma vez realizada a conversão, o método _void EvaluatePostfix()_ é chamado. Este itera sobre os itens de _postfix_, adicionando operandos à pilha _solveStack_. Quando um operador é achado, os dois últimos operandos de _solveStack_ são removidos e o método _int Operations(int, int, string)_ é chamado para realizar a operação, com o resultado sendo adicionando à _solveStack_. Paralelamente, o método também atualiza a pilha de bool _boolPositions_ que identifica quais operandos na _solveStack_ são booleanos e quais são inteiros. Ao final de uma execução do método sem erros, o único elemento restante na _solveStack_ será o resultado da expressão.

### Identificação de erros

O método _void EvaluatePostfix()_ irá identificar um erro caso ocorra uma operação entre int e bool, caso um operador seja usado com o tipo inapropriado de operando ou caso haja uma divisão por 0. Em todos esses casos a iteração sobre _postfix_ será interrompida e o bool _error_ será modificado para true.

### Impressão do Resultado

Após a avaliação, a instância de _Evaluator_ é deletada e o método destrutor da classe _Evaluator_ imprime o resultado. Caso o bool _error_ seja false e o resultado for booleano, "true" ou "false" são impressos, caso o resultando não seja booleano, o valor numérico é impresso e caso _error_ seja true, "error" é impresso.

```
1
8
-2
1
true
false
error
```
