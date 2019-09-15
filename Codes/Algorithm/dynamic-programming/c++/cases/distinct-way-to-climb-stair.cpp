/*
    Distinct Way to CLimb Stairs
    Archive of Reversing.ID
    Algorithm (Dynamic Programming)
    
Compile:
    [clang]
    $ clang++ distinct-way-to-climb-stair.cpp -o distinct-way-to-climb-stair

    [gcc]
    $ g++ distinct-way-to-climb-stair.cpp -o distinct-way-to-climb-stair

    [msvc]
    $ cl distinct-way-to-climb-stair.cpp

Run:
    $ distinct-way-to-climb-stair
*/
#include <cstring>

/*
Masalah:
    Terdapat sebuah tangga dengan N anak tangga. Jika seseorang dapat menaiki anak tangga
    dengan melewati satu atau dua anak tangga per langkah, berapa banyak cara unik yang 
    dapat ditempuh untuk mencapai puncak?

Solusi:
    Mirip dengan fibonacci.

    Terdapat kondisi langkah tersisa sebelum mencapai puncak, yaitu:
    - 1 langkah menuju puncak
    - 2 langkah menuju puncak

    Berapa cara yang ada sehingga tersisa 1 langkah (atau 2 langkah) menuju puncak?

*/

// ======================================================================================

/** Recursive Solution -- Memoization **/

size_t algorithm(size_t lookup[], size_t idx)
{
    if (lookup[idx] == 0)
    {
        lookup[idx] = 
            // cara yang digunakan sebelumnya hingga tersisa 1 langkah ke puncak
            algorithm(lookup, idx - 1) + 

            // cara yang digunakan sebelumnya hingga tersisa 2 langkah ke puncak
            algorithm(lookup, idx - 2);
    }

    return lookup[idx];
}

// Wrapper pemanggilan ke fungsi DP
size_t algorithm(size_t N)
{
    size_t lookup[N + 1];
    size_t result = 0;

    lookup[0] = 0;  // cara yang digunakan untuk melewati 0 anak tangga
    lookup[1] = 1;  // cara yang digunakan untuk melewati 1 anak tangga
    lookup[2] = 2;  // cara yang digunakan untuk melewati 2 anak tangga
    
    // inisialisasi tabel
    memset(lookup, 0, sizeof(lookup));

    return algorithm(lookup, N);
}

// ======================================================================================

/** Iterative Solution -- Tabulation **/

size_t algorithm(size_t N)
{
    size_t table[N + 1];
    size_t result = 0;

    table[0] = 0;  // cara yang digunakan untuk melewati 0 anak tangga
    table[1] = 1;  // cara yang digunakan untuk melewati 1 anak tangga
    table[2] = 2;  // cara yang digunakan untuk melewati 2 anak tangga

    for (size_t i = 3; i <= N; i++)
        table[i] = table[i - 1] + table[i - 2];
    
    return table[N];
}