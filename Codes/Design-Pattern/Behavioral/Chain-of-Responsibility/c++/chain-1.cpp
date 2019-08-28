/*
    Chain of Responsibility
    Archive of Reversing.ID
    Design Pattern (Behavioral)


Compile:
    [clang]
    $ clang++ chain.cpp -o chain

    [gcc]
    $ g++ chain.cpp -o chain

    [msvc]
    $ cl chain.cpp

Run:
    $ chain

Note:
    Umumnya akan digunakan pula objek seperti Command maupun enkapsulasi
    dari sebuah request sebagai parameter dari handle(). 
*/
#include <memory>
#include <iostream>


/* *********************************** DECLARATION *********************************** */

/**
 * Request (concrete)
 * 
 * Tipe objek yang akan ditangani oleh handler.
 */
class Request 
{
public: 
    int characteristic;
};

// ======================================================================================

/**
 * Handler (concrete)
 * 
 * Interface yang mendefinisikan handle.
 */
class Handler
{
    // Menunjuk ke handler selanjutnya di chain.
    std::shared_ptr<Handler>    _next{nullptr};

public:
    Handler() { }
    Handler(std::shared_ptr<Handler> successor) : _next{successor}
    { }
    
    // base handle selalu mendelegasikan penanganan request ke handler berikutnya
    virtual void handle(Request & request)
    {
        if (_next)
            _next->handle(request);
    }

    // Menambah handler ke rangkaian handler yang sudah ada
    void add(std::shared_ptr<Handler> successor)
    {
        if (_next)
            _next->add(successor);
        else
            _next = successor;
    }

    void setSuccessor(std::shared_ptr<Handler> successor)
    {
        _next = successor;
    }
};

// ======================================================================================

/**
 * ConcreteHandlerA (concrete)
 * 
 * Variasi handler.
 */
class ConcreteHandlerA : public Handler 
{
public:
    ConcreteHandlerA() { }

    ConcreteHandlerA(std::shared_ptr<Handler> successor) : Handler(successor)
    { }
    
    // Penanganan dapat beragam.
    void handle(Request & request) override
    {
        // Periksa apakah request dapat ditangani handler ini.
        if (request.characteristic % 3 == 1)
            std::cout << "[ConcreteHandlerA] :: handle request" << std::endl;
        // Jika tidak, gunakan handle() parent untuk mendelegasikan ke handler lain
        else 
            Handler::handle(request);
    }
};

/**
 * ConcreteHandlerB (concrete)
 * 
 * Variasi handler.
 */
class ConcreteHandlerB : public Handler 
{
public:
    ConcreteHandlerB() { }

    ConcreteHandlerB(std::shared_ptr<Handler> successor) : Handler(successor)
    { }
    
    // Penanganan dapat beragam.
    void handle(Request & request) override
    {
        // Periksa apakah request dapat ditangani handler ini.
        if (request.characteristic % 3 == 2)
            std::cout << "[ConcreteHandlerB] :: handle request" << std::endl;
        // Jika tidak, gunakan handle() parent untuk mendelegasikan ke handler lain
        else 
            Handler::handle(request);
    }
};

/**
 * ConcreteHandlerC (concrete)
 * 
 * Variasi handler.
 */
class ConcreteHandlerC : public Handler 
{
public:
    ConcreteHandlerC() { }

    ConcreteHandlerC(std::shared_ptr<Handler> successor) : Handler(successor)
    { }

    // Penanganan dapat beragam.
    void handle(Request & request) override
    {
        // Periksa apakah request dapat ditangani handler ini.
        if (request.characteristic % 3 == 0)
            std::cout << "[ConcreteHandlerC] :: handle request" << std::endl;
        // Jika tidak, gunakan handle() parent untuk mendelegasikan ke handler lain
        else 
            Handler::handle(request);
    }
};


/* *********************************** USAGE *********************************** */

int main(int argc, char* argv[])
{
    // Handler berantai
    auto h1 = std::make_shared<ConcreteHandlerA>();
    auto h2 = std::make_shared<ConcreteHandlerB>(h1);
    auto h3 = std::make_shared<ConcreteHandlerC>(h2);

    // Request
    Request request;

    // Menangani handler berbeda
    for (int i = 0; i < 3; i++)
    {
        request.characteristic = i;
        h3->handle(request);
    }

    return 0;
}