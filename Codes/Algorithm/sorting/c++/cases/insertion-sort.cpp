/*
    Insertion Sort
    Archive of Reversing.ID
    Algorithm (Sorting)
    
Compile:
    [clang]
    $ clang++ insertion-sort.cpp -o insertion-sort

    [gcc]
    $ g++ insertion-sort.cpp -o insertion-sort

    [msvc]
    $ cl insertion-sort.cpp

Run:
    $ insertion-sort
*/


/*
    Implementasi Insertion Sort.

    Array dibangun dengan cara penyusunan ulang.
    Elemen array dibandingkan satu sama lain secara sekuensial dan disusun secara simultan
    dengan urutan tertentu.
*/

// ======================================================================================

/** Recursive Solution **/

template <typename T>
void algorithm(T arr[], size_t size)
{
    // base case adalah 1 elemen
    if (size > 1)
    {
        // urutkan (size - 1) elemen terlebih daulu
        algorithm(arr, size - 1);

        // sisipkan elemen terakhir ke posisi yang tepat di array terurut
        T key = arr[size - 1];
        size_t j = size - 2;

        // pindahkan elemen [0 .. j-1] yang lebih besar dari key
        for (; j >= 0 && arr[j] > key; j--)
            arr[j + 1] = arr[j];
        
        arr[j + 1] = key;
    }
}

// ======================================================================================

/** Iterative Solution **/

template <typename T>
void algorithm(T arr[], size_t size)
{
    ssize_t i, j;
    T key;

    for (i = 1; i < size; i++)
    {
        // ambil key sebagai pivot
        key = arr[i];
        
        // geser semua elemen yang lebih besar daripada key ke kanan.
        for (j = i - 1; j >= 0 && arr[j] > key; j--)
            arr[j + 1] = arr[j];
        
        arr[j + 1] = key;
    }
}