/*
    Sieve of Eratosthenes
    Archive of Reversing.ID
    Algorithm (Mathematics/Numbers)
    
Compile:
    [clang]
    $ clang++ sieve-of-eratosthenes.cpp -o sieve-of-eratosthenes

    [gcc]
    $ g++ sieve-of-eratosthenes.cpp -o sieve-of-eratosthenes

    [msvc]
    $ cl sieve-of-eratosthenes.cpp

Run:
    $ sieve-of-eratosthenes
*/
#include <vector>
#include <cmath>

/*
    Penggunaan Sieve of Eratosthenes untuk membangkitkan bilangan prima.
*/

// ======================================================================================

/*
    Bangkitkan semua bilangan prima yang bernilai lebih kecil atau sama dengan N.

Langkah:
    - bentuk senarai berisi bilangan bulat dari 2 hingga N (2, 3, 4, ..., N)
    - dimulai dari p = 2, hapus bilangan yang merupakan kelipatan dari p.
    - cari bilangan bulat pertama yang tidak dihapus oleh p, dan ulangi langkah sebelumnya.
*/

auto algorithm(size_t N)
{
    // menyimpan bilangan prima
    std::vector<size_t> primes;

    // daftar bilangan
    bool marks[N + 1];
    memset(marks, true, sizeof(marks));

    // lakukan penghapusan
    for (size_t p = 2; p * p <= N; p++)
    {
        // bilangan ini belum dihapus sebelumnya
        if (marks[p])
        {
            // hapus semua bilangan kelipatan p * p
            for (size_t i = p * 2; i <= N; i+= p)
                marks[i] = false;
        }
    }

    // masukkan bilangan yang belum ditandai
    for (size_t i = 2; i <= N; i++)
    {
        if (marks[i])
            primes.push_back(i);
    }

    return primes;
}

// ======================================================================================

/*
    Segmented Sieve
    Bangkitkan semua bilangan prima yang bernilai lebih kecil atau sama dengan N.
    Time complexity sama dengan Sieve of Eratosthenes normal namun lebih hemat space.

Langkah:
    - bentuk array terbatas (sqrt(N))
    - lakukan sieve of eratosthenes pada segmen

    gunakan fungsi algorithm() di atas sebagai sieve()
*/

// sieve of eratosthenes pada rentang terbatas untuk membentuk lookup table.
auto sieve(size_t N);

// melakukan sieve berulang ulang berdasarkan hasil dari sieve()
auto algorithm(size_t N)
{
    std::vector<size_t> primes;
    std::vector<size_t> lookup;

    size_t batas = floor(sqrt(N)) + 1;
    size_t low   = batas;
    size_t high  = 2 * batas;

    bool marks[batas + 1];

    // hitung semua bilangan prima lebih kecil atau sama dengan sqrt(N)
    lookup = sieve(batas);
    primes = lookup;

    // proses satu segmen dalam satu waktu
    while (low < N)
    {
        if (high >= N)
            high = N;
        
        // inisialisasi 
        memset(marks, true, sizeof(marks));

        /*
        gunakan bilangan prima yang telah ditemukan untuk menghapus bilangan prima di 
        segmen
        */
        for (size_t i = 0, ps = lookup.size(); i < ps; i++)
        {
            int lolim = floor(low / lookup[i]) * lookup[i];
            if (lolim < low)
                lolim += lookup[i];
            
            /*
            tandai kelipatan lookup[i] di segmen [low .. high]
            */
            for (size_t j = lolim; j < high; j += lookup[i])
                marks[j - low] = false;
        }
        
        // masukkan bilangan yang belum ditandai
        for (size_t i = low; i < high; i++)
        {
            if (marks[i - low])
                primes.push_back(i);
        }

        // update segmen
        low  = low  + batas;
        high = high + batas;
    }

    return primes;
}