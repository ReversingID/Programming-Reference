/*
    Perfect-Power Number
    Archive of Reversing.ID
    Algorithm (Mathematics/Numbers)
    
Compile:
    [clang]
    $ clang++ perfect-power-number.cpp -o perfect-power-number

    [gcc]
    $ g++ perfect-power-number.cpp -o perfect-power-number

    [msvc]
    $ cl perfect-power-number.cpp

Run:
    $ perfect-power-number
*/
#include <cmath>
#include <vector>
#include <algorithm>

/*
    Perfect-Power adalah bilangan yang dapat diekspreskan sebagai perpangkatan 
    bilangan lain.

Baris Perfect-Power:
    4, 8, 9, 16, 25, 27, 32, 36, 49, ...
*/

// ======================================================================================

/*
    Testing
    Periksa apakah sebuah bilangan merupakan Perfect-Power Number
*/

bool algorithm(size_t num)
{
    if (num == 1) return true;

    for (size_t x = 2, batas = sqrt(num); x <= batas; x++)
    {
        size_t p = x;

        // lakukan perkalian terus menerus
        while (p <= num)
        {
            p = p * x;
            if (p == num)
                return true;
        }
    }

    return false;
}

// ======================================================================================

/*
    Iterative Solution
    Sequence Generator -- Naive Method
    Bangkitkan baris Perfect-Power Number yang bernilai kurang dari atau sama dengan num.
*/

auto algorithm(size_t num)
{
    // menyimpan semua Perfect-Power Number
    std::vector<size_t> result;

    result.push_back(1);

    // bangkitkan bilangan dan pastikan bernilai kurang dari atau sama dengan num.
    for (size_t i = 2; i * i <= num; i++)
    {
        // masukkan nilai kuadrat
        size_t j = i * i;
        result.push_back(j);

        // masukkan nilai pangkat lain
        while (j * i <= num)
        {
            result.push_back(j * i);
            j = j * i;
        }
    }
    
    // urutkan bilangan dan pastikan tak ada bilangan yang duplikat
    std::sort(result.begin(), result.end());
    result.erase(std::unique(result.begin(), result.end()), result.end());
    
    return result;
}