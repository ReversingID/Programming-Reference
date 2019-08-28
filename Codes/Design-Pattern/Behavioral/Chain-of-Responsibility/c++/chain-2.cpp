/*
    Chain of Responsibility
    Archive of Reversing.ID
    Design Pattern (Behavioral)

    Menggunakan sebuah method criteria() sebagai filter.

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

protected:
    // Kriteria untuk menentukan apakah request diproses oleh handler ini.
    virtual bool criteria(Request & request) = 0;

    // Pemrosesan request terjadi di sini.
    virtual bool process(Request & request) = 0;

public:
    Handler() { }
    Handler(std::shared_ptr<Handler> successor) : _next{successor}
    { }
    
    // base handle selalu mendelegasikan penanganan request ke handler berikutnya
    virtual void handle(Request & request)
    {
        // Jika request memenuhi kriteria maka lakukan penanganan 
        if (criteria(request))
            process(request);
        
        // Jika tidak maka lempar ke handle berikutnya
        else if (_next != nullptr)
            _next->handle(request);
        
        // Tidak ada penanganan terjadi jika successor tidak ditemukan.
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
    
    bool criteria(Request & request) override
    {
        return (request.characteristic % 3 == 1);
    }

    bool process(Request & request) override 
    {
        std::cout << "[ConcreteHandlerA] :: handle request" << std::endl;
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
    
    bool criteria(Request & request) override
    {
        return (request.characteristic % 3 == 2);
    }

    bool process(Request & request) override 
    {
        std::cout << "[ConcreteHandlerB] :: handle request" << std::endl;
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

    bool criteria(Request & request) override
    {
        return (request.characteristic % 3 == 0);
    }

    bool process(Request & request) override 
    {
        std::cout << "[ConcreteHandlerC] :: handle request" << std::endl;
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