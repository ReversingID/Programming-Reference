/*
    Binary Search
    Archive of Reversing.ID
    Algorithm (Searching)

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
    Implementasi Binary Search.

    Kode yang sama ada di bagian Divide and Conquer.
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
            return algorithm(arr, low, mid - 1, val, idx);
        else 
            return algorithm(arr, mid + 1, high, val, idx);
    }
}

template <typename T>
bool algorithm(T arr[], size_t size, T val, size_t & idx)
{
    return algorithm(arr, 0, size - 1, val);
}

// ======================================================================================

/** Iterative solution **/

template <typename T>
bool algorithm(T arr[], size_t size, T val, size_t & idx)
{
    size_t mid;
    size_t low = 0, high = size - 1;
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