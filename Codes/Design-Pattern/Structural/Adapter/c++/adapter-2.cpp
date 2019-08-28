/*
    Adapter / Wrapper
    Archive of Reversing.ID
    Design Pattern (Structural)
    
    Menggunakan composition.

Compile:
    [clang]
    $ clang++ adapter.cpp -o adapter

    [gcc]
    $ g++ adapter.cpp -o adapter

    [msvc]
    $ cl adapter.cpp

Run:
    $ adapter
*/
#include <memory>
#include <iostream>


/* *********************************** DECLARATION *********************************** */
/**
 * Target (concrete)
 * 
 * Interface yang diharapkan diakses.
 */
class Target
{
public:
    /* Virtual destructor */
    virtual ~Target() { }
    
    /**
     * Operasi yang akan dilakukan.
     */
    virtual void request()
    {
        std::cout << "Target::Request ... " << std::endl;
    }
};

// ======================================================================================

/**
 * Service (concrete)
 * 
 * Kelas yang menyediakan layanan.
 */
class Service 
{
public:
    void doRequest()
    {
        std::cout << "Service::doRequest ... " << std::endl;
    }
};

// ======================================================================================

/**
 * Adapter (concrete)
 * 
 * Kelas yang akan mengadaptasi / melakukan wrapping, sehingga Service dapat digunakan
 * seperti menggunakan Target.
 * 
 * Adapter merupakan diturunkan dari Target sehingga dapat digunakan selayaknya Target.
 */
class Adapter : public Target
{
    std::unique_ptr<Service> _svc;

public:
    Adapter (Service* svc)
    {
        _svc = std::unique_ptr<Service>{svc};
    }

    // Pemanggilan request akan 
    void request() override
    {
        _svc->doRequest();
    }
};


/* *********************************** USAGE *********************************** */

int main(int argc, char* argv[])
{
    // Instansiasi objek yang akan diadaptasi
    auto service = new Service();

    // Instansiasi wrapper yang mengadaptasi Adaptee sebagai Target.
    auto target  = std::unique_ptr<Target>{new Adapter(service)};

    // request() akan diterjemahkan menjadi pemanggilan doRequest()
    target->request();

    return 0;
}