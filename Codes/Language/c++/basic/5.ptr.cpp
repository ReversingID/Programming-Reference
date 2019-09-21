/*
    Pointer
    Archive of Reversing.ID
    Programming Language (C++)

    Sifat dan operasi pada Pointer dan Reference.
*/

#include <iostream>


int main(int argc, char* argv[])
{
    // deklarasi variabel normal
    int   i_var = 0;
    int   i_var2 = 10;

    // deklarasi sebuah pointer mengarah ke i_var
    int * i_ptr = &i_var;

    // deklarasi sebuah reference mengarah ke i_var
    int & i_ref = i_var;

    std::cout << "Nilai awal: " << std::endl;
    std::cout << "   i_var  = " << i_var << " (" << &i_var << ")" << std::endl;
    std::cout << "   i_var2 = " << i_var2 << " (" << &i_var2 << ")" << std::endl;
    std::cout << "   i_ptr  = " << *i_ptr << " (" << i_ptr << ")" << std::endl;
    std::cout << "   i_ref  = " << i_ref << " (" << &i_ref << ")" << std::endl;

    *i_ptr = 135;
    
    std::cout << "* i_ptr = 135 " << std::endl;
    std::cout << "   i_var  = " << i_var << " (" << &i_var << ")" << std::endl;
    std::cout << "   i_var2 = " << i_var2 << " (" << &i_var2 << ")" << std::endl;
    std::cout << "   i_ptr  = " << *i_ptr << " (" << i_ptr << ")" << std::endl;
    std::cout << "   i_ref  = " << i_ref << " (" << &i_ref << ")" << std::endl;

    i_ptr = &i_var2;
    i_var2 = 100;
    
    std::cout << "i_ptr = &i_var2 " << std::endl;
    std::cout << "   i_var  = " << i_var << " (" << &i_var << ")" << std::endl;
    std::cout << "   i_var2 = " << i_var2 << " (" << &i_var2 << ")" << std::endl;
    std::cout << "   i_ptr  = " << *i_ptr << " (" << i_ptr << ")" << std::endl;
    std::cout << "   i_ref  = " << i_ref << " (" << &i_ref << ")" << std::endl;

    return 0;
}