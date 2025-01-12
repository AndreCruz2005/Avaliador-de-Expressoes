#include <iostream>
#include <string>
#include "../headers/list.h"

template <class T>
List<T>::List()
{
    arr = new T[1];
    maxSize = 1;
    currentSize = 0;
}

template <class T>
void List<T>::expand()
{ // Função para alocar mais espaço

    // Cria um pointer para uma nova array com o dobro do espaço
    maxSize *= 2;
    T *temporary = new T[maxSize];

    // Copia items para a nova array
    for (int i = 0; i < currentSize; i++)
    {
        temporary[i] = arr[i];
    }

    // Substitui array
    delete[] arr;
    arr = temporary;
}

template <class T>
void List<T>::append(T item, int idx)
{
    if (isFull())
    {
        expand();
    }

    // Move os items a direita do novo item 1 espaço
    for (int i = currentSize; i > idx; i--)
    {
        arr[i] = arr[i - 1];
    }

    arr[idx] = item;
    currentSize++;
}

template <class T>
void List<T>::append(T item)
{
    if (isFull())
    {
        expand();
    }

    arr[currentSize] = item;
    currentSize++;
}

template <class T>
T &List<T>::operator[](int idx)
{ // Sobrecarga do operador [] para acessar item
    return arr[idx];
}

template <class T>
T List<T>::pop()
{ // Remove e retorna último item
    currentSize--;
    return arr[currentSize];
}

template <class T>
void List<T>::print()
{ // Debug
    for (auto j = 0; j < currentSize; j++)
    {
        cout << arr[j] << " ";
    }
    cout << endl;
}

template class List<int>;
template class List<bool>;
template class List<string>;
