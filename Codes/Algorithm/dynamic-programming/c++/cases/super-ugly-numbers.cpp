/*
    Super Ugly Numbers
    Archive of Reversing.ID
    Algorithm (Dynamic Programming)
    
Compile:
    [clang]
    $ clang++ super-ugly-numbers.cpp -o super-ugly-numbers

    [gcc]
    $ g++ super-ugly-numbers.cpp -o super-ugly-numbers

    [msvc]
    $ cl super-ugly-numbers.cpp

Run:
    $ super-ugly-numbers
*/
#include <vector>

/*
Masalah:
    Super Ugly Numbers adalah bilangan bulat positif dengan faktor prima tertentu.

    Diberikan sebuah angka N, tentukan angka ke-N dari baris Super Ugly Number.

Solusi:
    Generalisasi dari persoalan Ugly Number.
    Serupa dengan solusi Ugly Number namun dengan variasi K faktor prima.

*/

// ======================================================================================

// mencari nilai minimum dari senarai. Senarai tidak dapat dipastikan dalam keadaan terurut

/*
    Mencari nilai minimum dari senarai.
    Senarai tidak dapat dipastikan dalam keadaan terurut.

    Fungsi akan mengembalikan index dimana nilai minimum ditemukan.
*/

int min_element(int arr[], int N)
{
    int i;
    int _min;

    _min = arr[0];

    for (i = 1; i < N; i++)
    {
        if (arr[i] < _min)
            _min = arr[i];
    }

    return _min;
}

// ======================================================================================

/** Iterative Solution -- Tabulation **/

int algorithm(int N, int primes[], int N)
{
    // menampung ugly number yang dibangkitkan
    int ugly[N];

    // alokasikan generator untuk setiap bilangan prima
    int index[N];
    int generator[N];
    int i, j;
    int next_ugly = 1;

    for (i = 0; i < N; i++)
    {
        index[i] = 0;
        generator[i] = primes[i];
    }

    // inisialisasi elemen ugly pertama
    ugly[0] = 1;

    for (i = 1; i < N; i++)
    {
        // cari nilai minimum dari baris independen
        next_ugly = min_element(generator, N);

        // masukkan bilangan ke baris
        ugly[i] = next_ugly;

        // update nilai di baris
        for (j = 0; j < N; j++)
        {
            if (next_ugly == generator[j])
            {
                index[j] ++;
                generator[j] = ugly[ index[j] ] * primes[j];
            }
        }
    }

    // ketika berakhir, telah dibangkitkan N - 1 bilangna
    return next_ugly;
}