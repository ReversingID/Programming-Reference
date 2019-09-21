/*
    Switch 
    Archive of Reversing.ID
    Programming Language (C++)

    Statement Switch untuk pencocokan majemuk.
*/

#include <iostream>

int main(int argc, char* argv[])
{
    // definisi variabel lokal
    int grade = 'B';

    switch (grade)
    {
        case 'A':
            std::cout << "Excellent" << std:: endl;
            break;
        case 'B':
        case 'C':
            std::cout << "Well done" << std:: endl;
            break;
        case 'D':
            std::cout << "You passed" << std:: endl;
            break;
        case 'F':
            std::cout << "Better try again" << std:: endl;
            break;
        default:
            std::cout << "Invalid grade" << std:: endl;
    }

    std::cout << "Your grade is : " << grade << std::endl;

    return 0;
}