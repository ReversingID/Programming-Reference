/*
    Greedy
    Archive of Reversing.ID
    Algorithm


Compile:
    [clang]
    $ clang++ greedy.cpp -o greedy

    [gcc]
    $ g++ greedy.cpp -o greedy

    [msvc]
    $ cl greedy.cpp

Run:
    $ greedy
*/
#include <set>

/*
    Skema umum algoritma Greedy:

    - Himpunan kandidat (C)
    - Himpunan solusi (S)
    - Fungsi seleksi (selection)
    - Fungsi kelayakan (feasible)
    - Fungsi obyektif (objective)
*/

// ======================================================================================

/* Mengambil kandidat */
int  selection(int candidates[], size_t size);

/* memeriksa kelayakan */
bool feasible(int solution[], size_t size);

/* memeriksa kelengkapan solusi */
bool objective(int solution[], size_t size);


bool algorithm(int candidates[], size_t clength, int solution[], size_t & slength)
{
    size_t slen = 0, clen = clength;

    while (! objective(solution, slen) && clen > 0)
    {
        // pilih kandidat
        int c = selection(candidates, clen);

        // buang kandidat dari himpunan kandidat
        remove(candidates, c);
        clen --;

        // tambahkan kandidat ke himpunan solusi
        add(solution, c);

        if (! feasible(solution, slen + 1))
            slen ++;
    }

    if (objective(solution, slen))
    {
        slength = slen;
        return true;
    }

    return false;
}