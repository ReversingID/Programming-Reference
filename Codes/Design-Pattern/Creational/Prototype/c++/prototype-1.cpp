/*
    Prototype
    Archive of Reversing.ID
    Design Pattern (Creational)

Compile:
    [clang]
    $ clang++ prototype.cpp -o prototype
    
    [gcc]
    $ g++ prototype.cpp -o prototype

    [msvc]
    $ cl prototype.cpp

Run:
    $ prototype
*/
#include <memory>


/* *********************************** DECLARATION *********************************** */
/**
 * Prototype (abstract)
 * 
 * Kelas abstrak yang mendefinisikan method clone() untuk membentuk salinan diri.
 */
class Prototype
{
public:
    virtual ~Prototype() { }
    virtual auto clone() -> std::unique_ptr<Prototype> = 0;
};

// ======================================================================================

/**
 * ConcreteProduct (concrete)
 */
class ConcreteProduct : public Prototype 
{
public:
    ConcreteProduct() { }

    // Menyalin informasi dari prototype 
    ConcreteProduct(const ConcreteProduct & cp)
    { }

    // Memberikan objek baru sebagai salinan dari prototype.
    auto clone() -> std::unique_ptr<Prototype>
    {
        return std::make_unique<ConcreteProduct>(*this);
    }
};


/* *********************************** USAGE *********************************** */
#include <iostream>

int main(int argc, char* argv[])
{
    // Buat sebuah prototype sebuah objek
    auto proto = std::make_unique<ConcreteProduct>();
    
    // Salin objek dari prototype proto
    auto clone1 = proto->clone();

    // Salin objek dari prototype proto
    auto clone2 = proto->clone();

    std::cout << proto.get() << std::endl;
    std::cout << clone1.get() << std::endl;
    std::cout << clone2.get() << std::endl;

    return 0;
}