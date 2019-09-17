/*
    Emirp Number
    Archive of Reversing.ID
    Algorithm (Mathematics/Numbers)
    
Compile:
    [clang]
    $ clang++ emirp-number.cpp -o emirp-number

    [gcc]
    $ g++ emirp-number.cpp -o emirp-number

    [msvc]
    $ cl emirp-number.cpp

Run:
    $ emirp-number
*/

/*
    Emirp Number (emirp = prime, dieja dari belakang) adalah bilangan prima yang dihasilkan
    ketika urutan digit dibalik.
    Emirp Number tidak harus palindrom.
*/

// ======================================================================================

/*
    Iterative Solution
    Testing -- Naive Method
    Periksa apakah suatu bilangan merupakan Emirp Number.
*/

/*
    Periksa apakah suatu bilangan merupakan bilangan prima.
    Algoritma pilihan: 
        - Fermat's Little Theorem
        - Lucas Primality Test 
        - Miller-Rabin Primality Test
*/
bool primality_test(size_t num);

// Kembalikan bilangan Emirp yang sesuai jika N merupakan Emirp Number.
// Jika bukan, kembalikan 0.
size_t algorithm(size_t num)
{
    // jika num bukan Emirp number
    size_t result = 0;
    size_t mun;
    size_t d;

    // jika num adalah bilangan prima, operasi pengecekan Emirp dilakukan
    if (primality_test(num))
    {
        // balikkan setiap digit 
        mun = 0;
        while (num != 0)
        {
            d = num % 10;
            mun = mun * 10 + d;
            num /= 10;
        }

        // periksa apakah bilangan ini merupakan bilangan prima, jika ya kembalikan.
        if (primality_test(mun))
            result = mun;
    }
    
    return result;
}