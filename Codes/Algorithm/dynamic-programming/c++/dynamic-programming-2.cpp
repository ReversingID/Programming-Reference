/*
    Dynamic Programming
    Archive of Reversing.ID
    Algorithm

    Dynamic Programming dengan pendekatan Tabulation.


Compile:
    [clang]
    $ clang++ dynamic-programming.cpp -o dynamic-programming

    [gcc]
    $ g++ dynamic-programming.cpp -o dynamic-programming

    [msvc]
    $ cl dynamic-programming.cpp

Run:
    $ dynamic-programming
*/

#define NIL     -1
#define MAX     100

/*
    Tabulation
    Bottom-up approach.

    Membangun table berisi nilai setiap kemungkinan dan membangun solusi dengan data terakhir
    hasil pemrosesan di tabel.
*/

// ======================================================================================

/*
    Fungsi iteratif
*/
int algorithm(int size)
{
    int table[size + 1];

    int i;

    // inisialisasi elemen dasar dari tabel.
    table[0] = 0;

    /* 
    iterasi semua kemungkinan subproblem dan catat hasilnya untuk membangun solusi lebih
    besar 
    */
    for (i = 1; i <= size; i++)
    {
        // komputasi solusi saat ini 
        int result = compute(table[i - 1], i);

        // simpan nilai hasil komputasi ke tabel
        table[i] = result;
    }

    // solusi utama merupakanelemen terakhir yang dibangun di tabel
    return table[size];
}