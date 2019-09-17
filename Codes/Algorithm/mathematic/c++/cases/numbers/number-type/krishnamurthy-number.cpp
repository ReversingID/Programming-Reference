/*
    Krishnamurthy Number
    Archive of Reversing.ID
    Algorithm (Mathematics/Numbers)
    
Compile:
    [clang]
    $ clang++ krishnamurthy-number.cpp -o krishnamurthy-number

    [gcc]
    $ g++ krishnamurthy-number.cpp -o krishnamurthy-number

    [msvc]
    $ cl krishnamurthy-number.cpp

Run:
    $ krishnamurthy-number
*/

/*
    Krishnamurthy Number adalah bilangan dengan penjumlahan dari faktorial setiap digit 
    menghasilkan bilangan itu sendiri.

Contoh:
    145 -> 1! + 4! + 5! = 1 + 24 + 120 = 145

Catatan:
    Nama lain: Strong Number
*/

// ======================================================================================

// menghasilkan faktorial dari bilangan
size_t factorial(size_t num)
{
    size_t result = 1;

    while (num != 0)
    {
        result = result * num;
        num --;
    }

    return result;
}

// ======================================================================================

/*
    Iterative Solution
    Testing -- Naive Method
    Periksa apakah suatu bilangan merupakan Krishnamurthy Number.
*/

bool algorithm(size_t num)
{
    size_t sum = 0, t = num;

    while (t != 0)
    {
        // dapatkan faktorial dari digit terakhir dan tambahkan ke sum
        sum += factorial(t % 10);

        // perbarui t dengan menghilangkan digit terakhir
        t = t / 10;
    }

    return (sum == num);
}

// ======================================================================================

/*
    Iterative Solution
    Testing -- Precached
    Periksa apakah suatu bilangan merupakan Krishnamurthy Number.
*/

bool algorithm(size_t num)
{
    size_t sum = 0, t = num;
    size_t cache[10];

    cache[0] = cache[1] = 1;
    for (size_t i = 2; i < 10; i++)
        cache[i] = i * cache[i - 1];
    
    while (t != 0)
    {
        // dapatkan faktorial dari digit terakhir dan tambahkan ke sum
        sum += cache[t % 10];

        // perbarui t dengan menghilangkan digit terakhir
        t = t / 10;
    }

    return (sum == num);
}