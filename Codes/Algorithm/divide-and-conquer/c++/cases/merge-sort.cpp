/*
    Merge Sort
    Archive of Reversing.ID
    Algorithm (Divide and Conquer)
    
Compile:
    [clang]
    $ clang++ merge-sort.cpp -o merge-sort

    [gcc]
    $ g++ merge-sort.cpp -o merge-sort

    [msvc]
    $ cl merge-sort.cpp

Run:
    $ merge-sort
*/


/*
    Implementasi Merge Sort

    Membagi array menjadi dua bagian, melakukan operasi terhadap keduanya kemudian 
    menggabungkan dua bagian yang telah terurut.

Langkah:
    merge-sort(arr[], L, R)

    jika R > L
    - cari titik tengah untuk membagi array jadi dua bagian:
        M = (L+R)/2
    - panggil merge-sort untuk bagian pertama
        merge-sort(arr, L, M)
    - panggil merge-sort untuk bagian kedua
        merge-sort(arr, M+1, R)
    - gabung kedua bagian
        merge(arr, L, M, R)

*/
#include <memory>

// ======================================================================================

template <typename T>
void algorithm(T arr[], size_t low, size_t high)
{
    if (high > low)
    {
        /*
        Divide.
        Membagi array menjadi dua partisi.
        */
        size_t size = high - low + 1;
        size_t mid  = (low + high) / 2;

        algorithm(arr, low,     mid);
        algorithm(arr, mid + 1, high);

        /*
        Combine.
        Menyatukan hasil yang ada dari dua partisi.
        */
        // menampung hasil merge
        auto arr2 = std::make_unique<T[]>(size);

        size_t k = 0;
        size_t i = low;
        size_t j = mid + 1;

        while (i <= mid && j <= high)
        {
            if (arr[i] <= arr[j])
                arr2[k++] = arr[i++];
            else 
                arr2[k++] = arr[j++];
        }

        while (i <= mid)
            arr2[k++] = arr[i++];
        
        while (j <= high)
            arr2[k++] = arr[j++];
        
        for (k = 0; k < size; k++)
            arr[low + k] = arr2[k];
    }
}

template <typename T>
void algorithm(T arr[], size_t N)
{
    algorithm(arr, 0, N - 1);
}