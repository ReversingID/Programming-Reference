/*
    KMP (Knuth-Morris-Pratt)
    Archive of Reversing.ID
    Algorithm (Strings)
    
Compile:
    [clang]
    $ clang++ knuth-morris-pratt.cpp -o knuth-morris-pratt

    [gcc]
    $ g++ knuth-morris-pratt.cpp -o knuth-morris-pratt

    [msvc]
    $ cl knuth-morris-pratt.cpp

Run:
    $ knuth-morris-pratt
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
    KMP menggunakan degenerating algorithm, pola yang berpola dengan kemunculan lebih dari 
    sekali).

    Pencarian dilakukan berdasarkan blok / window.
    Ketika dideteksi ada mismatch (setelah beberapa match), kita akan melewati beberapa 
    karakter 

*/

// ======================================================================================

/* 
membangun tabel bantu untuk memproses pencarian

lps[i] = prefix layak terpanjang dari pattern[0 .. i] yang juga merupakan suffix 
         pattern[0 ..i]

contoh:
    pattern: "AAAA"
    lps:    [ 0, 1, 2, 3 ]

    pattern: "ABCDE"
    lps:    [ 0, 0, 0, 0, 0 ]

    pattern: "AABAACAABAA"
    lps:    [ 0, 1, 0, 1, 2, 1, 2, 3, 4, 5 ]
*/
void preprocess(int lps[], int M, char pattern[])
{
    // panjang LPS sebelumnya
    int length = 0;
    int i;

    lps[0] = 0;     // huruf pertama tak memiliki prefix

    i = 1;
    while (i < M)
    {
        // menghitung kesamaan karakter ini dengan karakter sebelumnya
        if (pattern[i] == pattern[length])
        {
            length ++;
            lps[i] = length;
            i ++;
        }
        else 
        {
            if (length != 0)
                length = lps[length - 1];
            else 
            {
                lps[i] = 0;
                i++;
            }
                
        }
    }
}

auto algorithm(char text[], int N, char pattern[], int M)
{
    // digunakan untuk melompati beberapa karakter ketika matching.
    int lps[M];
    int i, j;

    // posisi ditemukan pola
    std::vector<int> result;

    // preprocess pola, inisialisasi LPS
    preprocess(lps, M, pattern);

    i = j = 0;
    while (i < N)
    {
        if (pattern[j] == text[i])
        {
            i++;
            j++;
        }

        if (j == M)
        {
            result.push_back(i - j);
            j = lps[j - 1];             // skip beberapa karakter sesuai prefix
        }

        // mismatch setelah j match
        else if (i < N && pattern[j] != text[i])
        {
            // tidak perlu match lps[0 .. lps[j - 1]] karakter karena dipastikan match
            if (j != 0)
                j = lps[j - 1];
            else 
                i = i + 1;
        }
    }

    return result;
}