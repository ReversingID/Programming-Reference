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
 * 
 * Adapter merupakan turunan dari Target dan Service sehingga dapat diinstansiasi sebagai
 * salah satu dari keduanya.
 */
class Adapter : public Target, private Service
{
public:
    // Pemanggilan request akan diteruskan ke Service
    void request() override
    {
        doRequest();
    }
};


/* *********************************** USAGE *********************************** */

int main(int argc, char* argv[])
{
    // Instansiasi "target" yang sebenarnya adalah objek Adapter.
    auto target = std::unique_ptr<Target>{new Adapter};

    // request() akan diterjemahkan menjadi pemanggilan doRequest()
    target->request();
    
    return 0;
}