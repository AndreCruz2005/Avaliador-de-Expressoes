#ifndef LIST_H
#define LIST_H
#include "dynamicArray.h"
using namespace std;

template <class T>
class List : public DynamicArray<T>
{
public:
    // Sobrecarga do operador [] para acessar item da lista
    inline T &operator[](int idx) { return this->arr[idx]; };
};

#endif