/*
    Greatest Common Divisor
    Archive of Reversing.ID
    Algorithm (Mathematics/Numbers)
    
Compile:
    [clang]
    $ clang++ gcd.cpp -o gcd

    [gcc]
    $ g++ gcd.cpp -o gcd

    [msvc]
    $ cl gcd.cpp

Run:
    $ gcd
*/

/*
GCD (Greatest Common Divisor) atau FPB (Faktor Persekutuan terBesar)
    Mencari faktor terbesar yang membagi kedua bilangan.
*/

// ======================================================================================

/*
    Recursive Solution
    Mencari GCD dengan algoritma euclid
*/

size_t algorithm(size_t num_1, size_t num_2)
{
    if (num_2 == 0)
        return num_1;

    return algorithm(num_2, num_1 % num_2);
}

// ======================================================================================

/* 
    Iterative Solution
    Mencari GCD dengan algoritma euclid
*/

size_t algorithm(size_t num_1, size_t num_2)
{
    size_t num_3 = num_1 % num_2;

    while (num_3 > 0)
    {
        num_1 = num_2;
        num_2 = num_3;
        num_3 = num_1 % num_2;
    }
    
    return num_2;
}

// ======================================================================================

/*
    Equation Solution
    Mencari GCD dengan cara menyelesaikan persamaan:

    LCM * GCD = num_1 * num_2
*/

// Mencari LCM. Lihat di bagian LCM
size_t lcm(size_t num_1, size_t num_2);

size_t algorithm(size_t num_1, size_t num_2)
{
    auto value = lcm(num_1, num_2);

    return (num_1 * num_2) / value;
}