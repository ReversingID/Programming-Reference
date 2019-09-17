/*
    Full-Prime Number
    Archive of Reversing.ID
    Algorithm (Mathematics/Numbers)
    
Compile:
    [clang]
    $ clang++ full-prime-number.cpp -o full-prime-number

    [gcc]
    $ g++ full-prime-number.cpp -o full-prime-number

    [msvc]
    $ cl full-prime-number.cpp

Run:
    $ full-prime-number
*/

/*
    Full-Prime Number adalah bilangan prima yang setiap digit merupakan bilangan prima.

Contoh:
    53 -> 5 dan 3 masing-masing bilangan prima
*/

// ======================================================================================

// periksa apakah sebuah bilangan merupakan bilangan prima
bool prime_check(size_t num)
{
    if (n <= 1)
        return false;
    if (n <= 3)
        return true;
    
    // keluarkan pengecekan kelipatan 2 dan 3 sehingga kita bisa loop mulai dari 5
    if (num % 2 == 0 || num % 3 == 0)
        return false;
    
    for (size_t i = 5; i * i <= num; i += 6)
        if (num % i == 0 || num % (i + 2) == 0)
            return false;
    
    return true;
}

// ======================================================================================

/*
    Iterative Solution
    Testing -- Naive Method
    Periksa apakah suatu bilangan merupakan Full-Prime Number.
*/

bool algorithm(size_t num)
{
    size_t d;

    if (!prime_check(num))
        return false;

    while (num != 0)
    {
        d = num % 10;

        if (d != 2 && d != 3 && d != 5 && d != 7)
            return false;
        
        num = num / 10;
    }

    return true;
}