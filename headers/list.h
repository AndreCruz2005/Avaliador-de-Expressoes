#ifndef LIST_H
#define LIST_H
using namespace std;

template <class T>
class List
{
    T *arr;          // Pointer para a array que armazena os elementos da lista
    int currentSize; // Número de items na lista
    int maxSize;     // Espaço alocado para a lista

    void expand()
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

    inline bool isFull() { return currentSize == maxSize; }

public:
    List()
    {
        arr = new T[1];
        maxSize = 1;
        currentSize = 0;
    }

    void append(T item, int idx)
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

    void append(T item)
    {
        if (isFull())
        {
            expand();
        }
        arr[currentSize] = item;
        currentSize++;
    }

    T &operator[](int idx)
    { // Sobrecarga do operador [] para acessar item
        return arr[idx];
    }

    T pop()
    { // Remove e retorna último item
        currentSize--;
        return arr[currentSize];
    }

    void print()
    { // Debug
        for (auto j = 0; j < currentSize; j++)
        {
            cout << arr[j] << " ";
        }
        cout << endl;
    }

    inline T &back() { return arr[currentSize - 1]; }

    inline int length() { return currentSize; };

    inline void free() { delete[] arr; }
};
#endif