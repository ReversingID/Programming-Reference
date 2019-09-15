/*
    Counting Inversions
    Archive of Reversing.ID
    Algorithm (Divide and Conquer)
    
Compile:
    [clang]
    $ clang++ counting-inversions.cpp -o counting-inversions

    [gcc]
    $ g++ counting-inversions.cpp -o counting-inversions

    [msvc]
    $ cl counting-inversions.cpp

Run:
    $ counting-inversions
*/
#include <cstdint>

/*
Masalah:
    Diberikan sebuah array dengan n elemen. Tentukan seberapa jauh (atau dekat) array
    tersebut dari kondisi terurut.

    Jika array telah terurut maka inversion count bernilai 0.
    Jika array terurut secara terbalik maka inversion count bernilai maksimum.
    Dua element arr[i] dan arr[j] membentuk inversion jika arr[i] > arr[j] dan i < j

Contoh:
    baris 2, 4, 1, 3, 5 memiliki tiga inversion: (2, 1), (4, 1), (4, 3)
*/

// ======================================================================================

template <typename T>
int merge(T arr[], T arr2[], size_t left, size_t mid, size_t right)
{
    size_t i, j, k;
    int    inv_count = 0;

    i = k = left;
    j = mid;

    while ((i <= mid - 1) && (j <= right))
    {
        if (arr[i] <= arr[j])
            arr2[k++] = arr[i++];
        else 
        {
            arr2[k++] = arr[j++];

            inv_count = inv_count + (mid - i);
        }
    }

    // salin elemen tersisa di subarray kiri jika ada
    while (i <= mid - 1)
        arr2[k++] = arr[i++];
    
    // salin elemen tersisa di subarray kanan jika ada
    while (j <= right)
        arr2[k++] = arr[j++];
    
    // salin kembali elemen yang telah disatukan ke array awal
    for (i = left; i <= right; i++)
        arr[i] = arr2[i];
    
    return inv_count;
}

template <typename T>
int algorithm(T arr[], T arr2[], size_t left, size_t right)
{
    int inv_count = 0;
    if (right > left)
    {
        /*
        Divide.
        Membagi array menjadi dua partisi.
        */
        size_t mid  = (left + right) / 2;

        inv_count  = algorithm(arr, arr2, left,     mid);
        inv_count += algorithm(arr, arr2, mid + 1, right);

        /*
        Combine.
        Menyatukan hasil yang ada dari dua partisi.
        */        
        inv_count += merge(arr, arr2, left, mid + 1, right);
    }
    return inv_count;
}

template <typename T>
int algorithm(T arr[], size_t N)
{
    T arr2[N];
    return algorithm(arr, arr2, 0, N - 1);
}