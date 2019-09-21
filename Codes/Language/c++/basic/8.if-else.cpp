/*
    IF-ELSE
    Archive of Reversing.ID
    Programming Language (C++)

    Statement IF untuk pengujian kondisi.
*/

#include <iostream>

int main(int argc, char* argv[])
{
    // definisi variabel lokal
    int a = 100;

    // periksa ekspresi boolean dengan statement IF
    if (a < 20) 
    {   // jika kondisi benar, maka cetak
        std::cout << "a is less than 20" << std::endl;
    }
    else 
    {   // jika kondisi salah, maka cetak
        std::cout << "a is not less than 20" << std::endl;
    }

    std::cout << "Value of a is : " a << std::endl;

    return 0;
}