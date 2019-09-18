/*
    Boyer-Moore
    Archive of Reversing.ID
    Algorithm (Strings)
    
Compile:
    [clang]
    $ clang++ boyer-moore.cpp -o boyer-moore

    [gcc]
    $ g++ boyer-moore.cpp -o boyer-moore

    [msvc]
    $ cl boyer-moore.cpp

Run:
    $ boyer-moore
*/
#include <vector>

/*
    Pattern Searching.

    Boyer Moore adalah kombinasi dari dua pendekatan:
        - bad character heuristic
        - good suffix heuristic
    
    Kedua heuristik dipakai secara independen untuk melakukan pencarian pattern di text.
    Boyer Moore memulai pencocokan dari karakter terakhir pattern.

Masalah:
    Diberikan teks dengan panjang N, dan pola dengan panjang M.
    Jika teks memuat pola, tentukan posisi awal kemunculan pola tersebut.

Contoh:
    teks = "archive of REVERSING.ID "
    pola = "REV"
    output = pattern found at index 11

*/

// ======================================================================================

/*

Bad Character Heuristic:
    Karakter dari text yang tidak cocok dengan karakter terkini dari pattern disebut 
    Bad Character. Ketika terjadi mismatch, shift pattern hingga
        - mismatch menjadi match
        - pattern P melebihi mismatch character
*/
#define NO_OF_CHARS     256

void preprocess(int badchars[NO_OF_CHARS], char pattern[], int M)
{
    int i;

    // awalnya, semua kemunculan adalah -1
    for (i = 0; i < NO_OF_CHARS; i++)
        badchars[i] = -1;
    
    // bangun bad chars
    for (i = 0; i < M; i++)
        badchars[pattern[i]] = i;
}

auto algorithm(char text[], int N, char pattern[], int M)
{
    int lookup[NO_OF_CHARS];
    int t, p;

    // posisi ditemukan pola
    std::vector<int> result;
    
    // bangun larik bad chars sebagai heuristik pencarian
    preprocess(lookup, pattern, M);

    t = 0;
    while (t <= N - M)
    {
        p = M - 1;

        // iterasi pattern dari kanan ke kiri selama karakter pattern dan text cocok
        while (p >= 0 && pattern[p] == text[t + p])
            p--;
        
        // jika pattern muncul di shift saat ini, index p akan bernilai -1
        if (p < 0)
        {
            result.push_back(t);

            /* 
            shift pattern sehingga karakter berikutnya di teks align dengan 
            kemunculan terakhir di pattern.
            */
            if (t + M < N)
                t += M - lookup[text[t + M]];
            else 
                t ++;
        }
        else 
            t += std::max(1, p - lookup[text[t + p]]);
    }

    return result;
}

// ======================================================================================

/*
Good Suffix Heuristic:
    Terdapat substring t di Text dan Pattern. 
    Shift pattern hingga:
        - terdapat kemunculan t di Pattern cocok dengan t di Text
        - Prefix Pattern cocok dengan suffix t
        - P melebihi t
*/
void preprocess(int bpos[], int shift[], char pattern[], int M)
{
    int i, j;

    for (i = 0; i <= M; i++)
        shift[i] = 0;
    
    // preprocess strong suffix
    i = M;
    j = M + 1;
    bpos[i] = j;

    while (i > 0)
    {
        while (j <= M && pattern[i - 1] != pattern[j - 1])
        {
            if (shift[j] == 0)
                shift[j] = j - i;

            j = bpos[j];
        }

        i--;
        j--;
        bpos[i] = j;
    }

    // preprocess case
    j = bpos[0];

    for (i = 0; i <= M; i++)
    {
        if (shift[i] == 0)
            shift[i] = j;
        
        if (i == j)
            j = bpos[j];
    }
}

auto algorithm(char text[], int N, char pattern[], int M)
{
    int t, p;
    int bpos[M + 1], shift[M + 1];

    // posisi ditemukan pola
    std::vector<int> result;
    
    // bangun larik good suffix sebagai heuristik pencarian
    preprocess(bpos, shift, pattern, M);

    t = 0;
    while (t <= N - M)
    {
        p = M - 1;

        // iterasi pattern dari kanan ke kiri selama karakter pattern dan text cocok
        while (p >= 0 && pattern[p] == text[t + p])
            p--;
        
        // jika pattern muncul di shift saat ini, index p akan bernilai -1
        if (p < 0)
        {
            result.push_back(t);

            t += shift[0];
        }
        else 
            t += shift[p + 1];
    }

    return result;
}