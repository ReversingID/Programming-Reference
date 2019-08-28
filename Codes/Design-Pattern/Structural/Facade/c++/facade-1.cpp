/*
    Facade
    Archive of Reversing.ID
    Design Pattern (Structural)


Compile:
    [clang]
    $ clang++ facade.cpp -o facade

    [gcc]
    $ g++ facade.cpp -o facade

    [msvc]
    $ cl facade.cpp

Run:
    $ facade
*/
#include <memory>
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
        std::cout << "SubSystem-1 :: operation ... " << std::endl;
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
        std::cout << "SubSystem-2 :: operation ... " << std::endl;
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
    std::unique_ptr<SubSystem1> _sub1;
    std::unique_ptr<SubSystem2> _sub2;

public:
    Facade ()
    {
        _sub1 = std::make_unique<SubSystem1>();
        _sub2 = std::make_unique<SubSystem2>();
    }

    /*
    Operasi ini membungkus dua proses yang ada sehingga dianggap sebagai 
    1 operasi tunggal.
    */
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
    auto facade = std::make_unique<Facade>();
    facade->operation();

    return 0;
}