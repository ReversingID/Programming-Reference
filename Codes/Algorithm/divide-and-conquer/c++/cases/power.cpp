/*
    Power
    Archive of Reversing.ID
    Algorithm (Divide and Conquer)
    
Compile:
    [clang]
    $ clang++ power.cpp -o power

    [gcc]
    $ g++ power.cpp -o power

    [msvc]
    $ cl power.cpp

Run:
    $ power
*/
#include <cstdint>

/*
Problem:
    Menghitung perpangkatan dengan melakukan perkalian secara rekursif.

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

uint64_t algorithm(uint64_t base, uint64_t exp)
{
    // Divide
    if (exp == 0)
        return 1;
    else if (exp % 2 == 0)
        return algorithm(base, exp / 2) * algorithm(base, exp / 2);
    else 
        return base * algorithm(base, exp / 2) * algorithm(base, exp / 2);
}

// ======================================================================================

/**
 * Single-function solve
 * Non-Recursive
 */

uint64_t algorithm(uint64_t base, uint64_t exp)
{
    uint64_t result = 1;
    
    while (exp > 0)
    {
        if (exp & 1)
            result = result * base; // conquer + combine
        
        exp  = exp / 2;         // divide
        base = base * base;     // conquer
    }

    return result;
}