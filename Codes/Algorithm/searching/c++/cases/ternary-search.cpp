/*
    Ternary Search
    Archive of Reversing.ID
    Algorithm (Searching)

    Decrease and Conquer.
    
Compile:
    [clang]
    $ clang++ ternary-search.cpp -o ternary-search

    [gcc]
    $ g++ ternary-search.cpp -o ternary-search

    [msvc]
    $ cl ternary-search.cpp

Run:
    $ ternary-search
*/

/*
    Implementasi Ternary Search.

    Serupa dengan Binary Search namun membagi array menjadi 3 ruas dengan 2 titik tengah.
*/

// ======================================================================================

/** Recursive Solution **/

template <typename T>
bool algorithm(T arr[], size_t low, size_t high, T val, size_t & idx)
{
    if (high >= low)
    {
        // Decrease
        size_t mid1 = low + (high - low)/3;
        size_t mid2 = mid1 + (high - low)/3;
        
        if (arr[mid1] == val)
        {
            idx = mid1;
            return true;
        }
        else if (arr[mid2] == val)
        {
            idx = mid2;
            return true;
        }
        else if (arr[mid1] > val)
            return algorithm(arr, low, mid1 - 1, val, idx);
        else if (arr[mid2] < val)
            return algorithm(arr, mid2 + 1, high, val, idx);
        else 
            return algorithm(arr, mid1 + 1, mid2 - 1, val, idx);
    }

    // Pencarian tidak berhasil karena ruang pencarian sudah tidak ada.
    return false;
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
    size_t mid1, mid2;
    size_t low = 0, high = size - 1;

    while (low <= high)
    {
        mid1 = low + (high - low)/3;
        mid2 = mid1 + (high - low)/3;
        
        if (arr[mid1] == val)
        {
            idx = mid1;
            return true;
        }
        else if (arr[mid2] == val)
        {
            idx = mid2;
            return true;
        }
        else if (arr[mid1] > val)
            high = mid1 - 1;
        else if (arr[mid2] < val)
            low = mid2 + 1;
        else 
        {
            low = mid1 + 1;
            high = mid2 - 1;
        }
    }

    return false;
}