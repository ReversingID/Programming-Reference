/*
    Pentagonal Number
    Archive of Reversing.ID
    Algorithm (Mathematics/Numbers)
    
Compile:
    [clang]
    $ clang++ pentagonal-number.cpp -o pentagonal-number

    [gcc]
    $ g++ pentagonal-number.cpp -o pentagonal-number

    [msvc]
    $ cl pentagonal-number.cpp

Run:
    $ pentagonal-number
*/

/*
    Pentagonal Number adalah bilangan yang bisa disusun sehingga dapat membentuk sebuah
    pentagon.

    Pentagonal Number adalah satu wujud dari Polygonal Number.
    Pada Polygonal Number, sebuah bilangan merepresentasikan titik-titik yang disusun 
    membentuk poligon sama sisi.

    Suku ke-N Polygonal Number memenuhi persamaan:

        P(S, N) = (S - 2) N (N - 1) / 2 + N 
    
    Dimana S adalah jumlah sisi Polygonal Number.
    Maka rumus Pentagonal Number sebagai:

        P(N) = 3 N (N - 1) / 2 + N

Baris Pentagonal: 
    1, 5, 22

*/

// ======================================================================================

/* 
    Iterative Solution
    Testing
    Periksa apakah bilangan merupakan Pentagonal Number
*/

bool algorithm(size_t num)
{
    size_t i = 1, t;

    do 
    {
        t = (3 * i * i - i) / 2;
        i ++;
    } while (t < num);

    // periksa apakah hasil perhitungan bernilai sama dengan num
    return (t == num);
}

// ======================================================================================

/*
    Iterative Solution
    N-th Term Generator
    Bangkitkan Pentagonal Number suku ke-N
*/

size_t algorithm(size_t N)
{
    return (3 * N * N - N) / 2;
}

// ======================================================================================

/*
    Iterative Solution
    Sequence Generator
    Bangkitkan N buah bilangan Pentagonal
*/

auto algorithm(size_t N)
{
    std::vector<size_t> result;

    // bangun solusi
    for (size_t i = 1; i <= N; i++)
        result.push_back((3 * N * N - N) / 2);

    return result;
}