#ifndef LIST_H
#define LIST_H
using namespace std;

template <typename T>
class List
{
    T *arr;

    int size;

public:
    List();
    ~List();
    void insert(T);
    void insert(T, int idx);
    T &at(int idx);
    T pop();
    inline int length();
};
#endif