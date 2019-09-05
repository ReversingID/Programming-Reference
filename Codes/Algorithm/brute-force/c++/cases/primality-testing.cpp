/*
    Primality Testing
    Archive of Reversing.ID
    Algorithm (Brute-Force)
    
Compile:
    [clang]
    $ clang++ primality-testing.cpp -o primality-testing

    [gcc]
    $ g++ primality-testing.cpp -o primality-testing

    [msvc]
    $ cl primality-testing.cpp

Run:
    $ primality-testing
*/
#include <cmath>


/*
Masalah:
    Diberikan sebuah bilangan bulat positif. Ujilah apakah bilangan tersebut merupakan
    bilangan prima atau bukan.
*/

// ======================================================================================

bool algorithm(int x)
{
    if (x < 2)              // 1 bukan bilangan prima
        return false;
    else if (x == 2)        // 2 bilangan prima
        return true;
    else 
    {
        int batas = sqrt(x);
        int i;
        
        for (i = 2; i <= batas; i++)
        {
            if (x % i == 0)
                return false;
        }

        return true;
    }
}