/*
    Strategy
    Archive of Reversing.ID
    Design Pattern (Behavioral)

Compile:
    [clang]
    $ clang++ strategy.cpp -o strategy
    
    [gcc]
    $ g++ strategy.cpp -o strategy

    [msvc]
    $ cl strategy.cpp

Run:
    $ strategy
*/
#include <memory>
#include <iostream>


/* *********************************** DECLARATION *********************************** */

/**
 * Strategy (abstract)
 * 
 * Mendeklarasikan interface yang akan diimplementasikan class algoritma.
 */
class Strategy
{
public:
    virtual ~Strategy() { }

    virtual void execute() = 0;
};

// ======================================================================================

/**
 * ConcreteAlgorithmA (concrete)
 * 
 * Implementasikan algoritma menggunakan interface Strategy.
 */
class ConcreteAlgorithmA: public Strategy
{
public:
    void execute()
    {
        std::cout << "[Algorithm A] :: execute" << std::endl;
    }
};

// ======================================================================================

/**
 * ConcreteAlgorithmB (concrete)
 * 
 * Implementasikan algoritma menggunakan interface Strategy.
 */
class ConcreteAlgorithmB: public Strategy
{
public:
    void execute()
    {
        std::cout << "[Algorithm B] :: execute" << std::endl;
    }
};

// ======================================================================================

/**
 * Context (concrete)
 * 
 * Menyimpan reference ke objek Strategy.
 */
class Context
{
    std::shared_ptr<Strategy>   _strategy;

public:
    Context (std::shared_ptr<Strategy> strategy) : _strategy{strategy}
    { }
    
    void doAction()
    {
        _strategy->execute();
    }
};


/* *********************************** USAGE *********************************** */

int main(int argc, char* argv[])
{
    // Mendefinisikan state awal
    auto algo = std::make_unique<ConcreteAlgorithmA>();
    auto ctx  = std::make_unique<Context>(std::move(algo));

    ctx->doAction();

    return 0;
}