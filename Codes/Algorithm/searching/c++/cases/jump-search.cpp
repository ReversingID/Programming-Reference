/*
    Jump Search
    Archive of Reversing.ID
    Algorithm (Searching)
    
Compile:
    [clang]
    $ clang++ jump-search.cpp -o jump-search

    [gcc]
    $ g++ jump-search.cpp -o jump-search

    [msvc]
    $ cl jump-search.cpp

Run:
    $ jump-search
*/

/*
    Implementasi Jump Search.

    Jump Search adalah algoritma pencarian untuk senarai terurut.
    Ide dasarnya adalah memeriksa sesedikit mungkin elemen dengan melompat beberapa langkah
    ke depan (melewati beberapa elemen).

Langkah:
    - cari rentang (blok) dimana elemen kemungkinan berada
    - lakukan Sequential Search pada blok tersebut. 
*/

// ======================================================================================

template <typename T>
T min(T a, T b)
{
    if (a < b)  return a;
    else        return b;
}

/* Sequential Search - digunakan untuk mencari elemen di block */
template <typename T>
bool search(T arr[], size_t size, T val, size_t & idx)
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

// ======================================================================================

template <typename T>
bool algorithm(T arr[], size_t size, T val, size_t & idx)
{
    // Menentukan banyaknya langkah per lompatan
    size_t step = sqrt(size);

    // Mencari blok dimana elemen mungkin berada
    size_t prev = 0;
    size_t next = step;
    while (arr[min(next, size) - 1] < val)
    {
        prev = next;
        next += step;

        if (prev >= size)
            return false;
    }

    // lakukan sequential search untuk mencari val di blok
    if (search(&arr[prev], next - prev, val, idx))
    {
        idx += prev;
        return true;
    }

    return false;
}