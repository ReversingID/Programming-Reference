/*
    Permutation Coefficient
    Archive of Reversing.ID
    Algorithm (Dynamic Programming)
    
Compile:
    [clang]
    $ clang++ permutation-coefficient.cpp -o permutation-coefficient

    [gcc]
    $ g++ permutation-coefficient.cpp -o permutation-coefficient

    [msvc]
    $ cl permutation-coefficient.cpp

Run:
    $ permutation-coefficient
*/
#include <cstring>

/*
    Permutation Coefficient didefinisikan sebagai:

    P(n, k) = n! / (n-k)!

    solusi rekursif:

    P(n, k) = P(n - 1, k) + k * P(n - 1, k - 1)
    P(n, 0) = 1

Masalah:
    Diberikan bilangan bulat positif n dan k. Tentukan Permutation Coefficient dari C(n, k)
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
            if (j == 0)
                table[i][j] = 1;
            else 
                table[i][j] = 
                    table[i - 1][j] + 
                    (j * table[i - 1][j - 1]);
        }
    }

    return table[N][K];
}

// ======================================================================================

/** Iterative Solution -- Tabulation with Space Optimization **/

/*
Misalkan terdapat array 1 dimensi yang menghitung faktorial N.
Kita dapat menggunakan nilai faktorial tersebut untuk mengaplikasikan P(n, k) = n!/(n-k)!
*/

int algorithm(size_t N, size_t K)
{
    // lookup table
    int table[N + 1];
    size_t batas;

    // setup nilai awal
    table[0] = 1;

    // bangun solusi
    for (size_t i = 1; i <= N; i++)
        table[i] = i * table[i - 1];

    return table[N] / table[N - K];
}