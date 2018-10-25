/*
    Prototype
    Archive of Reversing.ID
    Design Pattern (Creational)

Definition:
    
Compile:
    [gcc]
    $ g++ prototype.cpp -o prototype

    [msvc]
    $ cl prototype.cpp

Run:
    $ prototype
*/
#include <iostream>

/**
 * Definisi (Gang of Four):
 * 
 * Skenario:
 * 
 */
/* *********************************** DECLARATION *********************************** */
/**
 * Prototype (abstract)
 */
class Prototype
{
public:
    virtual ~Prototype() { }
    virtual Prototype * clone() = 0;
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
    {

    }

    // Memberikan objek baru sebagai salinan dari prototype.
    Prototype * clone()
    {
        return new ConcreteProduct(*this);
    }
};


/* *********************************** USAGE *********************************** */

int main(int argc, char* argv[])
{
    // Buat sebuah prototype sebuah objek
    Prototype * proto = new ConcreteProduct();
    
    // Salin objek dari prototype proto
    Prototype * clone1 = proto->clone();

    // Salin objek dari prototype proto
    Prototype * clone2 = proto->clone();

    delete proto;
    delete clone1;
    delete clone2;
    
    return 0;
}