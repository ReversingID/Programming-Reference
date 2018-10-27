/*
    Adapter / Wrapper
    Archive of Reversing.ID
    Design Pattern (Structural)

Definition:
    Memberikan abstraksi terhadap kelas sehingga dapat dimanfaatkan
    kelas lain melalui penyesuaian interface yang diharapkan.
    
Compile:
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
    /**
     * Virtual destructor.
     */
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
 * Adaptee (concrete)
 * 
 * Kelas yang akan diadaptasi (wrapped)
 */
class Adaptee 
{
public:
    void doRequest()
    {
        std::cout << "Adaptee::doRequest ... " << std::endl;
    }
};

// ======================================================================================

/**
 * Adapter (concrete)
 * 
 * Kelas yang akan mengadaptasi / melakukan wrapping, sehingga Adaptee dapat digunakan
 * seperti menggunakan Target.
 */
class Adapter : public Target, private Adaptee
{
    Adaptee * _adp;

public:
    Adapter (Adaptee * adp)
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
    Adaptee * adaptee = new Adaptee();

    // Instansiasi wrapper yang mengadaptasi Adaptee sebagai Target.
    Target * adapter = new Adapter(adaptee);

    // request() akan diterjemahkan menjadi pemanggilan doRequest()
    adapter->request();

    delete adapter;
    delete adaptee;

    return 0;
}