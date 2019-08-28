/*
    Proxy
    Archive of Reversing.ID
    Design Pattern (Structural)


Compile:
    [clang]
    $ clang++ flyweight.cpp -o flyweight

    [gcc]
    $ g++ proxy.cpp -o proxy

    [msvc]
    $ cl proxy.cpp

Run:
    $ proxy
*/
#include <memory>
#include <iostream>


/* *********************************** DECLARATION *********************************** */

/**
 * Subject (abstract)
 */
class Subject
{
public:
    /* Virtual destructor */
    virtual ~Subject() { }
    
    /**
     * Contoh operasi kelas yang akan diimplementasikan oleh setiap kelas turunan
     */
    virtual void request() = 0;
};

// ======================================================================================

/**
 * ConcreteSubject (concrete)
 */
class ConcreteSubject : public Subject 
{
public:
    virtual ~ConcreteSubject() { }
    
    void request() override
    {
        std::cout << "[ConcreteSubject] :: request" << std::endl;
    }
};

// ======================================================================================

/**
 * Proxy (concrete)
 * 
 * Class yang meneruskan request menuju subject.
 */
class Proxy : public Subject
{
    std::shared_ptr<Subject> _sub;

public:
    Proxy () { }
    Proxy (std::shared_ptr<Subject> subject) : _sub{subject}
    { }
    
    void request()
    {
        std::cout << "Proxy request ..." << std::endl;
        _sub->request();
    }
};


/* *********************************** USAGE *********************************** */

int main(int argc, char* argv[])
{
    auto sub = std::shared_ptr<Subject>{new ConcreteSubject};
    auto proxy = std::make_unique<Proxy>(sub);

    proxy->request();

    return 0;
}