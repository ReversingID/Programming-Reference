/*
    String
    Archive of Reversing.ID
    Programming Language (C++)

    Representasi String
*/

#include <cstring>

/*
    Terdapat dua tipe string di C++:
        - C-Style
        - C++ String class
    
    Pada C-Style, string diimplementasikan sebagai array of character dengan
    0 atau \0 sebagai batas akhir string.

    Pada C++ String class, terdapat sebuah class yang merepresentasikan string
    dengan operasinya (akan dibahas pada class).
*/

int main(int argc, char* argv[])
{
    // C-Style string, deklarasi array dengan karakter tiap elemennya
    char str1[] = {'R', 'e', 'v', 'e', 'r', 's', 'i', 'n', 'g', '.', 'I', 'D', 0};
    char str2[] = "Programming";
    char str3[32];

    // C++ String class
    std::string str4 = "Reversing.ID";
    std::string str5 = "Programming";
    std::string str6;

    // -- Operasi C-Style string
    // copy
    strcpy(str3, str1);

    // concatenation
    strcat(str3, str1);


    // -- Operasi C++ String class
    // copy
    str6 = str4;

    // concatenation
    str6 += str5;

    return 0;
}