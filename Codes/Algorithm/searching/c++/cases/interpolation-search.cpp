/*
    Interpolation Search
    Archive of Reversing.ID
    Algorithm (Searching)

Compile:
    [clang]
    $ clang++ interpolation-search.cpp -o interpolation-search

    [gcc]
    $ g++ interpolation-search.cpp -o interpolation-search

    [msvc]
    $ cl interpolation-search.cpp

Run:
    $ interpolation-search
*/

/*
    Implementasi Interpolation Search.

    Kode yang sama ada di bagian Divide and Conquer.
*/

// ======================================================================================

template <typename T>
ssize_t algorithm(T arr[], size_t low, size_t high, T val)
{
    // Pencarian tidak berhasil karena ruang pencarian sudah tidak ada.
    if (low > high)
        return -1;
    else 
    {
        // Decrease
        size_t mid = (low + high)/2;
        T v = arr[mid];

        if (v == val)
            return mid;
        else if (val < v)
            return algorithm(arr, low, mid - 1, val);
        else 
            return algorithm(arr, mid + 1, high, val);
    }
}

template <typename T>
size_t algorithm(T arr[], size_t size, T val)
{
    return algorithm(arr, 0, size - 1, val);
}

// ======================================================================================

template <typename T>
ssize_t algorithm(T arr[], size_t size, T val)
{
    size_t pos;
    size_t low = 0, high = size - 1;
    T delta, v;

    while (low <= high && val >= arr[low] && val <= arr[high])
    {
        delta = (val - arr[low]) / (arr[high] - arr[low]);
        pos   = low + floor((high - low) * delta);
        v     = arr[pos];

        if (v == val)
            return pos;
        else if (val < v)
            high = pos - 1;
        else 
            low = pos + 1;
    }

    return -1;
}