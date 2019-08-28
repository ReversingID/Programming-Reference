/*
    Adapter / Wrapper
    Archive of Reversing.ID
    Design Pattern (Structural)

    Menggunakan inheritance.
    Adapter merupakan turunan dari Target dan Service.
    
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
    virtual void doRequest()
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
 */
class Adapter : public Target, private Service
{
    Service * _adp;

public:
    Adapter (Service * adp)
    {
        _adp = adp;
    }

    void request()
    {
        _adp->doRequest();
    }
};


/* *********************************** USAGE *********************************** */

int main(int argc, char* argv[])
{
    // Instansiasi objek yang akan diadaptasi
    Service * Service = new Service();

    // Instansiasi wrapper yang mengadaptasi Service sebagai Target.
    Target * target = new Adapter(Service);

    // request() akan diterjemahkan menjadi pemanggilan doRequest()
    target->request();

    // Bebaskan resource
    delete target;
    delete Service;

    return 0;
}