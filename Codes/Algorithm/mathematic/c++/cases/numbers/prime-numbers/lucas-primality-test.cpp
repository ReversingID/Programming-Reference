/*
    Lucas Primality Test
    Archive of Reversing.ID
    Algorithm (Mathematics/Numbers/Prime Numbers)
    
Compile:
    [clang]
    $ clang++ lucas-primality-test.cpp -o lucas-primality-test

    [gcc]
    $ g++ lucas-primality-test.cpp -o lucas-primality-test

    [msvc]
    $ cl lucas-primality-test.cpp

Run:
    $ lucas-primality-test
*/
#include <cmath>

/*
    Periksa apakah suatu bilangan merupakan bilangan prima

Jika p adalah prima dan a adalah bilangan bulat, maka a^p kongruen dengan a (mod p).

        A ^ (N - 1) ≡ 1 (mod N)
    
    sehingga untuk setiap faktor prima Q dari (N - 1)

        A ^ (N - 1)/Q !≡ 1 (mod N)
*/

// ======================================================================================

// bangkitkan faktor prima dari N
void prime_factors(size_t N, std::vector<int> & factors)
{
    size_t batas;

    if (N % 2 == 0)
        factors.push_back(2);
    
    while (N % 2 == 0) N = N / 2;

    for (size_t i = 3, batas = sqrt(N); i <= batas; i += 2)
    {
        if (N % i == 0)
            factors.push_back(i);
        
        while (N % i == 0)
            N = N / i;
    }

    if (N > 2)
        factors.push_back(N);
}

// ======================================================================================

bool Algorithm(size_t val)
{
    size_t t;

    if (val == 1)       // 1 bukan bilangan prima
        return false;
    if (val == 2)       // 2 bilangan prima
        return true;
    if (val % 2 == 0)   // kelipatan 2 bukan bilangan prima
        return false;

    // bangkitkan semua faktor dari val - 1
    std::vector<int> factors;
    prime_factors(val - 1, factors);

    // pengecekan Lucas
    for (size_t i = 2; i < val; i++)
    {
        // pengecekan kondisi (1)
        if (power(i, val - 1, val) != 1)
            return false;
        
        // periksa setiap faktor dari val - 1 memenuhi kondisi (2)
        for (auto & factor : factors)
        {
            if (power(i, (val - 1)/factor, val) == 1)
                return false;
        }
    }

    return true;
}