/*
    Binomial Coefficient
    Archive of Reversing.ID
    Algorithm (Dynamic Programming)
    
Compile:
    [clang]
    $ clang++ binomial-coefficient.cpp -o binomial-coefficient

    [gcc]
    $ g++ binomial-coefficient.cpp -o binomial-coefficient

    [msvc]
    $ cl binomial-coefficient.cpp

Run:
    $ binomial-coefficient
*/
#include <cstring>

/*
    Binomial Coefficient didefinisikan sebagai:

    C(n, k) = C(n - 1, k - 1) + C(n - 1, k)
    C(n, 0) = C(n, n) = 1

    Note: rumus Kombinasi
    Note: bilangan segitiga pascal juga merupakan binomial

Masalah:
    Diberikan bilangan bulat positif n dan k. Tentukan Binomial Coefficient dari C(n, k)
*/

// ======================================================================================

/** Iterative Solution -- Tabulation **/

int algorithm(size_t N, size_t K)
{
    // lookup table
    int table[N + 1][K + 1];
    size_t batas;

    // bangun solusi
    for (size_t i = 0; i <= N; i++)
    {
        batas = std::min(i, K);
        for (size_t j = 0; j <= batas; j++)
        {
            if (j == 0 || j == i)
                table[i][j] = 1;
            else 
                table[i][j] = 
                    table[i - 1][j - 1] + 
                    table[i - 1][j];
        }
    }

    return table[N][K];
}

// ======================================================================================

/** Iterative Solution -- Tabulation with Space Optimization **/

// Perhitungan dilakukan per baris dengan baris saat ini diturunkan dari baris sebelumnya

int algorithm(size_t N, size_t K)
{
    // lookup table
    int table[K + 1];
    size_t batas;

    // setup nilai awal
    memset(table, 0, sizeof(table));

    table[0] = 1;

    // bangun solusi
    for (size_t i = 1; i <= N; i++)
    {
        batas = std::min(i, K);
        for (size_t j = batas; j > 0; j--)
            table[j] = table[j] + table[j - 1];
    }

    return table[K];
}