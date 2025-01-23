#ifndef STACK_H
#define STACK_H
#include "dynamicArray.h"
using namespace std;

template <class T>
class Stack : public DynamicArray<T>
{
public:
    // Remove e retorna último item da pilha
    inline T pop() { return this->arr[--this->currentSize]; };
};

#endif