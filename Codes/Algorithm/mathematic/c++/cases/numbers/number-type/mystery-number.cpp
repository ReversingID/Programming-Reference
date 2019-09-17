/*
    Mystery Number
    Archive of Reversing.ID
    Algorithm (Mathematics/Numbers)
    
Compile:
    [clang]
    $ clang++ mystery-number.cpp -o mystery-number

    [gcc]
    $ g++ mystery-number.cpp -o mystery-number

    [msvc]
    $ cl mystery-number.cpp

Run:
    $ mystery-number
*/

/*
    Mystery Number adalah bilangan yang dapat diekspresikan sebagai penjumlahan dua 
    bilangan dengan masing-masing bilangan merupakan kebalikan satu sama lain.

Baris Mystery Number:
    121 -> 29 + 92
*/

// ======================================================================================

// membalikkan digit dari suatu bilangan
size_t reverse(size_t num, size_t t)
{
    size_t t = 0;
    
    while (num > 0)
    {
        t = (t * 10) + (num % 10);
        num = num / 10;
    }

    return t;
}

// ======================================================================================

/* 
    Iterative Solution
    Testing -- Tes semua kemungkinan
    Periksa apakah bilangan merupakan Mystery Number
*/

bool algorithm(size_t num)
{
    size_t j;

    for (size_t i = 1, batas = num / 2; i <= batas; i++)
    {
        if (i + reverse(num) == num)
            return true;
    }

    return false;
}