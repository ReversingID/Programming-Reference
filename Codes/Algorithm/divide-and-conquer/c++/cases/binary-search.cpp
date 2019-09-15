/*
    Binary Search
    Archive of Reversing.ID
    Algorithm (Divide and Conquer)

    Decrease and Conquer.
    
Compile:
    [clang]
    $ clang++ binary-search.cpp -o binary-search

    [gcc]
    $ g++ binary-search.cpp -o binary-search

    [msvc]
    $ cl binary-search.cpp

Run:
    $ binary-search
*/

/*
Masalah:
    Diberikan sebuah array dengan elemen terurut. Tentukan apakah sebuah nilai ada di 
    dalam array tersebut.

Langkah:
    - bandingkan X dengan elemen pertengahan.
    - jika x bernilai sama, kembalikan index
    - jika tidak, bagi array jadi dua bagian
        - jika X bernilai lebih kecil daripada elemen tengah, cari di subarray kiri
        - jika X bernilai lebih besar daripada elemen tengah, cari di subarray kanan
*/

// ======================================================================================

/** Recursive Solution **/

template <typename T>
bool algorithm(T arr[], size_t low, size_t high, T val, size_t & idx)
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
            return algorithm(arr, low, mid - 1, val);
        else 
            return algorithm(arr, mid + 1, high, val);
    }
}

template <typename T>
bool algorithm(T arr[], size_t N, T val, size_t & idx)
{
    return algorithm(arr, 0, N - 1, val);
}

// ======================================================================================

/** Iterative Solution **/

template <typename T>
bool algorithm(T arr[], size_t N, T val, size_t & idx)
{
    size_t mid;
    size_t low = 0, high = N - 1;
    T v;

    while (low <= high)
    {
        mid = (low + high)/2;
        v   = arr[mid];

        if (v == val)
        {
            idx = mid;
            return true;
        }
        else if (val < v)
            high = mid - 1;
        else 
            low = mid + 1;
    }

    return false;
}