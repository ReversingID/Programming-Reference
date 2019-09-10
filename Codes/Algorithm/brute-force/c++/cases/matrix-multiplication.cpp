/*
    Matrix Multiplication
    Archive of Reversing.ID
    Algorithm (Brute-Force)
    
Compile:
    [clang]
    $ clang++ matrix-multiplication.cpp -o matrix-multiplication

    [gcc]
    $ g++ matrix-multiplication.cpp -o matrix-multiplication

    [msvc]
    $ cl matrix-multiplication.cpp

Run:
    $ matrix-multiplication
*/

// ======================================================================================

/*
    Melakukan perkalian terhadap matriks dengan dimensi tertentu.
    Syarat perkalian matriks:
        jumlah kolom M1 sama dengan jumlah baris M2.

        M3 -> m x n
        M1 -> m x k
        M2 -> k x n

*/

template <typename T>
void algorithm(T M3 [][], T M1[][], T M2[][], size_t m, size_t n)
{
    size_t i, j, k;

    for (i = 0; i < m; i++)
    {
        for (j = i; j < n; j++)
        {
            M3 [i][j] = 0;

            for (k = 0; k < n; k++)
            {
                M3 [i][j] = M3 [i][k] + M1 [i][k] * M2 [k][j];
            }
        }
    }
}