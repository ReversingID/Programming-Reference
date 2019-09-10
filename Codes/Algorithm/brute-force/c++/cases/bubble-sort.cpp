/*
    Bubble Sort
    Archive of Reversing.ID
    Algorithm (Brute-Force)
    
Compile:
    [clang]
    $ clang++ bubble-sort.cpp -o bubble-sort

    [gcc]
    $ g++ bubble-sort.cpp -o bubble-sort

    [msvc]
    $ cl bubble-sort.cpp

Run:
    $ bubble-sort
*/


/*
    Implementasi Bubble Sort.

Langkah:
    - scan rentang array
    - pindahkan elemen besar menuju ujung.
*/

// ======================================================================================

template <typename T>
void swap(T & a, T & b)
{
    T t = b;
    b = a;
    a = t;
}

// ======================================================================================

/** Recursive Solution **/

template <typename T>
void algorithm(T arr[], size_t size)
{
    // base case adalah 1 elemen
    if (size > 1)
    {
        /*
        Melakukan satu pass Bubble Sort.
        Setelah ini, elemen terbesar akan dipindahkan ke akhir.
        */
        for (size_t i = 0; i < size - 1; i++)
            if (arr[i] > arr[i + 1])
                swap(arr[i], arr[i + 1]);
        
        // lakukan rekursi ke rentang array tersisa
        algorithm(arr, size - 1);
    }
}

// ======================================================================================

/** Iterative Solution **/

template <typename T>
void algorithm(T arr[], size_t size)
{
    for (size_t i = 0; i < size; i++)
        for (size_t j = 0; j < size - i - 1; j++)
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
}