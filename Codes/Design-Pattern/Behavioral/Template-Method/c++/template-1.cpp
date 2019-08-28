/*
    Template Method
    Archive of Reversing.ID
    Design Pattern (Behavioral)

Compile:
    [clang]
    $ clang++ template.cpp -o template
    
    [gcc]
    $ g++ template.cpp -o template

    [msvc]
    $ cl template.cpp

Run:
    $ template
*/
#include <memory>
#include <iostream>


/* *********************************** DECLARATION *********************************** */

/**
 * AbstractClass (abstract)
 * 
 * Mendefinisikan kerangka algoritma
 */
class AbstractClass
{
    // Operasi yang umum ada
    void operation_0()
    {
        std::cout << "[AbstractClass] :: operation 0" << std::endl;
    }

protected:
    // Beberapa operasi yang spesifik dan akan diimplementasikan nanti.
    virtual void operation_1() = 0;
    virtual void operation_2() = 0;

public:
    virtual ~AbstractClass() { }

    /*
    Template method mendefinisikan bahwa suatu operasi terdiri dari beberapa langkah.
    Subclass bertugas mendefinisikan langkah konkret tersebut.
    */
    virtual void execute()
    {
        operation_1();
        operation_2();
    }
};

// ======================================================================================

/**
 * ConcreteClassA (concrete)
 * 
 * Implementasikan operasi primitif untuk menjalankan langkah spesifik dari algoritma.
 * Bisa saja ada banyak concrete class yang masing-masing mengimplementasikan 
 * keseluruhan operasi
 */
class ConcreteClassA: public AbstractClass
{
public:
    void operation_1() override
    {
        std::cout << "[ConcreteClass-A] :: operation 1" << std::endl;
    }

    void operation_2() override
    {
        std::cout << "[ConcreteClass-A] :: operation 2" << std::endl;
    }
};

// ======================================================================================

/**
 * ConcreteClassB (concrete)
 * 
 * Implementasikan operasi primitif untuk menjalankan langkah spesifik dari algoritma.
 * Bisa saja ada banyak concrete class yang masing-masing mengimplementasikan 
 * keseluruhan operasi.
 * 
 * 
 */
class ConcreteClassB: public AbstractClass
{
public:
    void operation_1() override
    {
        std::cout << "[ConcreteClass-B] :: operation 1" << std::endl;
    }

    void operation_2() override
    {
        std::cout << "[ConcreteClass-B] :: operation 2" << std::endl;
    }
};


/* *********************************** USAGE *********************************** */

int main(int argc, char* argv[])
{
    std::unique_ptr<AbstractClass> tm1 = std::make_unique<ConcreteClassA>();
    std::unique_ptr<AbstractClass> tm2 = std::make_unique<ConcreteClassB>();

    tm1->execute();
    tm2->execute();

    return 0;
}