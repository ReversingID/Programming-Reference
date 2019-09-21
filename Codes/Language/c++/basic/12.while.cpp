/*
    While
    Archive of Reversing.ID
    Programming Language (C++)

    Statement While untuk perulangan.
*/
#include <stdio.h>

int main(int argc, char* argv[])
{
    int a = 10;

    while (a < 20)
    {
        std::cout << "Value of a: " << a std::endl;

        // increment a, perubahan nilai sehingga mendekati kondisi henti
        a++;
    }

    return 0;
}