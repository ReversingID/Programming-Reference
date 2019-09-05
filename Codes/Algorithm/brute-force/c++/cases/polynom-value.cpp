/*
    Polynom Value
    Archive of Reversing.ID
    Algorithm (Brute-Force)
    
Compile:
    [clang]
    $ clang++ polynom-value.cpp -o polynom-value

    [gcc]
    $ g++ polynom-value.cpp -o polynom-value

    [msvc]
    $ cl polynom-value.cpp

Run:
    $ polynom-value
*/
#include <cmath>


/*
Masalah:
    Diberikan sebuah senarai merepresentasikan koefisien polinom. Berapa nilai polinom jika
    variabel X disubstitusikan dengan suatu nilai?
*/

// ======================================================================================

int algorithm(int coeff[], size_t size, int x)
{
    size_t  i, j;
    int     val = coeff[0];
    int     pangkat = 1;

    for (i = 1; i < size; i++)
    {
        pangkat *= x;
        val += coeff[i] * pangkat;
    }

    return val;
}