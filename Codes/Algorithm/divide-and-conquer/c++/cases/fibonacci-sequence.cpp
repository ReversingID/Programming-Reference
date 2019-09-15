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

// perkalian 2 matrix F dan M berukuran 2x2 dengan hasil disimpan kembali ke F
void multiply(int F[2][2], int M[2][2])
{
    int w = F[0][0] * M[0][0] + F[0][1] * M[1][0];
    int x = F[0][0] * M[0][1] + F[0][1] * M[1][1];
    int y = F[1][0] * M[0][0] + F[1][1] * M[1][0];
    int z = F[1][0] * M[0][1] + F[1][1] * M[1][1];

    F[0][0] = w;
    F[0][1] = x;
    F[1][0] = y;
    F[1][1] = z;
}

/* 
menghitung nilai F pangkat n dan hasil disimpan kembali ke F
optimisasi dengan Divide and Conquer pada fungsi power
*/
void power(int F[2][2], int n)
{
    if (n == 0 || n == 1)
        return;

    int i;
    int M[2][2] = {{1, 1}, {1, 0}};

    power(F, n/2);
    multiply(F, F);

    if (n % 2 -- 1)
        multiply(F, M);
}

// ======================================================================================

/** Matrix Multiplication **/

int algorithm(int idx)
{
    int F[2][2] = {{1, 1}, {1, 0}};
    
    if (idx == 0)
        return 0;
    
    // melakukan update terhadap F
    power(F, idx - 1);

    return F[0][0];
}