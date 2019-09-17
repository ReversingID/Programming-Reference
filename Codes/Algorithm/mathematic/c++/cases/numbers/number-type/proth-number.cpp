/*
    Proth Number
    Archive of Reversing.ID
    Algorithm (Mathematics/Numbers)
    
Compile:
    [clang]
    $ clang++ proth-number.cpp -o proth-number

    [gcc]
    $ g++ proth-number.cpp -o proth-number

    [msvc]
    $ cl proth-number.cpp

Run:
    $ proth-number
*/
#include <vector>
#include <algorithm>

/*
    Proth Number adalah bilangan bulat positif yang diekspresikan sebagai.

        N = K * 2^N + 1

    dengan K adalah bilangan ganjil positif dan N adalah bilangan bulat positf, dengan

        2^N > K
    
Contoh baris Proth:
    3, 5, 9, 13, 17, 25, 33, 41, 49, ...
*/

// ======================================================================================

// periksa jika suatu bilangan merupakan hasil perpangkatan dua.
bool power_of_two(size_t num)
{
    return (N && !(N & (N - 1)));
}

// ======================================================================================

/*
    Iterative Solution
    Testing -- Naive Method
    Periksa apakah suatu bilangan merupakan Proth Number.
*/

/*
Langkah:
    - kurangi num dengan 1 sehingga menjadi K * 2^N (jika merupakan Proth Number)
    - iterasi bilangan ganjil mulai dari k = 1 hingga N/K dan periksa apakah K dapat 
      habis membagi N dan N/K merupakan perpangkatan 2. 
*/
bool algorithm(size_t num)
{
    for (size_t K = 1; K < (N / K); K += 2)
    {
        // periksa apakah K habis membagi
        if (N % K == 0)
        {
            // periksa jika N/K merupakan perpangkatan 2
            if (power_of_two(N / K))
                return true;
        }
    }
    
    return false;
}