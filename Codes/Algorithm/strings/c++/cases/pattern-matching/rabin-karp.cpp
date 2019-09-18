/*
    Rabin-Karp
    Archive of Reversing.ID
    Algorithm (Strings)
    
Compile:
    [clang]
    $ clang++ rabin-karp.cpp -o rabin-karp

    [gcc]
    $ g++ rabin-karp.cpp -o rabin-karp

    [msvc]
    $ cl rabin-karp.cpp

Run:
    $ rabin-karp
*/
#include <vector>

/*
    Pattern Searching.

Masalah:
    Diberikan teks dengan panjang N, dan pola dengan panjang M.
    Jika teks memuat pola, tentukan posisi awal kemunculan pola tersebut.

Contoh:
    teks = "archive of REVERSING.ID "
    pola = "REV"
    output = pattern found at index 11

Solusi:
    - RK melakukan iterasi dan pencocokan karakter per karakter
    - String dibagi menjadi substring dan dihitung hash value, pencocokan dilakukan
      antar hash value substring. Hash yang dihitung
        - pattern
        - semua substring text dengan panjang m

*/

// ======================================================================================

// jumlah karakter dalam alfabet (ASCII)
#define NO_OF_CHARS 256;

// ======================================================================================

/* 
melakukan hashing

kriteria hash:
    - hash dari shift selanjutnya harus dapat dihitung dengan efisien dari hash sekarang
      dan karakter berikutnya di text.

*/

auto algorithm(char text[], int N, char pattern[], int M, int q)
{
    int i, j;
    int p_hash = 0;  // hash value untuk pattern
    int t_hash = 0;  // hash value untuk text
    int h = 1;

    std::vector<int> result;

    // nilai dari h adalah pow(NO_OF_CHARS, M-1) % q
    for (i = 0; i < M - 1; i++)
        h = (h * NO_OF_CHARS) % q;
    
    // hitung nilai hash dari pattern dan window pertama dari text
    for (i = 0; i < M; i++)
    {
        p_hash = (NO_OF_CHARS * p_hash + pattern[i]) % q;
        t_hash = (NO_OF_CHARS * t_hash + text[i]) % q;
    }

    // geser satu per satu
    for (i = 0; i <= N - M; i++)
    {
        // periksa apakah hash sama.
        // jika sama, cek karakter satu per satu
        if (p_hash == t_hash)
        {
            // bandingkan substring text dengan pattern
            for (j = 0; j < M && text[i + j] == pattern[j]; j++);

            if (j == M)
                result.push_back(i);
        }

        // hitung hash untuk window berikutnya
        if (i < N - M)
        {
            // perbarui hash dengan menghapus digit awal dan menambah digit baru
            t_hash = (NO_OF_CHARS * (t_hash - text[i] * h) + text[i + M]) % q;

            // jika t negatif, ubah menjadi positif
            if (t_hash < 0)
                t_hash += q;
        }
    }

    return result;
}

// wrapper
auto algorithm(char text[], int N, char pattern[], int M)
{
    // bilangan prima
    int q = 101;

    return algorithm(text, N, pattern, M, q);
}