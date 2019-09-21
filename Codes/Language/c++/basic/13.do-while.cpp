/*
    Do-While
    Archive of Reversing.ID
    Programming Language (C++)

    Statement Do-While untuk perulangan.
*/
#include <iostream>

int main(int argc, char* argv[])
{
    int a = 10;

    do
    {
        std::cout << "Value of a: " << a << std::endl;

        // increment a, perubahan nilai sehingga mendekati kondisi henti
        a++;
    } while (a < 20);

    return 0;
}