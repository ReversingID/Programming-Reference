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

size_t min_element(size_t arr[], size_t N)
{
    size_t i;
    size_t _min;

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

size_t algorithm(size_t N, size_t primes[], size_t K)
{
    // menampung ugly number yang dibangkitkan
    size_t ugly[N];

    // alokasikan generator untuk setiap bilangan prima
    size_t index[K];
    size_t generator[K];
    size_t i, j;
    size_t next_ugly = 1;

    for (i = 0; i < K; i++)
    {
        index[i] = 0;
        generator[i] = primes[i];
    }

    // inisialisasi elemen ugly pertama
    ugly[0] = 1;

    for (i = 1; i < N; i++)
    {
        // cari nilai minimum dari baris independen
        next_ugly = min_element(generator, K);

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