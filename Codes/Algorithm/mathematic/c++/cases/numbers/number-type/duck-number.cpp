/*
    Duck Number
    Archive of Reversing.ID
    Algorithm (Mathematics/Numbers)
    
Compile:
    [clang]
    $ clang++ duck-number.cpp -o duck-number

    [gcc]
    $ g++ duck-number.cpp -o duck-number

    [msvc]
    $ cl duck-number.cpp

Run:
    $ duck-number
*/

/*
    Duck Number adalah bilangan yang memiliki angka 0 namun tidak sebagai angka di depan.

Contoh:
    707069
*/

// ======================================================================================

/*
    Iterative Solution
    Testing -- Naive Method
    Periksa apakah suatu bilangan merupakan Duck Number.
*/

bool algorithm(size_t num)
{
    while (num != 0)
    {
        // dapatkan digit dan periksa apakah nilainya 0
        // periksa nilai dari digit
        if (num % 10 == 0)
            return true;
        
        num = num / 10;
    }

    return false;
}