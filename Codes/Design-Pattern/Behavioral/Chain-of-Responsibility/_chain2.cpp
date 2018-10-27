/*
    Chain of Responsibility
    Archive of Reversing.ID
    Design Pattern (Behavioral)

Definition:
    Menciptakan serangkaian handler yang akan menangani sebuah request berdasarkan
    kriteria tertentu.
    
Compile:
    [gcc]
    $ g++ chain2.cpp -o chain2

    [msvc]
    $ cl chain2.cpp

Run:
    $ chain2
*/
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
 * BaseHandler (concrete)
 * 
 * Kelas dasar yang akan diturunkan menjadi berbagai handler.
 * Kelas ini juga akan menjadi entrypoint dalam handling.
 */
class BaseHandler
{
    // Pointer yang menunjuk ke chain berikutnya.
    BaseHandler * _next;

protected:
    // Kriteria untuk menentukan apakah request diproses oleh handle ini.
    virtual bool criteria(Request & request) = 0;

    // Pemrosesan request terjadi di sini.
    virtual void process(Request & request) = 0;

public:
    BaseHandler()
    {
        _next = nullptr;
    }

    void setNext(BaseHandler * next)
    {
        _next = next;
    }

    // Menambah handler ke rangkaian handler yang sudah ada
    void add(BaseHandler * next)
    {
        if (_next)
            _next->add(next);
        else 
            _next = next;
    }

    // BaseHandle selalu mendelegasikan penanganan request ke handler berikutnya.
    virtual void handle(Request & request)
    {
        // Jika request memenuhi kriteria maka tangani
        if (criteria(request))
            process(request);
        // Jika tidak maka lempar ke handle berikutnya
        else if (_next != nullptr)
            _next->handle(request);
        // Jika tidak ditemukan handle berikutnya, maka gagalkan
    }
};

// ======================================================================================

/**
 * Handler1 (concrete)
 */
class Handler1 : public BaseHandler
{
public:
    bool criteria(Request & request)
    {
        return (request.characteristic % 3 == 1);
    }

    void process(Request & request)
    {
        std::cout 
            << "Pesan \"" << request.characteristic << "\" ditangani Handle1" 
            << std::endl;    
    }
};

// ======================================================================================

/**
 * Handler2 (concrete)
 */
class Handler2 : public BaseHandler
{
public:
    bool criteria(Request & request)
    {
        return (request.characteristic % 3 == 2);
    }

    void process(Request & request)
    {
        std::cout 
            << "Pesan \"" << request.characteristic << "\" ditangani Handle2" 
            << std::endl;    
    }
};

// ======================================================================================

/**
 * Handler3 (concrete)
 */
class Handler3 : public BaseHandler
{
public:
    bool criteria(Request & request)
    {
        return (request.characteristic % 3 == 0);
    }

    void process(Request & request)
    {
        std::cout 
            << "Pesan \"" << request.characteristic << "\" ditangani Handle3" 
            << std::endl;    
    }
};


/* *********************************** USAGE *********************************** */

int main(int argc, char* argv[])
{
    // Handle
    Handler1 one;
    Handler2 two;
    Handler3 three;

    // request
    Request  request;

    // kaitkan handler
    one.add(&two);
    one.add(&three);

    // Request dengan karakteristik 1
    request.characteristic = 1;
    one.handle(request);
    
    // Request dengan karakteristik 1
    request.characteristic = 2;
    one.handle(request);

    // Request dengan karakteristik 1
    request.characteristic = 3;
    one.handle(request);


    return 0;
}