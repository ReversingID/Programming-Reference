/*
    Unusual Number
    Archive of Reversing.ID
    Algorithm (Mathematics/Numbers)
    
Compile:
    [clang]
    $ clang++ unusual-number.cpp -o unusual-number

    [gcc]
    $ g++ unusual-number.cpp -o unusual-number

    [msvc]
    $ cl unusual-number.cpp

Run:
    $ unusual-number
*/

/*
    Unusual Number adalah bilangan natural dimana faktor prima terbesar bernilai lebih
    besar daripada akar kuadrat bilangan tersebut.

Baris Unusual Number:
    2, 3, 5, 6, 7, 10, 11, 13, 14, 15, 17, ...
*/

// ======================================================================================

size_t largest_prime_factor(size_t num)
{
    size_t max = 0;

    // 2 adalah bilangan prima bukan ganjil sehingga menjadi kasus khusus
    if (num % 2 == 0)
    {
        max = 2;
        while (num % 2 == 0)
            num = num / 2;
    }

    for (size_t i = 3, batas = sqrt(num); i <= batas; i += 2)
    {
        if (num % i == 0)
        {
            max = i;
            while (num % i == 0)
                num = num / i;
        }
    }

    if (num > 2)
        max = num;

    return max;
}

// ======================================================================================

/*
    Iterative Solution
    Testing -- Naive Method
    Periksa apakah suatu bilangan merupakan Unusual Number.
*/

bool algorithm(size_t num)
{
    return (largest_prime_factor(num) > sqrt(num));
}