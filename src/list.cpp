#include <iostream>
#include <string>
#include "../headers/list.h"
using namespace std;

template <typename T>
List<T>::List()
{
    arr = new T[1];
    size = 1;
}

template <typename T>
void List<T>::insert(T item)
{
    size++;
    T *newArr = new T[size];

    for (auto i = 0; i < size - 1; i++)
    {
        newArr[i] = arr[i];
    }

    newArr[size - 1] = item;

    delete[] arr;
    arr = newArr;
}

template <typename T>
void List<T>::insert(T item, int idx)
{
    if (idx < 0 || idx > size)
    {
        throw invalid_argument("Indíce fora da lista");
    }

    size++;
    T *newArr = new T[size];

    for (auto i = 0; i < size; i++)
    {
        if (i < idx)
        {
            newArr[i] = arr[i];
        }
        else if (i == idx)
        {
            newArr[i] = item;
        }
        else
        {
            newArr[i] = arr[i - 1];
        }
    }

    delete[] arr;
    arr = newArr;
}

template <typename T>
T &List<T>::at(int idx)
{
    if (idx < 0 || idx >= size)
    {
        throw invalid_argument("Indíce fora da lista");
    }
    return arr[idx];
}

template <typename T>
T List<T>::pop()
{
    T lastItem = arr[size - 1];

    size--;
    T *newArr = new T[size];

    for (auto i = 0; i < size; i++)
    {
        newArr[i] = arr[i];
    }

    delete[] arr;
    arr = newArr;

    return lastItem;
}

template <typename T>
inline int List<T>::length()
{
    return size;
}

template <typename T>
List<T>::~List()
{
    delete[] arr;
}

int main()
{

    List<string> listed;
    listed.insert("Ur mom");
    listed.insert("Ur dad");
    listed.insert("Ur sis");
    listed.insert("Ur bro");
    int len = listed.length();
    for (auto i = 0; i < len - 1; i++)
    {
        cout << listed.at(i) << endl;
    }
    return 0;
}