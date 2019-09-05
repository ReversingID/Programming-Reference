/*
    Sequential Search
    Archive of Reversing.ID
    Algorithm (Searching)
    
Compile:
    [clang]
    $ clang++ sequential-search.cpp -o sequential-search

    [gcc]
    $ g++ sequential-search.cpp -o sequential-search

    [msvc]
    $ cl sequential-search.cpp

Run:
    $ sequential-search
*/

/*
    Implementasi Sequential Search / Linear Search.

    Kode yang sama ada di bagian Brute Force
*/

// ======================================================================================

template <typename T>
bool algorithm(T arr[], size_t size, T val, size_t & idx)
{
    for (size_t i = 0; i < size; i++)
    {
        if (arr[i] == val)
        {
            idx = i;
            return true;
        }
    }

    return false;
}