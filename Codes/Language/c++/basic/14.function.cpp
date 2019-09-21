/*
    Function
    Archive of Reversing.ID
    Programming Language (C++)

    Fungsi sebagai potongan kode.
*/
#include <stdio.h>

int max(int num1, int num2)
{
    // deklarasi variabel lokal yang dibutuhkan
    int result;

    // operasi sebuah fungsi
    if (num1 > num2)
        result = num1;
    else 
        result = num2;
    
    // kembalikan nilai yang sesuai
    return result;
}

int main(int argc, char* argv[])
{
    // deklarasi variabel dan isi dengan nilai dari kembalian fungsi
    int a = max(3, 5);
    int b = max(7, 10);

    std::cout << "max(3, 5) = " << a << std::endl;
    std::cout << "max(7,10) = " << b << std::endl;

    return 0;
}