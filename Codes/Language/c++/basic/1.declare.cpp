/*
    Declaration
    Archive of Reversing.ID
    Programming Language (C++)

    Deklarasi berbagai tipe data dasar
*/

int main(int argc, char* argv[])
{
    // deklarasi variabel dan konstanta
    // tipe data:   integral = char, int, long
    //              float = float, double 

    // -- definisi bilangan bulat
    short s;
    int   i;
    long  l;

    // -- definisi bilangan pecahan (floating-point)
    float f;
    double d;

    // variabel vs konstanta
    int i_var; 
    int i_var2, i_var3;
    const int X = 10;
    const int Y = 15, Z = 20;

    // memungkinkan untuk assign ulang ke variable tapi tidak ke konstanta
    i_var = 1;
    i_var3 = i_var2 = i_var;


    return 0;
}