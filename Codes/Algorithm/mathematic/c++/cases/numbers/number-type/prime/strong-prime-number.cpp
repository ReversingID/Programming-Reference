/*
    Strong-Prime Number
    Archive of Reversing.ID
    Algorithm (Mathematics/Numbers)
    
Compile:
    [clang]
    $ clang++ strong-prime-number.cpp -o strong-prime-number

    [gcc]
    $ g++ strong-prime-number.cpp -o strong-prime-number

    [msvc]
    $ cl strong-prime-number.cpp

Run:
    $ strong-prime-number
*/

/*
    Sebuah bilangan N merupakan Strong-Prime Number jika untuk setiap faktor prima P darinya,
    P^2 dapat habis membagi N.
*/

// ======================================================================================

// periksa apakah sebuah bilangan merupakan bilangan prima
bool prime_check(size_t num)
{
    if (n <= 1)
        return false;
    if (n <= 3)
        return true;
    
    // keluarkan pengecekan kelipatan 2 dan 3 sehingga kita bisa loop mulai dari 5
    if (num % 2 == 0 || num % 3 == 0)
        return false;
    
    for (size_t i = 5; i * i <= num; i += 6)
        if (num % i == 0 || num % (i + 2) == 0)
            return false;
    
    return true;
}

// ======================================================================================

/*
    Testing -- Naive Method
    Periksa apakah suatu bilangan merupakan Strong-Prime Number.
*/

size_t algorithm(size_t num)
{
    if (num == 2 || !prime_check(num))
        return false;
    
    size_t  prev = num - 1,
            next = num + 1;
    size_t  mean;

    // cari bilangan prima setelah bilangan ini
    while (! prime_check(next))
        next ++;
    
    // cari bilangan prima sebelum bilangan ini
    while (! prime_check(prev))
        prev --;
    
    mean = (prev + next) / 2;

    return (num > mean);
}