/*
    Root Simplification
    Archive of Reversing.ID
    Algorithm (Mathematics/Numbers)
    
Compile:
    [clang]
    $ clang++ root-simplification.cpp -o root-simplification

    [gcc]
    $ g++ root-simplification.cpp -o root-simplification

    [msvc]
    $ cl root-simplification.cpp

Run:
    $ root-simplification
*/
#include <tuple>
#include <cmath>

/*
    Menyederhanakan bilangan akar √X Menjadi bentuk perfect dan radicand C√D
    
    √A = B√C
        A = num
        B = perfect number
        C = radicand

Contoh:
    √20 = 2√5
    √56 = 3√7

    berlaku juga untuk akar lain (akar pangkat 3, akar pangkat 4, dsb).
*/

// ======================================================================================

/* 
    Iterative Solution
    Melakukan faktorisasi, mencari faktor-faktor prima dari bilangan dan membangun
    perfect number dan radicand di setiap iterasi.
*/

auto algorithm(size_t num, size_t degree)
{
    size_t power  = 0;
    size_t number = 2;

    size_t perfect = 1, radicand = 1;

    // proses faktor 2 sebagai satu-satunya faktor prima genap.
    power  = 0;
    while (num % 2 == 0)
    {
        num = num / 2;

        power ++;
        if (power == degree)
        {
            power = 0;
            perfect *= 2;
        }
    }

    for (size_t j = 0; j < power; j++)
            radicand *= 2;

    // proses faktor prima dimulai dari 3
    for (size_t i = 3, batas = sqrt(num); i <= batas; i += 2)
    {
        power = 0;

        // mendapatkan bernilai sama
        while (num % i == 0)
        {
            num = num / i;

            power++;
            if (power == degree)
            {
                power = 0;
                perfect *= i;
            }
        }

        for (size_t j = 0; j < power; j++)
            radicand *= i;
    }

    // jika ada faktor yang lebih besar daripada sqrt(num)
    if (num > 2)
        radicand *= num;
    
    // get<0> -> perfect, get<0> -> radicand
    return std::make_tuple(perfect, radicand);
}