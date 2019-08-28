/*
    State
    Archive of Reversing.ID
    Design Pattern (Behavioral)

    Tidak ada penyimpanan context di dalam State.
    Pergantian state dipicu oleh fungsi di dalam State.

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
public:
    virtual ~State() { }
    virtual bool handle(Context * ctx) = 0;

    bool changeState(Context * ctx, std::shared_ptr<State> state);
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
    Context (std::shared_ptr<State> state) : _state{state}
    { }

    void changeState(std::shared_ptr<State> state)
    {
        _state = state;
    }
    
    void request()
    {
        _state->handle(this);
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
    bool handle(Context * ctx);
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
    bool handle(Context * ctx);
};

// ======================================================================================

/**
 * Letakkan definisi fungsi di luar deklarasi class agar dapat mengenali class State lain.
 */
bool State::changeState(Context * ctx, std::shared_ptr<State> state)
{
    ctx->changeState(state);
    return true;
}

bool ConcreteStateA::handle(Context * ctx)
{
    std::cout << "[State A] handle ..." << std::endl;
    std::cout << "Have to change to [State B]" << std::endl;

    // Transisi ke state B
    return changeState(ctx, std::make_shared<ConcreteStateB>());
}

bool ConcreteStateB::handle(Context * ctx) 
{
    std::cout << "[State B] handle ..." << std::endl;
    std::cout << "Have to change to [State A]" << std::endl;

    // Transisi ke state A
    return changeState(ctx, std::make_shared<ConcreteStateA>());
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