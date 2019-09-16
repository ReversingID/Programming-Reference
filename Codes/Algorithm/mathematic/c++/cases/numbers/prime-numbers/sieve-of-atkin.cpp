/*
    Sieve of Atkin
    Archive of Reversing.ID
    Algorithm (Mathematics/Numbers)
    
Compile:
    [clang]
    $ clang++ sieve-of-atkin.cpp -o sieve-of-atkin

    [gcc]
    $ g++ sieve-of-atkin.cpp -o sieve-of-atkin

    [msvc]
    $ cl sieve-of-atkin.cpp

Run:
    $ sieve-of-atkin
*/
#include <vector>
#include <cmath>

/*
    Penggunaan Sieve of Atkin untuk membangkitkan bilangan prima.
*/

// ======================================================================================

/*
    Bangkitkan semua bilangan prima yang bernilai lebih kecil atau sama dengan N.

Langkah:
    1 buat daftar hasil dengan isi [2, 3, 5]
    2 buat daftar sieve dengan entry untuk setiap bilangan bulat positif, ditandai 
      sebagai non-prime.
    3 untuk setiap bilangan Z di daftar hasil, lakukan operasi modulo 60 dengan sisa R.
        3.1 jika R adalah 1, 13, 17, 29, 37, 41, 49, atau 53, ubah entry untuk setiap 
            solusi yang mungkin menjadi 4x^2 + y^2 = N
        3.2 jika R adalah 7, 19, 31, atau 43, ubah entry untuk setiap solusi yang mungkin 
          menjadi 3x^2 + y^2 = N 
        3.3 jika R adalah 11, 23, 47, atau 59, ubah entry untuk setiap solusi yang mungkin 
            menjadi 3x^2 - y^2 = N, dimana X - Y 
        3.4 selain itu, abaikan.
    4 mulai dari bilangan terkecil di daftar sieve.
    5 ambil bilangan berikutnya, tandai sebagai prima, dan masukkan ke dalam hasil.
    6 kuadratkan bilangan dan tandai semua bilangan yang ada di list sebagai bukan prima.
      Catatan: 2, 3, 5 tidak boleh ditandai non-prime.
    7 ulangi langkah 6.

*/

auto algorithm(size_t N)
{
    // menyimpan bilangan prima
    std::vector<size_t> primes;

    if (N > 2)
        primes.push_back(2);
    if (N > 3)
        primes.push_back(3);
    
    // inisialisasi 
    bool marks[N];
    memset(marks, false, sizeof(marks));

    size_t Z;
    for (size_t X = 1; X * X < N; X++)
    {
        for (size_t Y = 1; Y * Y < N; Y++)
        {
            Z = (4 * X * X) + (Y * Y);
            if (Z <= N && (Z % 12 == 1 || Z % 12 == 5))
                marks[Z] ^= true;
            
            Z = (3 * X * X) + (Y * Y);
            if (Z <= N && Z % 12 == 7)
                marks[Z] ^= true;
            
            Z = (3 * X * X) - (Y * Y);
            if (X > Y && Z <= N && Z % 12 == 11)
                marks[Z] ^= true;
        }
    }

    // tandai semua kelipatan pangkat dua sebagai non prima
    for (size_t R = 5; R * R < N; R++)
    {
        if (marks[R])
        {
            for (size_t i = R * R; i < N; i += R * R)
                marks[i] = false;
        }
    }

    // masukkan bilangan yang belum ditandai
    for (size_t i = 5; i < N; i++)
    {
        if (marks[i])
            primes.push_back(i);
    }

    return primes;
}