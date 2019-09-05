/*
    Comb Sort
    Archive of Reversing.ID
    Algorithm (Sorting)
    
Compile:
    [clang]
    $ clang++ comb-sort.cpp -o comb-sort

    [gcc]
    $ g++ comb-sort.cpp -o comb-sort

    [msvc]
    $ cl comb-sort.cpp

Run:
    $ comb-sort
*/


/*
    Implementasi Comb Sort
    
    Peningkatan dari Bubble Sort.
    Bubble Sort selalu membandingkan nilai yang bertetangga. Sementara Comb Sort menggunakan
    jarak ukuran lebih dari 1. 
*/

// ======================================================================================

template <typename T>
void swap(T & a, T & b)
{
    T t = b;
    b = a;
    a = t;
}

int getNextGap(int gap)
{
    // perkecil gap dengan shrink factor
    gap = (gap * 10) / 13;

    if (gap < 1)
        return 1;
    
    return gap;
}

// ======================================================================================

/** Iterative Solution **/

void algorithm(int arr[], size_t size)
{
    // inisialisasi gap
    size_t   gap = size;
    bool swapped = true;

    while (gap != 1 || swapped)
    {
        // cari gap berikutnya
        gap = getNextGap(gap);

        // inisialisasi swapp
        swapped = false;

        // bandingkan semua elemen dengan gap sekarang
        for (size_t i = 0; i < size - gap; i++)
        {
            if (arr[i] > arr[i + gap])
            {
                swap(arr[i], arr[i + gap]);
                swapped = true;
            }
        }
    }
}