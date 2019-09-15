/*
    Z-Array Algorithm
    Archive of Reversing.ID
    Algorithm (Strings)
    
Compile:
    [clang]
    $ clang++ z-array.cpp -o z-array

    [gcc]
    $ g++ z-array.cpp -o z-array

    [msvc]
    $ cl z-array.cpp

Run:
    $ z-array
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
    Bentuk Z array.
    Element Z[i] menyimpan panjang substring terpanjang dari str[i] yang juga merupakan
    prefix dari str[0 .. N-1].

    Gabungkan pattern dan text menjadi string "P$T" dengan P = Pattern, T = Text, dan 
    $ = karakter spesial yang tak ada di pattern maupun text. Kemudian bangun Z-array.
    Jika elemen Z pada titik tertentu bernilai sama dengan panjang pattern, maka pattern 
    ditemukan.
*/

// ======================================================================================

/*
    Gabungkan (concatenate) pattern dan text menjadi string "P$T" dengan P = Pattern, 
    T = Text, dan $ = karakter spesial yang tak ada di pattern maupun text.
    Bangun Z-array dari "P$T".

    Simpan interval [L, R] yaitu prefix substring (substring yang merupakan prefix).
*/

void preprocess(int z[], char text[], int N, char pattern[], int M)
{
    int i, j, k;
    int L, R;
    int C = N + M + 1;
    char concat[C];

    // Gabungkan Pattern $ Text
    i = 0;
    for (j = 0; j < M; i++, j++)
        concat[i] = pattern[j];
    
    concat[i++] = '$';

    for (j = 0; j < N; i++, j++)
        concat[i] = text[j];

    /*
    Bangun z-array
    interval [L, R] membuat window yang mencocokkan dengan prefix string
    */
    L = R = 0;
    for (i = 1; i < C; i++)
    {
        // jika i > R maka tak ada yang cocok sehingga kita hitung z[i] secara naif
        if (i > R)
        {
            L = R = i;

            /*
            di awal, R - L = 0, sehingga pengecekan akan dilakukan dari index 0.

            */
            while (R < C && concat[R - L] == concat[R])
                R ++;
            
            z[i] = R - L;
            R --;
        }
        else 
        {
            // k = i - L sehingga k berkaitan dengan jumlah kecocolan di interval [L, R]
            k = i - L;

            if (z[k] < R - i + 1)
                z[i] = z[k];
            else 
            {
                L = i;

                while (R < C && concat[R - L] == concat[R])
                    R ++;
                
                z[i] = R - L;
                R --;
            }
        }
    }
}

auto algorithm(char text[], int N, char pattern[], int M)
{
    int i;
    int C = N + M + 1;
    int z[C];

    // posisi ditemukan pola
    std::vector<int> result;

    // bangun Z-array
    preprocess(z, text, N, pattern, M);

    // lakukan pencarian di Z-array
    for (i = 0; i < C; i++)
    {
        if (z[i] == M)
            result.push_back(i - M - 1);
    }

    return result;
}