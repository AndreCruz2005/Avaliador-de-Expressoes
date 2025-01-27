#include <iostream>
#include <string>
#include "../headers/dynamicArray.h"

template <class T>
DynamicArray<T>::DynamicArray()
{
    // A array é iniciada com 8 espaços para reduzir a necessidade de expansões
    arr = new T[8];
    maxSize = 8;
    currentSize = 0;
}

template <class T>
void DynamicArray<T>::expand()
{ // Função para alocar mais espaço, é chamada quando todos os espaços da array estão ocupados

    // Cria um pointer para uma nova array com o dobro do espaço
    maxSize *= 2;
    T *temporary = new T[maxSize];

    // Copia items da array original para a nova array
    for (size_t i = 0; i < currentSize; i++)
    {
        temporary[i] = arr[i];
    }

    // Deleta a array original e aponta arr para a array expandida
    delete[] arr;
    arr = temporary;
}

template <class T>
void DynamicArray<T>::append(T item, int idx)
{
    if (isFull())
    {
        expand();
    }

    // Abre espaço para um novo item movendo todos os items que estão a direita do índice, 1 espaço
    for (size_t i = currentSize; i > idx; i--)
    {
        arr[i] = arr[i - 1];
    }

    arr[idx] = item;
    currentSize++;
}

template <class T>
void DynamicArray<T>::append(T item)
{
    if (isFull())
    {
        expand();
    }

    arr[currentSize] = item;
    currentSize++;
}

template <class T>
void DynamicArray<T>::print()
{ // Debug
    for (size_t j = 0; j < currentSize; j++)
    {
        cout << arr[j] << endl;
    }
    cout << endl;
}

template class DynamicArray<int>;
template class DynamicArray<bool>;
template class DynamicArray<string>;
