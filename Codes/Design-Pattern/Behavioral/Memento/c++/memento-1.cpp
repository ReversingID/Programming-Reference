/*
    Memento
    Archive of Reversing.ID
    Design Pattern (Behavioral)

    Memento sederhana tanpa Caretaker yang menyimpan history.

Compile:
    [clang]
    $ clang++ memento.cpp -o memento
    
    [gcc]
    $ g++ memento.cpp -o memento

    [msvc]
    $ cl memento.cpp

Run:
    $ memento
*/
#include <memory>
#include <iostream>


/* *********************************** DECLARATION *********************************** */

/**
 * Memento (concrete)
 * 
 * Value object bertindak sebagai snapshot.
 */
class Memento
{
    std::string     _state;

    friend class Originator;

    Memento (const std::string & state) : _state{state}
    { }

    void setState(const std::string & state)
    {
        _state = state;
    }

    std::string getState () 
    {
        return _state;
    }
};

using MementoPtr = std::shared_ptr<Memento>;

// ======================================================================================

/**
 * Originator (concrete)
 */
class Originator
{
    std::string     _state;

public:
    Originator()
    { }

    Originator (const std::string & state) : _state{state}
    { }

    // === Memento ===
    auto createMemento()
    {
        return std::shared_ptr<Memento>{new Memento(_state)};
    }

    void restoreToMemento(MementoPtr memento)
    {
        _state   = memento->getState();
    }

    // === States ===
    auto getState()
    {
        return _state;
    }

    void setState(const std::string & state)
    {
        _state = state;
    }
};

/* *********************************** USAGE *********************************** */

int main(int argc, char* argv[])
{
    auto origin = std::make_unique<Originator>();

    origin->setState("Old-State");
    std::cout << "State: " << origin->getState() << std::endl;
    std::cout << "===========================" << std::endl;

    // Buat memento dan ubah state
    auto m = origin->createMemento();

    origin->setState("New-State");
    std::cout << "State: " << origin->getState() << std::endl;
    std::cout << "===========================" << std::endl;

    // Restore state
    origin->restoreToMemento(std::move(m));
    std::cout << "State: " << origin->getState() << std::endl;
    std::cout << "===========================" << std::endl;


    return 0;
}