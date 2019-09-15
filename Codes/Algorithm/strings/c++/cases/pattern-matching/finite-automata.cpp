/*
    Finite Automata
    Archive of Reversing.ID
    Algorithm (Strings)
    
Compile:
    [clang]
    $ clang++ finite-automata.cpp -o finite-automata

    [gcc]
    $ g++ finite-automata.cpp -o finite-automata

    [msvc]
    $ cl finite-automata.cpp

Run:
    $ finite-automata
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
    BBangun array 2D yang merepresentasikan Finite Automate.
    Pencarian dilakukan dari state awal automata dengan karakter pertama dari text. Di 
    setiap langkah, kita ambil karakter berikutnya dari text dan berpindah ke state 
    berikutnya. Ketika state akhir tercapai maka pattern ditemukan.

    Pembangunan Finite Automata merupakan bagian yang tricky.

    Jumlah state di Finite Automata yang dibangun adalah M + 1.
*/

// ======================================================================================

#define NO_OF_CHARS 256

// ======================================================================================

/** Time complexity O(M^3 * NO_OF_CHARS) **/

int getNextState(char pattern[], int M, int state, int c)
{
    // jika karakter c sama dengan karakter berikutnya di pattern, increment state
    if (state < M && c == pattern[state])
        return state + 1;
    
    // ns menyimpan state berikutnya
    int ns, i;

    // ns akan menyimpan prefix terpanjang yang menjadi suffix di pattern[0 .. state - 1]c

    // mulai dari nilai terbesar yang dimungkinkan dan berhenti ketika ditemukan prefix
    // yang juga merupakan suffix
    for (ns = state; ns > 0; ns--)
    {
        if (pattern[ns - 1] == c)
        {
            i = 0;
            while (i < ns - 1 && pattern[i] == pattern[state - ns + 1 + i])
                i ++;
            
            if (i == ns - 1)
                return ns;
        }
    }

    return 0;
}

// bangun table Finite Automata untuk pattern yang diberikan
void preprocess(int FA[][NO_OF_CHARS], char pattern[], int M)
{
    int state, c;

    for (state = 0; state <= M; state++)
        for (c = 0; c < NO_OF_CHARS; c++)
            FA[state][c] = getNextState(pattern, M, state, c);
}

// ======================================================================================

/** Time complexity O(M * NO_OF_CHARS) **/

/* 
Menggunakan konstruksi array yang serupa dengan KMP.

Langkah:
    1. Isi baris pertama. Semua baris pertama selalu 0 kecuali entry untuk pattern[0]
       yang bernilai 1 (selalu menuju state 1)
    2. inisialisasi LPS sebagai 0 untuk menunjuk index pertama.
    3. Lakukan hal berikut untuk baris i = 1 ke M
        a. salin entry dari baris dengan index yang sama dengan LPS
        b. update entry untuk pattern[i] ke i + 1
        c. update LPS menuju state berikutnya.
*/

void preprocess(int FA[][NO_OF_CHARS], char pattern[], int M)
{
    int i, lps = 0, c;

    // inisialisasi baris pertama
    for (c = 0; c < NO_OF_CHARS; c++)
        FA[0][c] = 0;
    
    FA[0][pattern[0]] = 1;

    // isi entry baris lain
    for (i = 1; i <= M; i++)
    {
        // calin nilai dari baris dengan index lps
        for (c = 0; c < NO_OF_CHARS; c++)
            FA[i][c] = FA[lps][c];
        
        // update entry terkait karakter ini
        FA[i][pattern[i]] = i + 1;

        /// update lps untuk baris berikutnya
        if (i < M)
            lps = FA[lps][pattern[i]];
    }
}

// ======================================================================================

auto algorithm(char text[], int N, char pattern[], int M)
{
    int i, state;
    int FA[M + 1][NO_OF_CHARS];

    // posisi ditemukan pola
    std::vector<int> result;

    // bangun Finite Automata
    preprocess(FA, pattern, M);

    // lakukan pencarian di Z-array
    for (i = 0, state = 0; i < N; i++)
    {
        // berpindah ke state berikutnya
        state = FA[state][text[i]];
        if (state == M)
            result.push_back(i - M + 1);
    }

    return result;
}