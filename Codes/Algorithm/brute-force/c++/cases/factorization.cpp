/*
    Factorization
    Archive of Reversing.ID
    Algorithm (Brute-Force)
    
Compile:
    [clang]
    $ clang++ factorization.cpp -o factorization

    [gcc]
    $ g++ factorization.cpp -o factorization

    [msvc]
    $ cl factorization.cpp

Run:
    $ factorization
*/
#include <vector>

/*
Masalah:
    Diberikan sebuah bilangan bulat `n`. Tentukan semua faktor bilangan bulat `n`
    dengan nilai selain 1 dan `n` itu sendiri.
*/

// ======================================================================================

auto algorithm(int n)
{
    std::vector<int>    factors;
    for (int i = 2; i < n - 1; i++)
    {
        // factor adalah angka yang habis membagi
        if (n % i == 0)
            factors.push_back(i);
    }

    return factors;
}