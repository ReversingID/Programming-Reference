/*
    Ugly Numbers
    Archive of Reversing.ID
    Algorithm (Dynamic Programming)
    
Compile:
    [clang]
    $ clang++ ugly-numbers.cpp -o ugly-numbers

    [gcc]
    $ g++ ugly-numbers.cpp -o ugly-numbers

    [msvc]
    $ cl ugly-numbers.cpp

Run:
    $ ugly-numbers
*/

/*
Masalah:
    Ugly numbers adalah bilangan dengan faktor prima hanya 2, 3, atau 5.
    Baris 1, 2, 3, 4, 5, 6, 8, 9, 10, 12, 15, ... memperlihatkan 11 ugly number pertama.
    Angka 1 ditetapkan sebagai bagian dari baris ini.

    Diberikan sebuah angka N, tentukan angka ke-N dari baris Ugly Number.

Solusi:
    Karena terdapat 3 faktor, bagi baris menjadi 3 grup berbeda

    - kelipatan 2 -> 2, 4, 6, 8, 10, ...
    - kelipatan 3 -> 3, 6, 9, 12, 15, ...
    - kelipatan 5 -> 5, 10, 15, 20, 25, ...

    kita dapatkan bahwa setiap subsequence merupakan baris ugly number dikalikan dengan
    konstanta.

    Pada setiap langkah, kita pilih elemen terkecil dan mengunjungi elemen satu persatu.

Langkah:
    - deklarasikan senarai untuk baris ugly numbers.
    - inisialisasi ugly number pertama ugly[0] = 1
    - inisialisasi index i2, i3, i5 ke elemen pertama
    - inisialisasi 3 generator untuk ugly number berikutnya.
        next_multiple_2 = ugly[i2] * 2;
        next_multiple_3 = ugly[i3] * 3;
        next_multiple_5 = ugly[i5] * 5;
    - lakukan iterasi untuk mengisi ugly number

*/

// ======================================================================================

/** Iterative Solution -- Tabulation **/

size_t algorithm(size_t N)
{
    // menampung ugly number yang dibangkitkan
    size_t ugly[N];

    // index berdasarkan kelipatan faktor 2, 3, atau 5
    size_t i2 = 0, i3 = 0, i5 = 0;

    // generator
    size_t next_multiple_2 = 2;
    size_t next_multiple_3 = 3;
    size_t next_multiple_5 = 5;
    size_t next_ugly   = 1;

    // inisialisasi elemen ugly pertama
    ugly[0] = 1;
    
    for (size_t i = 1; i < N; i++)
    {
        // cari nilai minimum dari 3 baris independen
        next_ugly = std::min(next_multiple_2, std::min(next_multiple_3, next_multiple_5));

        // masukkan bilangan ke baris
        ugly[i] = next_ugly;

        // update nilai di baris
        if (next_ugly == next_multiple_2)
        {
            i2 ++;
            next_multiple_2 = ugly[i2] * 2;
        }
        if (next_ugly == next_multiple_3)
        {
            i3 ++;
            next_multiple_3 = ugly[i3] * 3;
        }
        if (next_ugly == next_multiple_5)
        {
            i5 ++;
            next_multiple_5 = ugly[i5] * 5;
        }
    }

    // ketika berakhir, telah dibangkitkan N - 1 bilangna
    return next_ugly;
}