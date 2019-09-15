/*
    Dynamic Programming
    Archive of Reversing.ID
    Algorithm

    Dynamic Programming dengan pendekatan Memoization.


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
    Memoization
    Top-down approach.

    Melakukan lookup ke sebuah tabel sebelum komputasi dilakukan dan hanya melakukan
    komputasi bila hasil komputasi tidak tercatat.
*/

// ======================================================================================

// Misal nilai komputasi merupakan bilangan bulat
int lookup[MAX];


/*
    Inisialisasi lookup tabel dengan NIL atau nilai apapun yang menandai bahwa komputasi
    belum dilakukan.
*/
void initialize()
{
    size_t i;

    for (i = 0; i < MAX; i++)
        lookup[i] = NIL;
}


/*
    Fungsi rekursif.
*/
int algorithm(int sub)
{
    // evaluasi apakah nilai pada subproblem telah dicatat
    if (lookup[sub] == NIL)
    {
        // komputasi
        int result = sub;

        // simpan hasil komputasi ke dalam tabel
        lookup[sub] = result;
    }

    // berikan hasil komputasi
    return lookup[sub];
}