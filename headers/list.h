#ifndef LIST_H
#define LIST_H
using namespace std;

template <typename T>
class List
{
    T *arr;
    int currentSize;
    int maxSize;

    void expand()
    {
        maxSize *= 2;
        T *temporaryArray = new T[maxSize];

        for (int i = 0; i < currentSize; i++)
        {
            temporaryArray[i] = arr[i];
        }
        delete[] arr;
        arr = temporaryArray;
    }

    inline bool isFull() { return currentSize == maxSize; };

public:
    List()
    {
        arr = new T[1];
        maxSize = 1;
        currentSize = 0;
    }

    void insert(T item, int idx)
    {
        if (isFull())
        {
            expand();
        }
        for (int i = currentSize; i > idx; i--)
        {
            arr[i] = arr[i - 1];
        }
        arr[idx] = item;
        currentSize++;
    }

    void insert(T item)
    {
        if (isFull())
        {
            expand();
        }
        arr[currentSize] = item;
        currentSize++;
    }

    T &operator[](int idx)
    {
        return arr[idx];
    }

    T pop()
    {
        currentSize--;
        return arr[currentSize];
    }

    void print()
    {
        for (auto j = 0; j < currentSize; j++)
        {
            cout << arr[j] << " ";
        }
        cout << endl;
    }

    inline T &back() { return arr[currentSize - 1]; }

    inline int length() { return currentSize; };
};
#endif