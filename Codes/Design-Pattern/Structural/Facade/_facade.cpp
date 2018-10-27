/*
    Facade
    Archive of Reversing.ID
    Design Pattern (Structural)

Definition:
    Mendefinisikan interface yang terpadu (unified) terhadap sekelompok interface yang
    ada di subsystem.

Compile:
    [gcc]
    $ g++ facade.cpp -o facade

    [msvc]
    $ cl facade.cpp

Run:
    $ facade
*/
#include <iostream>


/* *********************************** DECLARATION *********************************** */
/**
 * SubSystem1 (concrete)
 * 
 * 
 */
class SubSystem1
{
public:    
    void operation () 
    {
        std::cout << "SubSystem1 :: operation ... " << std::endl;
    }
};


// ======================================================================================
/**
 * SubSystem2 (concrete)
 * 
 * 
 */
class SubSystem2
{
public:    
    void operation () 
    {
        std::cout << "SubSystem2 :: operation ... " << std::endl;
    }
};

// ======================================================================================

/**
 * Facade (concrete)
 * 
 * High-level interface untuk mengoperasikan subsystem.
 */
class Facade
{
    SubSystem1 * _sub1;
    SubSystem2 * _sub2;

public:
    Facade ()
    {
        _sub1 = new SubSystem1();
        _sub2 = new SubSystem2();
    }
    
    ~ Facade ()
    {
        delete _sub1;
        delete _sub2;
    }

    void operation()
    {
        _sub1->operation();
        _sub2->operation();
    }
};


/* *********************************** USAGE *********************************** */

int main(int argc, char* argv[])
{
    // Mendeklarasikan facade yang akan menangani 2 subsystem di belakang.
    Facade * facade = new Facade();

    facade->operation();

    delete facade;

    return 0;
}