/*
    Merge Sort
    Archive of Reversing.ID
    Algorithm (Sorting)
    
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
    Implementasi Merge Sort.

    Kode yang sama ada di bagian Divide and Conquer.
*/

// ======================================================================================

template <typename T>
void algorithm(T arr[], size_t low, size_t high)
{
    if (high > low)
    {
        size_t size = high - low + 1;
        size_t mid  = low + (high - low) / 2;

        algorithm(arr, low,     mid);
        algorithm(arr, mid + 1, high);

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
void algorithm(T arr[], size_t size)
{
    algorithm(arr, 0, size - 1);
}