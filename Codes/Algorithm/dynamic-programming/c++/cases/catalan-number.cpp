/*
    Nth Catalan Number
    Archive of Reversing.ID
    Algorithm (Dynamic Programming)
    
Compile:
    [clang]
    $ clang++ catalan-number.cpp -o catalan-number

    [gcc]
    $ g++ catalan-number.cpp -o catalan-number

    [msvc]
    $ cl catalan-number.cpp

Run:
    $ catalan-number
*/

/*
    Catalan numbers adalah barisan angka natural yang muncul di beberapa permasalahan
    menarik bidang pencacahan. 

    C(n) = sum C(i) * C(n - i - 1)

    Beberapa baris catalan adalah: 1, 1, 2, 5, 14, 42, 132, 429, ...

Masalah:
    Tentukan suku ke-n dari baris catalan.

*/

// ======================================================================================

/** Recursive Solution -- Memoization **/

size_t algorithm(int lookup[], size_t N)
{
    // periksa lookup table apabila hasil telah diketahui
    if (lookup[N] == 0)
    {
        size_t result = 0;
        for (size_t i = 2; i < N; i++)
            result += algorithm(i) * algorithm(n - i - 1);
        
        lookup[N] = result;
        return result;
    }

    return lookup[N];
}

/* wrapper pemanggilan fungsi DP */
size_t algorithm(size_t N)
{
    // deklarasi array untuk menyimpan hasil komputasi per subproblem
    size_t lookup[N + 1];

    // setup nilai awal
    lookup[0] = lookup[1] = 1;
    for (size_t i = 2; i < N; i++)
        lookup[i] = 0;

    // bangun solusi
    return algorithm(lookup, N);
}

// ======================================================================================

/** Iterative Solution -- Tabulation **/

size_t algorithm(size_t N)
{
    // deklarasi array untuk menyimpan hasil komputasi per subproblem
    int table[N + 1];

    // setup nilai awal
    table[0] = table[1] = 1;

    // isi tiap entry di table dengan formula rekursif
    for (size_t i = 2; i < N; i++)
    {
        table[i] = 0;
        for (size_t j = 0; j < i; j++)
            table[i] += table[j] * table[i - j - 1];
    }

    return table[N];
}