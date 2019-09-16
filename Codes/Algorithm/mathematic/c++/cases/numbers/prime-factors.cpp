/*
    Prime Factors
    Archive of Reversing.ID
    Algorithm (Mathematics/Numbers)
    
Compile:
    [clang]
    $ clang++ prime-factors.cpp -o prime-factors

    [gcc]
    $ g++ prime-factors.cpp -o prime-factors

    [msvc]
    $ cl prime-factors.cpp

Run:
    $ prime-factors
*/
#include <vector>
#include <cmath>

/*
    Memecah sebuah bilangan menjadi faktor-faktor prima.
*/

// ======================================================================================

/** Iterative Solution **/

auto algorithm(size_t num)
{
    size_t batas;
    std::vector<size_t> factors;

    // mendapatkan bernilai sama
    while (num % 2 == 0)
    {
        factors.push_back(2);
        num = num / 2;
    }

    // iterasi semua nilai
    for (size_t i = 3, batas = sqrt(num); i <= batas; i += 2)
    {
        // mendapatkan bernilai sama
        while (num % i == 0)
        {
            factors.push_back(i);
            num = num / i;
        }
    }

    // jika ada faktor yang lebih besar daripada sqrt(num)
    if (num > 2)
        factors.push_back(num);

    return factors;
}