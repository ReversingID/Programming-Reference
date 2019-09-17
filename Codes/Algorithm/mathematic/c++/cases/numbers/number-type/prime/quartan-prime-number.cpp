/*
    Quartan-Prime Number
    Archive of Reversing.ID
    Algorithm (Mathematics/Numbers)
    
Compile:
    [clang]
    $ clang++ quartan-prime-number.cpp -o quartan-prime-number

    [gcc]
    $ g++ quartan-prime-number.cpp -o quartan-prime-number

    [msvc]
    $ cl quartan-prime-number.cpp

Run:
    $ quartan-prime-number
*/

/*
    Quartan-Prime Number adalah bilangan prima yang dalam bentuk

        P = X^2 + Y^4 
    
    dengan X > 0, Y > 0 dan keduanya merupakan bilangan bulat di Quartan Prime

Contoh:
    2, 17, 97
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
    Testing -- Heuristic
    Periksa apakah suatu bilangan merupakan Quartan-Prime Number.
*/

/*
    Sebuah Quartan-Prime dapat diekspresikan ke dalam bentuk 16 Z + 1
*/

bool algorithm(size_t num)
{
    return (prime_check(num) && (num % 16 == 1));
}