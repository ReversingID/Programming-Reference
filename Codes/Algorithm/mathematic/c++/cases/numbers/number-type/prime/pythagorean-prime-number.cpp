/*
    Pythagorean-Prime Number
    Archive of Reversing.ID
    Algorithm (Mathematics/Numbers)
    
Compile:
    [clang]
    $ clang++ pythagorean-prime-number.cpp -o pythagorean-prime-number

    [gcc]
    $ g++ pythagorean-prime-number.cpp -o pythagorean-prime-number

    [msvc]
    $ cl pythagorean-prime-number.cpp

Run:
    $ pythagorean-prime-number
*/

/*
    Pythagorean-Prime Number adalah bilangan prima yang dalam bentuk

        P = 4 Z + 1
    
    dan dapat diekspresikan sebagai penjumlahan dua bilangan kuadrat

Contoh:
    5, 13, 17, 29, 37, 41, 53, 61, 73, 89, 97 
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
    Periksa apakah suatu bilangan merupakan Pythagorean-Prime Number.
*/

/*
    Sebuah Pythagorean-Prime dapat diekspresikan ke dalam bentuk 4 Z + 1
*/

bool algorithm(size_t num)
{
    return (prime_check(num) && (num % 4 == 1));
}