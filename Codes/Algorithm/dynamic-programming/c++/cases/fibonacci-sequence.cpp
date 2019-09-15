/*
    Fibonacci Sequence
    Archive of Reversing.ID
    Algorithm (Dynamic Programming)

    Solusi Memoization dan Tabulation
    
Compile:
    [clang]
    $ clang++ fibonacci-sequence.cpp -o fibonacci-sequence

    [gcc]
    $ g++ fibonacci-sequence.cpp -o fibonacci-sequence

    [msvc]
    $ cl fibonacci-sequence.cpp

Run:
    $ fibonacci-sequence
*/

/*
Masalah:
    Baris Fibonacci didefinisikan memiliki hubungan rekursif dengan nilai elemen saat ini
    merupakan penjumlahan dua elemen sebelumnya.

        fib[0] = 1
        fib[1] = 1
        fib[n] = fib[n - 1] + fib[n - 2]
    
    Baris:
        0, 1, 1, 2, 3, 5, 8, 13, 21, 34, ...
*/

// ======================================================================================

/** Recursive Solution -- Memoization **/

// Lookup table didefinisikan dan diinisialisasi di wrapper

int algorithm(T lookup[], size_t N)
{
    if (N > 1 && lookup[N] == 0)
    {
        lookup[N] = 
            algorithm(lookup, N - 1) + 
            algorithm(lookup, N - 2);
    }

    return lookup[N];
}

/* Wrapper pemanggilan fungsi DP */
int algorithm(size_t N)
{
    // deklarasi array untuk menyimpan hasil komputasi per subproblem
    int lookup[N + 1];

    // setup nilai awal
    lookup[0] = 0;
    lookup[1] = 1;
    
    for (size_t i = 2; i < N; i++)
        lookup[i] = 0;

    // bangun solusi
    return algorithm(lookup, N);
}

// ======================================================================================

/** Iterative Solution -- Tabulation **/

int algorithm(size_t N)
{
    // deklarasi array untuk menyimpan hasil komputasi per subproblem
    int table[N + 1];

    // setup nilai awal
    table[0] = 0;
    table[1] = 1;

    // bangun solusi
    for (size_t i = 2; i <= N; i++)
        table[i] = table[i - 1] + table[i - 2];
    
    return table[N];
}

// ======================================================================================

/** Iterative Solution -- Tabulation with Minimum Variable **/

int algorithm(size_t N)
{
    // deklarasi variabel untuk menyimpan hasil komputasi per subproblem
    int a = 0, b = 1;
    int c;

    if (N == 0) return a;
    
    // bangun solusi
    for (size_t i = 0; i <= N; i++)
    {
        c = a + b;
        a = b;
        b = c;
    }

    return b;
}