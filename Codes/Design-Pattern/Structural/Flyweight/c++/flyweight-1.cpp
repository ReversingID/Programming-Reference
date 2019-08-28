/*
    Flyweight
    Archive of Reversing.ID
    Design Pattern (Structural)


Compile:
    [clang]
    $ clang++ flyweight.cpp -o flyweight

    [gcc]
    $ g++ flyweight.cpp -o flyweight

    [msvc]
    $ cl flyweight.cpp

Run:
    $ flyweight
*/
#include <memory>
#include <vector>
#include <iostream>


/* *********************************** DECLARATION *********************************** */

/**
 * Flyweight (concrete)
 * 
 * 
 */
class Flyweight
{
    /* state yang digunakan bersama */
    std::string _state;

public:
    Flyweight (std::string state) : _state(state) { }

    virtual ~Flyweight () { }

    virtual void operation (const std::string & state) { }

    std::string getState () const 
    {
        return _state;
    }
};

// ======================================================================================

/**
 * ConcreteFlyweight (concrete)
 * 
 * 
 */
class ConcreteFlyweight : public Flyweight
{
public:
    ConcreteFlyweight (std::string state) : Flyweight(state)
    {
        std::cout << "ConcreteFlyweight build (" << state << ")... " << std::endl;
    }

    void operation (const std::string & state)
    {
        std::cout << "ConcreteFlyweight " << getState() << " || " << state << std::endl;
    }
};

// ======================================================================================

/**
 * FlyweightFactory (concrete)
 * 
 * 
 */
class FlyweightFactory
{
    using FlyweightPtr = std::unique_ptr<Flyweight>;

    std::vector<FlyweightPtr> _fws;

public:
    auto getFlyweight (std::string key) -> FlyweightPtr&
    {
        for (auto& fly : _fws)
        {
            if (fly->getState() == key)
            {
                std::cout << "already created by users ... " << std::endl;
                return fly;
            }
        }

        _fws.push_back(std::make_unique<ConcreteFlyweight>(key));
        return _fws[_fws.size()-1];
    }
};


/* *********************************** USAGE *********************************** */

int main(int argc, char* argv[])
{
    auto fc = std::make_unique<FlyweightFactory>();
    auto& fw1 = fc->getFlyweight("hello");
    auto& fw2 = fc->getFlyweight("world");
    auto& fw3 = fc->getFlyweight("hello");

    return 0;
}