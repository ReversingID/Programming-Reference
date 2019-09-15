/*
    Bell Numbers
    Archive of Reversing.ID
    Algorithm (Dynamic Programming)
    
Compile:
    [clang]
    $ clang++ bell-numbers.cpp -o bell-numbers

    [gcc]
    $ g++ bell-numbers.cpp -o bell-numbers

    [msvc]
    $ cl bell-numbers.cpp

Run:
    $ bell-numbers
*/

/*
    Bell numbers adalah barisan angka natural yang muncul di beberapa permasalahan
    menarik bidang pencacahan.

    B(n) = sum S(n, k)
    S(n + 1, k) = k * S(n, k) + S(n, k - 1)

Masalah:
    Tentukan suku ke-n dari baris Bell.
*/

// ======================================================================================

/** Iterative Solution -- Tabulation **/

size_t algorithm(size_t N)
{
    // lookup table
    int table[N + 1][N + 1];

    // setup nilai awal
    table[0][0] = 1;
    
    for (size_t i = 1; i <= N; i++)
    {
        // secara eksplisit mengisi untuk j = 0
        table[i][0] = table[i - 1][i - 1];

        for (size_t j = 1; j <= i; j++)
            table[i][j] = table[i - 1][j - 1] + table[i][j - 1];
    }

    return table[N][0];
}