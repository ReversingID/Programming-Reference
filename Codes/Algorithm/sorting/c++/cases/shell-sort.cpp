/*
    Shell Sort
    Archive of Reversing.ID
    Algorithm (Sorting)
    
Compile:
    [clang]
    $ clang++ shell-sort.cpp -o shell-sort

    [gcc]
    $ g++ shell-sort.cpp -o shell-sort

    [msvc]
    $ cl shell-sort.cpp

Run:
    $ shell-sort
*/


/*
    Implementasi Shell Sort.
*/

// ======================================================================================

template <typename T>
void swap(T & a, T & b)
{
    T t = b;
    b = a;
    a = t;
}

template <typename T>
void algorithm(T arr[], size_t size)
{
    ssize_t i, j;
    ssize_t d = size;
    bool flag = true;
    
    while (flag && d > 1)
    {
        flag = false;
        d = (d + 1) / 2;

        for (i = 0; i < size - d; i++)
        {
            if (arr[i + d] < arr[i])
            {
                swap(arr[i + d], arr[i]);
                flag = true;
            }
        }
    }
}