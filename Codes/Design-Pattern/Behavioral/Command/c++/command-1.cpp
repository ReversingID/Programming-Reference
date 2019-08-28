/*
    Command
    Archive of Reversing.ID
    Design Pattern (Behavioral)

Compile:
    [clang]
    $ clang++ command.cpp -o command
    
    [gcc]
    $ g++ command.cpp -o command

    [msvc]
    $ cl command.cpp

Run:
    $ command
*/
#include <memory>
#include <iostream>


/* *********************************** DECLARATION *********************************** */

/**
 * Receiver (concrete)
 * 
 * Kelas yang akan menangani command.
 */
class Receiver
{
public:    
    void action () 
    {
        std::cout << "Receiver :: action ... " << std::endl;
    }
};

// ======================================================================================

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
 * ConcreteCommand (concrete)
 */
class ConcreteCommand : public Command
{
    std::shared_ptr<Receiver>   _rcv;

public:
    ConcreteCommand (std::shared_ptr<Receiver> rcv) : _rcv{rcv}
    { }

    void execute () override
    {
        _rcv->action();
    }
};

// ======================================================================================

/**
 * Invoker (concrete)
 * 
 * Menginisiasi eksekusi sebuah command.
 */
class Invoker
{
    std::shared_ptr<Command> _cmd;

public:
    Invoker (std::shared_ptr<Command> cmd) : _cmd{cmd}
    { }

    void invoke ()
    {
        _cmd->execute();
    }
};


/* *********************************** USAGE *********************************** */

int main(int argc, char* argv[])
{
    auto rcv = std::make_shared<Receiver>();
    auto cmd = std::make_shared<ConcreteCommand>(rcv);
    auto inv = std::make_shared<Invoker>(cmd);

    inv->invoke();

    return 0;
}