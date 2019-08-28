/*
    Bridge
    Archive of Reversing.ID
    Design Pattern (Structural)

    Menggunakan composition.

Compile:
    [clang]
    $ clang++ bridge.cpp -o bridge

    [gcc]
    $ g++ bridge.cpp -o bridge

    [msvc]
    $ cl bridge.cpp

Run:
    $ bridge
*/
#include <memory>
#include <iostream>


/* *********************************** DECLARATION *********************************** */
/**
 * Abstraction (abstract)
 * 
 * Hanya menyediakan interface dari operasi yang akan diimplementasikan.
 */
class Abstraction
{
public:
    /* Virtual destructor */
    virtual ~Abstraction() { }
    
    /**
     * Contoh operasi kelas yang akan diimplementasikan oleh setiap kelas turunan
     */
    virtual void operation() = 0;
};

// ======================================================================================

/**
 * Implementation (abstract)
 * 
 * Implementasi operasi dan variasinya.
 */
class Implementation : public Abstraction 
{
public:
    virtual void operation() = 0;
    virtual ~Implementation() { }

protected:
    Implementation() { }
};

// ======================================================================================

/**
 * ConcreteImplementation (concrete)
 * 
 * Salah satu variasi yang akan mengimplementasikan operasi.
 */
class ConcreteImplementation : public Implementation 
{
public:
    void operation()
    {
        std::cout << "ConcreteImplementation operation ... " << std::endl;
    }
};

// ======================================================================================

/**
 * RefinedAbstraction (concrete)
 * 
 * Class yang digunakan dalam operasi.
 */
class RefinedAbstraction : public Abstraction
{
    std::unique_ptr<Implementation> _imp;

public:
    RefinedAbstraction (Implementation * imp) : _imp{imp}
    { }
    
    void operation()
    {
        _imp->operation();
    }
};


/* *********************************** USAGE *********************************** */

int main(int argc, char* argv[])
{
    auto imp = new ConcreteImplementation();
    auto abs = std::unique_ptr<Abstraction>{new RefinedAbstraction(imp)};

    abs->operation();

    return 0;
}