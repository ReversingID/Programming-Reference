/*
    Triperfect Number
    Archive of Reversing.ID
    Algorithm (Mathematics/Numbers)
    
Compile:
    [clang]
    $ clang++ triperfect-number.cpp -o triperfect-number

    [gcc]
    $ g++ triperfect-number.cpp -o triperfect-number

    [msvc]
    $ cl triperfect-number.cpp

Run:
    $ triperfect-number
*/

/*
    Triperfect Number adalah bilangan dengan jumlah semua pembagi bernilai tiga kali 
    bilangan tersebut.

Contoh:
    120 = 1, 2, 3, 4, 5, 6, 8, 10, 12, 15, 20, 24, 30, 40, 60, 120
        1 + 2 + 3 + 4 + 5 + 6 + 8 + 10 + 12 + 15 + 20 + 24 + 30 + 40 + 60 + 120 = 360
        360 = 3 x 120
*/

// ======================================================================================

/* 
    Iterative Solution
    Testing
    Periksa apakah bilangan merupakan Triperfect Number
*/

bool algorithm(size_t num)
{
    // 1 dan bilangan itu sendiri merupakan faktor pembagi
    size_t sum = 1 + num; 

    // mencari faktor pembagi
    for (size_t i = 2; i * i <= num; i++)
    {
        if (num % i == 0)
        {
            // pembagi merupakan bilangan kuadrat, sehingga masukkan satu pembagi saja
            if (num / i == i)
                sum += i;
            else
                sum += i + num / i;   
        }
    }

    return (3 * num == sum && num != 1);
}