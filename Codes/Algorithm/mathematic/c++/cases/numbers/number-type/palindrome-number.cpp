/*
    Palindrome Number
    Archive of Reversing.ID
    Algorithm (Mathematics/Numbers)
    
Compile:
    [clang]
    $ clang++ palindrome-number.cpp -o palindrome-number

    [gcc]
    $ g++ palindrome-number.cpp -o palindrome-number

    [msvc]
    $ cl palindrome-number.cpp

Run:
    $ palindrome-number
*/

/*
    Palindrome adalah kata, frasa, angka, maupun susunan yang dapat dibaca dengan sama
    baik dari depan maupun dari belakang.

    Palindrome Number adalah sebuah bilangan yang memiliki sifat palindrome 

Contoh: 1345431
*/

// ======================================================================================

/*
    Recursive Solution
    Number Checking -- Naive Method
    Periksa apakah suatu bilangan merupakan Palindrome Number.
*/

size_t reverse(size_t num, size_t t)
{
    if (num == 0)
        return t;
    
    t = (t * 10) + (num % 10);
    return reverse(num / 10, temp);
}

bool algorithm(size_t num)
{
    return num == reverse(num, 0);
}

// ======================================================================================

/*
    Iterative Solution
    Number Checking -- Naive Method
    Periksa apakah suatu bilangan merupakan Palindrome Number.
*/

bool algorithm(size_t num)
{
    size_t t = 0, num2 = num;
    
    while (num2 > 0)
    {
        t = (t * 10) + (num2 % 10);
        num2 = num2 / 10;
    }

    return t == num;
}