#ifndef LIST_H
#define LIST_H
using namespace std;

template <typename T>
class List
{
    T *arr;
    int size;

public:
    List()
    {
        arr = new T[0];
        size = 0;
    }

    void insert(T item)
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

    void insert(T item, int idx)
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

    T *at(int idx)
    {
        if (idx < 0 || idx >= size)
        {
            throw invalid_argument("Indíce fora da lista");
        }
        return &arr[idx];
    }

    T pop()
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

    ~List()
    {
        delete[] arr;
    }

    inline int length() { return size; };
};
#endif