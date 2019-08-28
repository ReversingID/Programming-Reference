/*
    State
    Archive of Reversing.ID
    Design Pattern (Behavioral)

    State transition berada di method handle()

Compile:
    [clang]
    $ clang++ state.cpp -o state
    
    [gcc]
    $ g++ state.cpp -o state

    [msvc]
    $ cl state.cpp

Run:
    $ state
*/
#include <memory>
#include <iostream>


/* *********************************** DECLARATION *********************************** */

class Context;

// ======================================================================================

/**
 * State (abstract)
 * 
 * Mendefinisikan interface untuk mengenkapsulasi perilaku dari state.
 */
class State
{
protected:
    Context *   _ctx;

public:
    virtual ~State() { }
    virtual bool handle() = 0;

    void setContext(Context * ctx)
    {
        _ctx = ctx;
    }
};

// ======================================================================================

/**
 * Context (concrete)
 * 
 * Memberikan interface untuk mengakses state.
 */
class Context
{
    std::shared_ptr<State>  _state;

public:
    Context (std::shared_ptr<State> state)
    {
        _state = state;
        _state->setContext(this);
    }

    void changeState(std::shared_ptr<State> state)
    {
        _state = state;
        _state->setContext(this);
    }
    
    void request()
    {
        _state->handle();
    }
};

// ======================================================================================

/**
 * ConcreteStateA (concrete)
 * 
 * Setiap turunan mengimplementasikan perilaku yang berasosiasi dengan state tertentu.
 */
class ConcreteStateA: public State
{
public:
    bool handle();
};

// ======================================================================================

/**
 * ConcreteStateB (concrete)
 * 
 * Setiap turunan mengimplementasikan perilaku yang berasosiasi dengan state tertentu.
 */
class ConcreteStateB: public State
{
public:
    bool handle();
};

// ======================================================================================

/**
 * Letakkan definisi fungsi di luar deklarasi class agar dapat mengenali class State lain.
 */
bool ConcreteStateA::handle()
{
    std::cout << "[State A] handle ..." << std::endl;
    std::cout << "Have to change to [State B]" << std::endl;

    // Transisi ke state B
    _ctx->changeState(std::make_shared<ConcreteStateB>());
    return true;
}

bool ConcreteStateB::handle() 
{
    std::cout << "[State B] handle ..." << std::endl;
    std::cout << "Have to change to [State A]" << std::endl;

    // Transisi ke state A
    _ctx->changeState(std::make_shared<ConcreteStateA>());
    return true;
}


/* *********************************** USAGE *********************************** */

int main(int argc, char* argv[])
{
    // Mendefinisikan state awal
    auto start = std::make_unique<ConcreteStateA>();

    auto ctx   = std::make_unique<Context>(std::move(start));

    ctx->request();
    ctx->request();

    return 0;
}