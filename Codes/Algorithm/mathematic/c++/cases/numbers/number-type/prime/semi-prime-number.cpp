/*
    Semi-Prime
    Archive of Reversing.ID
    Algorithm (Mathematics/Numbers)
    
Compile:
    [clang]
    $ clang++ semi-prime.cpp -o semi-prime

    [gcc]
    $ g++ semi-prime.cpp -o semi-prime

    [msvc]
    $ cl semi-prime.cpp

Run:
    $ semi-prime
*/

/*
    Periksa apakah bilangan bulat positif num merupakan bilangan semiprima (semiprime).

    Bilangan semiprima adalah bilangan yang dihasilkan dari perkalian dua bilangan prima.

Contoh: 
     6 = 2 x 3
     9 = 3 x 3
    35 = 5 x 7
*/

// ======================================================================================

/*
    Iterative Solution
    Testing -- Naive Method
    Periksa apakah suatu bilangan merupakan Semi-Prime Number.
*/

// lakukan faktorisasi kemudian periksa jumlah faktor 
bool algorithm(size_t num)
{
    int count = 0;

    // batasi hanya mencari 2 faktor
    for (size_t i = 2; count < 2 && i * i <= num; i++)
    {
        while (num % i == 0)
        {
            num = num / 2;
            count ++;
        }
    }

    // jika bilangan bernilai lebih dari satu, itu merupakan salah satu faktor
    if (num > 1)
        count ++;
    
    return (count == 2);
}