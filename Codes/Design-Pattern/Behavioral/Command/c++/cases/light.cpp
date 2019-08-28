/*
    Light
    Archive of Reversing.ID
    Design Pattern (Behavioral/Command)
    
Compile:
    [gcc]
    $ g++ light.cpp -o light

    [msvc]
    $ cl light.cpp

Run:
    $ light
*/
#include <memory>
#include <iostream>


/* *********************************** DECLARATION *********************************** */

/**
 * Command (abstract)
 * 
 * Kelas yang akan diturunkan untuk setiap jenis command yang dapat muncul dalam sistem.
 */
class Command
{
public:
    virtual ~Command () { }

    virtual void execute () = 0;
};

// ======================================================================================

/**
 * Light (concrete)
 * 
 * sebuah Light.
 */
class Light
{
public:    
    void on()
    {
        std::cout << "The light is on" << std::endl;
    }

    void off()
    {
        std::cout << "The light is off" << std::endl;
    }
};

// ======================================================================================

/**
 * FlipUpCommand (concrete)
 * 
 * ConcreteCommand.
 * Command untuk menyalakan (turn on) light
 */
class FlipUpCommand : public Command
{
    std::shared_ptr<Light>   light;

public:
    FlipUpCommand (std::shared_ptr<Light> light) : light{light}
    { }

    void execute () override
    {
        light->on();
    }
};

// ======================================================================================

/**
 * FlipDownCommand (concrete)
 * 
 * ConcreteCommand.
 * Command untuk mematikan (turn off) light
 */
class FlipDownCommand : public Command
{
    std::shared_ptr<Light>   light;

public:
    FlipDownCommand (std::shared_ptr<Light> light) : light{light}
    { }

    void execute ()
    {
        light->off();
    }
};

// ======================================================================================

using FlipUpCmd = std::shared_ptr<FlipUpCommand>;
using FlipDownCmd = std::shared_ptr<FlipDownCommand>;

/**
 * Switch (concrete)
 * 
 * Invoker
 * Menginisiasi eksekusi sebuah command (flip up / flip down).
 */
class Switch
{
    FlipUpCmd   _up;
    FlipDownCmd _down;

public:
    Switch (FlipUpCmd up, FlipDownCmd down) : _up{up}, _down{down}
    { }

    void flipUp()
    {
        _up->execute();
    }

    void flipDown()
    {
        _down->execute();
    }
};


/* *********************************** USAGE *********************************** */

int main(int argc, char* argv[])
{
    auto lamp = std::make_shared<Light>();

    auto up = std::make_shared<FlipUpCommand>(lamp);
    auto down = std::make_shared<FlipDownCommand>(lamp);

    auto sw = std::make_unique<Switch>(up, down);

    sw->flipUp();
    sw->flipDown();

    return 0;
}