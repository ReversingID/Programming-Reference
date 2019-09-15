/*
    Modular Exponentiation
    Archive of Reversing.ID
    Algorithm (Divide and Conquer)
    
Compile:
    [clang]
    $ clang++ modular-exponentiation.cpp -o modular-exponentiation

    [gcc]
    $ g++ modular-exponentiation.cpp -o modular-exponentiation

    [msvc]
    $ cl modular-exponentiation.cpp

Run:
    $ modular-exponentiation
*/
#include <cstdint>

/*
Problem:
    Menghitung nilai perpangkatan suatu nilai dalam modular aritmetik. Perhitungna sisa
    bagi didapatkan dengan memanfaatkan sifat:

        (ab) mod p = ((a mod p) * (b mod p)) mod p

Langkah:
    Divide: bagi jadi subproblem berdasarkan jumlah pangkat.
    Conquer: lakukan pangkat dua yaitu perkalian antara base dan base
    Combine: lakukan perkalian terhadap hasil sebelumnya
*/

// ======================================================================================

/**
 * Single-function solve
 * Recursive
 */

uint64_t algorithm(uint64_t base, uint64_t exp, uint64_t mod)
{
    if (exp == 0)
        return 1;
    
    uint64_t val = algorithm(base, exp / 2, mod) % mod;
    if (exp % 2 == 0)
        return (val * val) % mod;
    else 
        return (base * val * val) % mod;
}

// ======================================================================================

/**
 * Single-function solve
 * Non-Recursive
 */

uint64_t algorithm(uint64_t base, uint64_t exp, uint64_t mod)
{
    uint64_t result = 1;

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