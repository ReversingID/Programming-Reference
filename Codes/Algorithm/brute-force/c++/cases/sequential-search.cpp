/*
    Sequential Search
    Archive of Reversing.ID
    Algorithm (Brute-Force)
    
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
Masalah:
    Diberikan senarai beranggotakan N buah elemen. Tentukan apakah X terdapat
    di dalam senarai tersebut.

Solusi:
    - Ambil elemen pertama dari senarai
    - Lakukan perbandingan dengan X (nilai yang dicari)
    - Jika keduanya bernilai sama, kembalikan index
    - Ulangi pencarian untuk elemen berikutnya hingga akhir jika belum ketemu.
    - Jika tidak ada elemen yang memenuhi kriteria, kembalikan nilai -1
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