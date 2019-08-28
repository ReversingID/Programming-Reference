/*
    Decorator
    Archive of Reversing.ID
    Design Pattern (Structural)

Compile:
    [clang]
    $ clang++ decorator.cpp -o decorator

    [gcc]
    $ g++ decorator.cpp -o decorator

    [msvc]
    $ cl decorator.cpp

Run:
    $ decorator
*/
#include <memory>
#include <iostream>


/* *********************************** DECLARATION *********************************** */

/**
 * Component (abstract)
 * 
 * Behavior akan diturunkan dari class ini.
 */
class Component
{
public:
    /* Virtual destructor. */
    virtual ~Component() { }
    
    virtual void operation () = 0;
};


// ======================================================================================

/**
 * ConcreteComponent (concrete)
 * 
 * Class utama (core).
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
    std::unique_ptr<Component> _com;

public:
    virtual ~Decorator() { }

    Decorator (Component * com)
    {
        _com = std::unique_ptr<Component>(com);
    }

    Decorator (std::unique_ptr<Component> com) : _com{std::move(com)}
    { }
    
    void operation() 
    {
        // Delegasi operasi.
        _com->operation();
    }
};

// ======================================================================================

/**
 * ConcreteDecorator (concrete)
 * 
 * Behavior konkret yang akan melakukan operasi tertentu.
 */
class ConcreteDecorator : public Decorator 
{
public:
    ConcreteDecorator (Component * com) : Decorator(com) 
    { }

    ConcreteDecorator (std::unique_ptr<Component> com) : Decorator(std::move(com))
    { }
    
    /*
    Perilaku tambahan yang akan dijalankan setelah menjalankan perilaku dari komponen awal.
    */
    void behavior ()
    {
        std::cout << "ConcreteDecorator::behavior ... " << std::endl;
    }

    void operation ()
    {
        // Delegasikan ke base class dan tambahkan perilaku tambahan
        Decorator::operation();
        behavior();
    }
};


/* *********************************** USAGE *********************************** */

int main(int argc, char* argv[])
{
    // Komponen standard tanpa perilaku tambahan
    auto com = std::make_unique<ConcreteComponent>();

    // Komponen baru dengan perilaku tambahan
    auto dec = std::make_unique<ConcreteDecorator>(std::move(com));

    // Komponen baru dengan perilaku tambahan lain.
    auto dec2 = std::make_unique<ConcreteDecorator>(std::move(dec));

    // Melakukan operasi dari dec2 (yang akan mengeksekusi dec dan com)
    std::cout << "Decorator dec2" << std::endl;
    dec2->operation(); 
    std::cout << std::endl;


    // Bisa juga melakukan chaining
    // Decorator * dec2 = new ConcreteDecorator(new ConcreteDecorator(new Component()));
    auto dec3 = 
        std::make_unique<ConcreteDecorator>(
            new ConcreteDecorator(new ConcreteComponent)
        );

    std::cout << "Decorator dec3" << std::endl;
    dec3->operation();
    std::cout << std::endl;

    return 0;
}