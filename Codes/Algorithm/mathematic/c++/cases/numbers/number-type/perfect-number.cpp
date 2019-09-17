/*
    Perfect Number
    Archive of Reversing.ID
    Algorithm (Mathematics/Numbers)
    
Compile:
    [clang]
    $ clang++ perfect-number.cpp -o perfect-number

    [gcc]
    $ g++ perfect-number.cpp -o perfect-number

    [msvc]
    $ cl perfect-number.cpp

Run:
    $ perfect-number
*/
#include <vector>
#include <algorithm>

/*
    Perfect Number adalah bilangan yang penjumlahan semua pembagi (selain dirinya)
    bernilai bilangan tersebut.

Contoh:
    6 memiliki pembagi 1, 2, 3 -> 1 + 2 + 3 = 6

*/

// ======================================================================================

/* 
    Periksa apakah bilangan merupakan Perfect Number
*/

auto algorithm(size_t num)
{
    size_t sum = 0, t = num;

    for (size_t i = 2; i * i <= num; i++)
    {
        if (t % i == 0)
        {
            if (i * i != num)
                sum += i + n / i;
            else 
                sum += i;
        }
    }
    
    return (sum == num && num > 1);
}