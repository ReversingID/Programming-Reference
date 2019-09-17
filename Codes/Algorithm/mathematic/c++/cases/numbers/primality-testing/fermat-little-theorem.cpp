/*
    Fermat Little Theorem
    Archive of Reversing.ID
    Algorithm (Mathematics/Numbers/Prime-Numbers)
    
Compile:
    [clang]
    $ clang++ fermat-little-theorem.cpp -o fermat-little-theorem

    [gcc]
    $ g++ fermat-little-theorem.cpp -o fermat-little-theorem

    [msvc]
    $ cl fermat-little-theorem.cpp

Run:
    $ fermat-little-theorem
*/
#include <cmath>
#include <random>

/*
    Periksa apakah suatu bilangan merupakan bilangan prima dengan Ferman Little Theorem.

Fermat's Little Theorem:
    Jika N adalah bilangan prima, maka untuk semua A, 1 < A < N - 1

        A ^ (N - 1) ≡ 1 (mod N)
    
    atau

        A ^ (N - 1) % N = 1

*/

// ======================================================================================

// mencari GCD (Greatest Common Divisor / FPB)
size_t gcd(size_t a, size_t b)
{
    size_t c = a % b;

    while (c > 0)
    {
        a = b;
        b = c;
        c = a % b;
    }

    return b;
}

// mencari modular exponentiation dari suatu nilai
size_t power(size_t base, size_t exp, size_t mod)
{
    size_t result = 1;

    base = base % mod;

    while (exp > 0)
    {
        if (exp & 1)
            result = (result * base) % mod;
        
        exp  = exp / 2;
        base = (base * base) % mod;
    }

    return result;
}

// ======================================================================================

bool algorithm(size_t val, size_t k)
{
    size_t t;

    // corner case
    if (val <= 1 || val == 4)
        return false;
    if (val == 2)
        return true;
    
    std::random_device  rd;
    std::mt19937        mt(rd());
    std::uniform_int_distribution<size_t> dist(0, val - 4);

    while (k > 0)
    {
        // ambil angka acak dalam rentang [2 .. val-2]
        t = 2 + dist(mt);

        // periksa jika t dan val co-prime
        if (gcd(t, val) != 1)
            return false;
        
        // Fermat's little theorem
        if (power(t, val - 1, val) != 1)
            return false;
        
        k--;
    }

    return true;
}