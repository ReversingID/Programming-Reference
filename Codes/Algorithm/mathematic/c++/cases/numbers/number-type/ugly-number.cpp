/*
    Ugly Number
    Archive of Reversing.ID
    Algorithm (Mathematics/Numbers)
    
Compile:
    [clang]
    $ clang++ ugly-number.cpp -o ugly-number

    [gcc]
    $ g++ ugly-number.cpp -o ugly-number

    [msvc]
    $ cl ugly-number.cpp

Run:
    $ ugly-number
*/
#include <cmath>

/*
    Ugly Number adalah bilangan dengan faktor prima hanya 2, 3, atau 5.

Baris Ugly Number:
    1, 2, 3, 4, 5, 6, 8, 9, 10, 12, 15, ...
*/

// ======================================================================================

/*
    Iterative Solution
    Testing -- Naive Method
    Periksa apakah suatu bilangan merupakan Ugly Number.
*/

/*
ugly number hanya memiliki faktor 2, 3, atau 5. Faktorisasi dan lihat apakah ada 
faktor lain
*/
bool algorithm(size_t num)
{
    size_t factors[] = {2, 3, 5};

    for (size_t i = 0; i < 3; i++)
    {
        while (num % factors[i] == 0)
            num = num / factors[i];
    }

    return (num == 1);
}

// ======================================================================================

/* 
    Iterative Solution
    N-th Term Generator
    Bangkitkan suku ke-N dari Ugly Number
*/

size_t algorithm(size_t N)
{
    // menampung ugly number yang dibangkitkan
    size_t ugly[N];

    // index berdasarkan kelipatan faktor 2, 3, atau 5
    size_t i2 = 0, i3 = 0, i5 = 0;

    // generator
    size_t next_multiple_2 = 2;
    size_t next_multiple_3 = 3;
    size_t next_multiple_5 = 5;
    size_t next_ugly   = 1;

    // inisialisasi elemen ugly pertama
    ugly[0] = 1;
    
    for (size_t i = 1; i < N; i++)
    {
        // cari nilai minimum dari 3 baris independen
        next_ugly = std::min(next_multiple_2, std::min(next_multiple_3, next_multiple_5));

        // masukkan bilangan ke baris
        ugly[i] = next_ugly;

        // update nilai di baris
        if (next_ugly == next_multiple_2)
        {
            i2 ++;
            next_multiple_2 = ugly[i2] * 2;
        }
        if (next_ugly == next_multiple_3)
        {
            i3 ++;
            next_multiple_3 = ugly[i3] * 3;
        }
        if (next_ugly == next_multiple_5)
        {
            i5 ++;
            next_multiple_5 = ugly[i5] * 5;
        }
    }

    // ketika berakhir, telah dibangkitkan N - 1 bilangna
    return next_ugly;
}