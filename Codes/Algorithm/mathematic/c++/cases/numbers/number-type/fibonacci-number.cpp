/*
    Fibonacci Number
    Archive of Reversing.ID
    Algorithm (Mathematics/Numbers)
    
Compile:
    [clang]
    $ clang++ fibonacci-number.cpp -o fibonacci-number

    [gcc]
    $ g++ fibonacci-number.cpp -o fibonacci-number

    [msvc]
    $ cl fibonacci-number.cpp

Run:
    $ fibonacci-number
*/

/*
    Fibonacci Number adalah bilangan-bilangan yang menjadi suku dalam baris fibonacci.

    Fibonacci memenuhi sistem persamaan berikut:
        F[0] = 0
        F[1] = 1
        F[N] = F[N - 1] + F[N - 2]

Baris fibonacci:
    1, 1, 2, 3, 5, 8, 13, 21, 34, ...
*/

// ======================================================================================

/*
    Iterative Solution
    Testing
    Periksa apakah suatu bilangan merupakan Fibonacci Number.
*/

bool algorithm(size_t num)
{
    // suku-suku fibonacci
    size_t a = 0, b = 1, c;

    // bangkitkan suku-suku fibonacci
    while (c < num && c != num)
    {
        c = a + b;
        a = b;
        b = c;
    }

    // periksa apakah c dan numb bernilai sama.
    return (c == num);
}

// ======================================================================================

/*
    Iterative Solution
    N-th Term Generator
    Bangkitkan suku ke-N
*/

size_t algorithm(size_t N)
{
    // suku-suku fibonacci
    size_t a = 0, b = 1, c;

    if (N == 0) return a;

    // bangkitkan suku-suku fibonacci
    for (size_t ctr = 1; ctr <= N; ctr++)
    {
        c = a + b;
        a = b;
        b = c;
    }

    // kembalikan c sebagai suku ke N
    return c;
}

// ======================================================================================

/*
    Recursive Solution
    N-th Term Generator
    Bangkitkan suku ke-N
*/

size_t algorithm(size_t lookup[], size_t N)
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
size_t algorithm(size_t N)
{
    // deklarasi array untuk menyimpan hasil komputasi per subproblem
    size_t lookup[N + 1];

    // setup nilai awal
    lookup[0] = 0;
    lookup[1] = 1;
    
    for (size_t i = 2; i < N; i++)
        lookup[i] = 0;

    // bangun solusi
    return algorithm(lookup, N);
}

// ======================================================================================

/*
    Iterative Solution
    N-th Term Generator
    Bangkitkan suku ke-N
*/

size_t algorithm(size_t N)
{
    // deklarasi array untuk menyimpan hasil komputasi per subproblem
    size_t table[N + 1];

    // setup nilai awal
    table[0] = 0;
    table[1] = 1;

    // bangun solusi
    for (size_t i = 2; i <= N; i++)
        table[i] = table[i - 1] + table[i - 2];
    
    return table[N];
}

size_t algorithm(size_t N)
{
    // suku-suku fibonacci
    size_t a = 0, b = 1, c;

    // bangkitkan suku-suku fibonacci
    for (size_t ctr = 1; ctr <= N; ctr++)
    {
        c = a + b;
        a = b;
        b = c;
    }

    // kembalikan c sebagai suku ke N
    return c;
}