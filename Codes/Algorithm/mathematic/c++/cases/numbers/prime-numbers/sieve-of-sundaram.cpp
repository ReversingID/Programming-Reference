/*
    Sieve of Sundaram
    Archive of Reversing.ID
    Algorithm (Mathematics/Numbers)
    
Compile:
    [clang]
    $ clang++ sieve-of-sundaram.cpp -o sieve-of-sundaram

    [gcc]
    $ g++ sieve-of-sundaram.cpp -o sieve-of-sundaram

    [msvc]
    $ cl sieve-of-sundaram.cpp

Run:
    $ sieve-of-sundaram
*/
#include <vector>

/*
    Penggunaan Sieve of Sundaram untuk membangkitkan bilangan prima.
*/

// ======================================================================================

/*
    Bangkitkan semua bilangan prima yang bernilai lebih kecil atau sama dengan N.

Langkah:
    - bangkitkan semua bilangan bulat yang lebih kecil daripada (2 * X + 2) untuk
      X = (N - 2) / 2
    - bentuk senarai berisi bilangan bulat dari 2 hingga N (2, 3, 4, ..., N)
    - lakukan penghapusan untuk nilai I + J + 2IJ, dimana 
        1 <= I <= J
*/

auto algorithm(size_t N)
{
    // menyimpan bilangan prima
    std::vector<size_t> primes;

    size_t X = (N - 2) / 2;

    // daftar bilangan
    bool marks[X + 1];
    memset(marks, true, sizeof(marks));

    // tandai semua bilangan dalam rentang I + J + 2IJ 
    for (size_t i = 1; i <= X; i++)
        for (size_t j = i; (i + j + 2*i*j) <= X; j++)
            marks[i + j + 2*i*j] = false;
        
    // 2 adalah bilangan prima
    primes.push_back(2);

    // masukkan bilangan yang belum ditandai
    for (size_t i = 1; i <= X; i++)
    {
        if (marks[i])
            primes.push_back(2 * i + 1);
    }

    return primes;
}