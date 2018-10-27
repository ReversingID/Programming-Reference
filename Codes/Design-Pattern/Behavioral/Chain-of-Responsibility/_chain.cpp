/*
    Chain of Responsibility
    Archive of Reversing.ID
    Design Pattern (Behavioral)

Definition:
    Menciptakan serangkaian handler yang akan menangani sebuah request berdasarkan
    kriteria tertentu.
    
Compile:
    [gcc]
    $ g++ chain.cpp -o chain

    [msvc]
    $ cl chain.cpp

Run:
    $ chain
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
        if (_next)
            return _next->handle(request);
    }
};

// ======================================================================================

/**
 * Handler1 (concrete)
 */
class Handler1 : public BaseHandler
{
public:
    void handle(Request & request)
    {
        // Cek kondisi spesifik yang bisa ditangani oleh handler ini
        if (request.characteristic % 3 == 1)
            // Tangani pesan jika sesuai kriteria
            std::cout << "Pesan \"" << request.characteristic << "\" ditangani Handle1" 
                      << std::endl;
        // Jika tidak terpenuhi maka lemparkan ke handler berikutnya
        else 
            BaseHandler::handle(request);
    }
};

// ======================================================================================

/**
 * Handler2 (concrete)
 */
class Handler2 : public BaseHandler
{
public:
    void handle(Request & request)
    {
        // Cek kondisi spesifik yang bisa ditangani oleh handler ini
        if (request.characteristic % 3 == 2)
            // Tangani pesan jika sesuai kriteria
            std::cout << "Pesan \"" << request.characteristic << "\" ditangani Handle2" 
                      << std::endl;
        // Jika tidak terpenuhi maka lemparkan ke handler berikutnya
        else 
            BaseHandler::handle(request);
    }
};

// ======================================================================================

/**
 * Handler3 (concrete)
 */
class Handler3 : public BaseHandler
{
public:
    void handle(Request & request)
    {
        // Cek kondisi spesifik yang bisa ditangani oleh handler ini
        if (request.characteristic % 3 == 0)
            // Tangani pesan jika sesuai kriteria
            std::cout << "Pesan \"" << request.characteristic << "\" ditangani Handle3" 
                      << std::endl;
        // Jika tidak terpenuhi maka lemparkan ke handler berikutnya
        else 
            BaseHandler::handle(request);
    }
};


/* *********************************** USAGE *********************************** */

int main(int argc, char* argv[])
{
    // Handler
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