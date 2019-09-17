/*
    Achilles Number
    Archive of Reversing.ID
    Algorithm (Mathematics/Numbers)
    
Compile:
    [clang]
    $ clang++ achilles-number.cpp -o achilles-number

    [gcc]
    $ g++ achilles-number.cpp -o achilles-number

    [msvc]
    $ cl achilles-number.cpp

Run:
    $ achilles-number
*/

/*
    Achilles Number adalah bilangan yang Powerful tapi bukan Perfect Power 
    (kuadrat sempurna).

Baris Achilles Number:
    72, 108, 200, 288, 392, 432, 500, 648, 675, 800, 864, 968, ...
*/

// ======================================================================================

// periksa apakah bilangan merupakan Powerful Number. Lihat powerful-number.cpp
bool powerful_test(size_t num);

// periksa apakah bilangan merupakan perfect-power. Lihat perfect-power-number.cpp
bool perfect_power_test(size_t num);

// ======================================================================================

/* 
    Iterative Solution
    Testing
    Periksa apakah bilangan merupakan Achilles Number
*/

bool algorithm(size_t num)
{
    return (powerful_test(num) && !perfect_power_test(num));
}