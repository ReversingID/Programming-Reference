/*
    Circular-Prime Number
    Archive of Reversing.ID
    Algorithm (Mathematics/Numbers)
    
Compile:
    [clang]
    $ clang++ circular-prime-number.cpp -o circular-prime-number

    [gcc]
    $ g++ circular-prime-number.cpp -o circular-prime-number

    [msvc]
    $ cl circular-prime-number.cpp

Run:
    $ circular-prime-number
*/

/*
    Circular-Prime Number adalah bilangan prima yang apabila mengalami cyclic permutation
    akan menghasilkan bilangan prima.

Contoh:
    113 -> 311, 131
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
    Periksa apakah suatu bilangan merupakan Circular-Prime Number.
*/

bool algorithm(size_t num)
{
    size_t t = num, d;
    size_t batas = 0, pos = 1;

    // mencari jumlah digit sebagai batas iterasi
    while (t != 0)
    {
        batas ++;
        pos *= 10;
        t = t / 10;
    }

    // iterasi untuk setiap digit
    for (size_t i = 0, t = num; i < batas; i++)
    {
        if (!prime_check(t))
            return false;

        d = t % 10;
        t = d * pos + (t / 10);
        pos = pos / 10;
    }

    return true;
}