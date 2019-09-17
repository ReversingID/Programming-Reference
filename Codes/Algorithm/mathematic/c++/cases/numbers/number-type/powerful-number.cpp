/*
    Powerful Number
    Archive of Reversing.ID
    Algorithm (Mathematics/Numbers)
    
Compile:
    [clang]
    $ clang++ powerful-number.cpp -o powerful-number

    [gcc]
    $ g++ powerful-number.cpp -o powerful-number

    [msvc]
    $ cl powerful-number.cpp

Run:
    $ powerful-number
*/
#include <vector>

/*
    Sebuah bilangan N merupakan Powerful Number jika untuk setiap faktor prima P darinya,
    P^2 dapat habis membagi N.

Baris Powerful Number:
    1, 4, 8, 9, 16, 25, 27, 32, 36, 49, 64, ...
*/

// ======================================================================================

/*
    Testing
    Periksa apakah suatu bilangan merupakan Powerful Number.
*/

bool algorithm(size_t num)
{
    size_t power;

    // eliminasi semua faktor 2
    power = 0;
    while (num % 2 == 0)
    {
        power ++;
        num = num / 2;
    }

    // jika faktor prima tidak memiliki pangkat tinggi, maka tidak dapat mencapai kuadrat
    if (power == 1)
        return false;
    
    for (size_t i = 3, batas = sqrt(num); i <= batas; i += 2)
    {
        if (num % i == 0)
        {
            power = 0;
            while (num % i == 0)
            {
                power ++;
                num = num / i;
            }

            // tidak mencapai kuadrat
            if (power == 1)
                return false;
        }
    }

    return true;
}