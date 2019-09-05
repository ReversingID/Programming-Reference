/*
    String Matching
    Archive of Reversing.ID
    Algorithm (Brute-Force)
    
Compile:
    [clang]
    $ clang++ string-matching.cpp -o string-matching

    [gcc]
    $ g++ string-matching.cpp -o string-matching

    [msvc]
    $ cl string-matching.cpp

Run:
    $ string-matching
*/


/*
Masalah:
    Diberikan sebuah string Text dengan panjang n karakter serta sebuah string Pattern
    dengan panjang m karakter. Tentukan apakah Pattern merupakan substring dari Text.
*/

// ======================================================================================

bool algorithm(char text[], size_t n, char pattern[], size_t m)
{
    size_t  i, j;

    for (i = 0; i < n; i++)
    {
        // apakah huruf ini sama dengan huruf awalan pattern
        if (text[i] == pattern[0])
        {
            // cocokkan huruf per huruf
            for (j = 1; j < m && (i + j) < n; j++)
            {
                if (text[i + j] != pattern[j])
                    break;
            }

            if (j >= m)
                return true;
        }
    }

    return false;
}