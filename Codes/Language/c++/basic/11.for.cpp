/*
    Foor
    Archive of Reversing.ID
    Programming Language (C++)

    Statement For untuk perulangan.
*/

#include <iostream>

int main(int argc, char* argv[])
{
    int a;

    // perulangan dengan pencacahan
    for (a = 10; a < 20; a = a + 1)
    {
        std::cout << "Value of a: " << a << std::endl;
    }

    return 0;
}