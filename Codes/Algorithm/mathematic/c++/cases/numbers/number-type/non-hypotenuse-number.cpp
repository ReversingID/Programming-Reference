/*
    Non-Hypotenuse Number
    Archive of Reversing.ID
    Algorithm (Mathematics/Numbers)
    
Compile:
    [clang]
    $ clang++ non-hypotenuse-number.cpp -o non-hypotenuse-number

    [gcc]
    $ g++ non-hypotenuse-number.cpp -o non-hypotenuse-number

    [msvc]
    $ cl non-hypotenuse-number.cpp

Run:
    $ non-hypotenuse-number
*/
#include <cmath>

/*
    Non-Hypotenuse Number adalah bilangan natural yang bila dikuadratkan tidak bisa
    diekspresikan sebagai penjumlahan dua buah bilangan bulat kuadrat.

        C^2 != A^2 + B^2
    
    untuk segala A dan B
*/

// ======================================================================================

/*
    Iterative Solution
    Testing -- Heuristic
    Periksa apakah suatu bilangan merupakan Non-Hypotenuse Number.
*/

/*
Langkah:
    - cari semua faktor prima dari num
    - periksa apakah faktor prima memenuhi 4k + 1
    - non-hypotenuse number memiliki faktor yang tidak dalam bentuk 4k + 1
*/

bool algorithm(size_t num)
{
    // 2 adalah bilangan prima yang tidak membentuk 4k + 1
    while (num % 2 == 0)
        num = num / 2;
    
    // di titik ini, num adalah bilangan ganjil.
    for (size_t i = 3, batas = sqrt(num); i <= batas; i += 2)
    {
        // jika i habis membagi num, periksa apakah i berbentuk 4k + 1
        if (num % i == 0)
        {
            if ((i - 1) % 4 == 0)
                return false;
            
            // keluarkan semua faktor i 
            while (num % i == 0)
                num = num / i;
        }
    }

    return ((num - 1) % 4 > 0);
}