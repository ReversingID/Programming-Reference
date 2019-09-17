/*
    Euclid Number
    Archive of Reversing.ID
    Algorithm (Mathematics/Numbers)
    
Compile:
    [clang]
    $ clang++ euclid-number.cpp -o euclid-number

    [gcc]
    $ g++ euclid-number.cpp -o euclid-number

    [msvc]
    $ cl euclid-number.cpp

Run:
    $ euclid-number
*/

/*
    Euclid Number adalah sebuah bilangan bulat positif yang memenuhi sifat berikut:

        E[N] = P[N] + 1

    Dimana P[N] adalah hasil perkalian dari N bilangan prima pertama 

Baris Euclid:
    3, 7, 31, 211, 2311, 30031, 510511, 9699691, ...

*/

// ======================================================================================

/*
    Fungsi untuk mendapatkan daftar bilangan prima dalam rentang 2 .. N
    Pilihan algoritma:
        - Sieve of Eratosthenes
        - Sieve of Sundaram
        - Sieve of Atkin
*/
std::vector<size_t> prime_generator(size_t N); 

// ======================================================================================

/*
    Note:
    Nilai bilangan Euclid pada tiap suku sangat besar.
    Berdasarkan rentang nilai yang dapat dijangkau size_t, kita akan asumsikan bahwa 
    kita hanya perlu membangkitkan bilangan prima hingga 10000
*/

#define PRIME_MAX   10000

/*
    Iterative Solution
    Testing -- Naive Method
    Periksa apakah suatu bilangan merupakan Euclid Number.
*/

bool algorithm(size_t num)
{
    size_t product = 1;
    size_t i = 0;

    auto primes = prime_generator(PRIME_MAX);

    while (product < num)
    {
        // kalikan bilangan sekarang dengan bilangan prima
        product = product * primes[i];

        if (product + 1 == num)
            return true;
        
        i ++;
    }

    return false;
}