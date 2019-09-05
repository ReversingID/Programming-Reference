/*
    Exchange Sort
    Archive of Reversing.ID
    Algorithm (Sorting)
    
Compile:
    [clang]
    $ clang++ exchange-sort.cpp -o exchange-sort

    [gcc]
    $ g++ exchange-sort.cpp -o exchange-sort

    [msvc]
    $ cl exchange-sort.cpp

Run:
    $ exchange-sort
*/


/*
    Implementasi Exchange Sort.

    Mirip dengan Bubble Sort.
    Exchange Sort membandingkan elemen pertama dengan setiap elemen berikutnya di array.
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
    
    for (i = 0; i < size - 1; i++)
        for (j = i + 1; j < size; j++)
            if (arr[i] > arr[j])
                swap(arr[i], arr[j]);
}