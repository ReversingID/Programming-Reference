/*
    Messenger
    Archive of Reversing.ID
    Design Pattern (Creational/Decorator)

Compile:
    [clang]
    $ clang++ messenger.cpp -o messenger

    [gcc]
    $ g++ messenger.cpp -o messenger

    [msvc]
    $ cl messenger.cpp

Run:
    $ messenger
*/
#include <memory>
#include <iostream>


/* *********************************** DECLARATION *********************************** */

/**
 * Core (abstract)
 */
class Interface
{
public:
    virtual ~Interface() { }

    virtual void write(std::string&) = 0;
};

// ======================================================================================

/**
 * Core (concrete)
 */
class Core : public Interface
{
public:
    void write(std::string& text) override { }
};


// ======================================================================================

/**
 * Decorator (concrete)
 */
class Decorator: public Interface
{
    std::unique_ptr<Interface> _iface;

public:
    Decorator(std::unique_ptr<Interface> iface) : _iface{std::move(iface)}
    { }

    virtual void write (std::string& text) override 
    {
        _iface->write(text);
    }
};

// ======================================================================================

/**
 * MessengerWithSalutation (concrete)
 */
class MessengerWithSalutation : public Decorator
{
    std::string _salutation;

public:
    MessengerWithSalutation(std::unique_ptr<Interface> iface, const std::string& str)
        : Decorator{std::move(iface)}, _salutation{str}
    { }

    virtual void write(std::string& text) override
    {
        text = _salutation + "\n\n" + text;
        Decorator::write(text);
    }
};


/* *********************************** USAGE *********************************** */

int main()
{
    const std::string salutation = "Greetings, ";
    std::string message1 = "This message is not decorated.";
    std::string message2 = "This message is decorated with a salutation.";

    auto messenger1 = std::make_unique<Core>();
    auto messenger2 = std::make_unique<MessengerWithSalutation>(std::make_unique<Core>(), salutation);

    messenger1->write(message1);
    std::cout << message1 << std::endl;
    std::cout << std::endl << "--------------------------------------" << std::endl << std::endl;

    messenger2->write(message2);
    std::cout << message2 << std::endl;
    std::cout << std::endl << "--------------------------------------" << std::endl << std::endl;

    return 0;
}