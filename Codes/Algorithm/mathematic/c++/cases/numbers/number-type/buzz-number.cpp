/*
    Buzz Number
    Archive of Reversing.ID
    Algorithm (Mathematics/Numbers)
    
Compile:
    [clang]
    $ clang++ buzz-number.cpp -o buzz-number

    [gcc]
    $ g++ buzz-number.cpp -o buzz-number

    [msvc]
    $ cl buzz-number.cpp

Run:
    $ buzz-number
*/

/*
    Buzz Number adalah bilangan yang memiliki digit terakhir 7 atau habis dibagi 7.

Contoh:
    63  -> habis dibagi 7
    147 -> habis dibagi 7 serta berakhiran 7
    57  -> digit terakhir adalah 7

*/

// ======================================================================================

/*
    Testing -- Naive Method
    Periksa apakah suatu bilangan merupakan Buzz Number.
*/

bool algorithm(size_t num)
{
    return (num % 10 == 7 || num % 7 == 0);
}