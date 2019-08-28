/*
    Memento
    Archive of Reversing.ID
    Design Pattern (Behavioral)

    Mengimplementasikan Caretaker.

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
#include <vector>
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

using OriginatorPtr = std::shared_ptr<Originator>;

// ======================================================================================

/**
 * Caretaker (concrete)
 * 
 * Bertanggungjawab untuk menyimpan memento.
 */
class CareTaker
{
    std::vector<MementoPtr>  _history;
    OriginatorPtr            _origin;

public:
    CareTaker (OriginatorPtr origin) : _origin{origin}
    { }

    void save()
    {
        _history.push_back(_origin->createMemento());
    }

    void undo()
    {
        if (_history.empty())
            return;

        auto m = _history.back();
        _origin->restoreToMemento(m);

        _history.pop_back();
    }
};

/* *********************************** USAGE *********************************** */

int main(int argc, char* argv[])
{
    auto origin = std::make_shared<Originator>();
    auto caretaker = std::make_unique<CareTaker>(origin);

    origin->setState("State One");
    caretaker->save();

    origin->setState("State Two");
    caretaker->save();

    origin->setState("State Two");
    caretaker->undo();

    std::cout << "State: " << origin->getState() << std::endl;
    std::cout << "===========================" << std::endl;

    return 0;
}