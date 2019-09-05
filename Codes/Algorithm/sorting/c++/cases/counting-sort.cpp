/*
    Counting Sort
    Archive of Reversing.ID
    Algorithm (Sorting)
    
Compile:
    [clang]
    $ clang++ counting-sort.cpp -o counting-sort

    [gcc]
    $ g++ counting-sort.cpp -o counting-sort

    [msvc]
    $ cl counting-sort.cpp

Run:
    $ counting-sort
*/
#include <cstring>      // untuk memset

#define RANGE   255

/*
    Implementasi Counting Sort.

    Melakukan sorting berdasarkan kemunculan key (key unik penanda nilai suatu elemen).
    Pengurutan dilakukan dengan perhitungan kemunculan key.

    Kelemahan:
    Hanya dapat melakukan pengurutan terhadap elemen bertipe bilangan bulat dengan rentang 
    nilai terbatas.
*/

// ======================================================================================

/** Iterative Solution **/

void algorithm(int arr[], size_t size)
{
    size_t i, j;
    int counter[RANGE + 1];
    
    // inisialisasi array dengan 0
    memset(counter, 0, sizeof(counter));

    // hitung kemunculan tiap elemen
    for (i = 0; i < size; i++)
        ++ counter[arr[i]];
    
    /* 
    iterasi dari awal hingga akhir, jika counter menunjukkan nilai positif maka proses
    sebagai elemen array
    */
    for (i = 0, j = 0; i <= RANGE; i++)
    {
        while (counter[i]--)
            arr[j++] = i;
    }
}