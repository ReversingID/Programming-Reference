/*
    Decorator
    Archive of Reversing.ID
    Design Pattern (Structural)

Definition:
    Menambahkan "responsibility" atau "behavior" ke objek secara dinamis melalui komponen
    yang dapat dirangkai dan dilepas.

Compile:
    [gcc]
    $ g++ decorator.cpp -o decorator

    [msvc]
    $ cl decorator.cpp

Run:
    $ decorator
*/
#include <iostream>


/* *********************************** DECLARATION *********************************** */
/**
 * Component (abstract)
 * 
 * Komponen-komponen yang akan dikomposisikan ke dalam Composite.
 */
class Component
{
public:
    /**
     * Virtual destructor.
     */
    virtual ~Component() { }
    
    virtual void operation () = 0;
};


// ======================================================================================

/**
 * ConcreteComponent (concrete)
 * 
 * Composite merupakan turunan Component yang diakses sebagai kumpulan beberapa Component.
 */
class ConcreteComponent : public Component 
{
public:
    void operation ()
    {
        std::cout << "ConcreteComponent::operation .. " << std::endl;
    }
};

// ======================================================================================

/**
 * Decorator (abstract)
 * 
 * Second level base class.
 * Memberikan behavior terhadap komponen lain.
 */
class Decorator : public Component
{
    Component * _com;

public:
    virtual ~Decorator() { }

    Decorator (Component * com)
    {
        _com = com;
    }
    
    // Delegasi operasi.
    void operation() 
    {
        _com->operation();
    }
};

// ======================================================================================

/**
 * ConcreteDecorator (concrete)
 * 
 * 
 */
class ConcreteDecorator : public Decorator 
{
public:
    ConcreteDecorator (Component * com) : Decorator(com) { }
    
    void addBehavior ()
    {
        std::cout << "ConcreteDecorator::addBehavior ... " << std::endl;
    }

    void operation ()
    {
        // Delegasikan ke base class dan tambahkan perilaku tambahan
        Decorator::operation();
        addBehavior();
    }
};


/* *********************************** USAGE *********************************** */

int main(int argc, char* argv[])
{
    // Komponen standard tanpa perilaku tambahan
    Component * com = new ConcreteComponent();

    // Komponen baru dengan perilaku tambahan
    Decorator * dec = new ConcreteDecorator(com);

    // Komponen baru dengan perilaku tambahan lain.
    Decorator * dec2 = new ConcreteDecorator(dec);

    // Bisa juga melakukan chaining
    // Decorator * dec2 = new ConcreteDecorator(new ConcreteDecorator(new Component()));

    // Melakukan operasi dari dec (yang akan mengeksekusi com)
    dec->operation(); 
    
    delete com;
    delete dec;
    delete dec2;

    return 0;
}