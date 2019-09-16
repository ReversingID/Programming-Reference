/*
    Least Common Multiple
    Archive of Reversing.ID
    Algorithm (Mathematics/Numbers)
    
Compile:
    [clang]
    $ clang++ lcm.cpp -o lcm

    [gcc]
    $ g++ lcm.cpp -o lcm

    [msvc]
    $ cl lcm.cpp

Run:
    $ lcm
*/
#include <algorithm>

/*
LCM (Least Common Multiple) atau KPK (Kelipatan Persekutuan terKecil)
    Mencari sebuah bilangan kelipatan yang habis dibagi oleh kedua bilangan.
*/

// ======================================================================================

/*
    Iterative Solution
    Naive Method
    Melakukan pencarian nilai secara terurut menaik hingga dapat dibagi kedua bilangan.

    Simpan bilangan terbesar di value
    Iterasi dengan tambahkan 1 hingga value habis dibagi kedua bilangan.
*/

size_t algorithm(size_t num_1, size_t num_2)
{
    size_t value = std::max(num_1, num_2);
    
    /*
    Bit trick: periksa bila kedua bilangan bernilai 0.
    */
    while ((value % num_1) || (value % num_2))
        value ++;
    
    return value;
}

// ======================================================================================

/*
    Iterative Solution
    Iterasi dengan nilai increment yang bervariasi.

    Simpan bilangna terbesar di value.
    Iterasi dengan tambahkan bilangan terbesar di tiap iterasi hingga value habis dibagi
    kedua bilangan.

    Misal:
        a = 138 -> 2 * 3 * 23
        b = 45  -> 3 * 3 * 5

    GCD = 3, sehingga
        a = 46 * GCD 
        b = 15 * GCD

    untuk mencapai LCM maka kita perlu mengalikan a dengan 15 atau bisa kita 
    dekomposisi menjadi penjumlahan a secara berulang sampai 15 kali.
*/

size_t algorithm(size_t num_1, size_t num_2)
{
    size_t larger  = std::max(num_1, num_2), 
           smaller = std::min(num_1, num_2);
    size_t value   = larger;
    
    while (value % smaller)
        value += larger;

    return value;
}

// ======================================================================================

/*
    Equation Solution
    Mencari GCD dengan cara menyelesaikan persamaan:

    LCM * GCD = num_1 * num_2
*/

// Mencari GCD. Lihat di bagian GCD
size_t gcd(size_t num_1, size_t num_2);

size_t algorithm(size_t num_1, size_t num_2)
{
    auto value = gcd(num_1, num_2);

    return (num_1 * num_2) / value;
}