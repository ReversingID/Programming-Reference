/*
    Naive Primality Test
    Archive of Reversing.ID
    Algorithm (Mathematics/Numbers)
    
Compile:
    [clang]
    $ clang++ naive-primality-test.cpp -o naive-primality-test

    [gcc]
    $ g++ naive-primality-test.cpp -o naive-primality-test

    [msvc]
    $ cl naive-primality-test.cpp

Run:
    $ naive-primality-test
*/
#include <cmath>

/*
    Periksa apakah suatu bilangan merupakan bilangan prima
*/

// ======================================================================================

/** Prime Number Check -- Naive Method **/

bool Algorithm(size_t val)
{
    if (val < 2)        // 0 dan 1 bukan bilangan prima
        return false;
    if (val == 2)       // 2 bilangan prima
        return true;
    else 
    {
        int batas = sqrt(val);

        // periksa dari 2 ke sqrt(val)
        for (size_t i = 2; i < val; i++)
            if (val % i == 0)
                return false;
        
        return true;
    }
}