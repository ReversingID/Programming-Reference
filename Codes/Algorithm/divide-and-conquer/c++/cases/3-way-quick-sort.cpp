/*
    3-Way Quick-Sort
    Archive of Reversing.ID
    Algorithm (Divide and Conquer)
    
Compile:
    [clang]
    $ clang++ 3-way-quick-sort.cpp -o 3-way-quick-sort

    [gcc]
    $ g++ 3-way-quick-sort.cpp -o 3-way-quick-sort

    [msvc]
    $ cl 3-way-quick-sort.cpp

Run:
    $ 3-way-quick-sort
*/
#include <cstdlib>

/*
Masalah:
    Pada algoritma Quick Sort sederhana, sebuah elemen dipilih sebagai pivot, array
    dipartisi berdasarkan pivot dan diurutkan secara rekursif.

    Pada 3-Way Quick Sort, terdapat 3 partisi:
        - arr [0 .. i]: element kurang dari pivot
        - arr [i + 1 .. j - 1]: elemen bernilai sama dengan pivot
        - arr [j .. h]: elemen lebih dari pivot
    
    Implementasi ini mengambil elemen terakhir sebagai pivot.
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
void partition(T arr[], ssize_t low, ssize_t high, ssize_t & i, ssize_t & j)
{
    ssize_t p = i = low - 1;
    ssize_t q = j = high;
    T val = arr[high];

    while (true)
    {
        /*
        Dari kiri, cari elemen pertama yang bernilai lebih besar atau sama dengan val.
        Loop akan dipastikan berhenti karena val adalah elemen terakhir.
        */
        while (arr[++i] < val);

        /*
        Dari kanan, cari elemen pertama yang bernilai lebih kecil atau sama dengan val.
        */
        while (val < arr[--j])
            if (j == low)
                break;
        
        // jika i dan j bersilangan, operasi selesai.
        if (i >= j) break;

        // Swap, sehingga nilai lebih kecil ada di kiri dan nilai lebih besar ada di kanan.
        swap(arr[i], arr[j]);

        // Pindahkan semua nilai yang sama di kiri ke awal array 
        if (arr[i] == val)
        {
            p++;
            swap(arr[p], arr[i]);
        }

        // Pindahkan semua nilai yang sama di kanan ke akhir array
        if (arr[j] == val)
        {
            q--;
            swap(arr[j], arr[q]);
        }
    }

    // Pindahkan elemen pivot ke index yang tepat
    swap(arr[i], arr[high]);

    // Pindahkan semua nilai yang sama di kiri ke sebelah arr[i]
    j = i - 1;
    for (ssize_t k = low; k < p; k++, j--)
        swap(arr[k], arr[j]);
    
    // Pindahkan semua nilai yang sama di kanan ke sebelah arr[i]
    i = i + 1;
    for (ssize_t k = high - 1; k > q; k--, i++)
        swap(arr[i], arr[k]);
}

template <typename T>
void algorithm(T arr[], ssize_t low, ssize_t high)
{
    if (high > low)
    {
        ssize_t i, j;
        
        // partisi array
        partition(arr, low, high, i, j);

        algorithm(arr, low, j);
        algorithm(arr, i,   high);
    }
}

template <typename T>
void algorithm(T arr[], size_t N)
{
    algorithm(arr, 0, N - 1);
}