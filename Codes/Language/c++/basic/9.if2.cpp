/*
    IF
    Archive of Reversing.ID
    Programming Language (C++)

    Statement IF untuk pengujian kondisi.
*/
#include <iostream>

int main(int argc, char* argv[])
{
    // definisi variabel lokal
    int a = 0;

    // periksa ekspresi boolean dengan statement IF
    if (a > 0) 
    {   // jika kondisi benar, maka cetak
        std::cout << "a is positive" << std::endl;
    }
    else if (a < 0)
    {   // jika kondisi benar, maka cetak
        std::cout << "a is negative" << std::endl;
    }

    std::cout << "Value of a is : " << a << std::endl;

    return 0;
}