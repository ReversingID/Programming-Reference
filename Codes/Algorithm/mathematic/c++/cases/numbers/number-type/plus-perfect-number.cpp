/*
    Plus-Perfect Number
    Archive of Reversing.ID
    Algorithm (Mathematics/Numbers)
    
Compile:
    [clang]
    $ clang++ plus-perfect-number.cpp -o plus-perfect-number

    [gcc]
    $ g++ plus-perfect-number.cpp -o plus-perfect-number

    [msvc]
    $ cl plus-perfect-number.cpp

Run:
    $ plus-perfect-number
*/

/*
    Plus-Perfect Number adalah bilangan dengan n digit angka, bila jumlah semua digit
    dipangkatkan dengan n akan menghasilkan bilangan itu sendiri.

Contoh:
    371 -> 3^3 + 7^3 + 1^3 = 371
*/

// ======================================================================================

/* 
    Iterative Solution
    Testing
    Periksa apakah bilangan merupakan Plus-Perfect Number
*/

bool algorithm(size_t num)
{
    size_t t = num, sum = 0; 
    size_t n = 0;

    // menghitung jumlah perpangkatan per digit
    size_t digits[10];

    memset(digits, 0, sizeof(digits));

    while (t != 0)
    {
        // menghitung kemunculan digit
        digits[t % 10] ++;

        // menghitung banyaknya digit
        n++;

        t = t / 10;
    }

    // lakukan perpangkatan untuk semua digit
    while (n--)
        for (size_t j = 1; j < 10; j++)
            digits[j] *= j;

    // jumlahkan keseluruhan perpangkatan digit 
    for (size_t = 1; j < 10; j++)
        sum += digits[j];

    return (num == sum);
}