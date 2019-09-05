/*
    Exponential Search
    Archive of Reversing.ID
    Algorithm (Searching)
    
Compile:
    [clang]
    $ clang++ exponential-search.cpp -o exponential-search

    [gcc]
    $ g++ exponential-search.cpp -o exponential-search

    [msvc]
    $ cl exponential-search.cpp

Run:
    $ exponential-search
*/

/*
    Implementasi Exponential Search.

    Exponential Search adalah algoritma pencarian untuk senarai terurut.
    Ide dasarnya adalah memeriksa sesedikit mungkin elemen dengan melompat beberapa langkah
    ke depan (melewati beberapa elemen).

Langkah:
    - cari rentang (blok) dimana elemen kemungkinan berada
    - lakukan Binary Search pada blok tersebut. 
*/

// ======================================================================================

template <typename T>
T min(T a, T b)
{
    if (a < b)  return a;
    else        return b;
}

/* Binary Search - digunakan untuk mencari elemen di block */
template <typename T>
bool search(T arr[], size_t low, size_t high, T val, size_t & idx)
{
    // Pencarian tidak berhasil karena ruang pencarian sudah tidak ada.
    if (low > high)
        return false;
    else 
    {
        // Decrease
        size_t mid = (low + high)/2;
        T v = arr[mid];

        if (v == val)
        {
            idx = mid;
            return true;
        }
        else if (val < v)
            return search(arr, low, mid - 1, val, idx);
        else 
            return search(arr, mid + 1, high, val, idx);
    }
}

template <typename T>
bool algorithm(T arr[], size_t size, T val, size_t & idx)
{
    idx = 0;

    // Jika val ditemukan sebagai elemen pertama
    if (arr[0] == val)
        return 0;
    
    // Cari rentang untuk melakukan binary search dengan doubling berturut-turut
    size_t i = 1;
    while (i < size && arr[i] <= val)   i = i * 2;

    // lakukan binary search untuk mencari val di blok
    return search(arr, i / 2, min(i, size), val, idx);
}