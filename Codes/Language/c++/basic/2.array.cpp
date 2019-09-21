/*
    Array
    Archive of Reversing.ID
    Programming Language (C++)

    Sifat dan penggunaan array.
*/

#include <iostream>

int main(int argc, char* argv[])
{
    int    plain [10];
    double assigned [10] = { 100.0, 2.0, 3.4, 7.0, 50.0 } ;

    // assign value ke index 6 dari array "plain"
    plain [6] = 10;

    std::cout << "plain[0]    = " << plain[0] << std::endl;
    std::cout << "plain[6]    = " << plain[6] << std::endl;
    std::cout << "assigned[0] = " << assigned[0] << std::endl;
    std::cout << "assigned[6] = " << assigned[6] << std::endl;

    // assign value ke index 6 dari arrai "assigned"
    assigned[6] = 3.14;

    std::cout << "assigned[6] = " << assigned[6] << std::endl;

    return 0;
}