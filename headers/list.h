#ifndef LIST_H
#define LIST_H
using namespace std;

template <class T>
class List
{
    // Pointer para a array que armazena os elementos da lista
    T *arr;

    // Número de items na lista
    int currentSize;

    // Espaço alocado para a lista
    int maxSize;

    // Método para alocar mais espaçao para a list
    void expand();

    // Checa se a lista está cheia
    inline bool isFull() { return currentSize == maxSize; }

public:
    // Construtor
    List();

    // Adiciona item em posição especificada
    void append(T item, int idx);

    // Adiciona item no final da lista
    void append(T item);

    // Acessa item da lista
    T &operator[](int idx);

    // Remove e retorna último item da lista
    T pop();

    // Acessa último item da lista
    inline T &back() { return arr[currentSize - 1]; }

    // Retorna tamanho atual
    inline int length() { return currentSize; };

    // Libera espaço ocupado na memória pela array
    inline void free() { delete[] arr; }

    // Debug
    void print();
};
#endif