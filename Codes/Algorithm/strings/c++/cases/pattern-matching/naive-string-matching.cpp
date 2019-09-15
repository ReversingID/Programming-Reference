/*
    Naive String Matching
    Archive of Reversing.ID
    Algorithm (Strings)
    
Compile:
    [clang]
    $ clang++ naive-string-matching.cpp -o naive-string-matching

    [gcc]
    $ g++ naive-string-matching.cpp -o naive-string-matching

    [msvc]
    $ cl naive-string-matching.cpp

Run:
    $ naive-string-matching
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

*/

// ======================================================================================

auto algorithm(char text[], int N, char pattern[], int M)
{
    int t, p;

    // posisi ditemukan pola
    std::vector<int> result;
    
    // geser pattern satu per satu 
    for (t = 0; t <= N - M; t++)
    {
        p = 0;
        while (p < M && text[t + p] == pattern[p]) p++;
        
        if (p == M)
            result.push_back(t);
    }

    return result;
}