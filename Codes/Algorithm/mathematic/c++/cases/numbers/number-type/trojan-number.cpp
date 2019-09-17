/*
    Trojan Number
    Archive of Reversing.ID
    Algorithm (Mathematics/Numbers)
    
Compile:
    [clang]
    $ clang++ trojan-number.cpp -o trojan-number

    [gcc]
    $ g++ trojan-number.cpp -o trojan-number

    [msvc]
    $ cl trojan-number.cpp

Run:
    $ trojan-number
*/

/*
    Trojan Number adalah Strong Number (Krishnamurthy Number) tapi bukan sebuah
    pangkat sempurna (Perfect Power). 
*/

// ======================================================================================

// periksa apakah bilangan merupakan Strong Number. Lihat powerful-number.cpp
bool strong_test(size_t num);

// periksa apakah bilangan merupakan perfect-power. Lihat perfect-power-number.cpp
bool perfect_power_test(size_t num);

// ======================================================================================

/*
    Iterative Solution
    Testing -- Naive Method
    Periksa apakah suatu bilangan merupakan Trojan Number.
*/

bool algorithm(size_t num)
{
    return (strong_test(num) && !perfect_power_test(num));
}