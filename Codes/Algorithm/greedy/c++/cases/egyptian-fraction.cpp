/*
    Egyptian Fraction
    Archive of Reversing.ID
    Algorithm (Greedy)
    
Compile:
    [clang]
    $ clang++ egyptian-fraction.cpp -o egyptian-fraction

    [gcc]
    $ g++ egyptian-fraction.cpp -o egyptian-fraction

    [msvc]
    $ cl egyptian-fraction.cpp

Run:
    $ egyptian-fraction
*/
#include <vector>
#include <cmath>

/*
    Setiap pecahan (faction) dapat direpresentasikan sebagai penjumlahan unit fraction.
    Unit fraction adalah pecahan dengan penyebut bernilai satu dan pembilang merupakan 
    bilangan bulat positif (misal: 1/5).

Masalah:
    Terdapat sebuah pecahan. ubahlah bentuk pecahan tersebut menjadi penjumlahan beberapa
    unit fraction bernilai sama.

Langkah:
    - representasikan pecahan dalam bentuk 'nr/dr' dengan dr > nr.
    - ekstrak unit-faction terbesar.

*/

// ======================================================================================

// Mencari GCD (Greatest Common Divisor / FPB)

int gcd(int a, int b)
{
    int c = a % b;

    while (c > 0)
    {
        a = b;
        b = c;
        c = a % b;
    }

    return b;
}

// ======================================================================================

/** Recursive Solution **/

// pecahan harus valid, penyebut atau pembilang tidak boleh bernilai 0

auto algorithm(int num, int denum) -> std::vector<int>
{
    // menyimpan unit-fraction selama operasi
    std::vector<int> result;

    // bila pembilang bernilai 1, maka sudah merupakan unit fraction.
    if (num == 1)
        result.push_back(denum);
    else 
    {
        // cari unit fraction dan penyebut yang baru
        int unit = std::ceil(denum/(num * 1.0));
        int newdenum = gcd((num * unit) - denum, denum * unit);

        // masukkan penyebut dari unit fraction
        result.push_back(unit);

        // cari unit fraction lain
        auto subresult = algorithm(((num * unit) - denum)/newdenum, (denum * unit)/newdenum);
        result.reserve(result.size() + subresult.size());
        result.insert(result.end(), subresult.begin(), subresult.end());
    }

    return result;
}

// ======================================================================================

/** Iterative Solution **/

// pecahan harus valid, penyebut atau pembilang tidak boleh bernilai 0

auto algorithm(int num, int denum)
{
    std::vector<int> result;
    int unit, newdenum;

    while (num > 1)
    {
        // cari unit fraction dan penyebut yang baru
        unit = std::ceil(denum / (num * 1.0));
        newdenum = gcd((num * unit) - denum, denum * unit);

        // masukkan penyebut dari unit fraction
        result.push_back(unit);

        // cari unit fraction lain
        num   = ((num * unit) - denum)/newdenum;
        denum = (denum * unit) / newdenum;
    }

    // pembilang bernilai 1, maka sudah merupakan unit fraction.
    result.push_back(denum);

    return result;
}