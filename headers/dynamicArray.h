#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H
using namespace std;

template <class T>
class DynamicArray
{
    // Espaço alocado para a array
    int maxSize;

    // Método para alocar mais espaçao para a array
    void expand();

    // Checa se a objeto está cheia para chamar o método expand()
    inline bool isFull() { return currentSize == maxSize; }

protected:
    // Pointer para a array que armazena os elementos da objeto
    T *arr;

    // Número de items na objeto
    int currentSize;

public:
    // Construtor
    DynamicArray();

    // Adiciona item em posição especificada
    void append(T item, int idx);

    // Adiciona item no final da array
    void append(T item);

    // Acessa último item da array
    inline T &back() { return arr[currentSize - 1]; }

    // Retorna número de items na array
    inline int length() { return currentSize; };

    // Libera espaço ocupado na memória pela array
    inline void free() { delete[] arr; }

    // Debug
    void print();
};
#endif
