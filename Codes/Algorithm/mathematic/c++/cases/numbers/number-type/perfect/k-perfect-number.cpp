/*
    K-Perfect Number
    Archive of Reversing.ID
    Algorithm (Mathematics/Numbers)
    
Compile:
    [clang]
    $ clang++ k-perfect-number.cpp -o k-perfect-number

    [gcc]
    $ g++ k-perfect-number.cpp -o k-perfect-number

    [msvc]
    $ cl k-perfect-number.cpp

Run:
    $ k-perfect-number
*/

/*
    K-Perfect Number adalah bilangan dengan jumlah semua pembagi bernilai K kali lipat 
    bilangan tersebut.

    K = 3 disebut Triperfect
*/

// ======================================================================================

/* 
    Iterative Solution
    Testing
    Periksa apakah bilangan merupakan K-Perfect Number
*/

bool algorithm(size_t num, size_t k)
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

    return (k * num == sum && num != 1);
}