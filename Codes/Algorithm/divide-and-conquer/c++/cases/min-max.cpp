/*
    Min or Max Value
    Archive of Reversing.ID
    Algorithm (Divide and Conquer)
    
Compile:
    [clang]
    $ clang++ min-max.cpp -o min-max

    [gcc]
    $ g++ min-max.cpp -o min-max

    [msvc]
    $ cl min-max.cpp

Run:
    $ min-max
*/

/*
Masalah:
    Diberikan senarai beranggotakan N buah bilangan bulat. Cari elemen terkecil dan
    terbesar di dalam elemen tersebut.
*/

// ======================================================================================

template <typename T>
void algorithm(T arr[], size_t low, size_t high, T & min, T & max)
{
    // Conquer
    if (low == high)
        min = max = arr[low];
    else if (high - low == 1)
    {
        if (arr[low] < arr[high])
        {
            min = arr[low];
            max = arr[high];
        }
        else 
        {
            min = arr[high];
            max = arr[low];
        }
    }
    else
    {
        T min2, max2;
        size_t  mid = (low + high) / 2;

        // Divide
        algorithm(arr, low, mid, min, max);
        algorithm(arr, mid + 1, high, min2, max2);

        // Merge
        if (min2 < min) min = min2;
        if (max2 > max) max = max2;
    }
}

template <typename T>
void algorithm(T arr[], size_t N, T & min, T & max)
{
    algorithm(arr, 0, N - 1, min, max);
}