/*
    Selection Sort
    Archive of Reversing.ID
    Algorithm (Sorting)
    
Compile:
    [clang]
    $ clang++ selection-sort.cpp -o selection-sort

    [gcc]
    $ g++ selection-sort.cpp -o selection-sort

    [msvc]
    $ cl selection-sort.cpp

Run:
    $ selection-sort
*/


/*
    Implementasi Selection Sort.

    Array dibangun dengan cara penyusunan ulang.
    Elemen array dibandingkan satu sama lain secara sekuensial dan disusun secara simultan
    dengan urutan tertentu.

Langkah:
    - mencari nilai terkecil pada suatu rentang
    - menukar elemen terkecil dengan elemen pertama pada rentang
    - memperkecil rentang dengan mengeluarkan elemen pertama dari rentang dan ulangi
      operasi dari langkah pertama.
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
    size_t i, j, min_idx;

    // perlahan memindahkan batas dari unsorted array
    for (i = 0; i < size - 1; i++)
    {
        // cari elemen dengna nilai minimum
        min_idx = i;
        for (j = i + 1; j < size; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;
        
        swap(arr[min_idx], arr[i]);
    }
}